#include "project.h"
 

void J1939_FF00_VECTOR_CCIM_AIN1(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{     
    if (pMsg->msg_length < 2) {
       // SetDebugMessage ("FF00 CCIM_AIN1: less than 2bytes: %u", pMsg->msg_length);
        return;
    }
 
    uint32_t uiData = 0;
    int iData = 0;

    CCIM_Fault_Counter = 0; 
    PORTNOZ_rs232counter -= 1;
    if (PORTNOZ_rs232counter < 0 && CCIM_Fault == 0)
    {
        PORTNOZ_rs232counter = 0;

        // Extract data (2 bytes)
        uiData = (static_cast<uint32_t>(pMsg->msg_content[1]) << 8) | (static_cast<uint32_t>(pMsg->msg_content[0]) & 0x00FF);

        if (SettingsGetDataMode() == flipped) {
            uiData = 450 - uiData;
        }

        uiRaw_PN = uiData;   
        uint32_t pn_min = SettingsGetPN_MIN();
        uint32_t pn_max = SettingsGetPN_MAX();

        // Ensure valid range for pn_min and pn_max
        if (pn_max <= pn_min) {
            return; // Invalid range, exit early
        }

        // Clamp uiData
        if (uiData > pn_max) uiData = pn_max;
        if (uiData < pn_min) uiData = pn_min;

        // Scale to 0–1000
          iData = (int)(((long)uiData - pn_min) * 1000 / (pn_max - pn_min));
     

        // Clamp iData
        if (iData > 999) iData = 999;
        if (iData < 0)   iData = 0;

        // Store data in the database
        DBVAR_T DBData;
        DBData.ui = (uint32_t)iData;
        Database_Set_Conditional(db_VECTOR_port_nozzle, &DBData, DBVARTYPE_UNSIGNED_INT, DBSOURCE_CAN);
       
    }
    
}
