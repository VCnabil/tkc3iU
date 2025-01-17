#include "project.h"


void J1939_FF16_VECTOR_RS232_NFUFAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{

    uint32_t uiData = 0;
    No_or_Bad_CAN_Data = 0; // Reset CAN data link fault timeout

    // Validate message length
    if (pMsg->msg_length < 1)
    {
       // SetDebugMessage("FF16 RS232_NFUFAULT: Not enough data. Bytes received: %u", pMsg->msg_length);
        return;
    }

    // Extract data
    uiData = static_cast<uint32_t>(pMsg->msg_content[0]);

    // Retrieve the current value from the database
    uint32_t currentValue = 0;
    bool hasCurrent = Database_Get_CurrentValue(db_VECTOR_nfu_fault_error, &currentValue);

    // Prepare database value for update
    DBVAR_T dbValue;
    dbValue.ui = uiData; // Use .ui since the data is unsigned

    // Update the database
    bool updateSuccess = Database_Set_Conditional(
        db_VECTOR_nfu_fault_error,
        &dbValue,
        DBVARTYPE_UNSIGNED_INT,
        DBSOURCE_CAN
    );

    // Alarm handling on successful update
    if (updateSuccess)
    {
        if (hasCurrent && (dbValue.ui != currentValue))
        {
            AlarmMuteFlag = 0; // Reset mute flag
            uiUnacknowledged_PropulsionSystemFault = 1; // Set fault flag for alarm controller
        }
    }
   
   
 
}
