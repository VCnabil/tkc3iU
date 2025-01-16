//------------------------------------------------------------------------------
//  TITLE :          can.c
//  DESCRIPTION :    CAN bus functions.
//------------------------------------------------------------------------------

#include "project.h"

//------------------------------------------------------------------------------
// DEFINES
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// GLOBALS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// LOCAL FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
static void CANDecodeRxStd(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);
static void CANDecodeRxExt(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CANInit
//
// Initialise the CAN ports
//------------------------------------------------------------------------------
void CANInit(void)
{
	// Setup callback functions for the CANViewer
	//CANViewerInit();
 //	can_set_receive_callback(CAN_PORT1, CANViewerLogMessageReceive);
 //	can_set_receive_callback(CAN_PORT2, CANViewerLogMessageReceive);
 //	can_set_transmit_callback(CAN_PORT1, CANViewerLogMessageTransmit);
 //	can_set_transmit_callback(CAN_PORT2, CANViewerLogMessageTransmit);

    // Set speed to 250k
    can_bitrate_set(CAN_PORT1, 250000);
    // Open CAN port 1
    can_open(CAN_PORT1);

    // Set speed to 250k
    can_bitrate_set(CAN_PORT2, 250000);
    // Open CAN port 2
    can_open(CAN_PORT2);
}

//------------------------------------------------------------------------------
// CANDeInit
//
// De-initialise the CAN ports
//------------------------------------------------------------------------------
void CANDeInit(void)
{
}

//------------------------------------------------------------------------------
// CANProcessRx
//
// Process any messages received on the CAN ports
//------------------------------------------------------------------------------
void CANProcessRx(void)
{
  
    //if (SettingsGetDataMode() != CANbus_mode && SettingsGetDataMode() != CANbus_GPSI_mode)
    //{
    //    return;
    //}
    // Check both ports
    uint32_t canPort;
    for (canPort = CAN_PORT1; canPort < CAN_MAX_PORTS; canPort++)
    {
        // Check for CAN messages received
        CAN_MSG_T canMsg;
        while (can_receive_message((CAN_PORTS_T)canPort, &canMsg) == 0)
        {
            // Is it an extended CAN frame?
            if (canMsg.extend != 0)
            {
                // Yes. Decode with the extended function then
                CANDecodeRxExt((CAN_PORTS_T)canPort, &canMsg);
            }
            else
            {
                // No. Decode with the standard function then
                CANDecodeRxStd((CAN_PORTS_T)canPort, &canMsg);
            }
        }
    }
}

// Send a CAN message to the specified port
BOOL CANSend(CAN_PORTS_T canPort, uint32_t id, BOOL bExtended, uint8_t* pData, uint32_t dataLen)
{
    BOOL bRet = FALSE;
    CAN_MSG_T canMsg;

	// This function should not be used to transmit on a J1939 or NMEA2000 bus unless the device has a Source Address.
	// It can obtain a source address by doing an address claim, this is not done in this template project.
	// We recommend using CT2KLib if you are on a J1939 or NMEA2000 bus and doing anything more than listening.
	assert(FALSE && "See comment in CANSend function");

    if (dataLen <= CAN_CONTENT_MAX_LENGTH)
    {
        uint32_t i;

        // Create the CAN frame for the message
        canMsg.extend = (bExtended != FALSE) ? 1 : 0;
        canMsg.request_remote = 0;
        canMsg.id = id;
        canMsg.msg_length = (uint8_t)dataLen;
        // copy data
        for (i = 0; i < dataLen; i++)
        {
            canMsg.msg_content[i] = pData[i];
        }

        // Send message
        if (can_transmit_message(canPort, &canMsg) == 0)
        {
            // Success
            bRet = TRUE;
        }
    }

    return bRet;
}

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------

// Decode standard (11-bit) CAN messages
static void CANDecodeRxStd(CAN_PORTS_T canPort,
                           CAN_MSG_T* pMsg)
{
	// Which Id was it?
	switch (pMsg->id)
	{
	case 0x7FF:
		// Do your frame decoding here...
		break;

	default:
		break;
	}
}

// Decode extended (29-bit) CAN messages
static void CANDecodeRxExt(CAN_PORTS_T canPort,CAN_MSG_T* pMsg)
{
	// Which PGN was it?
	switch (CANIDEXT_GETPGN(pMsg->id))
	{
   
            //Indication via CCIM....................................................................
        case PGN_FF00:
            if(SettingsGetDataMode() == CANbus_GPSI_mode)J1939_FF00_VECTOR_CCIM_AIN1(canPort, pMsg);
            break;
        case PGN_FF01:
            if (SettingsGetDataMode() == CANbus_GPSI_mode)J1939_FF01_VECTOR_CCIM_AIN2(canPort, pMsg);
		    break;
        case PGN_FF02:
            if (SettingsGetDataMode() == CANbus_GPSI_mode)J1939_FF02_VECTOR_CCIM_AIN3(canPort, pMsg);
            break;
        case PGN_FF03:
            if (SettingsGetDataMode() == CANbus_GPSI_mode)J1939_FF03_VECTOR_CCIM_AIN4(canPort, pMsg);
            break;
        case PGN_FF04:
            if (SettingsGetDataMode() == CANbus_GPSI_mode)J1939_FF04_VECTOR_CCIM_AIN5(canPort, pMsg);
		    break;
        case PGN_FF05:
            if (SettingsGetDataMode() == CANbus_GPSI_mode)J1939_FF05_VECTOR_CCIM_AIN6(canPort, pMsg);
		    break;
            //Faults via RS232.......................................................................
        case PGN_FF15:    //signal fault, recieved via RS232
            if (SettingsGetStationType() == wing_station)J1939_FF15_VECTOR_RS232_SIGFAULT(canPort, pMsg);  
            break;
        case PGN_FF16:    //NFU fault, recieved via RS232
            if (SettingsGetStationType() == wing_station)J1939_FF16_VECTOR_RS232_NFUFAULT(canPort, pMsg); 
            break;
        case PGN_FF17:    //STA1 fault, recieved via RS232
			if (SettingsGetStationType() == wing_station)J1939_FF17_VECTOR_RS232_STA1FAULT(canPort, pMsg);  
            break;
        case PGN_FF18:    //STA2 fault, recieved via RS232  
            if (SettingsGetStationType() == wing_station)J1939_FF18_VECTOR_RS232_STA2FAULT(canPort, pMsg);  
			break;
        case PGN_FF19:    //STA3 fault, recieved via RS232
			if (SettingsGetStationType() == wing_station)J1939_FF19_VECTOR_RS232_STA3FAULT(canPort, pMsg);  
			break;
		case PGN_FF1A:    //CAL fault, recieved via RS232
            if (SettingsGetStationType() == wing_station)J1939_FF1A_VECTOR_RS232_CALFAULT(canPort, pMsg);  
            break;
            //Indication via RS232...................................................................
        case PGN_FF0F:
            J1939_FF0F_VECTOR_RS232_PORTNOZZLE(canPort, pMsg);
            break;
        case PGN_FF10:
		    J1939_FF10_VECTOR_RS232_STBDNOZZLE(canPort, pMsg);
            break;
        case PGN_FF11:
                J1939_FF11_VECTOR_RS232_PORTBUCKET(canPort, pMsg);
            break;
        case PGN_FF12:
			    J1939_FF12_VECTOR_RS232_STBDBUCKET(canPort, pMsg);
         break;
        case PGN_FF13:
                J1939_FF13_VECTOR_RS232_PORTTRIMTAB(canPort, pMsg);
            break;
        case PGN_FF14:
			    J1939_FF14_VECTOR_RS232_STBDTRIMTAB(canPort, pMsg);
            break;

        case PGN_FF50:
            J1939_FF50_VECTOR_ALARM_ACKNOWLEDGE(canPort, pMsg);
            break;
    
	default:
		break;
	}
}
