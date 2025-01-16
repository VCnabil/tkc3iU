#include "project.h"
/*
void vDECODE_PGN_FF13_VECTOR_RS232_PORTTAB( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    UInt16 uiData = 0;
    No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout

    PORTTAB_rs232counter = 10; //reset counter (rs232->CAN xmissions supercede CCIM xmissions)
    //extract data (it's two bytes of data because the scale is 0 to 1000)
    uiData = ( ( ( UInt16 )( rx_tail->data[DBYTE2] ) << 8 ) | ( UInt16 )( rx_tail->data[DBYTE1] & 0x00ff ) );

    //store it in the data-bizzle fo shizzle
    if ( ucDbTimerRefresh( db_VECTOR_port_trimtab, ucEngineNum, SPECIAL_J1939 ) )
    {
        data_base[db_VECTOR_port_trimtab][0].data.flt = ( float )uiData;
        TIMER_network = TIMER_NETWORK_PRESET;
    }

}


*/
void J1939_FF13_VECTOR_RS232_PORTTRIMTAB(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
  
    uint32_t uiData = 0;
  No_or_Bad_CAN_Data = 0;
  PORTTAB_rs232counter = 10; //reset counter (rs232->CAN xmissions supercede CCIM xmissions)

  if (pMsg->msg_length < 2)
  {
	SetDebugMessage("FF13 RS232_PORTTRIMTAB: Not enough data. Bytes received: %u", pMsg->msg_length);
	return;
  }
  uiData = (static_cast<uint32_t>(pMsg->msg_content[2]) << 8) |
		   (static_cast<uint32_t>(pMsg->msg_content[1]) & 0x00FF);

  uint32_t currentValue = 0.0f;
  bool hascurrent = Database_Get_CurrentValue(db_VECTOR_port_trimtab, &currentValue);

  DBVAR_T dbValue;
  dbValue.ui = static_cast<uint32_t>(uiData);

  bool updateSuccess = Database_Set_Conditional(
	db_VECTOR_port_trimtab,
	&dbValue,
	DBVARTYPE_UNSIGNED_INT,
	DBSOURCE_CAN
  );
  if (updateSuccess)
  {
	if (hascurrent && (dbValue.ui != currentValue))
	{
	  AlarmMuteFlag = 0;
	  uiUnacknowledged_PropulsionSystemFault = 1;
	}
  }
}
