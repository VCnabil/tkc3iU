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

int Autocal_Status = 0;
int Autocal_CMD=0;
int Set1_Set2_Mode = 0;
int Position_Capture_Request=0;

int Intsteer_Enable = 0;
int Enable_RS232_Transmission = 0;
int Local_Enable_RS232_Transmission = 0;
// These are new variables to hold the status of Central alarm faults. These will replace the database elements
// These will also have 4 states similar to propn alarms described above
// These are introduced to reduce the overhead caused by using  the database method
  int Central_Alarm_01, Central_Alarm_02, Central_Alarm_03, Central_Alarm_04, Central_Alarm_05;
  int Central_Alarm_06, Central_Alarm_07, Central_Alarm_08, Central_Alarm_09, Central_Alarm_10;
  int Central_Alarm_11, Central_Alarm_12, Central_Alarm_13, Central_Alarm_14, Central_Alarm_15;
 int Central_Alarm_16, Central_Alarm_17, Central_Alarm_18, Central_Alarm_19, Central_Alarm_20;
   int* centralAlarmArray[NUMBER_OF_CENTRAL_ALARMS];
   int* propnFaultArray[NUMBER_0F_PROPN_FAULTS];

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
int Serial_Fault_State=0; 
int InMainScreen, InFaultScreen, AlarmMuteFlag, AlarmMuteFlag_CentralAlarm, StaticAlarmDisplayed, clearonce;
int SCFaultCount, CSFaultCount, CANFaultCount;

//for RS232-CAN message prioritizing over CCIM CAN messages.
int PORTNOZ_rs232counter, STBDNOZ_rs232counter, PORTBKT_rs232counter, STBDBKT_rs232counter;
int PORTTAB_rs232counter, STBDTAB_rs232counter;
int RS232_XMIT_COUNTER = 0;

// indication display variables for applying hysteresis to display bar graphs (stacks)
int bars_prev_PORT_BUCKET, bars_prev_PORT_NOZZLE, bars_prev_PORT_TAB;
int bars_prev_STBD_BUCKET, bars_prev_STBD_NOZZLE, bars_prev_STBD_TAB;
int PB_dir, PN_dir, SA_dir, PT_dir, SB_dir, SN_dir, ST_dir;
int STACK_HALF, stack_temp;
int indexI, stack_value, x_pos, y_pos, solid_bars, empty_bars;
 
int uiRaw_PB, uiRaw_SB, uiRaw_PN, uiRaw_SN, uiRaw_PT, uiRaw_ST;
int CAL_FLAG=0;
int PB_MAX_TEMP, PB_MIN_TEMP, PN_MAX_TEMP, PN_MIN_TEMP; //for calibration abort
int SB_MAX_TEMP, SB_MIN_TEMP, SN_MAX_TEMP, SN_MIN_TEMP; //for calibration abort
int PT_MAX_TEMP, PT_MIN_TEMP, ST_MAX_TEMP, ST_MIN_TEMP; //for calibration abort
int PB_NEUTRAL_THRUST_TEMP, SB_NEUTRAL_THRUST_TEMP;

// Extern declarations for Alarm Flags (assuming they are defined elsewhere)
  unsigned int uiUnacknowledged_PropulsionSystemFault;
  unsigned int vci_status, autopilot, dk_tr_mode;

  unsigned int VCI_soundSiren; // a global flag indicating a new alarm has come , needed to sound siren

  unsigned int dockMode_delayCntr;
  //******************************************************************************
  //|                            FAULT DECODING                                  |
  //******************************************************************************

  void setFaultFlag(int status, int* faultState)
  {
      if (status) // Fault is active
      {
          if (*faultState < STATE2)
          {
              *faultState = STATE3; // Set to active fault state
              VCI_soundSiren = 1;   // Trigger siren
          }
      }
      else // Fault is inactive
      {
          if (*faultState > STATE1)
          {
              *faultState = STATE1; // Clear fault state
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
  void Decode_SignalFault(void)
  {
      uint32_t faultBits = 0;
      if (Database_Get_CurrentValue(db_VECTOR_signal_fault_error, &faultBits))
      {
          setFaultFlag(GETBIT(faultBits, 0), &SBkt_sigFault);
          setFaultFlag(GETBIT(faultBits, 1), &PBkt_sigFault);
          setFaultFlag(GETBIT(faultBits, 2), &SNoz_sigFault);
          setFaultFlag(GETBIT(faultBits, 3), &PNoz_sigFault);
          setFaultFlag(GETBIT(faultBits, 4), &STab_sigFault);
          setFaultFlag(GETBIT(faultBits, 5), &PTab_sigFault);
      }
  }
  void Decode_NfuFault(void) {
  
      uint32_t faultBits = 0;
	  if (Database_Get_CurrentValue(db_VECTOR_nfu_fault_error, &faultBits))
	  {
		  setFaultFlag(GETBIT(faultBits, 0), &SBkt_nfuFault);
		  setFaultFlag(GETBIT(faultBits, 1), &PBkt_nfuFault);
		  setFaultFlag(GETBIT(faultBits, 2), &SNoz_nfuFault);
		  setFaultFlag(GETBIT(faultBits, 3), &PNoz_nfuFault);
		  setFaultFlag(GETBIT(faultBits, 4), &STab_nfuFault);
		  setFaultFlag(GETBIT(faultBits, 5), &PTab_nfuFault);
	  }
  }

  void Decode_STA1Fault(void) {
      uint32_t faultBits = 0;
      if (Database_Get_CurrentValue(db_VECTOR_STA1_fault_error, &faultBits))
      {
          SLev1_Fault = GETBIT(faultBits, 2);
          PLev1_Fault = GETBIT(faultBits, 3);
          setFaultFlag(GETBIT(faultBits, 0), &Idle1_Fault);
          setFaultFlag(GETBIT(faultBits, 1), &Helm1_Fault);
          setFaultFlag(GETBIT(faultBits, 4), &JoyY1_Fault);
          setFaultFlag(GETBIT(faultBits, 5), &JoyX1_Fault);
      }
  }

  void Decode_STA2Fault(void) {
	  uint32_t faultBits = 0;
	  if (Database_Get_CurrentValue(db_VECTOR_STA2_fault_error, &faultBits))
	  {
          SLev2_Fault = GETBIT(faultBits, 2);
          PLev2_Fault = GETBIT(faultBits, 3);
		  setFaultFlag(GETBIT(faultBits, 0), &Idle2_Fault);
		  setFaultFlag(GETBIT(faultBits, 1), &Helm2_Fault);
		  setFaultFlag(GETBIT(faultBits, 4), &JoyY2_Fault);
		  setFaultFlag(GETBIT(faultBits, 5), &JoyX2_Fault);
	 
	  }
  }

  void Decode_STA3Fault(void) {
	  uint32_t faultBits = 0;
	  if (Database_Get_CurrentValue(db_VECTOR_STA3_fault_error, &faultBits))
	  {
          Idle3_Fault = GETBIT(faultBits, 0);
          Helm3_Fault = GETBIT(faultBits, 1);
          SLev3_Fault = GETBIT(faultBits, 2);
          PLev3_Fault = GETBIT(faultBits, 3);
          JoyY3_Fault = GETBIT(faultBits, 4);
          JoyX3_Fault = GETBIT(faultBits, 5);
	  }
  }

  void Decode_CalFault(void) {
      uint32_t faultBits = 0;
      if (Database_Get_CurrentValue(db_VECTOR_cal_fault_error, &faultBits))
      {
          setFaultFlag(GETBIT(faultBits, 0), &Trim1_Fault);
          setFaultFlag(GETBIT(faultBits, 1), &Roll1_Fault);
          setFaultFlag(GETBIT(faultBits, 2), &Cal_Fault);
          setFaultFlag(GETBIT(faultBits, 3), &AP_Fault);
          setFaultFlag(GETBIT(faultBits, 4), &Trim2_Fault);
          setFaultFlag(GETBIT(faultBits, 5), &Roll2_Fault);
      }
}
void Decode_InterlockFault(void) {
    unsigned int gdf;
    unsigned int cdf;

    uint32_t faultBits = 0;
	if (Database_Get_CurrentValue(db_VECTOR_interlock_fault_error, &faultBits))
	{
        gdf = GETBIT(faultBits, 0);
        cdf = GETBIT(faultBits, 1);
        // implement a 4 second delay for dockmode clutch disengage alarm to register
        if (cdf && dockMode_delayCntr == 0 && (clutchDiseng_Fault < STATE2))
        {
            dockMode_delayCntr = 5; // init the counter, it is decremented in the vSched_call_1000mS() function in main
        }
        else if (cdf && dockMode_delayCntr == 1) // when the cntr reaches 1 , set the fault
        {
            setFaultFlag(gdf, &generalDock_Fault);
            setFaultFlag(cdf, &clutchDiseng_Fault);
        }
        else if (cdf == 0)
        {
            setFaultFlag(gdf, &generalDock_Fault);
            setFaultFlag(cdf, &clutchDiseng_Fault);
            dockMode_delayCntr = 0;
        }
        //generalDock_Fault = GETBIT(flt,0);
        //  setFaultFlag(GETBIT(flt,0), &generalDock_Fault);
        //  setFaultFlag(GETBIT(flt,1), &clutchDiseng_Fault);
        Inbd_Fault = GETBIT(faultBits, 2);
	}
}



int x_size_off[10] = { 2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };
int y_size_off[19] = { -2, 1, 0, -1, -2, -3, -4, -5, -6, -7,
                       -8, -9, -10, -11, -12, -13, -14, -15, -16
};
int x_size_off_tabs[19] = { 0, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }; //for indication stack bar taper




//bar remain constant, but we add an offset to the driving value when the
//current (calculated) number of bars is less than the previous number of bars
//7 = about 1.5% hysteresis (7 counts in each direction, scale of 1000)
//void VECTOR_stack_update(int stack_number)
//{
//    switch (stack_number)
//    {
//    case 0:
//        stack_value = (int)data_base[db_VECTOR_port_trimtab][0].data.flt;
//        //stack number, stack_value, x_start, y_start, x_incr, y_incr, x_size, y_size, bars prev, dir
//        bars_prev_PORT_TAB = DrawTabStack(stack_number, stack_value, T1_xpos,
//            7, 0, 4, 10, 2, bars_prev_PORT_TAB, &PT_dir);
//        break;
//
//    case 1:
//        stack_value = (int)data_base[db_VECTOR_port_bucket][0].data.flt;
//        bars_prev_PORT_BUCKET = DrawBucketStack(stack_number, stack_value, B1_xpos,
//            43, 0, -4, -10, 2, bars_prev_PORT_BUCKET, &PB_dir);
//        break;
//
//    case 2:
//        stack_value = (int)data_base[db_VECTOR_stbd_bucket][0].data.flt;
//        bars_prev_STBD_BUCKET = DrawBucketStack(stack_number, stack_value, B2_xpos,
//            43, 0, -4, 10, 2, bars_prev_STBD_BUCKET, &SB_dir);
//        break;
//
//    case 3:
//        stack_value = (int)data_base[db_VECTOR_stbd_trimtab][0].data.flt;
//        bars_prev_STBD_TAB = DrawTabStack(stack_number, stack_value, T2_xpos,
//            7, 0, 4, -10, 2, bars_prev_STBD_TAB, &ST_dir);
//        break;
//
//    case 4:
//        stack_value = (int)data_base[db_VECTOR_port_nozzle][0].data.flt;
//        bars_prev_PORT_NOZZLE = DrawNozzleStack(stack_number, stack_value, N1_xpos, 114, N1_xincr,
//            0, -N1_xsize, -10, bars_prev_PORT_NOZZLE, &PN_dir);
//        break;
//
//    case 5:
//        stack_value = (int)data_base[db_VECTOR_stbd_nozzle][0].data.flt;
//        //DrawSteerStack(stack_number, stack_value, S_xpos, 114, 4,0,-2,-10, bars_prev_STEER_ANGLE, &SA_dir);
//        bars_prev_STBD_NOZZLE = DrawNozzleStack(stack_number, stack_value, N2_xpos, 114, N2_xincr,
//            0, -N2_xsize, -10, bars_prev_STBD_NOZZLE, &SN_dir);
//        break;
//
//    };
//}
int B1_xpos, B2_xpos, N1_xpos, N2_xpos, T1_xpos, T2_xpos;
int N1_xincr, N2_xincr, N1_xsize, N2_xsize, DoubleBarFlag;
int B1_present, B2_present, N1_present, N2_present, T1_present, T2_present;

//bar remain constant, but we add an offset to the driving value when the
//current (calculated) number of bars is less than the previous number of bars
//7 = about 1.5% hysteresis (7 counts in each direction, scale of 1000)
void VECTOR_stack_update(int stack_number)
{
    uint32_t indication_configV2 = 0;
    uint32_t portNozzlePositionV2 = 0;
    uint32_t stbdNozzlePositionV2 = 0;
    uint32_t portBucketPositionV2 = 0;
    uint32_t stbdBucketPositionV2 = 0;
    uint32_t portInterceptorPositionV2 = 0;
    uint32_t stbdInterceptorPositionV2 = 0;
    Database_Get_CurrentValue(db_VECTOR_I14_INDICConfig, &indication_configV2);
    Database_Get_CurrentValue(db_VECTOR_port_nozzle, &portNozzlePositionV2);
    Database_Get_CurrentValue(db_VECTOR_stbd_nozzle, &stbdNozzlePositionV2);
    Database_Get_CurrentValue(db_VECTOR_port_bucket, &portBucketPositionV2);
    Database_Get_CurrentValue(db_VECTOR_stbd_bucket, &stbdBucketPositionV2);
    Database_Get_CurrentValue(db_VECTOR_port_trimtab, &portInterceptorPositionV2);
    Database_Get_CurrentValue(db_VECTOR_stbd_trimtab, &stbdInterceptorPositionV2);


    switch (stack_number)
    {
    case 0:
        stack_value = (int)portInterceptorPositionV2; // get data from db_VECTOR_port_trimtab
		//stack number, stack_value, x_start, y_start, x_incr, y_incr, x_size, y_size, bars prev, dir
		bars_prev_PORT_TAB = DrawTabStack(stack_number, stack_value, T1_xpos,
			7, 0, 4, 10, 2, bars_prev_PORT_TAB, &PT_dir);
		break;
    case 1:
        stack_value = (int)portBucketPositionV2;
        bars_prev_PORT_BUCKET = DrawBucketStack(stack_number, stack_value, B1_xpos,
            43, 0, -4, -10, 2, bars_prev_PORT_BUCKET, &PB_dir);
        break;
    case 2:
        stack_value = (int)stbdBucketPositionV2;
        bars_prev_STBD_BUCKET = DrawBucketStack(stack_number, stack_value, B2_xpos,
            43, 0, -4, 10, 2, bars_prev_STBD_BUCKET, &SB_dir);
        break;
    case 3:
        stack_value = (int)stbdInterceptorPositionV2;
        bars_prev_STBD_TAB = DrawTabStack(stack_number, stack_value, T2_xpos,
            7, 0, 4, -10, 2, bars_prev_STBD_TAB, &ST_dir);
        break;
    case 4:
        stack_value = (int)portNozzlePositionV2;
        bars_prev_PORT_NOZZLE = DrawNozzleStack(stack_number, stack_value, N1_xpos, 114, N1_xincr,
            0, -N1_xsize, -10, bars_prev_PORT_NOZZLE, &PN_dir);
        break;
    case 5:
        stack_value = (int)stbdNozzlePositionV2;
        //DrawSteerStack(stack_number, stack_value, S_xpos, 114, 4,0,-2,-10, bars_prev_STEER_ANGLE, &SA_dir);
        bars_prev_STBD_NOZZLE = DrawNozzleStack(stack_number, stack_value, N2_xpos, 114, N2_xincr,
            0, -N2_xsize, -10, bars_prev_STBD_NOZZLE, &SN_dir);
        break;
    default:
        break;
    }

}
//---------------------------------------------------------------------------------------------
//Indicator Processing for Nozzle Angle--------------------------------------------------------
//---------------------------------------------------------------------------------------------
int DrawNozzleStack(int stack_num, int stack_val, int x_start, int y_start,
    int x_incr, int y_incr, int x_size, int y_size, int bars_previous, int* ptr_direction)
{

    int number_bars;

    //use twice as many bars if there is only a single nozzle meter displayed
    if (( SettingsGetIndicationConfig() == 1) ||
        (SettingsGetIndicationConfig() == 3) ||
        (SettingsGetIndicationConfig() == 5))
        number_bars = (NUMBER_BARS + NUMBER_BARS / 2);

    else
        number_bars = NUMBER_BARS;

    //initialize variable values
    x_pos = x_start;
    y_pos = y_start;
    solid_bars = 0;

    //for center indication: draw either the port half or the stbd half of the stack
    stack_val = stack_val - 500;
    STACK_HALF = STBD;

    if (stack_val < 0)
    {
        STACK_HALF = PORT;
        x_incr = -x_incr;
        stack_val = -stack_val;
    }

    stack_temp = stack_val;    //keep stack_val intact for later.

    //determine number of solid bars
    if (stack_temp != 0)
        while (stack_temp > 0)
        {
            stack_temp = stack_temp - (500 / number_bars);
            solid_bars = solid_bars + 1;
        }

    else
        solid_bars = 1;

    //if we're on the starboard half of the steering stack and moving more port
    //or if we're on the port half of the steering stack and moving more starboard...
    if (((STACK_HALF == STBD) && (*ptr_direction == STBD)) ||
        ((STACK_HALF == PORT) && (*ptr_direction == PORT)))
    {
        if (solid_bars < bars_previous)
        {
            solid_bars = 0;
            stack_temp = stack_val + HYSTERESIS_FACTOR;

            if (stack_temp != 0)
                while (stack_temp > 0)
                {
                    stack_temp = stack_temp - (500 / number_bars);
                    solid_bars = solid_bars + 1;
                }

            else
                solid_bars = 1;
        }
    }

    //clamp
    if (solid_bars > number_bars)
        solid_bars = number_bars;

    //if we're on the port half of the steering stack and moving more port
    //or if we're on the starboard half of the steering stack and moving more starboard...
    if (((STACK_HALF == PORT) && (*ptr_direction == STBD)) ||
        ((STACK_HALF == STBD) && (*ptr_direction == PORT)))
    {
        if (solid_bars > bars_previous)
        {
            solid_bars = 0;
            stack_temp = stack_val - HYSTERESIS_FACTOR;

            if (stack_temp != 0)
                while (stack_temp > 0)
                {
                    stack_temp = stack_temp - (500 / number_bars);
                    solid_bars = solid_bars + 1;
                }

            else
                solid_bars = 1;
        }
    }

    //Change the direction of movement if necessary
    if (solid_bars < bars_previous)
    {
        if (STACK_HALF == STBD)
            *ptr_direction = PORT;

        if (STACK_HALF == PORT)
            *ptr_direction = STBD;
    }

    if (solid_bars > bars_previous)
    {
        if (STACK_HALF == STBD)
            *ptr_direction = STBD;

        if (STACK_HALF == PORT)
            *ptr_direction = PORT;
    }

  
    //Clear stacks if the indication data stream is lost

    if (((SettingsGetDataMode() == CANbus_GPSI_mode) && (SettingsGetStationType() == main_station) &&
        (CCIM_Fault == 1) && (Serial_Fault == 1)) ||
        ((SettingsGetDataMode() == CANbus_GPSI_mode) && (SettingsGetStationType() == wing_station) &&
            (CCIM_Fault == 1) && (MS_CAN_Fault != 0)) ||
        ((SettingsGetDataMode() == CANbus_mode) && (MS_CAN_Fault != 0)) || //wing station
        ((SettingsGetDataMode() == rs232_mode) && (Serial_Fault == 1)) || //main station
        ((SettingsGetDataMode() == rs232_mode) && (stack_num == 4) && (PNoz_sigFault > STATE1)) ||
        ((SettingsGetDataMode() == rs232_mode) && (stack_num == 5) && (SNoz_sigFault > STATE1)))

    {
       
        for (indexI = 0; indexI < number_bars; indexI = indexI + 1)
        {
            blockclearEx(x_pos, y_pos, (x_pos + x_size), (y_pos + y_size + y_size_off[indexI]), MAKERGB565(121, 137, 121), LAYER_FRONT);

            x_pos = x_pos + x_incr;  //horizontal stack
        }

        x_pos = x_start;
        x_incr = -x_incr;

        for (indexI = 0; indexI < number_bars; indexI = indexI + 1)
        {
             blockclearEx(x_pos, y_pos, (x_pos + x_size), (y_pos + y_size + y_size_off[indexI]), MAKERGB565(121, 137, 121), LAYER_FRONT);


            x_pos = x_pos + x_incr;  //horizontal stack
        }
    }

    else //no sensor fault...
    {
        //draw solid bars............................................
        
        for (indexI = 0; indexI < solid_bars; indexI = indexI + 1)
        {
           

            blockfillEx(
                (x_pos + x_size), 
                (y_pos + y_size + y_size_off[indexI]),
                x_pos, 
                y_pos, 
                BLACK,
                100,
                LAYER_FRONT);

            x_pos = x_pos + x_incr;  //horizontal stack
        }

        //draw empty bars............................................
        for (indexI = indexI; indexI < number_bars; indexI = indexI + 1)
        {
          blockclearEx(x_pos, y_pos, (x_pos + x_size), (y_pos + y_size + y_size_off[indexI]), MAKERGB565(121, 137, 121), LAYER_FRONT);

            x_pos = x_pos + x_incr;  //horizontal stack
        }

        //clear the non-used (left or right) half of the indication stack
        //accounts for any bars not cleared during quick movements
        x_incr = -x_incr;
        x_pos = x_start + x_incr;
        y_pos = y_start;

        for (indexI = 1; indexI < number_bars; indexI = indexI + 1)
        {
            blockclearEx(x_pos, y_pos, (x_pos + x_size), (y_pos + y_size + y_size_off[indexI]), MAKERGB565(121, 137, 121), LAYER_FRONT);

            x_pos = x_pos + x_incr;  //horizontal stack
        }
    }

    return(solid_bars);
}


//---------------------------------------------------------------------------------------------
//Indicator Processing for Bucket Angle--------------------------------------------------------
//---------------------------------------------------------------------------------------------
int DrawBucketStack(int stack_num, int stack_val, int x_start, int y_start,
    int x_incr, int y_incr, int x_size, int y_size, int bars_previous, int* ptr_direction)
{

    //initialize variable values
    x_pos = x_start;
    y_pos = y_start;
    solid_bars = 0;

    if (stack_num == 1) //port bucket
        for (indexI = 0; indexI < 20; indexI = indexI + 1)
            x_size_off[indexI] = -x_size_off[indexI];

    //for center indication: draw either the DOWN half or the UP half of the stack
    stack_val = stack_val - 500;
    STACK_HALF = UP;

    if (stack_val < 0)
    {
        STACK_HALF = DOWN;
        y_incr = -y_incr;
        stack_val = -stack_val;
    }

    stack_temp = stack_val;    //keep stack_val intact for later.

    //determine number of solid bars
    if (stack_temp != 0)
        while (stack_temp > 0)
        {
            stack_temp = stack_temp - (500 / NUMBER_BARS);
            solid_bars = solid_bars + 1;
        }

    else
        solid_bars = 1;

    //if we're on the starboard half of the steering stack and moving more DOWN
    //or if we're on the DOWN half of the steering stack and moving more starboard...
    if (((STACK_HALF == UP) && (*ptr_direction == UP)) ||
        ((STACK_HALF == DOWN) && (*ptr_direction == DOWN)))
    {
        if (solid_bars < bars_previous)
        {
            solid_bars = 0;
            stack_temp = stack_val + HYSTERESIS_FACTOR;

            if (stack_temp != 0)
                while (stack_temp > 0)
                {
                    stack_temp = stack_temp - (500 / NUMBER_BARS);
                    solid_bars = solid_bars + 1;
                }

            else
                solid_bars = 1;
        }
    }

    //if we're on the DOWN half of the steering stack and moving more DOWN
    //or if we're on the starboard half of the steering stack and moving more starboard...
    if (((STACK_HALF == DOWN) && (*ptr_direction == UP)) ||
        ((STACK_HALF == UP) && (*ptr_direction == DOWN)))
    {
        if (solid_bars > bars_previous)
        {
            solid_bars = 0;
            stack_temp = stack_val - HYSTERESIS_FACTOR;

            if (stack_temp != 0)
                while (stack_temp > 0)
                {
                    stack_temp = stack_temp - (500 / NUMBER_BARS);
                    solid_bars = solid_bars + 1;
                }

            else
                solid_bars = 1;
        }
    }

    //Change the direction of movement if necessary
    if (solid_bars < bars_previous)
    {
        if (STACK_HALF == UP)
            *ptr_direction = DOWN;

        if (STACK_HALF == DOWN)
            *ptr_direction = UP;
    }

    if (solid_bars > bars_previous)
    {
        if (STACK_HALF == UP)
            *ptr_direction = UP;

        if (STACK_HALF == DOWN)
            *ptr_direction = DOWN;
    }

    //Clear stacks if the indication data stream is lost


    if (((SettingsGetDataMode() == CANbus_GPSI_mode) && (SettingsGetStationType() == main_station) &&
        (CCIM_Fault == 1) && (Serial_Fault == 1)) ||
        ((SettingsGetDataMode() == CANbus_GPSI_mode) && (SettingsGetStationType() == wing_station) &&
            (CCIM_Fault == 1) && (MS_CAN_Fault != 0)) ||
        ((SettingsGetDataMode() == CANbus_mode) && (MS_CAN_Fault != 0)) || //wing station
        ((SettingsGetDataMode() == rs232_mode) && (Serial_Fault == 1)) || //main station
        ((SettingsGetDataMode() == rs232_mode) && (stack_num == 4) && (PNoz_sigFault > STATE1)) ||
        ((SettingsGetDataMode() == rs232_mode) && (stack_num == 5) && (SNoz_sigFault > STATE1)))

    {

        for (indexI = 0; indexI < NUMBER_BARS; indexI = indexI + 1)
        {
            blockclearEx(x_pos, y_pos, (x_pos + x_size + x_size_off[indexI]), (y_pos + y_size), MAKERGB565(121, 137, 121), LAYER_FRONT);

            y_pos = y_pos + y_incr;  //vertical stack
        }

        y_pos = y_start;
        y_incr = -y_incr;

        for (indexI = 0; indexI < NUMBER_BARS; indexI = indexI + 1)
        {
            blockclearEx(x_pos, y_pos, (x_pos + x_size + x_size_off[indexI]), (y_pos + y_size), MAKERGB565(121, 137, 121), LAYER_FRONT);


            y_pos = y_pos + y_incr;  //vertical stack
        }

    }

    else //no sensor fault...
    {
        //draw solid bars............................................
        for (indexI = 0; indexI < solid_bars; indexI = indexI + 1)
        {
            blockfillEx(x_pos, y_pos, (x_pos + x_size + x_size_off[indexI]), (y_pos + y_size),BLACK, 100, LAYER_FRONT);

            y_pos = y_pos + y_incr;  //vertical stack
        }

        //draw empty bars............................................
        for (indexI = indexI; indexI < NUMBER_BARS; indexI = indexI + 1)
        {
            blockclearEx(x_pos, y_pos, (x_pos + x_size + x_size_off[indexI]), (y_pos + y_size),MAKERGB565(121, 137, 121), LAYER_FRONT);


            y_pos = y_pos + y_incr;  //vertical stack
        }

        //clear the non-used (upper or lower) half of the indication stack
        //accounts for any bars not cleared during quick movements
        y_incr = -y_incr;
        x_pos = x_start;
        y_pos = y_start + y_incr;

        for (indexI = 1; indexI < NUMBER_BARS; indexI = indexI + 1)
        {
            blockclearEx(x_pos, y_pos, (x_pos + x_size + x_size_off[indexI]), (y_pos + y_size), MAKERGB565(121, 137, 121), LAYER_FRONT);



            y_pos = y_pos + y_incr;  //vertical stack
        }
    }

    if (stack_num == 1) //port bucket
        for (indexI = 0; indexI < 20; indexI = indexI + 1)
            x_size_off[indexI] = -x_size_off[indexI];

    return(solid_bars);
}



//---------------------------------------------------------------------------------------------
//Indicator Processing for Tabs ---------------------------------------------------------------
//---------------------------------------------------------------------------------------------
int DrawTabStack(int stack_num, int stack_val, int x_start, int y_start,
    int x_incr, int y_incr, int x_size, int y_size, int bars_previous, int* ptr_direction)
{
    //int direction;
    //initialize variable values
    x_pos = x_start;
    y_pos = y_start;
    solid_bars = 0;

    //add offset to make each bar's threshold in the middle of that bar's range
    stack_val = stack_val + 500 / (NUMBER_BARS * 2 - 1);

    if (stack_val > 999)
        stack_val = 999;

    stack_temp = stack_val;

    if (stack_num == 3) //bar directions reversed for stbd tab
        for (indexI = 0; indexI < 20; indexI = indexI + 1)
            x_size_off_tabs[indexI] = -x_size_off_tabs[indexI];

    //determine number of bars to draw
    if (stack_temp < (1000 / (NUMBER_BARS * 2 - 1)))
        solid_bars = 1;

    else
        while (stack_temp >= (NUMBER_BARS * 2 - 1))
        {
            stack_temp = stack_temp - (1000 / (NUMBER_BARS * 2 - 1));
            solid_bars = solid_bars + 1;
        }

    //introduce hysteresis to prevent flickering near the each bar's threshold
    if (*ptr_direction == DOWN)
    {
        if (solid_bars > bars_previous)
        {
            solid_bars = 0;
            stack_temp = stack_val - HYSTERESIS_FACTOR; //increase threshold

            if (stack_temp < (1000 / (NUMBER_BARS * 2 - 1))) //recalculate number of bars
                solid_bars = 1;

            else
            {
                while (stack_temp >= (NUMBER_BARS * 2 - 1))
                {
                    stack_temp = stack_temp - (1000 / (NUMBER_BARS * 2 - 1));
                    solid_bars = solid_bars + 1;
                }
            }
        }
    }

    if (*ptr_direction == UP)
    {
        if (solid_bars < bars_previous)
        {
            solid_bars = 0;
            stack_temp = stack_val + HYSTERESIS_FACTOR; //decrease threshold

            if (stack_temp < (1000 / (NUMBER_BARS * 2 - 1))) //recalculate number of bars
                solid_bars = 1;

            else
            {
                while (stack_temp >= (NUMBER_BARS * 2 - 1))
                {
                    stack_temp = stack_temp - (1000 / (NUMBER_BARS * 2 - 1));
                    solid_bars = solid_bars + 1;
                }
            }
        }
    }

    //Change (or reinforce) the direction of movement if ecessary
    if (solid_bars < bars_previous)
        *ptr_direction = DOWN;

    if (solid_bars > bars_previous)
        *ptr_direction = UP;

    //if (solid_bars == bars previous), keep the same direction (we don't really care).

    stack_temp = (NUMBER_BARS * 2) - solid_bars; //swap up and down...hi counts means tabs/drives are up!

 
    if (((SettingsGetDataMode() == CANbus_GPSI_mode) && (SettingsGetStationType() == main_station) &&
        (CCIM_Fault == 1) && (Serial_Fault == 1)) ||
        ((SettingsGetDataMode() == CANbus_GPSI_mode) && (SettingsGetStationType() == wing_station) &&
            (CCIM_Fault == 1) && (MS_CAN_Fault != 0)) ||
        ((SettingsGetDataMode() == CANbus_mode) && (MS_CAN_Fault != 0)) || //wing station
        ((SettingsGetDataMode() == rs232_mode) && (Serial_Fault == 1)) || //main station
        ((SettingsGetDataMode() == rs232_mode) && (stack_num == 4) && (PNoz_sigFault > STATE1)) ||
        ((SettingsGetDataMode() == rs232_mode) && (stack_num == 5) && (SNoz_sigFault > STATE1)))

    {
        for (indexI = 0; indexI < (NUMBER_BARS * 2 - 1); indexI = indexI + 1)
        {
           // _blockclear(x_pos, y_pos, (x_pos + x_size + x_size_off_tabs[indexI]), (y_pos + y_size));

            blockclearEx(x_pos, y_pos, (x_pos + x_size + x_size_off_tabs[indexI]), (y_pos + y_size), MAKERGB565(121, 137, 121), LAYER_FRONT);

            y_pos = y_pos + y_incr;  //vertical stack
        }
    }

    else
    {
        //draw solid bars............................................
        for (indexI = 0; indexI < stack_temp; indexI = indexI + 1)
        {
            //_blockfill(x_pos, y_pos, (x_pos + x_size + x_size_off_tabs[indexI]), (y_pos + y_size));

            blockfillEx(
				(x_pos + x_size + x_size_off_tabs[indexI]),
				(y_pos + y_size),
				x_pos,
				y_pos,
				BLACK,
				100,
				LAYER_FRONT);
            y_pos = y_pos + y_incr;  //vertical stack
        }

        //draw empty bars............................................
        for (indexI = indexI; indexI < (NUMBER_BARS * 2 - 1); indexI = indexI + 1)
        {
          //  _blockclear(x_pos, y_pos, (x_pos + x_size + x_size_off_tabs[indexI]), (y_pos + y_size));

            blockclearEx(x_pos, y_pos, (x_pos + x_size + x_size_off_tabs[indexI]), (y_pos + y_size), MAKERGB565(121, 137, 121), LAYER_FRONT);

            y_pos = y_pos + y_incr;  //vertical stack
        }
    }



    if (stack_num == 3)  //bar directions reversed for stbd tab
        for (indexI = 0; indexI < 20; indexI = indexI + 1)
            x_size_off_tabs[indexI] = -x_size_off_tabs[indexI];

    return(solid_bars); //return number of bars drawn, for hysteresis calculation next time!
}


