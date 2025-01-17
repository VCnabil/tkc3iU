//------------------------------------------------------------------------------
//  AUTHOR :			Nabil Lamriben 1/08/2025
//  TITLE :          scrnStart00.cpp
//  DESCRIPTION :    Implementation of scrnStart00 screen
//------------------------------------------------------------------------------
#include "scrn00Start.h"
#include "project.h"
#include "UI/screens.h"
#include <iostream>
#include <string>
#include "VCInc.h" 
 
//------------------------------------------------------------------------------
// Global variables for background color
//------------------------------------------------------------------------------
//static uint8_t red = 121, green = 137, blue = 121; // Initial RGB values
 
//------------------------------------------------------------------------------
// LOCAL FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------
void Scrn00StartEnter(void)
{ 
}

void Scrn00StartCreate(void)
{	
	vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
	// Draw a title
	SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
	SimpleTextDraw(lcd_get_width() / 2, 5, "Start ", BLACK, 100, LAYER_FRONT);
	// Setup buttons and their callbacks
	ButtonBarSetHeight(48);
   	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
	ButtonBarSetKeyText(KEYINDEX_1, FONT_INDEX_TTMAIN, 9, BLACK, "to", "OPTS");
	ButtonBarSetKeyText(KEYINDEX_2, FONT_INDEX_TTMAIN, 9, BLACK, "live", "DB view");
	ButtonBarSetKeyText(KEYINDEX_3, FONT_INDEX_TTMAIN, 9, BLACK, "debug", "COM");
	ButtonBarSetKeyText(KEYINDEX_4, FONT_INDEX_TTMAIN, 9, BLACK, "faults", "00");  
    ButtonBarSetKeyText(KEYINDEX_5, FONT_INDEX_TTMAIN, 9, BLACK, "Indic", "00");
	ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);

}
void Scrn00StartUpdate(void)
{
    // Clear the screen
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);

    // Display Station and Communication Mode String
    const char* info = GetStationAndComModeString();
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 10, info, BLACK, 100, LAYER_FRONT);

    // Check if Port Nozzle is stale
    BOOL isDbStale = IsPortNozzleStale();

    // Display the staleness status on the screen
    char staleStatus[64];
    snprintf(staleStatus, sizeof(staleStatus), "Port Nozzle Stale: %s", isDbStale ? "YES" : "NO");
    SimpleTextDraw(lcd_get_width() / 2, 75, staleStatus, BLACK, 100, LAYER_FRONT);

    // Display the last debug message
    SimpleTextDraw(lcd_get_width() / 2, 90, gDebugMsg, BLACK, 100, LAYER_FRONT);

    // Take action if stale
    if (isDbStale)
    {
        SimpleTextDraw(lcd_get_width() / 2, 105, "Warning: Port Nozzle is stale!", RED, 100, LAYER_FRONT);
    }

}




void Scrn00StartExit(void)
{//
  
}

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------
static void _Key1Release(void* userData)
{
    // Add actions for Key 1 release
	MMIScreenGoto(SCREENID_SYSOPTS);
}

static void _Key2Release(void* userData)
{
    // Add actions for Key 2 release
	MMIScreenGoto(SCREENID_SCRN01LIVEDBVIEW);
}

static void _Key3Release(void* userData)
{
    // Add actions for Key 3 release
    MMIScreenGoto(SCREENID_DEBUGCOM);
	 
}

static void _Key4Release(void* userData)
{
  
	 
  //  MMIScreenGoto(SCREENID_DEBUGCAN);
    //MMIScreenGoto(SCREENID_SCRN01FAULTS);
	MMIScreenGoto(SCREENID_FAULTS);
}

static void _Key5Release(void* userData)
{
    // Add actions for Key 5 release
    MMIScreenGoto(SCREENID_SCRN00INDICATONS);
	
}

