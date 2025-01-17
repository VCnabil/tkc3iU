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
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define TIMER_NETWORK_PRESET           100   /* wait 10s before displaying LOST CONNECTION   */
#define NUM_FAULT_ENTRIES 32
#define FAULTS_PER_PAGE 6
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

#define FAULT_DESCRIPTION_MAX_LENGTH 50

#define DEBUG_LOG_MAX_MESSAGES 10
#define DEBUG_MSG_MAX_LENGTH 256

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
 

// Global debug buffer
extern char gDebugMsg[DEBUG_MSG_MAX_LENGTH];

// Function to set the debug message
void SetDebugMessage(const char* format, ...);



void AddDebugMessage(const char* format, ...);
const char* GetDebugLogMessage(int index);

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

//These are assigned values based on the fault codes (recieved via RS232)
extern int PTab_sigFault, STab_sigFault, PNoz_sigFault, SNoz_sigFault, PBkt_sigFault, SBkt_sigFault;
extern int PTab_nfuFault, STab_nfuFault, PNoz_nfuFault, SNoz_nfuFault, PBkt_nfuFault, SBkt_nfuFault;
extern int JoyX1_Fault, JoyY1_Fault, PLev1_Fault, SLev1_Fault, Helm1_Fault, Idle1_Fault;
extern int JoyX2_Fault, JoyY2_Fault, PLev2_Fault, SLev2_Fault, Helm2_Fault, Idle2_Fault;
extern int JoyX3_Fault, JoyY3_Fault, PLev3_Fault, SLev3_Fault, Helm3_Fault, Idle3_Fault;
extern int Cal_Fault, Roll1_Fault, Trim1_Fault, Inbd_Fault, Otbd_Fault, AP_Fault, clutchDiseng_Fault, generalDock_Fault, Roll2_Fault, Trim2_Fault;
extern int Number_Faults, Number_Faults_PropSys, Number_Faults_CAN, Number_Faults_CentralAlarmSystem;
extern int RCV_CANFault, VCI_CAN_Fault, ClutchST1_CAN_Fault, ClutchST2_CAN_Fault;

extern   int Central_Alarm_01, Central_Alarm_02, Central_Alarm_03, Central_Alarm_04, Central_Alarm_05;
extern   int Central_Alarm_06, Central_Alarm_07, Central_Alarm_08, Central_Alarm_09, Central_Alarm_10;
extern   int Central_Alarm_11, Central_Alarm_12, Central_Alarm_13, Central_Alarm_14, Central_Alarm_15;
extern   int Central_Alarm_16, Central_Alarm_17, Central_Alarm_18, Central_Alarm_19, Central_Alarm_20;

extern unsigned int* centralAlarmArray[];

extern int No_or_Bad_Data, No_or_Bad_CAN_Data, No_or_Bad_CAN_Data_CentralAlarmSys, CCIM_Fault, CCIM_Fault_Counter;
extern int Serial_Fault, CAN_Fault, ControlSystem_Fault, Faults_on_Screen, MS_CAN_Fault, CentralAlarmSys_Fault, CentralAlarmSys_CAN_Fault;
extern int InMainScreen, InFaultScreen, AlarmMuteFlag, AlarmMuteFlag_CentralAlarm, StaticAlarmDisplayed, clearonce;
extern int SCFaultCount, CSFaultCount, CANFaultCount;
extern unsigned int uiUnacknowledged_PropulsionSystemFault;
extern unsigned int vci_status, autopilot, dk_tr_mode;  // these variables are used to display the status text on the screen
  

//allows wing stations to read the rs232->can data instead of the CCIM can data.
extern int PORTNOZ_rs232counter, STBDNOZ_rs232counter, PORTBKT_rs232counter, STBDBKT_rs232counter;
extern int PORTTAB_rs232counter, STBDTAB_rs232counter;

//for calibration
extern int uiRaw_PB, uiRaw_SB, uiRaw_PN, uiRaw_SN, uiRaw_PT, uiRaw_ST;
extern int CAL_FLAG;

extern int PB_MAX_TEMP, PB_MIN_TEMP, PN_MAX_TEMP, PN_MIN_TEMP;
extern int SB_MAX_TEMP, SB_MIN_TEMP, SN_MAX_TEMP, SN_MIN_TEMP;
extern int PT_MAX_TEMP, PT_MIN_TEMP, ST_MAX_TEMP, ST_MIN_TEMP;
extern int PB_NEUTRAL_THRUST_TEMP, SB_NEUTRAL_THRUST_TEMP;

extern unsigned int VCI_soundSiren;

#define     SETBIT(i, n)   ((i) |= (1L << (n)))
#define     GETBIT(i, n)   ( ((i) & (1L << (n))) >> (n) )
#define     CLRBIT(i, n)   ((i) &= ~(1L << (n)))
#define     TOGGLEBIT(i, n)    ((i) ^= (1L << (n)))

// Vector function to decode CAN faults
  //******************************************************************************
  //|                            FAULT DECODING                                  |
  //******************************************************************************
void decode_VCI_CAN_Fault();
void setFaultFlag(int status, int* flt);

void Decode_SignalFault(void);
void Decode_NfuFault(void);
void Decode_STA1Fault(void);
void Decode_STA2Fault(void);
void Decode_STA3Fault(void);
void Decode_CalFault(void);
extern unsigned int dockMode_delayCntr;
void Decode_InterlockFault(void);

const char* GetStationAndComModeString(void);

// Fault state for the faults.
enum { STATE0, STATE1, STATE2, STATE3 };
#endif // __VCINC_H__


 