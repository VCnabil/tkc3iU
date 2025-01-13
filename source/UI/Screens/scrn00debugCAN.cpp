//------------------------------------------------------------------------------
//  TITLE :          scrn00debugCAN.cpp
//  DESCRIPTION :    Implementation of scrn00debugCAN screen
//  AUTHOR :         Nabil Lamriben 1/10/2025
//------------------------------------------------------------------------------
#include "scrn00debugCAN.h"
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
void Scrn00DebugCANEnter(void)
{
    // to be implemented
}

void Scrn00DebugCANCreate(void)
{
    vLcdBlankerEx(MAKERGB565(200, 200, 200), ALPHA_COLOR);
    // Draw a title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 5, "Debug CAN Screen", BLACK, 100, LAYER_FRONT);
    // to be implemented
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
}

void Scrn00DebugCANUpdate(void)
{
    // to be implemented
}

void Scrn00DebugCANExit(void)
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
   // MMIScreenGoto(SCREENID_MAINMENU);
}
