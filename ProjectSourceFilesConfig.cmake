
#[[

This is the User Adjustable CMake File for this project and should be updated when new source files are added or old ones removed.

]]

set ( PROJECTSOURCES
#list the source files to be used here:
source/CAN/can.cpp
source/Database/database.cpp
source/NVSettings/settings.cpp
source/System/eventhandler.cpp
source/System/sdk_init.cpp
source/System/lighting.cpp
source/System/ipAddress.cpp
source/UART/uart.cpp
source/UART/NMEA0183/extractField.cpp
source/UI/screens.cpp
source/UI/ttfonts.cpp
source/UI/buttonbar.cpp
source/UI/keyboard.cpp
source/data.cpp
source/main.cpp
#screens
source/UI/Screens/scrn00Start.cpp
source/UI/Screens/scrn00SysOpts.cpp
source/UI/Screens/scrn01SysOpts.cpp
source/UI/screens/scrn00Test.cpp
source/UI/Screens/screen00Faults.cpp
source/UI/Screens/scrn00About.cpp
source/UI/Screens/scrn00Zerothrust.cpp
source/UI/Screens/scrn00Calibration.cpp
source/UI/Screens/scrn00Autocal.cpp
source/UI/Screens/scrn00Passcode.cpp
source/UI/Screens/scrn00CentralAlarm.cpp
source/UI/Screens/scrn00AlarmSummary.cpp
)