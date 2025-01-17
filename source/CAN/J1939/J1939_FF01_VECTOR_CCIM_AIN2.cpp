#include "project.h"

void J1939_FF01_VECTOR_CCIM_AIN2(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    if (pMsg->msg_length < 2) {
        return;
    }

    uint32_t uiData = 0;
    int iData = 0;

    CCIM_Fault_Counter = 0;
    STBDNOZ_rs232counter -= 1;

    if (STBDNOZ_rs232counter < 0 && CCIM_Fault == 0) {
        STBDNOZ_rs232counter = 0;

        uiData = (static_cast<uint32_t>(pMsg->msg_content[1]) << 8) | (static_cast<uint32_t>(pMsg->msg_content[0]) & 0x00FF);

        if (SettingsGetDataMode() == flipped) {
            uiData = 450 - uiData;
        }

        uiRaw_SN = uiData;

        uint32_t sn_min = SettingsGetSN_MIN();
        uint32_t sn_max = SettingsGetSN_MAX();

        if (sn_max <= sn_min) {
            return;
        }

        if (uiData > sn_max) uiData = sn_max;
        if (uiData < sn_min) uiData = sn_min;

        iData = (int)(((long)uiData - sn_min) * 1000 / (sn_max - sn_min));

        if (iData > 999) iData = 999;
        if (iData < 0)   iData = 0;

        DBVAR_T DBData;
        DBData.ui = (uint32_t)iData;
        Database_Set_Conditional(db_VECTOR_stbd_nozzle, &DBData, DBVARTYPE_UNSIGNED_INT, DBSOURCE_GPSI);
    }
}