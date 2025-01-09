//------------------------------------------------------------------------------
//  main.c
//------------------------------------------------------------------------------
#include "project.h"
#include "crc16.h"

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
