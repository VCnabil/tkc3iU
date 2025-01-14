#include "project.h"
/*

void vDECODE_PGN_FF03_VECTOR_CCIM_AIN4( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    UInt16 uiData = 0;
    int iData = 0;

    //  No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    CCIM_Fault_Counter = 0;          //reset CCIM fault timeout
    //if we recieve 10 CAN xmissions in a row from the CCIM, start to process the data
    //(otherwise process the data put on the CAN bus via the cantrak's rs232->CAN conversion)
    STBDBKT_rs232counter = STBDBKT_rs232counter - 1;

    if ( ( STBDBKT_rs232counter < 0 ) && ( CCIM_Fault == 0 ) )
    {
        STBDBKT_rs232counter = 0;

        //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
        uiData = ( ( ( UInt16 )( rx_tail->data[DBYTE2] ) << 8 ) | ( UInt16 )( rx_tail->data[DBYTE1] & 0x00ff ) );

        if ( gpSettings->BUCKETMAP_FLIP == flipped ) //swap up and down
            uiData = 450 - uiData;

        uiRaw_SB = uiData;

        //clamp...
        if ( uiData > ( unsigned int ) sb_max ) uiData = ( unsigned int ) sb_max;

        if ( uiData < ( unsigned int ) sb_min ) uiData = ( unsigned int ) sb_min;

        //store it in the data-bizzle fo shizzle
        if ( ucDbTimerRefresh( db_VECTOR_stbd_bucket, ucEngineNum, SPECIAL_J1939 ) )
        {
            //apply one of two gains for scaling, split by the neutral thrust value.
            if ( uiData < sb_neutral_thrust )
                iData = ( long ) ( uiData - sb_min ) * 500 / ( sb_neutral_thrust - sb_min ); //convert to scale of 0-500

            else
                iData = ( long ) ( uiData - sb_neutral_thrust ) * 500 / ( sb_max - sb_neutral_thrust ) + 500; //convert to scale of 500-1000

            //clamp...
            if ( iData > 999 ) iData = 999;

            if ( iData < 1 )   iData = 1;

            data_base[db_VECTOR_stbd_bucket][0].data.flt = ( float )iData;
            TIMER_network = TIMER_NETWORK_PRESET;
        }
    }
}

*/

static const uint16_t sb_min = 0;
static const uint16_t sb_max = 450;
static const uint16_t sb_neutral_thrust = 225;
void J1939_FF03_VECTOR_CCIM_AIN4(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    // Reset CCIM Fault Counter
    CCIM_Fault_Counter = 0;

    // Decrement RS232 counter for Stbd Bucket
    STBDBKT_rs232counter--;

    // Check if RS232 messages have been received sufficiently and no CCIM Fault
    if ((STBDBKT_rs232counter < 0) && (CCIM_Fault_Counter == 0))
    {
        STBDBKT_rs232counter = 0; // Reset counter

        // Ensure message has at least 2 bytes
        if (pMsg->msg_length < 2)
        {
            SetDebugMessage("FF03 CCIM AIN4: Not enough data. Bytes=%u", pMsg->msg_length);
            return;
        }

        // Extract two bytes (assuming little-endian: byte0 = LSB, byte1 = MSB)
        uint16_t rawData = (uint16_t)pMsg->msg_content[0]
            | ((uint16_t)pMsg->msg_content[1] << 8);

        // Apply flipping if required
        if (SettingsGetBucketMapFlip() == flipped)
        {
            rawData = (rawData <= sb_max) ? (sb_max - rawData) : 0;
        }

        // Clamp rawData to [sb_min, sb_max]
        if (rawData > sb_max)
            rawData = sb_max;
        if (rawData < sb_min)
            rawData = sb_min;

        // Scale rawData to 0..1000 with neutral thrust split
        int iData = 0;
        if (rawData < sb_neutral_thrust)
        {
            // Scale 0..500
            iData = (int)(((long)rawData - sb_min) * 500L / (sb_neutral_thrust - sb_min));
        }
        else
        {
            // Scale 500..1000
            iData = (int)(((long)rawData - sb_neutral_thrust) * 500L / (sb_max - sb_neutral_thrust) + 500);
        }

        // Clamp scaled data
        if (iData > 999) iData = 999;
        if (iData < 0)    iData = 0;

        // Prepare database variable
        DBVAR_T dbValue;
        dbValue.ui = (uint32_t)iData;

        // Store in Database
        Database_Set_Conditional(
            db_VECTOR_stbd_bucket,    // Database index for Stbd Bucket
            &dbValue,
            DBVARTYPE_UNSIGNED_INT,
            DBSOURCE_CAN
        );

        // Optional Debug Message
        // SetDebugMessage("FF03 AIN4: raw=%u => scaled=%d", rawData, iData);
    }
}
