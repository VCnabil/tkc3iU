#include "project.h"
/*

void vDECODE_PGN_FF18_VECTOR_RS232_STA2FAULT( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    UInt16 uiData = 0;
    int iData = 0;

    No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
    iData = ( int )rx_tail->data[DBYTE1];

    //store it in the data-bizzle fo shizzle
    if ( ucDbTimerRefresh( db_VECTOR_STA2_fault_error, ucEngineNum, SPECIAL_J1939 ) )
    {
        if ( iData != ( int )data_base[db_VECTOR_STA2_fault_error][0].data.flt )
        {
            AlarmMuteFlag = 0;
            uiUnacknowledged_PropulsionSystemFault = 1; // flag bit sent to Indication/Alarm controller
        }

        data_base[db_VECTOR_STA2_fault_error][0].data.flt = ( float )iData;
        TIMER_network = TIMER_NETWORK_PRESET;
    }

}

*/
void J1939_FF18_VECTOR_RS232_STA2FAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    // implement me later
}
