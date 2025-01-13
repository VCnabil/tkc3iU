//------------------------------------------------------------------------------
//  TITLE :          uart.cpp
//  DESCRIPTION :    Serial Communications functions.
//------------------------------------------------------------------------------

#include "project.h"
#include <ctype.h>
#include <NVSettings/settings.h>
 

#define IS_0183_SOF(c) (((c)=='$')||((c)=='!'))

typedef int(*DecodeFunc_t)(char* msgstring);

typedef struct
{
	const char *msgId;
	DecodeFunc_t decode;
} HandlerMapping_t;

//------------------------------------------------------------------------------
// LOCAL VARIABLES
//------------------------------------------------------------------------------

// Receive Buffer

//process example line "$PVCI,0,0,500,500,0,0,7,0,14,0,0,0,0,3,0,0,65,2*0C\r"
 
static const HandlerMapping_t m_mapping[] = {
	{ "PVCI", NMEA0183_ProcessPVCI },
};

static char m_RxMsgBuf[UART_MAX_MESSAGE_SIZE];
static uint8_t m_RxMsgIdx;

// Receive queue
static char m_MsgQueue[UART_MAX_MESSAGES][UART_MAX_MESSAGE_SIZE];
static MessageQueueInfo_t m_QueueInfo;
static UARTStats_t m_UartStats;
// Mutex to lock access to message queue
static MUTEXHANDLE_T m_queueLock;

//------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
static void _UARTProcess(uint8_t* pBuffer, uint32_t bufLen);
static bool _DecodeNextMessage(void);

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------

void UARTInit(void)
{
	memset(m_RxMsgBuf, 0, sizeof(m_RxMsgBuf));
	memset(m_MsgQueue, 0, sizeof(m_MsgQueue));
	memset(&m_QueueInfo, 0, sizeof(m_QueueInfo));
	memset(&m_UartStats, 0, sizeof(m_UartStats));
	m_RxMsgIdx = 0;
	m_QueueInfo.QueueSize = UART_MAX_MESSAGES;

	if (MutexCreate(&m_queueLock))
	{
		if (uart_open(uart_get_rs232_rs422_port(), UART_BAUDRATE_19200, UART_DATA_BITS_8, UART_STOP_BITS_1, UART_PARITY_NONE, _UARTProcess))
		{
			uart_flush(uart_get_rs232_rs422_port(), TRUE, TRUE);
		}
	}
	else
	{
		assert(FALSE && "Failed to create mutex in UARTInit");
	}
}
 
BOOL UARTSend(uint8_t *pData, uint32_t dataLen)
{
    return uart_write_buffer(uart_get_rs232_rs422_port(), pData, dataLen);
}

// Called from main loop to decode any messages received.
void UARTDecode(void)  
{

//	if (SettingsGetDataMode() != rs232_mode) return;


	// Have we received a message which hasn't been processed?
	while (_DecodeNextMessage())
	{
		// kick the watchdog so it doesn't reset the device
		watchdog_refresh();
	}
}
 
void GetUARTStats(UARTStats_t *stats)
{
	if (stats)
	{
		MutexLock(&m_queueLock);
		memcpy(stats, &m_UartStats, sizeof(UARTStats_t));
		MutexUnlock(&m_queueLock);
	}
}

void GetQueueInfo(MessageQueueInfo_t *info)
{
	if (info)
	{
		MutexLock(&m_queueLock);
		memcpy(info, &m_QueueInfo, sizeof(MessageQueueInfo_t));
		MutexUnlock(&m_queueLock);
	}
}

uint8_t* PeekMessage(peek_t peekType, int32_t queueIndex, uint8_t  *buffer, uint32_t bufferLength)
{
	uint32_t abs_idx = UINT32_MAX;
	uint8_t* retValue = nullptr;

	MutexLock(&m_queueLock);

	switch (peekType)
	{
	case PeekAbsolute:
		abs_idx = queueIndex;
		break;
	case PeekHead:
		abs_idx = (m_QueueInfo.NextReadIndex + queueIndex) % m_QueueInfo.QueueSize;
		break;
	case PeekTail:
		abs_idx = (m_QueueInfo.NextWriteIndex + m_QueueInfo.QueueSize - queueIndex) % m_QueueInfo.QueueSize;
		break;
	default:
		assert(false && "Invalid peekType");
		break;
	}

	if (abs_idx < m_QueueInfo.QueueSize)
	{
		// abs_idx was set by the switch and is less than the size of the queue
		strncpy((char *)buffer, m_MsgQueue[abs_idx], bufferLength);
		retValue = buffer;
	}

	MutexUnlock(&m_queueLock);
	return retValue;
}

//------------------------------------------------------------------------------
// PRIVATE FUNCTIONS
//------------------------------------------------------------------------------
static bool _DecodeNextMessage(void)
{
	bool processed = false;

	MutexLock(&m_queueLock);

	if (m_QueueInfo.NextReadIndex != m_QueueInfo.NextWriteIndex)
	{
		processed = true;
		watchdog_refresh();

		if (strlen(m_MsgQueue[m_QueueInfo.NextReadIndex]) > 6)
		{
			if (IS_0183_SOF(m_MsgQueue[m_QueueInfo.NextReadIndex][0]))  // '$' or '!'
			{
				if (m_MsgQueue[m_QueueInfo.NextReadIndex][1] != m_MsgQueue[m_QueueInfo.NextReadIndex][0]) //make sure we are comparing from index 1 which is P  not $
				{
					for (uint32_t mappingIndex = 0; mappingIndex < (sizeof(m_mapping) / sizeof(m_mapping[0])); mappingIndex++)
					{
						if (strncmp(&m_MsgQueue[m_QueueInfo.NextReadIndex][1], m_mapping[mappingIndex].msgId, strlen(m_mapping[mappingIndex].msgId)) == 0)
						{
							gPVCICallCount++;
							m_mapping[mappingIndex].decode(m_MsgQueue[m_QueueInfo.NextReadIndex]);
						}
					}
				}
			}
		}
		// Advance the read index to the next message in the queue
		m_QueueInfo.NextReadIndex = (m_QueueInfo.NextReadIndex + 1) % UART_MAX_MESSAGES;
	}

	MutexUnlock(&m_queueLock);

	return processed;
}

static bool _DecodeNextMessageWithDebug(void)
{
	bool processed = false;
	MutexLock(&m_queueLock);

	if (m_QueueInfo.NextReadIndex != m_QueueInfo.NextWriteIndex)
	{
		processed = true;
		watchdog_refresh();

		// Set debug message for received message
		SetDebugMessage("Received: %s", m_MsgQueue[m_QueueInfo.NextReadIndex]);

		if (strlen(m_MsgQueue[m_QueueInfo.NextReadIndex]) > 6)
		{
			if (IS_0183_SOF(m_MsgQueue[m_QueueInfo.NextReadIndex][0]))  // '$' or '!'
			{
				if (m_MsgQueue[m_QueueInfo.NextReadIndex][1] != m_MsgQueue[m_QueueInfo.NextReadIndex][0])
				{
					for (uint32_t mappingIndex = 0; mappingIndex < (sizeof(m_mapping) / sizeof(m_mapping[0])); mappingIndex++)
					{
						if (strncmp(&m_MsgQueue[m_QueueInfo.NextReadIndex][1], m_mapping[mappingIndex].msgId, strlen(m_mapping[mappingIndex].msgId)) == 0)
						{
							gPVCICallCount++;
							SetDebugMessage("Match found: %s", m_mapping[mappingIndex].msgId);
							m_mapping[mappingIndex].decode(m_MsgQueue[m_QueueInfo.NextReadIndex]);
						}
						else
						{
							SetDebugMessage("No match: %s", m_MsgQueue[m_QueueInfo.NextReadIndex]);
						}
					}
				}
				else
				{
					SetDebugMessage("Invalid SOF: %c", m_MsgQueue[m_QueueInfo.NextReadIndex][0]);
				}
			}
		}
		// Advance the read index to the next message in the queue
		m_QueueInfo.NextReadIndex = (m_QueueInfo.NextReadIndex + 1) % UART_MAX_MESSAGES;
	}
	else
	{
		SetDebugMessage("No new messages in queue.");
	}

	MutexUnlock(&m_queueLock);
	return processed;
}
 

static void _UARTProcess(uint8_t* pBuffer, uint32_t bufLen)
{
	uint32_t rxIdx = 0;
	uint8_t nextChar;
	uint32_t& queueSize = m_QueueInfo.QueueSize;
	uint32_t& nextReadIdx = m_QueueInfo.NextReadIndex;
	uint32_t& nextWriteIdx = m_QueueInfo.NextWriteIndex;
	while ((m_RxMsgIdx < UART_MAX_MESSAGE_SIZE) && (rxIdx < bufLen))
	{
		nextChar = pBuffer[rxIdx++];
		if ((nextChar == 0x0D) | (nextChar == 0x0A))
		{
			m_RxMsgBuf[m_RxMsgIdx++] = '\0';
			MutexLock(&m_queueLock);
			if ((nextWriteIdx + 1) == nextReadIdx)
			{
				nextReadIdx = (nextReadIdx + 1) % queueSize;
			}
			strcpy(m_MsgQueue[nextWriteIdx], m_RxMsgBuf);
			nextWriteIdx = (nextWriteIdx + 1) % queueSize;
			m_RxMsgIdx = 0;
			MutexUnlock(&m_queueLock);
		}
		else if ((m_RxMsgIdx != 0) || !isspace(nextChar))
		{
			m_RxMsgBuf[m_RxMsgIdx++] = nextChar;
		}
		if (m_RxMsgIdx == sizeof(m_RxMsgBuf))
		{
			m_RxMsgIdx = 0;
		}
	}
}

 