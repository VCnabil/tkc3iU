//------------------------------------------------------------------------------
//  main.c
//------------------------------------------------------------------------------
#include "project.h"
#include "crc16.h"

void init_Central_Alarm_Array()
{
    centralAlarmArray[0] = &Central_Alarm_01;
    centralAlarmArray[1] = &Central_Alarm_02;
    centralAlarmArray[2] = &Central_Alarm_03;
    centralAlarmArray[3] = &Central_Alarm_04;
    centralAlarmArray[4] = &Central_Alarm_05;
    centralAlarmArray[5] = &Central_Alarm_06;
    centralAlarmArray[6] = &Central_Alarm_07;
    centralAlarmArray[7] = &Central_Alarm_08;
    centralAlarmArray[8] = &Central_Alarm_09;
    centralAlarmArray[9] = &Central_Alarm_10;
    centralAlarmArray[10] = &Central_Alarm_11;
    centralAlarmArray[11] = &Central_Alarm_12;
    centralAlarmArray[12] = &Central_Alarm_13;
    centralAlarmArray[13] = &Central_Alarm_14;
    centralAlarmArray[14] = &Central_Alarm_15;
    centralAlarmArray[15] = &Central_Alarm_16;
    centralAlarmArray[16] = &Central_Alarm_17;

}

void  centralFaultArray_cleartoSTATE1()
{
    unsigned int size = NUMBER_OF_CENTRAL_ALARMS;

    while (size)
    {
        if (*centralAlarmArray[size - 1] > STATE1)
        {
            *centralAlarmArray[size - 1] = STATE1;
        }

        size--;
    }
}
void init_VCI_FaultArray()
{


    // initialize the fault array with the VCI faults concerned with RBM system
    propnFaultArray[0] = &PTab_sigFault;
    propnFaultArray[1] = &STab_sigFault;
    propnFaultArray[2] = &PNoz_sigFault;
    propnFaultArray[3] = &SNoz_sigFault;
    propnFaultArray[4] = &PBkt_sigFault;
    propnFaultArray[5] = &SBkt_sigFault;

    propnFaultArray[6] = &PTab_nfuFault;
    propnFaultArray[7] = &STab_nfuFault;
    propnFaultArray[8] = &PNoz_nfuFault;
    propnFaultArray[9] = &SNoz_nfuFault;
    propnFaultArray[10] = &PBkt_nfuFault;
    propnFaultArray[11] = &SBkt_nfuFault;

    propnFaultArray[12] = &JoyX1_Fault;
    propnFaultArray[13] = &JoyY1_Fault;
    propnFaultArray[14] = &Helm1_Fault;
    propnFaultArray[15] = &Idle1_Fault;
    propnFaultArray[16] = &JoyX2_Fault;
    propnFaultArray[17] = &JoyY2_Fault;
    propnFaultArray[18] = &Helm2_Fault;
    propnFaultArray[19] = &Idle2_Fault;

    propnFaultArray[20] = &Cal_Fault;
    propnFaultArray[21] = &Roll1_Fault;
    propnFaultArray[22] = &Trim1_Fault;
    propnFaultArray[23] = &Roll2_Fault;
    propnFaultArray[24] = &Trim2_Fault;
    propnFaultArray[25] = &AP_Fault;
    propnFaultArray[26] = &clutchDiseng_Fault;
    propnFaultArray[27] = &generalDock_Fault;
    propnFaultArray[28] = &VCI_CAN_Fault;
    propnFaultArray[29] = &ClutchST1_CAN_Fault;
    propnFaultArray[30] = &ClutchST2_CAN_Fault;
    propnFaultArray[31] = &Serial_Fault_State; // has to be last one for the siren logic to work

}
void  propnFaultArray_cleartoSTATE1( int size)
{


    while (size)
    {
        if (*propnFaultArray[size - 1] > STATE1)
        {
            *propnFaultArray[size - 1] = STATE1;
        }

        size--;
    }
}

void RunChecks() {

    CentralAlarmSys_CAN_Fault = 0;
    MS_CAN_Fault = 0;
    CAN_Fault = 0;
    Serial_Fault = 0;
    CCIM_Fault = 0;
    ++No_or_Bad_CAN_Data_CentralAlarmSys;
    if (No_or_Bad_CAN_Data_CentralAlarmSys == BAD_DATA_THRESHOLD - 1)
    {
        // This condition occurs just before transition of CentralAlarmSys_CAN_Fault flag from zero to one
        // NOTE: This conditional is used to set AlarmMuteFlag in order to avoid resetting every 50 ms.
        AlarmMuteFlag_CentralAlarm = 0;
    }
    if (No_or_Bad_CAN_Data_CentralAlarmSys >= BAD_DATA_THRESHOLD)
    {
        CentralAlarmSys_CAN_Fault = 1;
        No_or_Bad_CAN_Data_CentralAlarmSys = BAD_DATA_THRESHOLD;
        centralFaultArray_cleartoSTATE1();
    }

    //Check for Serial or CAN data link fault at main station------------------------------------------------
    //NOTES: 1) the serial link at the main station is always active.
    //       2) the can fault is suppressed in rs232 mode.
    //       3) GPSI (general purpose sensor interface) and CCIM (cantrak customer interface module) are synonymous

    if (SettingsGetStationType() == main_station) {
        //RS232 Fault----------------------------------
        No_or_Bad_Data = No_or_Bad_Data + 1;  //gets reset when good rs232 data is parsed.

        if (No_or_Bad_Data == BAD_DATA_THRESHOLD - 1)
        {
            // This condition occurs just before transition of Serial_Fault flag from zero to one
            // NOTE: These flags are set in this conditional to avoid resetting every 50 ms.
            AlarmMuteFlag = 0;
            uiUnacknowledged_PropulsionSystemFault = 1; // flag bit sent to Indication/Alarm controller
        }

        if (No_or_Bad_Data >= BAD_DATA_THRESHOLD)
        {
            Serial_Fault = 1;
            setFaultFlag(1, &Serial_Fault_State);

            No_or_Bad_Data = BAD_DATA_THRESHOLD;
            propnFaultArray_cleartoSTATE1(NUMBER_0F_PROPN_FAULTS - 1); // exclude the serial fault which is last one

        }

        else
        {
            setFaultFlag(0, &Serial_Fault_State);
        }

        //CAN (GPSI) link Fault-------------------------
        if (SettingsGetDataMode() == CANbus_GPSI_mode)
        {
            CCIM_Fault_Counter = CCIM_Fault_Counter + 1; //gets reset when AIN1 through AIN6 is parsed.

            if (CCIM_Fault_Counter >= BAD_DATA_THRESHOLD)
            {
                CCIM_Fault = 1;
                CAN_Fault = 1;
                CCIM_Fault_Counter = BAD_DATA_THRESHOLD;
            }
        }
    }//main station 
     //Check for CAN data link fault at wing station-----------------------------------------------------------
    //NOTES: 1) wing station is locked-out of RS232 mode
    //       2) in GPSI mode, either the GPSI or the main station can xmissions can cause the can fault.
    if (SettingsGetStationType() == wing_station)
    {
        //CAN (main station xmission) link Fault----------------
        No_or_Bad_CAN_Data = No_or_Bad_CAN_Data + 1; //gets reset to zero when good data is recieved via CAN.

        if (No_or_Bad_CAN_Data >= BAD_DATA_THRESHOLD)
        {
            MS_CAN_Fault = 1;
            No_or_Bad_CAN_Data = BAD_DATA_THRESHOLD;
        }

        //CAN (GPSI) link Fault---------------------------------
        if (SettingsGetDataMode() == CANbus_GPSI_mode)
        {
            CCIM_Fault_Counter = CCIM_Fault_Counter + 1;             //gets reset to zero when AIN1 through AIN6 is parsed.

            if (CCIM_Fault_Counter >= BAD_DATA_THRESHOLD)
            {
                CCIM_Fault = 1;
                CCIM_Fault_Counter = BAD_DATA_THRESHOLD;
            }
        }

        if ((MS_CAN_Fault == 1) || (CCIM_Fault == 1))
            CAN_Fault = 1;

        /*
                sprintf(test_dum, "ST = %d DM = %d NBCD = %d MSCF = %d CTR = %d CCIMF = %d\r\n",
                        gpSettings->STATION_TYPE, gpSettings->DATA_MODE, No_or_Bad_CAN_Data, MS_CAN_Fault,
                        CCIM_Fault_Counter, CCIM_Fault);
                cSendString(test_dum);
        */
    }


    //Transmit CAN data (if the station is the main station)-------------------------
    if (SettingsGetStationType() == main_station) {
    
    //    TransmitCanData();
    }

    //Transmit RS232 Settings / Requests to Control Box------------------------------
    //NOTE: the local enable/disable overrides the control box request.
    //      -->The local enable is set in the system options screen.
    if (Local_Enable_RS232_Transmission == 1)
        if (Enable_RS232_Transmission == 1)
        {
            RS232_XMIT_COUNTER = RS232_XMIT_COUNTER + 1;

            if (RS232_XMIT_COUNTER >= 2) //transmit 10x per second
            {
                //TransmitRS232Data();
                RS232_XMIT_COUNTER = 0;
            }
        }
}

//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
static void CANvuMainExit(void);

//------------------------------------------------------------------------------
// GLOBAL FUNCTIONS
//------------------------------------------------------------------------------

// Starts the SDK when running on the target
int main(int argc, char* argv[])
{
	int exitCode;
	exitCode = InitialiseSDKCFramework(argc, argv);
	return exitCode;
}

// Main program initialisation - This is called first and only once
extern "C" void CANvuMainInit(void)
{
	PlatformShutdownRegisterCallback(CANvuMainExit);
	sdk_init();
	FontInit();
	SettingsInit();
	CANInit();
	UARTInit();
	MMIInit(100, 100, 30);
	EventHandlerInit();
	LightingInit();
	DataBase_Init();
}

extern "C" void CANvuMain(void)
{
	printf("%s %s - %s\n", __DATE__, __TIME__, SOFTWARE);
	watchdog_refresh();
	ButtonBarInit();
	ScreensInit();
    init_Central_Alarm_Array();
    init_VCI_FaultArray();

}
extern "C" void CANvuMainLoop(void)
{
	watchdog_refresh();
	CANProcessRx();
	UARTDecode();
	MMIProcess(); 
	merge_layers();
	EventHandlerProcess();
}
static void CANvuMainExit(void)
{
	//  De-initialise the CAN ports
	CANDeInit();
}



