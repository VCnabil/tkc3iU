//------------------------------------------------------------------------------
//  TITLE :          scrn00Passcode.cpp
//  DESCRIPTION :    Implementation of scrn00Passcode screen
//  AUTHOR :         Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#include "scrn00Passcode.h"
#include "UI/screens.h"

// HIDE CONFIGURATION SCREEN PASSCODE = 3231
//Passcode
int entered = 0;
const int array_size = 5;
char passcode[array_size];
int passcodeScreen = 0;
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
void Scrn00PasscodeEnter(void)
{ 
  
}

void Scrn00PasscodeCreate(void)
{
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);

    // to be implemented
    ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters);
    ButtonBarSetKeyImages(KEYINDEX_2, &one, &one);
    ButtonBarSetKeyImages(KEYINDEX_3, &two, &two);
    ButtonBarSetKeyImages(KEYINDEX_4, &three, &three);
    ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);

    // Setup buttons and their callbacks
    ButtonBarSetHeight(48);
    ButtonBarSetBackgroundColour(MAKERGB565(121, 137, 121));
    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);

    // to be implemented
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 25, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 5, "System Calibration", BLACK, 100, LAYER_BACK);

    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(160, 60, "ENTER PASSWORD:", BLACK, 100, LAYER_BACK);

    hlineEx(132, 130, 116, NORMAL, SOLID, BLACK, 100, LAYER_BACK);
    hlineEx(156, 130, 140, NORMAL, SOLID, BLACK, 100, LAYER_BACK);
    hlineEx(164, 130, 180, NORMAL, SOLID, BLACK, 100, LAYER_BACK);
    hlineEx(188, 130, 204, NORMAL, SOLID, BLACK, 100, LAYER_BACK);
}

void Scrn00PasscodeUpdate(void)
{
    //vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
   // fill_lcd_screen(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // to be implemented
    if (entered < array_size) {
        passcode[entered] = '\0';
    }
    if (strcmp(passcode, "1123") == 0) {
        switch (passcodeScreen)
        {
        case 0:
            MMIScreenGoto(SCREENID_CALIBRATION);
            break;
        case 1:
            MMIScreenGoto(SCREENID_SYSOPTS01);
            break;
        }
    }
   if (strcmp(passcode, "3231") == 0) MMIScreenGoto(SCREENID_HIDEZERO);
}


void Scrn00PasscodeExit(void)
{
    memset(passcode, '\0', sizeof(passcode));
    entered = 0;
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
    if (entered == 4) {
        //fill_lcd_screen(MAKERGB565(121, 137, 121), LAYER_FRONT);
        fill_lcd_screen(WHITE, LAYER_FRONT);
        memset(passcode, '\0', sizeof(passcode));
        entered = 0;
    }
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(122 + (entered * 24), 115, "*", BLACK, 100, LAYER_FRONT);

    passcode[entered] = '1';
    entered++;

    if (entered < array_size - 1) {
        passcode[entered] = '\0';
    }
}

static void _Key3Release(void* userData)
{
    if (entered == 4) {
        //fill_lcd_screen(MAKERGB565(121, 137, 121), LAYER_FRONT);
        fill_lcd_screen(WHITE, LAYER_FRONT);
        memset(passcode, '\0', sizeof(passcode));
        entered = 0;
    }
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(122 + (entered * 24), 115, "*", BLACK, 100, LAYER_FRONT);

    passcode[entered] = '2';
    entered++;


    if (entered < array_size - 1) {
        passcode[entered] = '\0';
    }
}

static void _Key4Release(void* userData)
{
    if (entered == 4) {
        //fill_lcd_screen(MAKERGB565(121, 137, 121), LAYER_FRONT);
        fill_lcd_screen(WHITE, LAYER_FRONT);
        memset(passcode, '\0', sizeof(passcode));
        entered = 0;
    }
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(122 + (entered * 24), 115, "*", BLACK, 100, LAYER_FRONT);

    passcode[entered] = '3';
    entered++;


    if (entered < array_size - 1) {
        passcode[entered] = '\0';
    }
}

static void _Key5Release(void* userData)
{
    MMIScreenGoto(SCREENID_START);
}
