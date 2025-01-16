#include "project.h"
 
 
void J1939_FF0F_VECTOR_RS232_PORTNOZZLE(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    No_or_Bad_CAN_Data = 0;

    PORTNOZ_rs232counter = 10;

    if (pMsg->msg_length < 2)
	{
		SetDebugMessage("FF0F RS232_PORTNOZ: Not enough data. Bytes received: %u", pMsg->msg_length);
		return;
	}

    uint32_t uiData = (static_cast<uint32_t>(pMsg->msg_content[1]) << 8) | (static_cast<uint32_t>(pMsg->msg_content[0]) & 0x00FF);

    uint32_t currentValue = 0;
	bool hasCurrent = Database_Get_CurrentValue(db_VECTOR_port_nozzle, &currentValue);

	DBVAR_T dbValue;
	dbValue.ui = static_cast<uint32_t>(uiData);

	bool updateSuccess = Database_Set_Conditional(
		db_VECTOR_port_nozzle,
		&dbValue,
		DBVARTYPE_UNSIGNED_INT,
		DBSOURCE_NMEA0183
	);

	if (updateSuccess)
	{
		if (hasCurrent && (dbValue.ui != currentValue))
		{
			AlarmMuteFlag = 0;
			uiUnacknowledged_PropulsionSystemFault = 1;
		}


	}
}
