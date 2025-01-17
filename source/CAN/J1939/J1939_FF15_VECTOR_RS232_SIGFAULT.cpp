#include "project.h"
 
void J1939_FF15_VECTOR_RS232_SIGFAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg)
{
    uint32_t uiData = 0;
	No_or_Bad_CAN_Data = 0;
	if (pMsg->msg_length < 1)
	{
		SetDebugMessage("FF15 RS232_SIGFAULT: Not enough data. Bytes received: %u", pMsg->msg_length);
		return;
	}
	//extract data (it's two bytes of data because the A to D in the CCIM is 10-bit)
	uiData = static_cast<uint32_t>(pMsg->msg_content[0]);
	uint32_t currentValue = 0;
	bool hascurrent = Database_Get_CurrentValue(db_VECTOR_signal_fault_error, &currentValue);
	DBVAR_T dbValue;
	dbValue.ui = static_cast<uint32_t>(uiData);
	bool updateSuccess = Database_Set_Conditional(
		db_VECTOR_signal_fault_error,
		&dbValue,
		DBVARTYPE_UNSIGNED_INT,
		DBSOURCE_CAN
	);
	if (updateSuccess)
	{
		if (hascurrent && (dbValue.ui != currentValue))
		{
			AlarmMuteFlag = 0;
			uiUnacknowledged_PropulsionSystemFault = 1;
		}
	}
}
