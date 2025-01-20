
#[[

This is the User Adjustable CMake File for this project and should be updated when new source files are added or old ones removed. 

]]

set ( PROJECTSOURCES
#list the source files to be used here:
source/CAN/can.cpp
source/CAN/J1939/J1939_FEFC_INDIC.cpp
source/CAN/J1939/J19139_FF8D_FAULTS.cpp
source/Database/database.cpp
source/NVSettings/settings.cpp
source/System/eventhandler.cpp
source/System/sdk_init.cpp
source/System/lighting.cpp
source/System/ipAddress.cpp
source/UART/uart.cpp
source/UART/NMEA0183/extractField.cpp
source/UART/NMEA0183/PVCI.cpp 
source/UI/screens.cpp
source/UI/ttfonts.cpp
source/UI/buttonbar.cpp
source/UI/keyboard.cpp
source/UI/graphs.cpp
source/data.cpp
source/main.cpp
source/VCIncShared.cpp
source/UI/IndicatorUI/GVertical.cpp
source/UI/IndicatorUI/GHorizontal.cpp
#screens
source/UI/Screens/scrn00Start.cpp
source/UI/Screens/scrn00SysOpts.cpp
source/UI/Screens/scrn01SysOpts.cpp
source/UI/screens/scrn00Test.cpp
source/UI/screens/scrn00Test2.cpp
source/UI/Screens/screen00Faults.cpp
source/UI/Screens/scrn00About.cpp
source/UI/Screens/scrn00Zerothrust.cpp
source/UI/Screens/scrn00Calibration.cpp
source/UI/Screens/scrn00Autocal.cpp
source/UI/Screens/scrn00Passcode.cpp
source/UI/Screens/scrn00CentralAlarm.cpp
source/UI/Screens/scrn00AlarmSummary.cpp
source/UI/Screens/scrn00HideZero.cpp
source/UI/Screens/scrn00debugCAN.cpp
source/UI/Screens/scrn00debugCOM.cpp
source/UI/Screens/Scrn01Faults.cpp
source/UI/Screens/scrn02Faults.cpp
source/UI/Screens/Scrn01LiveDbView.cpp
source/CAN/J1939/J1939_FF00_VECTOR_CCIM_AIN1.cpp
source/CAN/J1939/J1939_FF01_VECTOR_CCIM_AIN2.cpp
source/CAN/J1939/J1939_FF02_VECTOR_CCIM_AIN3.cpp
source/CAN/J1939/J1939_FF03_VECTOR_CCIM_AIN4.cpp
source/CAN/J1939/J1939_FF04_VECTOR_CCIM_AIN5.cpp
source/CAN/J1939/J1939_FF05_VECTOR_CCIM_AIN6.cpp
source/CAN/J1939/J1939_FF0F_VECTOR_RS232_PORTNOZZLE.cpp
source/CAN/J1939/J1939_FF10_VECTOR_RS232_STBDNOZZLE.cpp
source/CAN/J1939/J1939_FF11_VECTOR_RS232_PORTBUCKET.cpp
source/CAN/J1939/J1939_FF12_VECTOR_RS232_STBDBUCKET.cpp
source/CAN/J1939/J1939_FF13_VECTOR_RS232_PORTTRIMTAB.cpp
source/CAN/J1939/J1939_FF14_VECTOR_RS232_STBDTRIMTAB.cpp
source/CAN/J1939/J1939_FF15_VECTOR_RS232_SIGFAULT.cpp
source/CAN/J1939/J1939_FF16_VECTOR_RS232_NFUFAULT.cpp
source/CAN/J1939/J1939_FF17_VECTOR_RS232_STA1FAULT.cpp
source/CAN/J1939/J1939_FF18_VECTOR_RS232_STA2FAULT.cpp
source/CAN/J1939/J1939_FF19_VECTOR_RS232_STA3FAULT.cpp
source/CAN/J1939/J1939_FF1A_VECTOR_RS232_CALFAULT.cpp
source/CAN/J1939/J1939_FF1B_VECTOR_RS232_INTERLOCKFAULT.cpp
source/CAN/J1939/J1939_FF51_VECTOR_ALARM_ACKNOWLEDGE.cpp
source/CAN/J1939/J1939_FF50_VECTOR_ALARM_ACKNOWLEDGE.cpp
source/UI/Screens/Scrn00Indicatons.cpp
source/UI/Screens/Scrn01Indicatons.cpp
source/UI/Screens/Scrn02Indicatons.cpp
)