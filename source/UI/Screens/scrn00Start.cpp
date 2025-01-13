//------------------------------------------------------------------------------
//  AUTHOR :			Nabil Lamriben 1/08/2025
//  TITLE :          scrnStart00.cpp
//  DESCRIPTION :    Implementation of scrnStart00 screen
//------------------------------------------------------------------------------
#include "scrn00Start.h"
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
	ButtonBarSetKeyText(KEYINDEX_4, FONT_INDEX_TTMAIN, 9, BLACK, "to", "faults");  
	ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);

}

void Scrn00StartUpdate(void)
{
    // Clear the screen background
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);

    // 1) Show PVCI calls
    int localPVCICount = gPVCICallCount;
    if (localPVCICount > 10000)localPVCICount = 0;
    char pvcimsg[32];
    sprintf(pvcimsg, "PVCI calls: %d", localPVCICount);
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20,
        HORIZONTAL_ALIGNMENT_CENTRE,
        VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 25, pvcimsg, BLACK, 100, LAYER_FRONT);

    // 2) Show J1939 calls
    int localJ1939Count = gJ1939CallCount;
    if (localJ1939Count > 10000)localJ1939Count = 0;    
    char j1939msg[32];
    sprintf(j1939msg, "J1939 calls: %d", localJ1939Count);
    // Draw it slightly lower on the screen
    SimpleTextDraw(lcd_get_width() / 2, 50, j1939msg, BLACK, 100, LAYER_FRONT);

    // 3) Optionally show any debug message
    SimpleTextDraw(lcd_get_width() / 2, 75, gDebugMsg, BLACK, 100, LAYER_FRONT);
	 
 
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
    MMIScreenGoto(SCREENID_SCRN01FAULTS);
}

static void _Key5Release(void* userData)
{
    // Add actions for Key 5 release
	
}