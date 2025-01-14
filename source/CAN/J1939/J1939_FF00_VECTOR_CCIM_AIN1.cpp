#include "project.h"
/*

void vDECODE_PGN_FF00_VECTOR_CCIM_AIN1( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    UInt16 uiData = 0;
    int iData = 0;

    //  No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    CCIM_Fault_Counter = 0;          //reset CCIM fault timeout
    //if we recieve 10 CAN xmissions in a row from the CCIM, start to process the data
    //(otherwise process the data put on the CAN bus via the cantrak's rs232->CAN conversion)
    PORTNOZ_rs232counter = PORTNOZ_rs232counter - 1;

    if ( ( PORTNOZ_rs232counter < 0 ) && ( CCIM_Fault == 0 ) )
    {
        PORTNOZ_rs232counter = 0;

        //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
        uiData = ( ( ( UInt16 )( rx_tail->data[DBYTE2] ) << 8 ) | ( UInt16 )( rx_tail->data[DBYTE1] & 0x00ff ) );

        if ( gpSettings->NOZZLEMAP_FLIP == flipped ) //swap left and right
            uiData = 450 - uiData;

        uiRaw_PN = uiData;  //for calibrating

        //clamp..
        if ( uiData > ( unsigned int ) pn_max ) uiData = ( unsigned int ) pn_max;

        if ( uiData < ( unsigned int ) pn_min ) uiData = ( unsigned int ) pn_min;

        //store it in the data-bizzle fo shizzle
        if ( ucDbTimerRefresh( db_VECTOR_port_nozzle, ucEngineNum, SPECIAL_J1939 ) )
        {
            iData = ( long ) ( uiData - pn_min ) * 1000 / ( pn_max - pn_min ); //convert to scale of 0-1000

            //clamp...
            if ( iData > 999 ) iData = 999;

            if ( iData < 1 )   iData = 1;

            data_base[db_VECTOR_port_nozzle][0].data.flt = ( float )iData;
            TIMER_network = TIMER_NETWORK_PRESET;
        }
    }
}

*/
 
static const uint16_t pn_min = 0;
static const uint16_t pn_max = 450;  // or 1023, depending on your actual A/D range

void J1939_FF00_VECTOR_CCIM_AIN1(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    if (pMsg->msg_length < 2)
    {
        // Not enough bytes for AIN1 data
        SetDebugMessage("FF00 CCIM AIN1: Not enough data (%u bytes)", pMsg->msg_length);
        return;
    }

    uint16_t rawData = (uint16_t)pMsg->msg_content[0]
        | ((uint16_t)pMsg->msg_content[1] << 8);


    if (SettingsGetNozzleMapFlip() == flipped)  // normal? flipped?
    {
        rawData = (pn_max > rawData) ? (pn_max - rawData) : 0;
    }

    // clamp to [pn_min, pn_max]
    if (rawData > pn_max)
        rawData = pn_max;
    if (rawData < pn_min)
        rawData = pn_min;

    // convert to 0..1000 scale (or 0..999) 
    // Example: iData = (rawData - pn_min) * 1000 / (pn_max - pn_min)
    // Let’s do integer math then store as float
    int iData = (int)(((long)rawData - pn_min) * 1000L / (pn_max - pn_min));
    if (iData > 999) iData = 999;
    if (iData < 0)   iData = 0;

    // Store in DB
    // Option A: Directly call Database_Set_CAN
    {
        DBVAR_T dbValue;
        dbValue.ui = (uint32_t)iData;

        Database_Set_Conditional(
            db_VECTOR_port_nozzle,
            &dbValue,
            DBVARTYPE_UNSIGNED_INT,
            DBSOURCE_CAN
        );
        //or 
        //Database_Set_CAN(
        //    db_VECTOR_port_nozzle,  // Where you want to store it
        //    &dbValue,
        //    DBVARTYPE_UNSIGNED_INT,      
        //    canPort,
        //    0,                     // nmeaInstanceOrSequenceID
        //    CANIDEXT_GETSOURCEADDR(pMsg->id) // Source Address
        //);
    }

    // Optional debug
    // SetDebugMessage("FF00 AIN1: raw=%u => scaled=%d", rawData, iData);

 
     CCIM_Fault_Counter = 0;


}
