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

#endif // #ifndef __PROJECT_H__
