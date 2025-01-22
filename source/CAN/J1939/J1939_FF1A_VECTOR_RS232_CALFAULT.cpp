#include "project.h"
 
void J1939_FF1A_VECTOR_RS232_CALFAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    uint32_t uiData = 0;
	No_or_Bad_CAN_Data = 0;

	if (pMsg->msg_length < 2)
	{
		SetDebugMessage("FF1A RS232_CALFAULT: Not enough data. Bytes received: %u", pMsg->msg_length);
		return;
	}
	uiData = (static_cast<uint32_t>(pMsg->msg_content[1]) & 0x00FF);

	uint32_t currentValue = 0;
	bool hascurrent =   Database_Get_CurrentValue(db_VECTOR_cal_fault_error, &currentValue);

	DBVAR_T dbValue;
	dbValue.ui = static_cast<uint32_t>(uiData);

	bool updateSuccess = Database_Set_Conditional(
		db_VECTOR_cal_fault_error,
		&dbValue,
		DBVARTYPE_UNSIGNED_INT,
		DBSOURCE_NMEA0183
	);
	if (updateSuccess)
	{
		if (hascurrent && (dbValue.flt != currentValue))
		{
			AlarmMuteFlag = 0;
			uiUnacknowledged_PropulsionSystemFault = 1;
		}
	}
}
