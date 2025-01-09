//------------------------------------------------------------------------------
//  TITLE :          scrn00SysOpt.cpp
//  DESCRIPTION :    Implementation of scrn00SysOpt screen
//  AUTHOR :         Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#include "project.h"
//#include "scrn00SysOpts.h"
#include "UI/screens.h"
//#include <iostream>
//#include <string>
#include "VCInc.h"

//------------------------------------------------------------------------------
// LOCAL VARIABLES
//------------------------------------------------------------------------------

// Which option are we currently highlighting to toggle?
static int g_currentOptionIndex = 0;
static bool is_use_Image = false;

//------------------------------------------------------------------------------
// LOCAL FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);

static void _DrawScreen(void);
static const char* _GetOptionName(int index);
static const char* _GetOptionValueString(int index);
static void _ToggleOptionValue(int index);

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------
void Scrn00SysOptEnter(void)
{
    // Called once when we navigate to this screen
}

void Scrn00SysOptCreate(void)
{
    // Color background
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);

    // Setup buttons (the "ButtonBar") and their callbacks
    ButtonBarSetHeight(48);
    
    
    if (is_use_Image == true) {
       // ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters);
        /*
        
        ButtonBarSetKeyImages(KEYINDEX_2, &up, &up);
        ButtonBarSetKeyImages(KEYINDEX_3, &down, &down);
        ButtonBarSetKeyImages(KEYINDEX_4, &toggle, &toggle);
        ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);*/
    }
    else {

        // KEY 1 = "back to Start"
        ButtonBarSetKeyText(KEYINDEX_1, FONT_INDEX_TTMAIN, 9, BLACK, "back to", "Start");
        // KEY 2 = "NEXT OPT"
        ButtonBarSetKeyText(KEYINDEX_2, FONT_INDEX_TTMAIN, 9, BLACK, "NEXT", "OPT");
        // KEY 3 = "PREV OPT"
        ButtonBarSetKeyText(KEYINDEX_3, FONT_INDEX_TTMAIN, 9, BLACK, "PREV", "OPT");
        // KEY 4 = "TOGG OPT"
        ButtonBarSetKeyText(KEYINDEX_4, FONT_INDEX_TTMAIN, 9, BLACK, "TOGG", "OPT");
        // KEY 5 = "EXIT"
        ButtonBarSetKeyText(KEYINDEX_5, FONT_INDEX_TTMAIN, 9, BLACK, "EXIT", "");
    }


    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);

    // Draw screen title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 25, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 5, "System Options", BLACK, 100, LAYER_FRONT);

    // We'll do the detailed lines in _DrawScreen()

    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);
    _DrawScreen();
}

void Scrn00SysOptUpdate(void)
{
    // This is called periodically. Let's redraw everything
    // in case something changes (optional).
    _DrawScreen();
}

void Scrn00SysOptExit(void)
{
    // Called once when leaving this screen
}

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------
static void _Key1Release(void* userData)
{
    // "back to Start"
    MMIScreenGoto(SCREENID_START);
}

static void _Key2Release(void* userData)
{
    // NEXT => increment current index
    g_currentOptionIndex++;
    if (g_currentOptionIndex >= SYSOPT_INDEX_MAX)
    {
        g_currentOptionIndex = 0;
    }
    _DrawScreen();
}

static void _Key3Release(void* userData)
{
    // PREV => decrement current index
    if (g_currentOptionIndex == 0)
    {
        g_currentOptionIndex = SYSOPT_INDEX_MAX - 1;
    }
    else
    {
        g_currentOptionIndex--;
    }
    _DrawScreen();
}

static void _Key4Release(void* userData)
{
    // TOGGLE the option
    _ToggleOptionValue(g_currentOptionIndex);
    _DrawScreen();
}

static void _Key5Release(void* userData)
{
    // "EXIT" => just go back to start
    MMIScreenGoto(SCREENID_START);
}

//------------------------------------------------------------------------------
// _DrawScreen()
//------------------------------------------------------------------------------
static void _DrawScreen(void)
{
    // Clear background
    fill_lcd_screen(MAKERGB565(121, 137, 121), LAYER_BACK);

    // We'll draw 6 lines, each for a setting:
    //  1) "COMMS_MODE: <value>"
    //  2) "STATION_TYPE: <value>"
    //  3) "DATA_MODE: <value>"
    //  4) "NOZZLEMAP_FLIP: <value>"
    //  5) "BUCKETMAP_FLIP: <value>"
    //  6) "TABMAP_FLIP: <value>"
    //
    // We'll highlight whichever is g_currentOptionIndex

    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 9, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);

    const int startX = 10;       // left margin
    const int startY = 60;       // top margin
    const int lineH = 12;       // line spacing

    for (int i = 0; i < SYSOPT_INDEX_MAX; i++)
    {
        char lineBuf[64];
        // Compose: "[*] COMMS_MODE: <value>" or "    COMMS_MODE: <value>"
        // If i == g_currentOptionIndex, we add an asterisk to highlight
        const char* highlight = (i == g_currentOptionIndex) ? "[*] " : "    ";
        const char* nameStr = _GetOptionName(i);
        const char* valStr = _GetOptionValueString(i);

        snprintf(lineBuf, sizeof(lineBuf), "%s%s: %s", highlight, nameStr, valStr);
        SimpleTextDraw(startX, startY + i * lineH, lineBuf, BLACK, 100, LAYER_BACK);
    }
}

//------------------------------------------------------------------------------
// Option Names
//------------------------------------------------------------------------------
static const char* _GetOptionName(int index)
{
    switch (index)
    {
    case SYSOPT_INDEX_COMMS_MODE:      return "COMMS_MODE";
    case SYSOPT_INDEX_STATION_TYPE:    return "STATION_TYPE";
    case SYSOPT_INDEX_DATA_MODE:       return "DATA_MODE";
    case SYSOPT_INDEX_NOZZLEMAP_FLIP:  return "NOZ_MAP_FLIP";
    case SYSOPT_INDEX_BUCKETMAP_FLIP:  return "BKT_MAP_FLIP";
    case SYSOPT_INDEX_TABMAP_FLIP:     return "TAB_MAP_FLIP";
    default:                           return "???";
    }
}

//------------------------------------------------------------------------------
// Build a string for the current value of each setting
//------------------------------------------------------------------------------
static const char* _GetOptionValueString(int index)
{
    static char s_valueBuf[32]; // re-used for all calls, keep it simple

    switch (index)
    {
    case SYSOPT_INDEX_COMMS_MODE:
    {
        uint8_t mode = SettingsGetCommsMode();
        if (mode == comm_mode_4)  return "comm_mode_4";
        if (mode == comm_mode_5)  return "comm_mode_5";
        snprintf(s_valueBuf, sizeof(s_valueBuf), "Unknown(%u)", mode);
        return s_valueBuf;
    }
    case SYSOPT_INDEX_STATION_TYPE:
    {
        uint8_t stType = SettingsGetStationType();
        if (stType == main_station) return "main_station";
        if (stType == wing_station) return "wing_station";
        snprintf(s_valueBuf, sizeof(s_valueBuf), "Unknown(%u)", stType);
        return s_valueBuf;
    }
    case SYSOPT_INDEX_DATA_MODE:
    {
        uint8_t dataMode = SettingsGetDataMode();
        if (dataMode == rs232_mode)      return "rs232_mode";
        if (dataMode == CANbus_mode)     return "CANbus_mode";
        if (dataMode == CANbus_GPSI_mode)return "CANbus_GPSI";
        snprintf(s_valueBuf, sizeof(s_valueBuf), "Unknown(%u)", dataMode);
        return s_valueBuf;
    }
    case SYSOPT_INDEX_NOZZLEMAP_FLIP:
    {
        uint8_t val = SettingsGetNozzleMapFlip();
        if (val == normal)  return "normal";
        if (val == flipped) return "flipped";
        snprintf(s_valueBuf, sizeof(s_valueBuf), "Unknown(%u)", val);
        return s_valueBuf;
    }
    case SYSOPT_INDEX_BUCKETMAP_FLIP:
    {
        uint8_t val = SettingsGetBucketMapFlip();
        if (val == normal)  return "normal";
        if (val == flipped) return "flipped";
        snprintf(s_valueBuf, sizeof(s_valueBuf), "Unknown(%u)", val);
        return s_valueBuf;
    }
    case SYSOPT_INDEX_TABMAP_FLIP:
    {
        uint8_t val = SettingsGetTabMapFlip();
        if (val == normal)  return "normal";
        if (val == flipped) return "flipped";
        snprintf(s_valueBuf, sizeof(s_valueBuf), "Unknown(%u)", val);
        return s_valueBuf;
    }
    default:
        return "???";
    }
}

//------------------------------------------------------------------------------
// Toggle logic for each setting
//------------------------------------------------------------------------------
static void _ToggleOptionValue(int index)
{
    switch (index)
    {
    case SYSOPT_INDEX_COMMS_MODE:
        SettingsToggleCommsMode();
        break;
    case SYSOPT_INDEX_STATION_TYPE:
        SettingsToggleStationType();
        break;
    case SYSOPT_INDEX_DATA_MODE:
        SettingsToggleDataMode();
        break;
    case SYSOPT_INDEX_NOZZLEMAP_FLIP:
        SettingsToggleNozzleMapFlip();
        break;
    case SYSOPT_INDEX_BUCKETMAP_FLIP:
        SettingsToggleBucketMapFlip();
        break;
    case SYSOPT_INDEX_TABMAP_FLIP:
        SettingsToggleTabMapFlip();
        break;
    default:
        break;
    }
}