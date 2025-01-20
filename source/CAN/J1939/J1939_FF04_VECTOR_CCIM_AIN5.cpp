#include "project.h"
 
void J1939_FF04_VECTOR_CCIM_AIN5(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    if (SettingsGetStationType() == wing_station) {
        return;
    }
    if (pMsg->msg_length < 2) {
        return;
    }

    uint32_t uiData = 0;
    int iData = 0;

    CCIM_Fault_Counter = 0;
    PORTTAB_rs232counter -= 1;

    if (PORTTAB_rs232counter < 0 && CCIM_Fault == 0) {
        PORTTAB_rs232counter = 0;

        uiData = (static_cast<uint32_t>(pMsg->msg_content[1]) << 8) |
            (static_cast<uint32_t>(pMsg->msg_content[0]) & 0x00FF);

        if (SettingsGetTabMapFlip() == flipped) {
            uiData = 450 - uiData;
        }

        uiRaw_PT = uiData;

        uint32_t pt_min = SettingsGetPT_MIN();
        uint32_t pt_max = SettingsGetPT_MAX();

        if (pt_max <= pt_min) {
            return;
        }

        if (uiData > pt_max) uiData = pt_max;
        if (uiData < pt_min) uiData = pt_min;

        iData = (int)(((long)uiData - pt_min) * 1000 / (pt_max - pt_min));

        if (iData > 999) iData = 999;
        if (iData < 0)   iData = 0;

        DBVAR_T DBData;
        DBData.ui = (uint32_t)iData;
        Database_Set_Conditional(db_VECTOR_port_trimtab, &DBData, DBVARTYPE_UNSIGNED_INT, DBSOURCE_GPSI);
    }


}
