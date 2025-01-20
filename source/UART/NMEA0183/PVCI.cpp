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
    uint32_t i14 = 0, i15 = 0, i16 = 0, i17 = 0, i18 = 0; // Variables for specific fields
    uint32_t previousValues[NUM_FIELDS] = { 0 }; // Array to store previous values for comparison
    int actualFieldCount = SettingsGetCommsMode() == comm_mode_5 ? 18 : 17;

    for (int i = 0; i < actualFieldCount; i++) {
        if (!_NMEA0183_ExtractField(i + 1, pBuffer, field, sizeof(field))) {
            return -1; // Failed to extract a required field
        }

        int value = atoi((const char*)field);
        DBVAR_T dbData;
        dbData.ui = (uint32_t)value;

        // Update database
        Database_Set_Conditional(PVCIFieldToDBIndex[i], &dbData, DBVARTYPE_UNSIGNED_INT, DBSOURCE_NMEA0183);

        // Check alarm-related fields and reset flags if needed
        if ((i >= 6 && i <= 12) || i == 16) {
            if (previousValues[i] != dbData.ui) {
                AlarmMuteFlag = 0; // Reset alarm mute
                clearonce = 0;     // Reset one-time clear
                uiUnacknowledged_PropulsionSystemFault = 1; // Raise unacknowledged fault flag
            }

            // Update stored previous values
            previousValues[i] = dbData.ui;
        }

        // Assign specific field values
        if (i == 13) i14 = dbData.ui; // i14: INDICATION_CONFIG
        if (i == 14) i15 = dbData.ui; // i15: Stop Transmit Request
        if (i == 15) i16 = dbData.ui; // i16: Autocal Status
        if (i == 16) i17 = dbData.ui; // i17: CAN Fault
        if (i == 17) i18 = dbData.ui; // i18: VCI Status (only in comm_mode_5)
    }

    // Clear the fault flag if all alarm-related fields are zero
    if (previousValues[6] == 0 && previousValues[7] == 0 && previousValues[8] == 0 &&
        previousValues[9] == 0 && previousValues[10] == 0 && previousValues[11] == 0 &&
        previousValues[12] == 0) {
        uiUnacknowledged_PropulsionSystemFault = 0;
    }

    // Configure the indication display setup per the control box's request
    if (SettingsGetIndicationConfig() != i14) {
        SettingsSetIndicationConfig(i14);
    }

    // Process the "stop transmit request" parameter received from the control box
    Enable_RS232_Transmission = (i15 != 1);

    // Set the autocal status value
    Autocal_Status = i16;
    RCV_CANFault = i17;

    // Set VCI status if comms mode is 5
    if (SettingsGetCommsMode() == comm_mode_5) {
        vci_status = i18;
    }

    // Reset serial fault timer
    No_or_Bad_Data = 0;

    return 0;
}
 