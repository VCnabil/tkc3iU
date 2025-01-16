//------------------------------------------------------------------------------
//  TITLE :        	VCIncShared.cpp 
//  DESCRIPTION :	For Global variables 
//  AUTHOR:			Nabil Lamriben 1/10/2025
//------------------------------------------------------------------------------
 #include "VCInc.h"
#include "project.h"
#include <stdarg.h>
#include <stdio.h>

// Provide the actual definition (storage) for these globals:
int gPVCICallCount = 0;
int gJ1939CallCount = 0;      // Definition with initial value = 0


// Example: Initialize shared vector
std::vector<std::string> dbElementStrings(DATABASE_MAX_VECTORVARS, "Unknown");

char gDebugMsg[DEBUG_MSG_MAX_LENGTH] = { 0 };

// Helper function to format debug messages
void SetDebugMessage(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(gDebugMsg, DEBUG_MSG_MAX_LENGTH, format, args);
    va_end(args);
}
static char debugLog[DEBUG_LOG_MAX_MESSAGES][DEBUG_MSG_MAX_LENGTH];
static int debugLogIndex = 0;

void AddDebugMessage(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	// Format the message and store it in the log
	vsnprintf(debugLog[debugLogIndex], DEBUG_MSG_MAX_LENGTH, format, args);
	va_end(args);

	// Increment the log index, wrapping around
	debugLogIndex = (debugLogIndex + 1) % DEBUG_LOG_MAX_MESSAGES;
}

const char* GetDebugLogMessage(int index)
{
	// Get the message at the specified index
	int actualIndex = (debugLogIndex + index) % DEBUG_LOG_MAX_MESSAGES;
	return debugLog[actualIndex];
}

// Provide the actual storage definition for m_FAULTS_DB[]
extern FAULTS_DB m_FAULTS_DB[] = {

 { STA1, 0, false, "Idle Knob" },
    { STA1, 1, false, "Helm / Tiller" },
    { STA1, 2, false, "Stbd Lever" },
    { STA1, 3, false, "Port Lever" },
    { STA1, 4, false, "Joystick Y-axis" },
    { STA1, 5, false, "Joystick X-axis" },

    { STA2, 0, false, "Idle Knob" },
	{ STA2, 1, false, "Helm / Tiller" },
	{ STA2, 2, false, "Stbd Lever" },
	{ STA2, 3, false, "Port Lever" },
	{ STA2, 4, false, "Joystick Y-axis" },
	{ STA2, 5, false, "Joystick X-axis" },

	{ STA3, 0, false, "Idle Knob" },
	{ STA3, 1, false, "Helm / Tiller" },
	{ STA3, 2, false, "Stbd Lever" },
	{ STA3, 3, false, "Port Lever" },
	{ STA3, 4, false, "Joystick Y-axis" },
	{ STA3, 5, false, "Joystick X-axis" },

	{ NFU, 0, false, "Stbd Bucket NFU" },
	{ NFU, 1, false, "Port Bucket NFU" },
	{ NFU, 2, false, "Stbd Nozzle NFU" },
	{ NFU, 3, false, "Port Nozzle NFU" },
	{ NFU, 4, false, "Stbd Trim Tab / INT NFU" },
	{ NFU, 5, false, "Port Trim Tab / INT NFU" },

	{ SFE, 0, false, "Stbd Bucket feedback" },
	{ SFE, 1, false, "Port Bucket feedback" },
	{ SFE, 2, false, "Stbd Nozzle feedback" },
	{ SFE, 3, false, "Port Nozzle feedback" },
	{ SFE, 4, false, "Stbd Trim Tab / INT feedback" },
	{ SFE, 5, false, "Port Trim Tab / INT feedback" },

	{ CFE, 0, false, "Calibration Fault" },
	{ GAL, 0, false, "General Alarm" }
};


// These are new variables to hold the status of Central alarm faults. These will replace the database elements
// These will also have 4 states similar to propn alarms described above
// These are introduced to reduce the overhead caused by using  the database method
  int Central_Alarm_01, Central_Alarm_02, Central_Alarm_03, Central_Alarm_04, Central_Alarm_05;
  int Central_Alarm_06, Central_Alarm_07, Central_Alarm_08, Central_Alarm_09, Central_Alarm_10;
  int Central_Alarm_11, Central_Alarm_12, Central_Alarm_13, Central_Alarm_14, Central_Alarm_15;
  int Central_Alarm_16, Central_Alarm_17, Central_Alarm_18, Central_Alarm_19, Central_Alarm_20;

//Fault Variables
// The Fault variables will now hold Fault state information, the larger number indicates higher weightage to the fault state
// STATE0  - no fault condition: and nothing to show on screen
// STATE1  - passive fault : a fault appeared and then cleared, this state is shown as a Inverse display on the screen
// STATE2  - Ack Active fault : An acknowledged active fault, An active fault is present and it has been acknowledge, this state is shown as regular text
// STATE3  - ACTIVE FAULT : an Active UN-ack fault exists, this state is shown by blinking text.
int PTab_sigFault, STab_sigFault, PNoz_sigFault, SNoz_sigFault, PBkt_sigFault, SBkt_sigFault;
int PTab_nfuFault, STab_nfuFault, PNoz_nfuFault, SNoz_nfuFault, PBkt_nfuFault, SBkt_nfuFault;
int JoyX1_Fault, JoyY1_Fault, PLev1_Fault, SLev1_Fault, Helm1_Fault, Idle1_Fault;
int JoyX2_Fault, JoyY2_Fault, PLev2_Fault, SLev2_Fault, Helm2_Fault, Idle2_Fault;
int JoyX3_Fault, JoyY3_Fault, PLev3_Fault, SLev3_Fault, Helm3_Fault, Idle3_Fault;
int Cal_Fault, Roll1_Fault, Trim1_Fault, Inbd_Fault, Otbd_Fault, AP_Fault, clutchDiseng_Fault, generalDock_Fault, Roll2_Fault, Trim2_Fault;
int Number_Faults, Number_Faults_PropSys, Number_Faults_CAN, Number_Faults_CentralAlarmSystem;
int RCV_CANFault = 0;
int VCI_CAN_Fault = 0;
int ClutchST1_CAN_Fault = 0;
int ClutchST2_CAN_Fault = 0;

//Alarm detection and display variables
int No_or_Bad_Data = 0;
int No_or_Bad_CAN_Data = 0;
int No_or_Bad_CAN_Data_CentralAlarmSys = 0;
int CCIM_Fault = 0;
int CCIM_Fault_Counter = 0;
int Serial_Fault, CAN_Fault, ControlSystem_Fault, Faults_on_Screen, MS_CAN_Fault, CentralAlarmSys_Fault, CentralAlarmSys_CAN_Fault; //MS = Main Station
int Serial_Fault_State; 
int InMainScreen, InFaultScreen, AlarmMuteFlag, AlarmMuteFlag_CentralAlarm, StaticAlarmDisplayed, clearonce;
int SCFaultCount, CSFaultCount, CANFaultCount;

//for RS232-CAN message prioritizing over CCIM CAN messages.
int PORTNOZ_rs232counter, STBDNOZ_rs232counter, PORTBKT_rs232counter, STBDBKT_rs232counter;
int PORTTAB_rs232counter, STBDTAB_rs232counter;


//for indicator calibration int uiRaw_PB, uiRaw_SB, uiRaw_PN, uiRaw_SN;// <--declared in can.c
int uiRaw_PB, uiRaw_SB, uiRaw_PN, uiRaw_SN;
int CAL_FLAG=0;
int PB_MAX_TEMP, PB_MIN_TEMP, PN_MAX_TEMP, PN_MIN_TEMP; //for calibration abort
int SB_MAX_TEMP, SB_MIN_TEMP, SN_MAX_TEMP, SN_MIN_TEMP; //for calibration abort
int PT_MAX_TEMP, PT_MIN_TEMP, ST_MAX_TEMP, ST_MIN_TEMP; //for calibration abort
int PB_NEUTRAL_THRUST_TEMP, SB_NEUTRAL_THRUST_TEMP;

// Extern declarations for Alarm Flags (assuming they are defined elsewhere)
  unsigned int uiUnacknowledged_PropulsionSystemFault;
  unsigned int vci_status, autopilot, dk_tr_mode;

  unsigned int VCI_soundSiren; // a global flag indicating a new alarm has come , needed to sound siren


  //******************************************************************************
  //|                            FAULT DECODING                                  |
  //******************************************************************************

  void setFaultFlag(int status, int* flt)
  {
	  if (status) // status 1
	  {
		  if (*flt < STATE2)
		  {
			  *flt = STATE3;
			  VCI_soundSiren = 1; // a global flag indicating a new alarm has come , needed to sound siren
		  }
	  }

	  else   // status 0
	  {
		  if (*flt > STATE1)
		  {
			  *flt = STATE1;
		  }
	  }
  }


  // Static buffer to hold the formatted string
  static char stationComModeString[128] = { 0 };

  const char* GetStationAndComModeString(void)
  {
      // Retrieve the StationType, DataMode, and ComMode
      uint8_t stationType = SettingsGetStationType();
      uint8_t data_mode = SettingsGetDataMode();
      uint8_t comMode = SettingsGetCommsMode();

      // Convert StationType to string
      const char* stationTypeStr;
      switch (stationType)
      {
      case main_station:
          stationTypeStr = "main";
          break;
      case wing_station:
          stationTypeStr = "wing";
          break;
      default:
          stationTypeStr = "??";
          break;
      }

      // Convert DataMode to string
      const char* dataModeStr;
      switch (data_mode)
      {
      case rs232_mode:
          dataModeStr = "rs232";
          break;
      case CANbus_mode:
          dataModeStr = "CAN";
          break;
      case CANbus_GPSI_mode:
          dataModeStr = "GPSI";
          break;
      default:
          dataModeStr = "??";
          break;
      }

      // Convert ComMode to string
      const char* comModeStr;
      switch (comMode)
      {
      case comm_mode_4:
          comModeStr = "4";
          break;
      case comm_mode_5:
          comModeStr = "5";
          break;
      default:
          comModeStr = "??";
          break;
      }

      // Format the string
      snprintf(stationComModeString, sizeof(stationComModeString),
          "STA: %s, DM: %s, CM: %s", stationTypeStr, dataModeStr, comModeStr);

      return stationComModeString;
  }

  void decode_VCI_CAN_Fault()
  {
	  setFaultFlag(GETBIT(RCV_CANFault, 0), &VCI_CAN_Fault);
	  setFaultFlag(GETBIT(RCV_CANFault, 1), &ClutchST1_CAN_Fault);
	  setFaultFlag(GETBIT(RCV_CANFault, 2), &ClutchST2_CAN_Fault);

  }

