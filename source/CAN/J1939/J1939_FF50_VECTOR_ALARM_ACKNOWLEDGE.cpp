#include "project.h"
#include "VCinc.h"
/*
void vDECODE_PGN_FF50_VECTOR_ALARM( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{

    UInt16 uiByte1 = 0;
    UInt16 uiByte2 = 0;
    UInt16 uiByte3 = 0;

    No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    No_or_Bad_CAN_Data_CentralAlarmSys = 0;  //reset Central Alarm System CAN data link fault timeout


    // extract data (stored bitwise)
    uiByte1 = ( UInt16 )( rx_tail->data[DBYTE1] );
    uiByte2 = ( UInt16 )( rx_tail->data[DBYTE2] );
    uiByte3 = ( UInt16 )( rx_tail->data[DBYTE3] );

    // Alarms
    setFaultFlag( GETBIT( uiByte1, 0 ), &Central_Alarm_01 );
    setFaultFlag( GETBIT( uiByte1, 1 ), &Central_Alarm_02 );
    setFaultFlag( GETBIT( uiByte1, 2 ), &Central_Alarm_03 );
    setFaultFlag( GETBIT( uiByte1, 3 ), &Central_Alarm_04 );
    setFaultFlag( GETBIT( uiByte1, 4 ), &Central_Alarm_05 );
    setFaultFlag( GETBIT( uiByte1, 5 ), &Central_Alarm_06 );
    setFaultFlag( GETBIT( uiByte1, 6 ), &Central_Alarm_07 );
    setFaultFlag( GETBIT( uiByte1, 7 ), &Central_Alarm_08 );


    setFaultFlag( GETBIT( uiByte2, 0 ), &Central_Alarm_09 );
    setFaultFlag( GETBIT( uiByte2, 1 ), &Central_Alarm_10 );
    setFaultFlag( GETBIT( uiByte2, 2 ), &Central_Alarm_11 );
    setFaultFlag( GETBIT( uiByte2, 3 ), &Central_Alarm_12 );
    setFaultFlag( GETBIT( uiByte2, 4 ), &Central_Alarm_13 );
    setFaultFlag( GETBIT( uiByte2, 5 ), &Central_Alarm_14 );
    setFaultFlag( GETBIT( uiByte2, 6 ), &Central_Alarm_15 );
    setFaultFlag( GETBIT( uiByte2, 7 ), &Central_Alarm_16 );

    setFaultFlag( GETBIT( uiByte3, 0 ), &Central_Alarm_17 );

   

}
*/
void J1939_FF50_VECTOR_ALARM_ACKNOWLEDGE(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    
    uint32_t uiByte1 = 0;
	uint32_t uiByte2 = 0;
	uint32_t uiByte3 = 0;

	No_or_Bad_CAN_Data = 0;
	No_or_Bad_CAN_Data_CentralAlarmSys = 0;

	if (pMsg->msg_length < 3)
	{
	SetDebugMessage("FF50 VECTOR_ALARM_ACKNOWLEDGE: Not enough data. Bytes received: %u", pMsg->msg_length);
//	return;
	}
	uiByte1 = static_cast<uint32_t>(pMsg->msg_content[1]);
	uiByte2 = static_cast<uint32_t>(pMsg->msg_content[2]);
	uiByte3 = static_cast<uint32_t>(pMsg->msg_content[3]);

	// Alarms
	setFaultFlag(GETBIT(uiByte1, 0), &Central_Alarm_01);
	setFaultFlag(GETBIT(uiByte1, 1), &Central_Alarm_02);
	setFaultFlag(GETBIT(uiByte1, 2), &Central_Alarm_03);
	setFaultFlag(GETBIT(uiByte1, 3), &Central_Alarm_04);
	setFaultFlag(GETBIT(uiByte1, 4), &Central_Alarm_05);
	setFaultFlag(GETBIT(uiByte1, 5), &Central_Alarm_06);
	setFaultFlag(GETBIT(uiByte1, 6), &Central_Alarm_07);
	setFaultFlag(GETBIT(uiByte1, 7), &Central_Alarm_08);

	setFaultFlag(GETBIT(uiByte2, 0), &Central_Alarm_09);
	setFaultFlag(GETBIT(uiByte2, 1), &Central_Alarm_10);
	setFaultFlag(GETBIT(uiByte2, 2), &Central_Alarm_11);
	setFaultFlag(GETBIT(uiByte2, 3), &Central_Alarm_12);
	setFaultFlag(GETBIT(uiByte2, 4), &Central_Alarm_13);
	setFaultFlag(GETBIT(uiByte2, 5), &Central_Alarm_14);
	setFaultFlag(GETBIT(uiByte2, 6), &Central_Alarm_15);
	setFaultFlag(GETBIT(uiByte2, 7), &Central_Alarm_16);

	setFaultFlag(GETBIT(uiByte3, 0), &Central_Alarm_17);

	/*
	bool alarm01 = GETBIT(uiByte1, 0);
	bool alarm02 = GETBIT(uiByte1, 1);
	bool alarm03 = GETBIT(uiByte1, 2);
	bool alarm04 = GETBIT(uiByte1, 3);
	bool alarm05 = GETBIT(uiByte1, 4);
	bool alarm06 = GETBIT(uiByte1, 5);
	bool alarm07 = GETBIT(uiByte1, 6);
	bool alarm08 = GETBIT(uiByte1, 7);

	bool alarm09 = GETBIT(uiByte2, 0);
	bool alarm10 = GETBIT(uiByte2, 1);
	bool alarm11 = GETBIT(uiByte2, 2);
	bool alarm12 = GETBIT(uiByte2, 3);
	bool alarm13 = GETBIT(uiByte2, 4);
	bool alarm14 = GETBIT(uiByte2, 5);
	bool alarm15 = GETBIT(uiByte2, 6);
	bool alarm16 = GETBIT(uiByte2, 7);

	bool alarm17 = GETBIT(uiByte3, 0);

	bool alarm01Current = 0;
	bool alarm02Current = 0;
	bool alarm03Current = 0;
	bool alarm04Current = 0;
	bool alarm05Current = 0;
	bool alarm06Current = 0;
	bool alarm07Current = 0;
	bool alarm08Current = 0;
	bool alarm09Current = 0;
	bool alarm10Current = 0;
	bool alarm11Current = 0;
	*/
}
