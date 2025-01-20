#include "project.h" 
 
void J1939_FF05_VECTOR_CCIM_AIN6(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
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
    STBDTAB_rs232counter -= 1;

    if (STBDTAB_rs232counter < 0 && CCIM_Fault == 0) {
        STBDTAB_rs232counter = 0;

        uiData = (static_cast<uint32_t>(pMsg->msg_content[1]) << 8) |
            (static_cast<uint32_t>(pMsg->msg_content[0]) & 0x00FF);

        if (SettingsGetTabMapFlip() == flipped) {
            uiData = 450 - uiData;
        }

        uiRaw_ST = uiData;

        uint32_t st_min = SettingsGetST_MIN();
        uint32_t st_max = SettingsGetST_MAX();

        if (st_max <= st_min) {
            return;
        }

        if (uiData > st_max) uiData = st_max;
        if (uiData < st_min) uiData = st_min;

        iData = (int)(((long)uiData - st_min) * 1000 / (st_max - st_min));

        if (iData > 999) iData = 999;
        if (iData < 0)   iData = 0;

        DBVAR_T DBData;
        DBData.ui = (uint32_t)iData;
        Database_Set_Conditional(db_VECTOR_stbd_trimtab, &DBData, DBVARTYPE_UNSIGNED_INT, DBSOURCE_GPSI);
    }
}
