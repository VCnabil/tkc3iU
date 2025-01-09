//------------------------------------------------------------------------------
//  TITLE :          scrn00CentralAlarm.cpp
//  DESCRIPTION :    Implementation of scrn00CentralAlarm screen
//  AUTHOR :         Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#include "scrn00CentralAlarm.h"
#include "UI/screens.h"

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
void Scrn00CentralAlarmEnter(void)
{
    // to be implemented
}

void Scrn00CentralAlarmCreate(void)
{
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // to be implemented
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
    // Draw a title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 5, "Central Alarm ", WHITE, 100, LAYER_BACK);
}

void Scrn00CentralAlarmUpdate(void)
{
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // to be implemented
}

void Scrn00CentralAlarmExit(void)
{
    // to be implemented
}

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------
static void _Key1Release(void* userData)
{
    // to be implemented
}

static void _Key2Release(void* userData)
{
    // to be implemented
}

static void _Key3Release(void* userData)
{
    // to be implemented
}

static void _Key4Release(void* userData)
{
    // to be implemented
}

static void _Key5Release(void* userData)
{
    // to be implemented
}
