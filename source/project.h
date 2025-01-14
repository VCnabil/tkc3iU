//----------------------------------------------------------------------------------
//  TITLE :          project.h
//  DESCRIPTION :    Single inclusion point of all header files used in the project.
//----------------------------------------------------------------------------------
#ifndef __PROJECT_H__
#define __PROJECT_H__

// Standard Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
// SDK Header files
#include "syslib.h"
#include "sim_config.h"
// Vector control Inc. Global variables and function prototypes
#include "VCInc.h"
// Software Version Number
#include "AppVersion.h"
#include "data.h"
#include "NVSettings/settings.h"
#include "CAN/can.h"
#include "CAN/J1939/J1939_FEFC_INDIC.h"
#include "CAN/J1939/J19139_FF8D_FAULTS.h"
#include "System/eventhandler.h"
#include "System/sdk_init.h"
#include "System/lighting.h"
#include "System/ipAddress.h"
#include "UART/NMEA0183/extractField.h"
#include "UART/NMEA0183/PVCI.h"
#include "UART/uart.h"
#include "Database/database.h"
#include "UI/ttfonts.h"
#include "UI/screens.h"
#include "UI/buttonbar.h"
#include "UI/keyboard.h"
//screens

#include "UI/Screens/scrn00debugCAN.h"
#include "UI/Screens/scrn00debugCOM.h"
#include "UI/Screens/scrn00Start.h"
#include "UI/Screens/scrn00SysOpts.h"
#include "UI/Screens/scrn01SysOpts.h"
#include "UI/Screens/scrn00Test.h"
#include "UI/Screens/scrn00Test2.h"
#include "UI/Screens/screen00Faults.h"
#include "UI/Screens/scrn00About.h"
#include "UI/Screens/scrn00Zerothrust.h"
#include "UI/Screens/scrn00Calibration.h"
#include "UI/Screens/scrn00Autocal.h"
#include "UI/Screens/scrn00Passcode.h"
#include "UI/Screens/scrn00CentralAlarm.h"
#include "UI/Screens/scrn00AlarmSummary.h"
#include "UI/Screens/scrn00HideZero.h"  

#include "UI/Screens/Scrn01Faults.h"
#include "UI/Screens/scrn02Faults.h"
#include "UI/Screens/Scrn01LiveDbView.h"
#include "CAN/J1939/J1939_FF00_VECTOR_CCIM_AIN1.h"
#include "CAN/J1939/J1939_FF01_VECTOR_CCIM_AIN2.h"
#include "CAN/J1939/J1939_FF02_VECTOR_CCIM_AIN3.h"
#include "CAN/J1939/J1939_FF03_VECTOR_CCIM_AIN4.h"
#include "CAN/J1939/J1939_FF04_VECTOR_CCIM_AIN5.h"
#include "CAN/J1939/J1939_FF05_VECTOR_CCIM_AIN6.h"
#include "CAN/J1939/J1939_FF0F_VECTOR_RS232_PORTNOZZLE.h"
#include "CAN/J1939/J1939_FF10_VECTOR_RS232_STBDNOZZLE.h"
#include "CAN/J1939/J1939_FF11_VECTOR_RS232_PORTBUCKET.h"
#include "CAN/J1939/J1939_FF12_VECTOR_RS232_STBDBUCKET.h"
#include "CAN/J1939/J1939_FF13_VECTOR_RS232_PORTTRIMTAB.h"
#include "CAN/J1939/J1939_FF14_VECTOR_RS232_STBDTRIMTAB.h"
#include "CAN/J1939/J1939_FF15_VECTOR_RS232_SIGFAULT.h"
#include "CAN/J1939/J1939_FF16_VECTOR_RS232_NFUFAULT.h"
#include "CAN/J1939/J1939_FF17_VECTOR_RS232_STA1FAULT.h"
#include "CAN/J1939/J1939_FF18_VECTOR_RS232_STA2FAULT.h"
#include "CAN/J1939/J1939_FF19_VECTOR_RS232_STA3FAULT.h"
#include "CAN/J1939/J1939_FF1A_VECTOR_RS232_CALFAULT.h"
#include "CAN/J1939/J1939_FF1B_VECTOR_RS232_INTERLOCKFAULT.h"
#include "CAN/J1939/J1939_FF51_VECTOR_ALARM_ACKNOWLEDGE.h"
#include "CAN/J1939/J1939_FF50_VECTOR_ALARM_ACKNOWLEDGE.h"
#endif // #ifndef __PROJECT_H__
