//------------------------------------------------------------------------------
//  TITLE :-  Database.h
//  AUTHOR :
//  DATE :
//  DESCRIPTION :  Database declarations
//
//------------------------------------------------------------------------------
#ifndef DATABASE_H
#define DATABASE_H
#include "type.h"

typedef enum
{
	DB_INSTANCE_1 = 0,
	DB_INSTANCE_2,
	DB_INSTANCE_3,
	DB_INSTANCE_4,
	//////////////////////////////////////////////////////////////////////////
	// Used for checking is "Valid" so must be LAST!
	DB_INSTANCE_INVALID,
} DB_INSTANCE_T;

// Data source
typedef enum
{
	DBSOURCE_NONE = 0,
	DBSOURCE_LOCAL,
	DBSOURCE_CAN,
    DBSOURCE_NMEA0183,
	//////////////////////////////////////////////////////////////////////////
	// Used for checking is "Valid" so must be LAST!
	DBSOURCE_INVALID,
} DBSOURCE_T;

// Unit types for parameters in database
typedef enum
{
    DBUNITS_PRESSURE = 0,
	DBUNITS_NONE,
    DBUNITS_END
} DBUNITS_T;

// This Enum is used for the database to control its size as well as to provide translations for the database descriptor's
typedef enum
{
	//NEW VECTOR DATABASE PARAMETERS first 19
	db_VECTOR_port_nozzle,
	db_VECTOR_stbd_nozzle,
	db_VECTOR_port_bucket,
	db_VECTOR_stbd_bucket,
	db_VECTOR_port_trimtab,
	db_VECTOR_stbd_trimtab,
	//senssors i7
	db_VECTOR_signal_fault_error,
	//nfu i8
	db_VECTOR_nfu_fault_error,
	//sta1 i9
	db_VECTOR_STA1_fault_error,
	//sta2 i10
	db_VECTOR_STA2_fault_error,
	//sta3 i11
	db_VECTOR_STA3_fault_error,
	//autocal faults and trimtab faults i12
	db_VECTOR_cal_fault_error,
	//interlock faults i13
	db_VECTOR_interlock_fault_error,
	//Ondication Configuration i14
	db_VECTOR_I14_INDICConfig,
	//vcican Enable RS232 i15
	db_VECTOR_I15_doEnableRS232,
	// autocalSTATUS i16
	db_VECTOR_I16_autocalSTATUS,
	//vcican faults i17
	db_VECTOR_VCICAN_fault_error,
	// VCIstatus i18
	db_VECTOR_VCIstatus,
 	// gENERALaLARM i19
	db_VECTOR_GAL_fault_error, 
	//PARAMETERS FOR CCIM DATA
	db_VECTOR_CCIM_AIN1,
	db_VECTOR_CCIM_AIN2,
	db_VECTOR_CCIM_AIN3,
	db_VECTOR_CCIM_AIN4,
	db_VECTOR_CCIM_AIN5,
	db_VECTOR_CCIM_AIN6,
	//////////////////////////////////////////////////////////////////////////
	// This must always be the last entry
	DATABASEINDEX_MAX,
	// This is used on the Screens and checked before accessing the DB so it knows if the item needs drawing or not.
	ITEM_NOT_SHOWN = DATABASEINDEX_MAX
} DATABASEINDEX_T;
//	enum used to go with DBVAR_T so we know the current type
typedef enum
{
	DBVARTYPE_UNSIGNED_CHAR_ARRAY_FOUR_ELEMENT = 0,
	DBVARTYPE_UNSIGNED_INT,
	DBVARTYPE_INT,
	DBVARTYPE_UNSIGNED_LONG,
	DBVARTYPE_LONG,
	DBVARTYPE_FLOAT,
	DBVARTYPE_POINTER
} DBVARTYPE_T;
//	Variable Union Structure, used by the database to hold data
typedef union
{
    uint8_t				array[4];
    uint32_t			ui;
    int32_t				i;
    uint32_t			ulg;
    int32_t				lg;
    float				flt;
    const uint8_t	*	ptr;
} DBVAR_T;
// Database element definition
typedef struct
{
	DBVAR_T					Data;					// displayed data
	DBVAR_T					PreviousData;			// displayed data
	DBVARTYPE_T				DataType;				// tells you how the data is stored
	DBSOURCE_T				OwnerSource;			// DB Source that set the data

	CAN_PORTS_T				canPort;				// Shows 0 or 1 depending on the can port. non can data should show CAN_MAX_PORTS
	uint8_t					sourceAddress;			// This is the Source Address of the device the data came from. for non-can data, it is 255 as that is invalid in CAN.
	uint8_t					nmeaInstance;			// This is the NMEA2000 "Instance" and is used primarily to pick the "engine" but is saved just in case.
	
	uint32_t				Timer;					// 1ms resolution down counter
	uint32_t				TimerDefault;			// reload value for timer
	DBUNITS_T				UnitType;				// DB_UNITS_T Type of Units
	uint32_t				MessageRxTime;			// get_uptime_milliseconds() when the message was received
	uint32_t				PreviousMessageRxTime;	// get_uptime_milliseconds() when the message was received
	uint32_t				DatabaseIndex;			// a Database Index so when the element is on its own, we know what it is.
}  DBELEMENT_T;

void DataBase_Init(void);
BOOL DataBase_IsItemValid(int DataBaseIndex, int InstanceIndex);
BOOL DataBase_Get(DBELEMENT_T* p_DB_Element, int DataBaseIndex, int InstanceIndex);
BOOL Database_Set_CAN(int DataBaseIndex, const DBVAR_T* pData, DBVARTYPE_T DataType, CAN_PORTS_T canPort, uint8_t nmeaInstanceOrSequenceID, uint8_t sourceAddress);
BOOL Database_Set_NMEA0183(int DataBaseIndex, const DBVAR_T* pData, DBVARTYPE_T DataType, uint8_t engineIndex);
bool Database_Get_CurrentValue(DATABASEINDEX_T dbIndex, uint32_t* pValue);
// --- The new function prototype ---
BOOL Database_Set_Conditional(int dbIndex,const DBVAR_T* pData,DBVARTYPE_T dataType,DBSOURCE_T source);
BOOL Database_GetIndexFromString(const char* String, uint32_t* DBIndex);
int Database_GetItemDescription(char* destination, size_t destinationSize, int DataBaseIndex);
void Database_SetItemDescription(int DataBaseIndex, const char* pDescription, uint32_t descriptionLength);
DBUNITS_T DatabaseGetUnitType(uint32_t DBIndex);
// Add the following declaration
bool Database_TimerRefresh(DATABASEINDEX_T dbIndex, unsigned char engineNum, DBSOURCE_T source);


#endif	
