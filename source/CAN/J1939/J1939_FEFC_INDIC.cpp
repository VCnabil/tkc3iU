#include "project.h"

void J1939_FEFC_INDIC(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    DBVAR_T DBData;

    // Validate the message length
    if (pMsg->msg_length < 8) {
        SetDebugMessage("J1939_FEFC_INDIC: Message length too short.");
        return;
    }

    //gJ1939CallCount++;
    // Process each byte and update the database
    static const DATABASEINDEX_T myDBIndexes[] = {
        db_VECTOR_port_nozzle,   
        db_VECTOR_stbd_nozzle,
        db_VECTOR_port_bucket,
        db_VECTOR_stbd_bucket,
        db_VECTOR_port_trimtab,
        db_VECTOR_stbd_trimtab,
        db_VECTOR_signal_fault_error,
        db_VECTOR_nfu_fault_error
       
    };

    for (int i = 0; i < 8; ++i) {
        uint8_t faultValue = pMsg->msg_content[i];

        // Check for valid fault data
        if (faultValue != DATA_NOT_AVAILABLE && faultValue != DATA_ERROR_INDICATOR) {
            DBData.ui = (uint32_t)faultValue;  // Store fault value as unsigned int
            //Database_Set_CAN();
          // Database_Set_CAN(myDBIndexes[i], &DBData, DBVARTYPE_UNSIGNED_INT, canPort, 0, CANIDEXT_GETSOURCEADDR(pMsg->id));
            Database_Set_Conditional(
                myDBIndexes[i],       // dbIndex
                &DBData,              // Pointer to DBVAR_T
                DBVARTYPE_UNSIGNED_INT,
                DBSOURCE_CAN
            );
        } else {
            // If data is invalid, optionally log or handle it
            SetDebugMessage("J1939_FEFC_INDIC: Fault data unavailable or invalid for byte %d", i + 1);
        }
    }
}
