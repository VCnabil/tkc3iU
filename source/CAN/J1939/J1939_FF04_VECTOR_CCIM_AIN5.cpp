#include "project.h"
/*

void vDECODE_PGN_FF04_VECTOR_CCIM_AIN5( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    uint32_t uiData = 0; 
    int iData = 0;

    //  No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    CCIM_Fault_Counter = 0;          //reset CCIM fault timeout
    //if we recieve 10 CAN xmissions in a row from the CCIM, start to process the data
    //(otherwise process the data put on the CAN bus via the cantrak's rs232->CAN conversion)
    PORTTAB_rs232counter = PORTTAB_rs232counter - 1;

    if ( ( PORTTAB_rs232counter < 0 ) && ( CCIM_Fault == 0 ) )
    {
        PORTTAB_rs232counter = 0;

        //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
        uiData = ( ( ( UInt16 )( rx_tail->data[DBYTE2] ) << 8 ) | ( UInt16 )( rx_tail->data[DBYTE1] & 0x00ff ) );

        if ( gpSettings->TABMAP_FLIP == flipped ) //swap up and down
            uiData = 450 - uiData;

        uiRaw_PT = uiData;

        //clamp...
        if ( uiData > ( unsigned int ) pt_max ) uiData = ( unsigned int ) pt_max;

        if ( uiData < ( unsigned int ) pt_min ) uiData = ( unsigned int ) pt_min;

        //store it in the data-bizzle fo shizzle
        if ( ucDbTimerRefresh( db_VECTOR_port_trimtab, ucEngineNum, SPECIAL_J1939 ) )
        {
            iData = ( long ) ( uiData - pt_min ) * 1000 / ( pt_max - pt_min ); //convert to scale of 0-1000

            //clamp...
            if ( iData > 999 ) iData = 999;

            if ( iData < 1 )   iData = 1;

            data_base[db_VECTOR_port_trimtab][0].data.flt = ( float )iData;
            TIMER_network = TIMER_NETWORK_PRESET;
        }
    }
}

*/
static const uint16_t pt_min = 0;
static const uint16_t pt_max = 450;
void J1939_FF04_VECTOR_CCIM_AIN5(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    
    uint32_t uiData = 0;
    int iData = 0;
    // Reset CCIM Fault Counter
    CCIM_Fault_Counter = 0;
    // Validate the message length  
    if (pMsg->msg_length < 2)
	{
		// Not enough bytes for AIN5 data
		SetDebugMessage("FF04 CCIM AIN5: Not enough data (%u bytes)", pMsg->msg_length);
		return;
	}

    //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
	uiData = ( ( ( uint32_t )( pMsg->msg_content[1] ) << 8 ) | ( uint32_t )( pMsg->msg_content[0] & 0x00ff ) );
 
	 


}
