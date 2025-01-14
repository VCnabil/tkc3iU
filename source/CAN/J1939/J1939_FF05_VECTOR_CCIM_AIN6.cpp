#include "project.h"

/*

void vDECODE_PGN_FF05_VECTOR_CCIM_AIN6( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    UInt16 uiData = 0;
    int iData = 0;

    //  No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    CCIM_Fault_Counter = 0;          //reset CCIM fault timeout
    //if we recieve 10 CAN xmissions in a row from the CCIM, start to process the data
    //(otherwise process the data put on the CAN bus via the cantrak's rs232->CAN conversion)
    STBDTAB_rs232counter = STBDTAB_rs232counter - 1;

    if ( ( STBDTAB_rs232counter < 0 ) && ( CCIM_Fault == 0 ) )
    {
        STBDTAB_rs232counter = 0;

        //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
        uiData = ( ( ( UInt16 )( rx_tail->data[DBYTE2] ) << 8 ) | ( UInt16 )( rx_tail->data[DBYTE1] & 0x00ff ) );

        if ( gpSettings->TABMAP_FLIP == flipped ) //swap up and down
            uiData = 450 - uiData;

        uiRaw_ST = uiData;

        //clamp...
        if ( uiData > ( unsigned int ) st_max ) uiData = ( unsigned int ) st_max;

        if ( uiData < ( unsigned int ) st_min ) uiData = ( unsigned int ) st_min;

        //store it in the data-bizzle fo shizzle
        if ( ucDbTimerRefresh( db_VECTOR_stbd_trimtab, ucEngineNum, SPECIAL_J1939 ) )
        {
            iData = ( long ) ( uiData - st_min ) * 1000 / ( st_max - st_min ); //convert to scale of 0-1000

            //clamp...
            if ( iData > 999 ) iData = 999;

            if ( iData < 1 )   iData = 1;

            data_base[db_VECTOR_stbd_trimtab][0].data.flt = ( float )iData;
            TIMER_network = TIMER_NETWORK_PRESET;
        }
    }
}

*/

static const uint16_t st_min = 0;
static const uint16_t st_max = 450;
void J1939_FF05_VECTOR_CCIM_AIN6(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    // Reset CCIM Fault Counter
    CCIM_Fault_Counter = 0;

    // Decrement RS232 counter for Stbd Trimtab
    STBDTAB_rs232counter--;

    // Check if RS232 messages have been received sufficiently and no CCIM Fault
    if ((STBDTAB_rs232counter < 0) && (CCIM_Fault_Counter == 0))
    {
        STBDTAB_rs232counter = 0; // Reset counter

        // Ensure message has at least 2 bytes
        if (pMsg->msg_length < 2)
        {
            SetDebugMessage("FF05 CCIM AIN6: Not enough data. Bytes=%u", pMsg->msg_length);
            return;
        }

        // Extract two bytes (assuming little-endian: byte0 = LSB, byte1 = MSB)
        uint16_t rawData = (uint16_t)pMsg->msg_content[0]
            | ((uint16_t)pMsg->msg_content[1] << 8);

        // Apply flipping if required
        if (SettingsGetTabMapFlip() == flipped)
        {
            rawData = (rawData <= st_max) ? (st_max - rawData) : 0;
        }

        // Clamp rawData to [st_min, st_max]
        if (rawData > st_max)
            rawData = st_max;
        if (rawData < st_min)
            rawData = st_min;

        // Scale rawData to 0..1000
        int iData = (int)(((long)rawData - st_min) * 1000L / (st_max - st_min));
        if (iData > 999) iData = 999;
        if (iData < 0)    iData = 0;

        // Prepare database variable
        DBVAR_T dbValue;
        dbValue.ui = (uint32_t)iData;

        // Store in Database
        Database_Set_Conditional(
            db_VECTOR_stbd_trimtab,    // Database index for Stbd Trimtab
            &dbValue,
            DBVARTYPE_UNSIGNED_INT,
            DBSOURCE_CAN
        );

        // Optional Debug Message
        // SetDebugMessage("FF05 AIN6: raw=%u => scaled=%d", rawData, iData);
    }
}
