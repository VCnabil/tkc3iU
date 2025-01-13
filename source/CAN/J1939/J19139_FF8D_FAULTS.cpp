#include "project.h"
// Array that maps each byte to the corresponding DB index.
// (If you don't have an 8th DB index for byte7, you can omit that or handle it conditionally.)
static const DATABASEINDEX_T s_ff8dDbIndexMap[8] =
{
    db_VECTOR_signal_fault_error,  // byte0
    db_VECTOR_nfu_fault_error,     // byte1
    db_VECTOR_STA1_fault_error,    // byte2
    db_VECTOR_STA2_fault_error,    // byte3
    db_VECTOR_STA3_fault_error,    // byte4
    db_VECTOR_cal_fault_error,     // byte5
    db_VECTOR_interlock_fault_error,// byte6
    // If you have a new DB index for the 8th byte, place it here. Otherwise, we can ignore it or do some conditional logic.
    db_VECTOR_interlock_fault_error // or some placeholder, or skip
};
void J1939_FF8D_FAULTS(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{

    // Safety check: ensure we have at least 7 or 8 bytes
  /*  if (pMsg->msg_length < 7)
    {
        SetDebugMessage("J1939_FF8D_FAULTS: Message too short (%d bytes).", pMsg->msg_length);
        return;
    }*/

    // For clarity/logging
    gJ1939CallCount++;

    // We will store each byte into the appropriate DB index.
    // Each byte is presumably a bitmask representing faults (0..255).
    // Example: if byte0 = 0x12, that means bits 1 & 4 are set, etc.

    for (uint8_t i = 0; i < pMsg->msg_length && i < 8; i++)
    {
       

        DBVAR_T dbData;
        dbData.ui = (uint32_t)pMsg->msg_content[i];

        // Write it into the DB as an unsigned int conditional
        Database_Set_Conditional(
            s_ff8dDbIndexMap[i], // DB index
            &dbData,             // Pointer to DBVAR_T
            DBVARTYPE_UNSIGNED_INT,
            DBSOURCE_CAN
        );

       
    }
  
}
