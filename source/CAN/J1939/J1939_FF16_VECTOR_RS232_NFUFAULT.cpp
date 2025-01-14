#include "project.h"


/*
void vDECODE_PGN_FF16_VECTOR_RS232_NFUFAULT( unsigned char ucEngineNum, struct buffer_object *rx_tail )
{
    UInt16 uiData = 0;
    int iData = 0;

    No_or_Bad_CAN_Data = 0;  //reset Can data link fault timeout
    //extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
    iData = ( int )rx_tail->data[DBYTE1];

    //store it in the data-bizzle fo shizzle
    if ( ucDbTimerRefresh( db_VECTOR_nfu_fault_error, ucEngineNum, SPECIAL_J1939 ) )
    {
        if ( iData != ( int )data_base[db_VECTOR_nfu_fault_error][0].data.flt )
        {
            AlarmMuteFlag = 0;
            uiUnacknowledged_PropulsionSystemFault = 1; // flag bit sent to Indication/Alarm controller
        }

        data_base[db_VECTOR_nfu_fault_error][0].data.flt = ( float )iData;
        TIMER_network = TIMER_NETWORK_PRESET;
    }

}
*/
void J1939_FF16_VECTOR_RS232_NFUFAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{

    // Reset CAN data link fault timeout
    No_or_Bad_CAN_Data = 0;

    // Optional: Reset RS232 counters if necessary
    // PORTNOZ_rs232counter = 10; // Uncomment if needed based on your prioritization logic

    // Ensure the message has at least 2 bytes
    if (pMsg->msg_length < 2)
    {
        SetDebugMessage("FF16 VECTOR_RS232_NFUFAULT: Not enough data. Bytes received: %u", pMsg->msg_length);
        return;
    }

    // Extract data: Assuming DBYTE1 corresponds to msg_content[1]
    // Adjust indexing based on your actual data structure
    int iData = static_cast<int>(pMsg->msg_content[1]);

    // Extract engine number from canPort
    unsigned char ucEngineNum = static_cast<unsigned char>(canPort);// ExtractEngineNum(canPort);

    // Define or retrieve SPECIAL_J1939 as per your system's requirements
    const int SPECIAL_J1939 = 0; // Placeholder value; replace with actual if needed

    // Check if the timer allows processing the data
    if (Database_TimerRefresh(db_VECTOR_nfu_fault_error, ucEngineNum, DBSOURCE_NMEA0183))
    {
        // Retrieve current value from the database for comparison
        uint32_t currentValue = 0;
        bool hasCurrent = Database_Get_CurrentValue(db_VECTOR_nfu_fault_error, &currentValue);

        // Compare the new data with the current database value
        if (hasCurrent && (iData != static_cast<uint32_t>(currentValue)))
        {
            // Trigger alarms if there's a change in data
            AlarmMuteFlag = 0;
            uiUnacknowledged_PropulsionSystemFault = 1; // Flag bit sent to Indication/Alarm controller
        }

        // Prepare the new database value
        DBVAR_T dbValue;
        dbValue.ui = static_cast<uint32_t>(iData); // Assuming the database stores float values

        // Update the database conditionally
        bool updateSuccess = Database_Set_Conditional(
            db_VECTOR_nfu_fault_error,   // Database index for NFU Fault
            &dbValue,
            DBVARTYPE_FLOAT,             // Data type (float)
            DBSOURCE_NMEA0183               // Source identifier (RS232)
        );

        if (updateSuccess)
        {
            // Update the network timer to indicate fresh data reception
          //  TIMER_network = TIMER_NETWORK_PRESET;
        }

        // Optional Debug Message
        // SetDebugMessage("FF16 RS232_NFUFAULT: data=%d => stored=%f", iData, dbValue.flt);
    }
   
 
}
