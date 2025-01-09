//------------------------------------------------------------------------------
//  TITLE :        	VCInc.h
//  DESCRIPTION :	VECTOR FUNCTIONS AND VARIABLES
//  AUTHOR:			Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#ifndef __VCINC_H__
#define __VCINC_H__

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

#endif // __VCINC_H__



/*

#define CR "\r"
#define LF "\n"
//fault decoding
void Decode_SignalFault(void); //assigns feedback signal fault variables
void Decode_NfuFault(void);  //assigns non-follow-up fault variables
void Decode_STA1Fault(void); //assigns STA1 command fault variables
void Decode_STA2Fault(void); //assigns STA2 command fault variables
void Decode_STA3Fault(void); //assigns STA3 command fault vairables
void Decode_CalFault(void);  //assigns Calibration and roll/trim command fault variables
void Decode_InterlockFault(void);  //assigns dockmode clutch interlock fault variables
void Decode_VCI_MISC(void); // assigns MIsc fault and status variables


//VARIABLES----------------------------------------------------------------
extern int index_1;

//Fault Variables

//These are assigned values based on the fault codes (recieved via RS232)
//in function.c in the Decode_xxxFault functions.
extern int PTab_sigFault, STab_sigFault, PNoz_sigFault, SNoz_sigFault, PBkt_sigFault, SBkt_sigFault;
extern int PTab_nfuFault, STab_nfuFault, PNoz_nfuFault, SNoz_nfuFault, PBkt_nfuFault, SBkt_nfuFault;
extern int JoyX1_Fault, JoyY1_Fault, PLev1_Fault, SLev1_Fault, Helm1_Fault, Idle1_Fault;
extern int JoyX2_Fault, JoyY2_Fault, PLev2_Fault, SLev2_Fault, Helm2_Fault, Idle2_Fault;
extern int JoyX3_Fault, JoyY3_Fault, PLev3_Fault, SLev3_Fault, Helm3_Fault, Idle3_Fault;
extern int Cal_Fault, Roll1_Fault, Trim1_Fault, Inbd_Fault, Otbd_Fault, AP_Fault, clutchDiseng_Fault, generalDock_Fault, Roll2_Fault, Trim2_Fault;
extern int Number_Faults, Number_Faults_PropSys, Number_Faults_CAN, Number_Faults_CentralAlarmSystem;
extern int RCV_CANFault, VCI_CAN_Fault, ClutchST1_CAN_Fault, ClutchST2_CAN_Fault;
extern int ST1_module_Fault, ST2_module_Fault, ST3_module_Fault;
//used for indication configuration based on parameter recieved via RS232
extern int B1_xpos, B2_xpos, N1_xpos, N2_xpos, T1_xpos, T2_xpos;
extern int N1_xincr, N2_xincr, N1_xsize, N2_xsize, DoubleBarFlag;
extern int B1_present, B2_present, N1_present, N2_present, T1_present, T2_present;

// RS232 counters for various components
extern int PORTNOZ_rs232counter, STBDNOZ_rs232counter;
extern int PORTBKT_rs232counter, STBDBKT_rs232counter;
extern int PORTTAB_rs232counter, STBDTAB_rs232counter;

//for RS232 Transmission from display to control box
extern int Enable_RS232_Transmission, Local_Enable_RS232_Transmission;

//for enabling / disabling IntSteer via the RS232 pot (operator sets in the system options screen)
extern int Intsteer_Enable;
//for initiating and ending a system (hydraulic) autocal from the system calibration screen
extern int Autocal_CMD;
extern int Autocal_Status; //status of the autocal, transmitted from the controller to the cantrak
extern int Set1_Set2_Mode, Position_Capture_Request;

//character arrays for rs232 transmission
extern char Intsteer[5];

//Array for holding and processing password (to enter calibration screen)
extern int Password_Array[6];
*/