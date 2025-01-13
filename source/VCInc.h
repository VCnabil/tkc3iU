//------------------------------------------------------------------------------
//  TITLE :        	VCInc.h
//  DESCRIPTION :	VECTOR FUNCTIONS AND VARIABLES
//  AUTHOR:			Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#ifndef __VCINC_H__
#define __VCINC_H__
#include "syslib.h"   // or whichever file declares MUTEXHANDLE_T
#include <vector>
#include <string>
#define NUM_FAULT_ENTRIES 32
#define DATABASE_MAX_VECTORVARS 18 //the first 16 variables are Vectors Control inc. variables
#define MAX_PROPN_FAULTS_DISP     11 // maximum number of faults displayed per screen 
#define MAX_SYSTEM_PARAMETERS 8  //defines number of system parameters in the system options screen
#define rs232_mode   1           //indication data received via rs232 (fault data is always)
#define CANbus_mode  2           //indication data received via CAN, no GPSI
#define CANbus_GPSI_mode  3      //indication data received via CAN, GPSI present
#define main_station 1
#define wing_station 2
#define normal 1                 //for nozzle mapping; 450 = steer right
#define flipped 2                //for nozzle mapping; 450 = steer left
#define comm_mode_4     4
#define comm_mode_5     5
//1 bucket, 1 nozzle (single jet)
#define idc1_1buk1noz 1
//2 buckets, 2 nozzles
#define idc2_2buk2noz 2
//2 buckets, 1 nozzle (stbd nozzle because of linked steering)
#define idc3_2buk1noz 3
//2 buckets, 2 nozzles, 2 trimtab/interceptors
#define idc4_2buk2noz2tab 4
//2 buckets, 1 nozzle (linked steering), 2 trimtab/interceptors
#define idc5_2buk1noz2tab 5
//2 buckets, 2 nozzles, graphics have graduations (YF Special)
#define idc6_2buk2noz_grad 6

#define NMEA_HEADER "$PVCC"      //NMEA header for serial xmission

extern int Intsteer_Enable;
//Enable_RS232_Transmission is set from reading the i15 from serial received line . if it is 1 , Enable_RS232_Transmission = 0; if it is 0, Enable_RS232_Transmission = 1 that s if we are the main statoin
extern int Enable_RS232_Transmission;
//Local_Enable_RS232_Transmission is set SysOpts screen .   
extern int Local_Enable_RS232_Transmission ;

typedef enum
{
    SYSOPT_INDEX_COMMS_MODE = 0,
    SYSOPT_INDEX_STATION_TYPE,
    SYSOPT_INDEX_DATA_MODE,
    SYSOPT_INDEX_NOZZLEMAP_FLIP,
    SYSOPT_INDEX_BUCKETMAP_FLIP,
    SYSOPT_INDEX_TABMAP_FLIP,
    SYSOPT_INDEX_XMIT232,
    SYSOPT_INDEX_INSTEER,
    SYSOPT_INDEX_MAX
} SYSOPT_INDEX_E;

// Shared string for database elements
extern std::vector<std::string> dbElementStrings;


extern int gPVCICallCount;        // Just the declaration
extern int gJ1939CallCount;   // Declaration of J1939 call count
extern MUTEXHANDLE_T gPVCICountMutex;
#define DEBUG_MSG_MAX_LENGTH 256

// Global debug buffer
extern char gDebugMsg[DEBUG_MSG_MAX_LENGTH];

// Function to set the debug message
void SetDebugMessage(const char* format, ...);



#define FAULT_DESCRIPTION_MAX_LENGTH 50

typedef enum
{
    STA1 = 0,
    STA2,
    STA3,
    NFU,
    SFE,
    CFE,
    GAL
} FAULT_CODE;

typedef struct
{
    FAULT_CODE     FaultCode;
    int            Bit;
    bool       isAcked;   // <--- new field
    char           Description[FAULT_DESCRIPTION_MAX_LENGTH];
} FAULTS_DB;

extern FAULTS_DB m_FAULTS_DB[];


#endif // __VCINC_H__


 