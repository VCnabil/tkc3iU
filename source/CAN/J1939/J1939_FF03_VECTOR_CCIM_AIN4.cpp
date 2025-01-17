#include "project.h"
 
void J1939_FF03_VECTOR_CCIM_AIN4(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    if (pMsg->msg_length < 2) {
        return;
    }

    uint32_t uiData = 0;
    int iData = 0;

    CCIM_Fault_Counter = 0;
    STBDBKT_rs232counter -= 1;

    if (STBDBKT_rs232counter < 0 && CCIM_Fault == 0) {
        STBDBKT_rs232counter = 0;

        uiData = (static_cast<uint32_t>(pMsg->msg_content[1]) << 8) |
            (static_cast<uint32_t>(pMsg->msg_content[0]) & 0x00FF);

        if (SettingsGetBucketMapFlip() == flipped) {
            uiData = 450 - uiData;
        }

        uiRaw_SB = uiData;

        uint32_t sb_min = SettingsGetSB_MIN();
        uint32_t sb_max = SettingsGetSB_MAX();
        uint32_t sb_neutral_thrust = SettingsGetSB_NEUTRAL_THRUST();

        if (sb_max <= sb_min || sb_neutral_thrust <= sb_min || sb_neutral_thrust >= sb_max) {
            return;
        }

        if (uiData > sb_max) uiData = sb_max;
        if (uiData < sb_min) uiData = sb_min;

        if (uiData < sb_neutral_thrust) {
            iData = (int)(((long)uiData - sb_min) * 500 / (sb_neutral_thrust - sb_min));
        }
        else {
            iData = (int)(((long)uiData - sb_neutral_thrust) * 500 / (sb_max - sb_neutral_thrust)) + 500;
        }

        if (iData > 999) iData = 999;
        if (iData < 0)   iData = 0;

        DBVAR_T DBData;
        DBData.ui = (uint32_t)iData;
        Database_Set_Conditional(db_VECTOR_stbd_bucket, &DBData, DBVARTYPE_UNSIGNED_INT, DBSOURCE_GPSI);
    }
}
