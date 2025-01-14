//------------------------------------------------------------------------------
//  TITLE :        	VCIncShared.cpp 
//  DESCRIPTION :	For Global variables 
//  AUTHOR:			Nabil Lamriben 1/10/2025
//------------------------------------------------------------------------------
 #include "VCInc.h"
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

int No_or_Bad_Data = 0;
int No_or_Bad_CAN_Data = 0;
int No_or_Bad_CAN_Data_CentralAlarmSys = 0;
int CCIM_Fault = 0;
int CCIM_Fault_Counter = 0;

//for RS232-CAN message prioritizing over CCIM CAN messages.
int PORTNOZ_rs232counter, STBDNOZ_rs232counter, PORTBKT_rs232counter, STBDBKT_rs232counter;
int PORTTAB_rs232counter, STBDTAB_rs232counter;


//for indicator calibration
//unsigned int uiRaw_PB, uiRaw_SB, uiRaw_PN, uiRaw_SN; <--declared in can.c
int CAL_FLAG;
int PB_MAX_TEMP, PB_MIN_TEMP, PN_MAX_TEMP, PN_MIN_TEMP; //for calibration abort
int SB_MAX_TEMP, SB_MIN_TEMP, SN_MAX_TEMP, SN_MIN_TEMP; //for calibration abort
int PT_MAX_TEMP, PT_MIN_TEMP, ST_MAX_TEMP, ST_MIN_TEMP; //for calibration abort
int PB_NEUTRAL_THRUST_TEMP, SB_NEUTRAL_THRUST_TEMP;

// Extern declarations for Alarm Flags (assuming they are defined elsewhere)
  int AlarmMuteFlag;
  int uiUnacknowledged_PropulsionSystemFault;



  //******************************************************************************
  //|                            FAULT DECODING                                  |
  //******************************************************************************

  void setFaultFlag(int status, int* flt)
  {
	  //if (status) // status 1
	  //{
		 // if (*flt < STATE2)
		 // {
			//  *flt = STATE3;
			//  VCI_soundSiren = 1; // a global flag indicating a new alarm has come , needed to sound siren
		 // }
	  //}

	  //else   // status 0
	  //{
		 // if (*flt > STATE1)
		 // {
			//  *flt = STATE1;
		 // }
	  //}
  }



  void decode_VCI_CAN_Fault()
  {

	  setFaultFlag(GETBIT(RCV_CANFault, 0), &VCI_CAN_Fault);
	  setFaultFlag(GETBIT(RCV_CANFault, 1), &ClutchST1_CAN_Fault);
	  setFaultFlag(GETBIT(RCV_CANFault, 2), &ClutchST2_CAN_Fault);

  }


  int RCV_CANFault = 0;
  int VCI_CAN_Fault = 0;
  int ClutchST1_CAN_Fault = 0;
  int ClutchST2_CAN_Fault = 0;