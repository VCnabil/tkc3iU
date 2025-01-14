#include "project.h"
/*
void vDECODE_PGN_FF02_VECTOR_CCIM_AIN3( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    UInt16 uiData = 0;
    int iData = 0;

    //  No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    CCIM_Fault_Counter = 0;          //reset CCIM fault timeout
    //if we recieve 10 CAN xmissions in a row from the CCIM, start to process the data
    //(otherwise process the data put on the CAN bus via the cantrak's rs232->CAN conversion)
    PORTBKT_rs232counter = PORTBKT_rs232counter - 1;

    if ( ( PORTBKT_rs232counter < 0 ) && ( CCIM_Fault == 0 ) )
    {
        PORTBKT_rs232counter = 0;

        //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
        uiData = ( ( ( UInt16 )( rx_tail->data[DBYTE2] ) << 8 ) | ( UInt16 )( rx_tail->data[DBYTE1] & 0x00ff ) );

        if ( gpSettings->BUCKETMAP_FLIP == flipped ) //swap up and down
            uiData = 450 - uiData;

        uiRaw_PB = uiData;

        //clamp...
        if ( uiData > ( unsigned int ) pb_max ) uiData = ( unsigned int ) pb_max;

        if ( uiData < ( unsigned int ) pb_min ) uiData = ( unsigned int ) pb_min;

        //store it in the data-bizzle fo shizzle
        if ( ucDbTimerRefresh( db_VECTOR_port_bucket, ucEngineNum, SPECIAL_J1939 ) )
        {
            //apply one of two gains for scaling, split by the neutral thrust value.
            if ( uiData < pb_neutral_thrust )
                iData = ( long ) ( uiData - pb_min ) * 500 / ( pb_neutral_thrust - pb_min ); //convert to scale of 0-500

            else
                iData = ( long ) ( uiData - pb_neutral_thrust ) * 500 / ( pb_max - pb_neutral_thrust ) + 500; //convert to scale of 500-1000

            //clamp...
            if ( iData > 999 ) iData = 999;

            if ( iData < 1 )   iData = 1;

            data_base[db_VECTOR_port_bucket][0].data.flt = ( float )iData;
            TIMER_network = TIMER_NETWORK_PRESET;
        }
    }
}

*/
static const uint16_t pb_min = 0;
static const uint16_t pb_max = 450;      // or your actual range
static const uint16_t pb_neutral_thrust = 225; // example if you want a 0..500..1000 split

void J1939_FF02_VECTOR_CCIM_AIN3(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    // Reset CCIM Fault Counter
    CCIM_Fault_Counter = 0;

    // Decrement RS232 counter for Port Bucket
    PORTBKT_rs232counter--;

    // Check if RS232 messages have been received sufficiently and no CCIM Fault
    if ((PORTBKT_rs232counter < 0) && (CCIM_Fault_Counter == 0))
    {
        PORTBKT_rs232counter = 0; // Reset counter

        // Ensure message has at least 2 bytes
        if (pMsg->msg_length < 2)
        {
            SetDebugMessage("FF02 CCIM AIN3: Not enough data. Bytes=%u", pMsg->msg_length);
            return;
        }

        // Extract two bytes (assuming little-endian: byte0 = LSB, byte1 = MSB)
        uint16_t rawData = (uint16_t)pMsg->msg_content[0]
            | ((uint16_t)pMsg->msg_content[1] << 8);

        // Apply flipping if required
        if (SettingsGetBucketMapFlip() == flipped)
        {
            rawData = (rawData <= pb_max) ? (pb_max - rawData) : 0;
        }

        // Clamp rawData to [pb_min, pb_max]
        if (rawData > pb_max)
            rawData = pb_max;
        if (rawData < pb_min)
            rawData = pb_min;

        // Scale rawData to 0..1000 with neutral thrust split
        int iData = 0;
        if (rawData < pb_neutral_thrust)
        {
            // Scale 0..500
            iData = (int)(((long)rawData - pb_min) * 500L / (pb_neutral_thrust - pb_min));
        }
        else
        {
            // Scale 500..1000
            iData = (int)(((long)rawData - pb_neutral_thrust) * 500L / (pb_max - pb_neutral_thrust) + 500);
        }

        // Clamp scaled data
        if (iData > 999) iData = 999;
        if (iData < 0)    iData = 0;

        // Prepare database variable
        DBVAR_T dbValue;
        dbValue.ui = (uint32_t)iData;

        // Store in Database
        Database_Set_Conditional(
            db_VECTOR_port_bucket,    // Database index for Port Bucket
            &dbValue,
            DBVARTYPE_UNSIGNED_INT,
            DBSOURCE_CAN
        );

    }
}
