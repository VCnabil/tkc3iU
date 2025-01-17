//------------------------------------------------------------------------------
//  TITLE :- Main parameter database - database.c
//  AUTHOR :
//  DATE :
//
//  DESCRIPTION :- Main database for all the parameters used in the system.
//
//------------------------------------------------------------------------------
#include <math.h>
#include "syslib.h"
#include "Database/database.h"
#include "CAN/can.h"

#include "UI/screens.h"
#include "UI/ttfonts.h"

#include <assert.h>
#include <vector>
#include <algorithm>
//------------------------------------------------------------------------------
// Local Enums and Types
//------------------------------------------------------------------------------

#define DBTIMER_MILLISECONDS	500

// Unit types for the initial database load
#define DATABASE_DESCRIPTION_MAX_LENGTH	50
typedef struct
{
    DBUNITS_T			Units;
	char				Description[DATABASE_DESCRIPTION_MAX_LENGTH];
    DATABASEINDEX_T		DatabaseItemCheck;
	std::vector<uint8_t>	DisplayedPrecision;
} DB_INFO_TABLE_T;

static uint32_t m_DatabaseInitUptime_ms = 0;

// Storage for all the database elements
static DBELEMENT_T		m_DBElements[DATABASEINDEX_MAX][DB_INSTANCE_INVALID];

// Mutex to protect against concurrent access from different threads for the above vars
static MUTEXHANDLE_T m_mutexHandle;
// The uptime when the timer process function was last called
static uint32_t m_timerFunctionLastUptime;

// Database units for each element. Only used in init
static DB_INFO_TABLE_T m_DBINFO[] =
{
	//NEW VECTOR DATABASE PARAMETERS
 

	//PARAMETERS FOR VECTOR DATABASE
	{ DBUNITS_NONE, "Vector Port Nozzle", db_VECTOR_port_nozzle, { 0 }},
	{ DBUNITS_NONE, "Vector Stbd Nozzle", db_VECTOR_stbd_nozzle, { 0 }},
	{ DBUNITS_NONE, "Vector Port Bucket", db_VECTOR_port_bucket, { 0 }},
	{ DBUNITS_NONE, "Vector Stbd Bucket", db_VECTOR_stbd_bucket, { 0 }},
	{ DBUNITS_NONE, "Vector Port Trimtab", db_VECTOR_port_trimtab, { 0 }},
	{ DBUNITS_NONE, "Vector Stbd Trimtab", db_VECTOR_stbd_trimtab, { 0 }},
	{ DBUNITS_NONE, "Vector Signal Fault Error", db_VECTOR_signal_fault_error, { 0 }},
	{ DBUNITS_NONE, "Vector NFU Fault Error", db_VECTOR_nfu_fault_error, { 0 }},
	{ DBUNITS_NONE, "Vector STA1 Fault Error", db_VECTOR_STA1_fault_error, { 0 }},
	{ DBUNITS_NONE, "Vector STA2 Fault Error", db_VECTOR_STA2_fault_error, { 0 }},
	{ DBUNITS_NONE, "Vector STA3 Fault Error", db_VECTOR_STA3_fault_error, { 0 }},
	{ DBUNITS_NONE, "Vector Cal Fault Error", db_VECTOR_cal_fault_error, { 0 }},
	{ DBUNITS_NONE, "Vector Interlock Fault Error", db_VECTOR_interlock_fault_error, { 0 }},
	{ DBUNITS_NONE, "Vector I14 INDICConfig", db_VECTOR_I14_INDICConfig, { 0 }},
	{ DBUNITS_NONE, "Vector I15 doEnableRS232", db_VECTOR_I15_doEnableRS232, { 0 }},
	{ DBUNITS_NONE, "Vector I16 autocalSTATUS", db_VECTOR_I16_autocalSTATUS, { 0 }},
	{ DBUNITS_NONE, "Vector VCICAN Fault Error", db_VECTOR_VCICAN_fault_error, { 0 }},
	{ DBUNITS_NONE, "Vector VCIstatus", db_VECTOR_VCIstatus, { 0 }},

	 
	//PARAMETERS FOR CCIM DATA
	{ DBUNITS_NONE, "Vector CCIM AIN1", db_VECTOR_CCIM_AIN1, { 0 }},
	{ DBUNITS_NONE, "Vector CCIM AIN2", db_VECTOR_CCIM_AIN2, { 0 }},
	{ DBUNITS_NONE, "Vector CCIM AIN3", db_VECTOR_CCIM_AIN3, { 0 }},
	{ DBUNITS_NONE, "Vector CCIM AIN4", db_VECTOR_CCIM_AIN4, { 0 }},
	{ DBUNITS_NONE, "Vector CCIM AIN5", db_VECTOR_CCIM_AIN5, { 0 }},
	{ DBUNITS_NONE, "Vector CCIM AIN6", db_VECTOR_CCIM_AIN6, { 0 }},

};

// none of these thread lock, locking is handled by external functions
static void _DataBase_ProcessTimer(void* pUserData = nullptr);
static void _Database_InitValues(void);
static void _DataBase_ValidateDBINFO(void);

void DataBase_Init(void)
{
	// Setup Mutex
	MutexCreate(&m_mutexHandle);

	_DataBase_ValidateDBINFO();
	
	_Database_InitValues();
	void* userData = (void*)m_DBElements;

	// Register with the Timer System for the timer process callback
	m_timerFunctionLastUptime = get_uptime_milliseconds();
	timer_register(_DataBase_ProcessTimer, nullptr, DBTIMER_MILLISECONDS, DBTIMER_MILLISECONDS);

	// Register with the MMI system for the "once per loop" Callbacks
	m_DatabaseInitUptime_ms = get_uptime_milliseconds();
}

BOOL DataBase_IsItemValid(int DataBaseIndex, int InstanceIndex)
{
    BOOL IsValid = FALSE;
	DBELEMENT_T DBElement;
	// This is thread safe as it uses the public functions which are thread safe
    if ((DataBaseIndex < DATABASEINDEX_MAX) && (InstanceIndex < DB_INSTANCE_INVALID))
    {
		DataBase_Get(&DBElement, DataBaseIndex, InstanceIndex);

        if (DBElement.Timer > 0)
        {
            IsValid = TRUE;
        }
    }
	else
	{
		assert(FALSE);
	}

    return IsValid;
}

BOOL DataBase_Get(DBELEMENT_T * p_DB_Element, int DataBaseIndex, int InstanceIndex)
{
    BOOL bRet = FALSE;

    if ((DataBaseIndex < DATABASEINDEX_MAX) && (InstanceIndex < DB_INSTANCE_INVALID))
    {
        {// Thread safe
			MutexLock(&m_mutexHandle);
			{
				memcpy(p_DB_Element,&m_DBElements[DataBaseIndex][InstanceIndex],sizeof(DBELEMENT_T));
			}
			MutexUnlock(&m_mutexHandle);
		}// Thread safe
        bRet = TRUE;
    }
    else
    {
        assert(FALSE);
    }

    return bRet;
}

static BOOL _Database_IsSourceValid(int DataBaseIndex, int InstanceIndex, DBSOURCE_T DBSource, CAN_PORTS_T canPort, uint8_t sourceAddress, uint8_t nmeaInstanceOrSequenceID)
{
    BOOL isValid = TRUE;

    return isValid;
}

static BOOL _Database_Set_Individual(int databaseRow, 
									 int databaseColumn, 
									 const DBVAR_T* pData, 
									 DBVARTYPE_T pData_DataType,
									 DBSOURCE_T DBSource, 
									 CAN_PORTS_T canPort, 
									 uint8_t sourceAddress,
									 uint8_t nmeaInstanceOrSequenceID)
{
	BOOL IsItemLoaded = FALSE;

	if ((databaseRow < DATABASEINDEX_MAX) && (databaseColumn < DB_INSTANCE_INVALID) && (pData != 0))
	{
		// Check item is allowed to be set by the source
		if (_Database_IsSourceValid(databaseRow, databaseColumn, DBSource, canPort, sourceAddress, nmeaInstanceOrSequenceID) != FALSE)
		{
			DBELEMENT_T* pElement;

			{// Thread safe
				MutexLock(&m_mutexHandle);
				{
					pElement = &m_DBElements[databaseRow][databaseColumn];

					pElement->PreviousMessageRxTime = pElement->MessageRxTime;
					pElement->MessageRxTime = get_uptime_milliseconds();

					pElement->OwnerSource = DBSource;

					pElement->nmeaInstance = nmeaInstanceOrSequenceID;
					pElement->canPort = canPort;
					pElement->sourceAddress = sourceAddress;

					pElement->PreviousData = pElement->Data;
					pElement->Data = *pData;

					// Timer needs to be updated AFTER the data as its used to catch a "new write" and skip the filtering if thats the case.
					pElement->Timer = pElement->TimerDefault;					

					pElement->DataType = pData_DataType;
					pElement->DatabaseIndex = databaseRow;
				}
				MutexUnlock(&m_mutexHandle);
			}// Thread safe

			//nabil 1-17-2025
			  // Global flag updates based on the database row
			switch (databaseRow)
			{
				case db_VECTOR_STA1_fault_error:
					Decode_STA1Fault();
					break;
				case db_VECTOR_STA2_fault_error:
					Decode_STA2Fault();
					break;
				case db_VECTOR_STA3_fault_error:
					Decode_STA3Fault();
					break;
				case db_VECTOR_nfu_fault_error:
					Decode_NfuFault();
					break;
				case db_VECTOR_signal_fault_error:
					Decode_SignalFault();
					break;
				case db_VECTOR_cal_fault_error:
					Decode_CalFault();
					break;
					// Add more cases as needed for other fault-related rows
				default:
					break;
			}
			// Succeeded
			IsItemLoaded = TRUE;
		}
	}
	else
	{
		assert(FALSE);
	}

	return IsItemLoaded;
}
static BOOL _Database_Set(int databaseRow,
	const DBVAR_T* pData,
	DBVARTYPE_T pData_DataType,
	DBSOURCE_T DBSource,
	CAN_PORTS_T canPort,
	uint8_t sourceAddress,
	uint8_t nmeaInstanceOrSequenceID)
{
	BOOL returnValue = FALSE;
	uint32_t numberOfEngines = DB_INSTANCE_INVALID;
	if (numberOfEngines >= 1)
	{
		if (_Database_Set_Individual(databaseRow, 0, pData, pData_DataType, DBSource, canPort, sourceAddress, nmeaInstanceOrSequenceID))
		{
			returnValue = TRUE;
		}
	}
	if (numberOfEngines >= 2)
	{
		if (_Database_Set_Individual(databaseRow, 1, pData, pData_DataType, DBSource, canPort, sourceAddress, nmeaInstanceOrSequenceID))
		{
			returnValue = TRUE;
		}
	}
	if (numberOfEngines >= 3)
	{
		if (_Database_Set_Individual(databaseRow, 2, pData, pData_DataType, DBSource, canPort, sourceAddress, nmeaInstanceOrSequenceID))
		{
			returnValue = TRUE;
		}
	}
	if (numberOfEngines >= 4)
	{
		if (_Database_Set_Individual(databaseRow, 3, pData, pData_DataType, DBSource, canPort, sourceAddress, nmeaInstanceOrSequenceID))
		{
			returnValue = TRUE;
		}
	}
	return returnValue;
}
BOOL Database_Set_CAN(int DataBaseIndex, const DBVAR_T* pData, DBVARTYPE_T DataType, CAN_PORTS_T canPort, uint8_t nmeaInstanceOrSequenceID, uint8_t sourceAddress)
{
	return _Database_Set(DataBaseIndex, pData, DataType, DBSOURCE_CAN, canPort, sourceAddress, nmeaInstanceOrSequenceID);
}
BOOL Database_Set_NMEA0183(int DataBaseIndex, const DBVAR_T* pData, DBVARTYPE_T DataType, uint8_t engineIndex)
{
	DBSOURCE_T DBSource = DBSOURCE_NMEA0183;
	CAN_PORTS_T canPort = (CAN_PORTS_T)2;
	uint8_t sourceAddress = 255;
	uint8_t nmeaInstanceOrSequenceID = 255;
	return _Database_Set_Individual(DataBaseIndex, engineIndex, pData, DataType, DBSource, canPort, sourceAddress, nmeaInstanceOrSequenceID);
}



BOOL Database_Set_Conditional(int dbIndex,const DBVAR_T* pData,DBVARTYPE_T dataType,DBSOURCE_T source)
{
	if (pData == NULL || dbIndex < 0 || dbIndex >= DATABASEINDEX_MAX)
	{
		return FALSE; // Invalid input
	}

	if (source == DBSOURCE_CAN || source == DBSOURCE_GPSI)
	{
		if (SettingsGetDataMode() != CANbus_mode && SettingsGetDataMode() != CANbus_GPSI_mode)
		{
			return FALSE; // do nothing
		}
	}
	else if (source == DBSOURCE_NMEA0183)
	{
		if (SettingsGetDataMode() != rs232_mode)
		{
			return FALSE; // do nothing
		}
	}
	// Perform the database update
	BOOL bRet = _Database_Set(dbIndex,pData,dataType,source,
		(CAN_PORTS_T)0, // dummy canPort
		255,            // dummy sourceAddress
		255             // dummy nmeaInstanceOrSequenceID
	);



	return bRet;
}




float DataBase_GetDataFromElementAsFloat(DBELEMENT_T* Element)
{
	float ReturnValue = 0.0f;
	float RealValue = 0.0f;
	switch (Element->DataType)
	{
	case DBVARTYPE_UNSIGNED_INT:
		RealValue = (float)Element->Data.ui;
		break;
	case DBVARTYPE_INT:
		RealValue = (float)Element->Data.i;
		break;
	case DBVARTYPE_UNSIGNED_LONG:
		RealValue = (float)Element->Data.ulg;
		break;
	case DBVARTYPE_LONG:
		RealValue = (float)Element->Data.lg;
		break;
	case DBVARTYPE_FLOAT:
		RealValue = (float)Element->Data.flt;
		break;
	case DBVARTYPE_UNSIGNED_CHAR_ARRAY_FOUR_ELEMENT:
	case DBVARTYPE_POINTER:
	default:
		assert("Bad Type" && FALSE);
		break;
	}
	switch (Element->DatabaseIndex)
	{
	case DATABASEINDEX_MAX:
	default:
		ReturnValue = RealValue;
		break;
	}
	return ReturnValue;
}
BOOL Database_GetIndexFromString(const char* pString, uint32_t* pDBIndex)
{
	BOOL isStringValid = FALSE;
	uint32_t LoopIndex = 0;
	assert(pString && pDBIndex);
	MutexLock(&m_mutexHandle);
	for (LoopIndex = 0; LoopIndex < DATABASEINDEX_MAX; LoopIndex++)
	{
		if (strcmp(pString, m_DBINFO[LoopIndex].Description) == 0)
		{
			*pDBIndex = LoopIndex;
			isStringValid = TRUE;
			break;
		}
	}
	MutexUnlock(&m_mutexHandle);
	return isStringValid;
}
int Database_GetItemDescription(char* destination, size_t destinationSize, int DataBaseIndex)
{
	if (DataBaseIndex < DATABASEINDEX_MAX)
	{
		MutexLock(&m_mutexHandle);
		int retValue = snprintf(destination, destinationSize, "%s", m_DBINFO[DataBaseIndex].Description);
		MutexUnlock(&m_mutexHandle);
		return retValue;
	}
	else
	{
		return -1;
	}
}
void Database_SetItemDescription(int DataBaseIndex, const char* pDescription, uint32_t descriptionLength)
{
	if (DataBaseIndex < DATABASEINDEX_MAX)
	{
		MutexLock(&m_mutexHandle);
		snprintf(m_DBINFO[DataBaseIndex].Description, sizeof(m_DBINFO[DataBaseIndex].Description), "%s", pDescription);
		MutexUnlock(&m_mutexHandle);
	}
}
DBUNITS_T DatabaseGetUnitType(uint32_t DBIndex)
{
	DBUNITS_T returnValue = DBUNITS_END;
	if (DBIndex < DATABASEINDEX_MAX)
	{
		returnValue = m_DBINFO[DBIndex].Units;
	}
	return returnValue;
}
static void _DataBase_ProcessTimer(void* pUserData)
{
	(void)pUserData;
	int DBIndex = 0;
	int InstanceIndex = 0;
	uint32_t currentUptime = get_uptime_milliseconds();
	uint32_t timerDifference = currentUptime - m_timerFunctionLastUptime;
	m_timerFunctionLastUptime = currentUptime;
	MutexLock(&m_mutexHandle);
	for (DBIndex = 0; DBIndex < DATABASEINDEX_MAX; DBIndex++)
	{
		for (InstanceIndex = 0; InstanceIndex < DB_INSTANCE_INVALID; InstanceIndex++)
		{
			DBELEMENT_T* pElement;
			pElement = &m_DBElements[DBIndex][InstanceIndex];
			if (pElement->Timer != UINT32_MAX)
			{
				if (pElement->Timer > 0)
				{
					pElement->Timer -= std::min(pElement->Timer, timerDifference);
				}
				if (pElement->Timer == 0)
				{
					pElement->OwnerSource = DBSOURCE_NONE;
				}
			}
		}
	}
	MutexUnlock(&m_mutexHandle);
}
static void _Database_InitValues(void)
{
	uint32_t DBIndex = 0;
	uint32_t InstanceIndex = 0;
	{
		MutexLock(&m_mutexHandle);
		{
			for (DBIndex = 0; DBIndex < DATABASEINDEX_MAX; DBIndex++)
			{
				for (InstanceIndex = 0; InstanceIndex < DB_INSTANCE_INVALID; InstanceIndex++)
				{
					DBELEMENT_T* pElement = &m_DBElements[DBIndex][InstanceIndex];
					pElement->Data.flt = 0;
					pElement->PreviousData.flt = 0;
					pElement->DataType = DBVARTYPE_FLOAT;
					pElement->OwnerSource = DBSOURCE_NONE;
					pElement->TimerDefault = 6000;
					pElement->Timer = 0;
					pElement->UnitType = m_DBINFO[DBIndex].Units;
					pElement->MessageRxTime = 0;
				}
			}
			for (InstanceIndex = 0; InstanceIndex < DB_INSTANCE_INVALID; InstanceIndex++)
			{
			}
			m_DBElements[db_VECTOR_port_nozzle][0].Data.ui = 11;
			m_DBElements[db_VECTOR_stbd_nozzle][0].Data.ui = 22;
			m_DBElements[db_VECTOR_port_bucket][0].Data.ui = 33;
			m_DBElements[db_VECTOR_stbd_bucket][0].Data.ui = 44;
			m_DBElements[db_VECTOR_port_trimtab][0].Data.ui = 55;
			m_DBElements[db_VECTOR_stbd_trimtab][0].Data.ui = 66;
			m_DBElements[db_VECTOR_signal_fault_error][0].Data.ui = 77;
			m_DBElements[db_VECTOR_nfu_fault_error][0].Data.ui = 88;
			m_DBElements[db_VECTOR_STA1_fault_error][0].Data.ui = 99;
			m_DBElements[db_VECTOR_STA2_fault_error][0].Data.ui = 100;
			m_DBElements[db_VECTOR_STA3_fault_error][0].Data.ui = 101;
			m_DBElements[db_VECTOR_cal_fault_error][0].Data.ui = 102;
			m_DBElements[db_VECTOR_interlock_fault_error][0].Data.ui = 103;
			m_DBElements[db_VECTOR_I14_INDICConfig][0].Data.ui = 104;
			m_DBElements[db_VECTOR_I15_doEnableRS232][0].Data.ui = 105;
			m_DBElements[db_VECTOR_I16_autocalSTATUS][0].Data.ui = 106;
			m_DBElements[db_VECTOR_VCICAN_fault_error][0].Data.ui = 107;
			m_DBElements[db_VECTOR_VCIstatus][0].Data.ui = 108;
			m_DBElements[db_VECTOR_CCIM_AIN1][0].Data.ui = 109;
			m_DBElements[db_VECTOR_CCIM_AIN2][0].Data.ui = 110;
			m_DBElements[db_VECTOR_CCIM_AIN3][0].Data.ui = 111;
			m_DBElements[db_VECTOR_CCIM_AIN4][0].Data.ui = 112;
			m_DBElements[db_VECTOR_CCIM_AIN5][0].Data.ui = 113;
			m_DBElements[db_VECTOR_CCIM_AIN6][0].Data.ui = 114;


		}
		MutexUnlock(&m_mutexHandle);
	}
}
static void _DataBase_ValidateDBINFO(void)
{
	uint32_t DBIndex = 0;
	uint32_t DBINFO_Size = 0;
	DBINFO_Size = sizeof(m_DBINFO) / sizeof(DB_INFO_TABLE_T);
	if (DBINFO_Size != DATABASEINDEX_MAX)
	{
		assert(FALSE);
	}
	for (DBIndex = 0; DBIndex < DATABASEINDEX_MAX; DBIndex++)
	{
		if (m_DBINFO[DBIndex].DatabaseItemCheck != (int32_t)DBIndex)
		{
			assert(FALSE);
		}
	}
}
 
bool Database_Get_CurrentValue(DATABASEINDEX_T dbIndex, uint32_t* pValue)
{
	DBELEMENT_T DBElement;
	if (DataBase_Get(&DBElement, dbIndex, 0))
	{
		*pValue = DBElement.Data.ui;
		return TRUE;
	}
	return FALSE;
}



BOOL IsPortNozzleStale(void)
{
	BOOL isStale = FALSE;
	MutexLock(&m_mutexHandle);
	{
		DBELEMENT_T* pElement = &m_DBElements[db_VECTOR_port_nozzle][0];
		if (pElement->Timer == 0 && pElement->OwnerSource == DBSOURCE_NONE)
		{
			isStale = TRUE;
		}
		SetDebugMessage("IsPortNozzleStale: Timer=%u, OwnerSource=%d, Stale=%s",
pElement->Timer, pElement->OwnerSource, isStale ? "YES" : "NO");

	}
	MutexUnlock(&m_mutexHandle);
	return isStale;
}

