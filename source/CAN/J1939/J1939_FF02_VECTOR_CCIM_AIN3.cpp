#include "project.h"


void J1939_FF02_VECTOR_CCIM_AIN3(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    if (pMsg->msg_length < 2) {
        return;
    }

    uint32_t uiData = 0;
    int iData = 0;

    CCIM_Fault_Counter = 0;
    PORTBKT_rs232counter -= 1;

    if (PORTBKT_rs232counter < 0 && CCIM_Fault == 0) {
        PORTBKT_rs232counter = 0;

        uiData = (static_cast<uint32_t>(pMsg->msg_content[1]) << 8) |
            (static_cast<uint32_t>(pMsg->msg_content[0]) & 0x00FF);

        if (SettingsGetBucketMapFlip() == flipped) {
            uiData = 450 - uiData;
        }

        uiRaw_PB = uiData;

        uint32_t pb_min = SettingsGetPB_MIN();
        uint32_t pb_max = SettingsGetPB_MAX();
        uint32_t pb_neutral_thrust = SettingsGetPB_NEUTRAL_THRUST();

        if (pb_max <= pb_min || pb_neutral_thrust <= pb_min || pb_neutral_thrust >= pb_max) {
            return;
        }

        if (uiData > pb_max) uiData = pb_max;
        if (uiData < pb_min) uiData = pb_min;

        if (uiData < pb_neutral_thrust) {
            iData = (int)(((long)uiData - pb_min) * 500 / (pb_neutral_thrust - pb_min));
        }
        else {
            iData = (int)(((long)uiData - pb_neutral_thrust) * 500 / (pb_max - pb_neutral_thrust)) + 500;
        }

        if (iData > 999) iData = 999;
        if (iData < 0)   iData = 0;

        DBVAR_T DBData;
        DBData.ui = (uint32_t)iData;
        Database_Set_Conditional(db_VECTOR_port_bucket, &DBData, DBVARTYPE_UNSIGNED_INT, DBSOURCE_GPSI);
    }

}
