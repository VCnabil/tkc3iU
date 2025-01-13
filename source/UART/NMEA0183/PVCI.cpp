//------------------------------------------------------------------------------
//  TITLE :        	PVCI.cpp
//  DESCRIPTION :	For Processing the  PVCI serial string and its variations
//  AUTHOR:			Nabil Lamriben 1/10/2025
//------------------------------------------------------------------------------
#include "project.h"
#include "PVCI.h"
#include "VCInc.h"
#include <cstdlib>
 

    //------------------------------------------------------------------------------
    // $PVCI: Port Nozzle, Starboard Nozzle, Port Bucket, Starboard Bucket, Port Trimtab, Starboard Trimtab
int NMEA0183_ProcessPVCI(char* pBuffer)
{
   

    if (!pBuffer || pBuffer[0] != '$') {
        return -1; // invalid
    }

    const int NUM_FIELDS = 18;
    unsigned char field[64];

    // Example DB indexes for the first six fields
    static DATABASEINDEX_T PVCIFieldToDBIndex[NUM_FIELDS] = {
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

    };

    int ActualFullNumberOfField = 17; 
    //if comms mod =5 then ActualFullNumberOfField =18
    if (SettingsGetCommsMode() == comm_mode_5)
	{
		ActualFullNumberOfField = 18;
	}

    for (int i = 0; i < ActualFullNumberOfField; i++)
    {
        // i+1 => the (i+1)th comma-delimited field
        if (!_NMEA0183_ExtractField(i + 1, pBuffer, field, sizeof(field)))
        {
            // If we fail to get the field, break or return
            break;
        }
        int value = atoi((const char*)field);

        // Store in the database
        DBVAR_T dbData;
        dbData.ui = (uint32_t)value;
       //  Database_Set_NMEA0183(PVCIFieldToDBIndex[i], &dbData, DBVARTYPE_UNSIGNED_INT, 0);
        Database_Set_Conditional(
            PVCIFieldToDBIndex[i],   // which DB index to write
            &dbData,                 // pointer to the DBVAR_T data
            DBVARTYPE_UNSIGNED_INT,  // the type (so we interpret dbData.ui)
            DBSOURCE_NMEA0183        // source is RS232
        );
        
    }

    return 0;
}

 