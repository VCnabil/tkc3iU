#include "project.h"
/*
void vDECODE_PGN_FF01_VECTOR_CCIM_AIN2( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    UInt16 uiData = 0;
    int iData = 0;

    //  No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    CCIM_Fault_Counter = 0;          //reset CCIM fault timeout
    //if we recieve 10 CAN xmissions in a row from the CCIM, start to process the data
    //(otherwise process the data put on the CAN bus via the cantrak's rs232->CAN conversion)
    STBDNOZ_rs232counter = STBDNOZ_rs232counter - 1;

    if ( ( STBDNOZ_rs232counter < 0 ) && ( CCIM_Fault == 0 ) )
    {
        STBDNOZ_rs232counter = 0;

        //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
        uiData = ( ( ( UInt16 )( rx_tail->data[DBYTE2] ) << 8 ) | ( UInt16 )( rx_tail->data[DBYTE1] & 0x00ff ) );

        if ( gpSettings->NOZZLEMAP_FLIP == flipped ) //swap left and right
            uiData = 450 - uiData;

        uiRaw_SN = uiData;

        //clamp...
        if ( uiData > ( unsigned int ) sn_max ) uiData = ( unsigned int ) sn_max;

        if ( uiData < ( unsigned int ) sn_min ) uiData = ( unsigned int ) sn_min;

        //store it in the data-bizzle fo shizzle
        if ( ucDbTimerRefresh( db_VECTOR_stbd_nozzle, ucEngineNum, SPECIAL_J1939 ) )
        {
            iData = ( long ) ( uiData - sn_min ) * 1000 / ( sn_max - sn_min ); //convert to scale of 0-1000

            //clamp...
            if ( iData > 999 ) iData = 999;

            if ( iData < 1 )   iData = 1;

            data_base[db_VECTOR_stbd_nozzle][0].data.flt = ( float )iData;
            TIMER_network = TIMER_NETWORK_PRESET;
        }
    }
}

*/


// Example min/max for stbd nozzle
static const uint16_t sn_min = 0;     // or your actual sn_min
static const uint16_t sn_max = 450;   // or 1023, etc.

void J1939_FF01_VECTOR_CCIM_AIN2(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    // Reset CCIM Fault Counter
    CCIM_Fault_Counter = 0;

    // Decrement RS232 counter for Port Nozzle
    PORTNOZ_rs232counter--;

    // Check if RS232 messages have been received sufficiently and no CCIM Fault
    if ((PORTNOZ_rs232counter < 0) && (CCIM_Fault_Counter == 0))
    {
        PORTNOZ_rs232counter = 0; // Reset counter

        // Ensure message has at least 2 bytes
        if (pMsg->msg_length < 2)
        {
            SetDebugMessage("FF01 CCIM AIN2: Not enough data. Bytes=%u", pMsg->msg_length);
            return;
        }

        // Extract two bytes (assuming little-endian: byte0 = LSB, byte1 = MSB)
        uint16_t rawData = (uint16_t)pMsg->msg_content[0]
            | ((uint16_t)pMsg->msg_content[1] << 8);

        // Apply flipping if required
        if (SettingsGetNozzleMapFlip() == flipped)
        {
            rawData = (rawData <= sn_max) ? (sn_max - rawData) : 0;
        }

        // Clamp rawData to [sn_min, sn_max]
        if (rawData > sn_max)
            rawData = sn_max;
        if (rawData < sn_min)
            rawData = sn_min;

        // Scale rawData to 0..1000
        int iData = (int)(((long)rawData - sn_min) * 1000L / (sn_max - sn_min));
        if (iData > 999) iData = 999;
        if (iData < 0)    iData = 0;

        // Prepare database variable
        DBVAR_T dbValue;
        dbValue.ui = (uint32_t)iData;

        // Store in Database
        Database_Set_Conditional(
            db_VECTOR_stbd_nozzle,    // Database index for Stbd Nozzle
            &dbValue,
            DBVARTYPE_UNSIGNED_INT,
            DBSOURCE_CAN
        );
    }
}
