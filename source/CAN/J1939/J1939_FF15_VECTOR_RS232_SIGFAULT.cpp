#include "project.h"
/*

void vDECODE_PGN_FF15_VECTOR_RS232_SIGFAULT( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    UInt16 uiData = 0;
    int iData = 0;

    No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
    iData = ( int )rx_tail->data[DBYTE1];

    //store it in the data-bizzle fo shizzle
    if ( ucDbTimerRefresh( db_VECTOR_signal_fault_error, ucEngineNum, SPECIAL_J1939 ) )
    {
        if ( iData != ( int )data_base[db_VECTOR_signal_fault_error][0].data.flt )
        {
            AlarmMuteFlag = 0;
            uiUnacknowledged_PropulsionSystemFault = 1; // flag bit sent to Indication/Alarm controller
        }

        data_base[db_VECTOR_signal_fault_error][0].data.flt = ( float )iData;
        TIMER_network = TIMER_NETWORK_PRESET;
    }

}
*/
void J1939_FF15_VECTOR_RS232_SIGFAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    uint32_t uiData = 0;
	No_or_Bad_CAN_Data = 0;
	if (pMsg->msg_length < 1)
	{
		SetDebugMessage("FF15 RS232_SIGFAULT: Not enough data. Bytes received: %u", pMsg->msg_length);
		return;
	}
	uiData = static_cast<uint32_t>(pMsg->msg_content[1]);
	uint32_t currentValue = 0.0f;
	bool hascurrent = Database_Get_CurrentValue(db_VECTOR_signal_fault_error, &currentValue);
	DBVAR_T dbValue;
	dbValue.ui = static_cast<uint32_t>(uiData);
	bool updateSuccess = Database_Set_Conditional(
		db_VECTOR_signal_fault_error,
		&dbValue,
		DBVARTYPE_UNSIGNED_INT,
		DBSOURCE_NMEA0183
	);
	if (updateSuccess)
	{
		if (hascurrent && (dbValue.flt != currentValue))
		{
			AlarmMuteFlag = 0;
			uiUnacknowledged_PropulsionSystemFault = 1;
		}
	}
  
  
}
