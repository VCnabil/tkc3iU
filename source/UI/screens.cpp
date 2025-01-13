//------------------------------------------------------------------------------
// screens.c
//------------------------------------------------------------------------------

#include "project.h"

static void _Key5Release(void* userData);
static void _Key5Hold(void* userData);

#if defined(ENABLE_FPS_COUNTER)
	// If this is defined it will display a frames per second count on the screen
	static void _DisplayFPSCounter(void* pUserData = nullptr);
#endif

void ScreensInit(void)
{
    // Register user screens 
    MMIRegisterScreen(SCREENID_START, Scrn00StartEnter, Scrn00StartCreate, Scrn00StartUpdate, Scrn00StartExit);
    MMIRegisterScreen(SCREENID_SYSOPTS, Scrn00SysOptUpdate, Scrn00SysOptCreate, Scrn00SysOptUpdate, Scrn00SysOptExit);
	MMIRegisterScreen(SCREENID_SYSOPTS01, Scrn01SysOptUpdate, Scrn01SysOptCreate, Scrn01SysOptUpdate, Scrn01SysOptExit);
    MMIRegisterScreen(SCREENID_TEST, Scrn00TestEnter, Scrn00TestCreate, Scrn00TestUpdate, Scrn00TestExit);
	MMIRegisterScreen(SCREENID_TEST2, Scrn00Test2Enter, Scrn00Test2Create, Scrn00Test2Update, Scrn00Test2Exit);
	//SCREENID_DEBUGCAN
	MMIRegisterScreen(SCREENID_DEBUGCAN, Scrn00DebugCANEnter, Scrn00DebugCANCreate, Scrn00DebugCANUpdate, Scrn00DebugCANExit);
	//SCREENID_DEBUGCOM
	MMIRegisterScreen(SCREENID_DEBUGCOM, Scrn00DebugCOMEnter, Scrn00DebugCOMCreate, Scrn00DebugCOMUpdate, Scrn00DebugCOMExit);


    MMIRegisterScreen(SCREENID_FAULTS, Scrn00FaultsEnter, Scrn00FaultsCreate, Scrn00FaultsUpdate, Scrn00FaultsExit);
    MMIRegisterScreen(SCREENID_ABOUT, Scrn00AboutEnter, Scrn00AboutCreate, Scrn00AboutUpdate, Scrn00AboutExit);
    MMIRegisterScreen(SCREENID_ZEROTHRUST, Scrn00ZerothrustEnter, Scrn00ZerothrustCreate, Scrn00ZerothrustUpdate, Scrn00ZerothrustExit);
	MMIRegisterScreen(SCREENID_HIDEZERO, Scrn00HideZeroEnter, Scrn00HideZeroCreate, Scrn00HideZeroUpdate, Scrn00HideZeroExit);

    MMIRegisterScreen(SCREENID_CALIBRATION, Scrn00CalibrationEnter, Scrn00CalibrationCreate, Scrn00CalibrationUpdate, Scrn00CalibrationExit);
    MMIRegisterScreen(SCREENID_AUTOCAL, Scrn00AutocalEnter, Scrn00AutocalCreate, Scrn00AutocalUpdate, Scrn00AutocalExit);
    MMIRegisterScreen(SCREENID_PASSCODE, Scrn00PasscodeEnter, Scrn00PasscodeCreate, Scrn00PasscodeUpdate, Scrn00PasscodeExit);
    MMIRegisterScreen(SCREENID_CENTRALALARM, Scrn00CentralAlarmEnter, Scrn00CentralAlarmCreate, Scrn00CentralAlarmUpdate, Scrn00CentralAlarmExit);
    MMIRegisterScreen(SCREENID_ALARMSUMMARY, Scrn00AlarmSummaryEnter, Scrn00AlarmSummaryCreate, Scrn00AlarmSummaryUpdate, Scrn00AlarmSummaryExit);
	
//
	// Initial screen.
	//MMIScreenGoto(SCREENID_PASSCODE);  
	MMIScreenGoto(SCREENID_START);

#if defined(ENABLE_FPS_COUNTER)
	// Enable the Frames Per Second counter on the screen
	MMIRegisterCallback(MMICALLBACKTYPE_POSTUPDATE, _DisplayFPSCounter, nullptr);
#endif
}

void ScreensSetupDefaultKeys(void)
{
	// Use this function to setup any keys that need to be setup the same for
	// all you screens. This can then be called from the screen create functions.

	ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);
	ButtonBarSetAnimation(BUTTONBARANIMATION_SLIDE);
	ButtonBarSetHeight(48);

	// Setup Key 5 Hold for menu access
	ButtonBarSetKeyImages(KEYINDEX_5, &lighting_ico, &lighting_ico_s);
	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
	ButtonBarRegisterKeyHoldCallback(KEYINDEX_5, _Key5Hold, nullptr, 1000, 0);
}

static void _Key5Release(void* userData)
{
	// Backlight change
	LightingEnter();
}

static void _Key5Hold(void* userData)
{
	// Display menu
//	MMIScreenGoto(SCREENID_MENU);
}

#if defined(ENABLE_FPS_COUNTER)
	// If this is defined it will display a frames per second count on the screen
	static void _DisplayFPSCounter(void* pUserData)
	{
		(void)pUserData;
		
	#define FRAME_X (lcd_get_width() / 2 - 24)
	#define FRAME_Y 1

		char str[50];

		// Draw the FPS on the screen
		blockfillEx(FRAME_X, FRAME_Y, FRAME_X + 48, FRAME_Y + 12, YELLOW, 100, LAYER_FRONT);
		sprintf(str, "FPS %u", GetMainLoopCurrentFPS());
		SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 1);
		SimpleTextDraw((FRAME_X + 24), (FRAME_Y + 1), str, BLACK, 100, LAYER_FRONT);
	#undef FRAME_X
	#undef FRAME_Y
	}
#endif // #if defined(MMI_ENABLE_FRAME_COUNTER)
