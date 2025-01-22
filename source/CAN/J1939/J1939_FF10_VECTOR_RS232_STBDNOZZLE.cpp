#include "project.h"

void J1939_FF10_VECTOR_RS232_STBDNOZZLE(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    uint32_t uiData = 0;
    No_or_Bad_CAN_Data = 0;
    STBDNOZ_rs232counter = 10; //reset counter (rs232->CAN xmissions supercede CCIM xmissions)

    if (pMsg->msg_length < 2)
	{
		SetDebugMessage("FF10 RS232_STBDNOZ: Not enough data. Bytes received: %u", pMsg->msg_length);
		return;
	}
    uiData = (static_cast<uint32_t>(pMsg->msg_content[1]) << 8) |
				   (static_cast<uint32_t>(pMsg->msg_content[0]) & 0x00FF);

    uint32_t currentValue = 0;
    bool hascurrent = Database_Get_CurrentValue(db_VECTOR_stbd_nozzle, &currentValue);

    DBVAR_T dbValue;
    dbValue.ui = static_cast<uint32_t>(uiData);

    bool updateSuccess = Database_Set_Conditional(
		db_VECTOR_stbd_nozzle,
		&dbValue,
        DBVARTYPE_UNSIGNED_INT,
		DBSOURCE_CAN
	);
 
	 
}
