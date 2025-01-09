//------------------------------------------------------------------------------
//  TITLE :          scrn00SysOpt.cpp
//  DESCRIPTION :    Implementation of scrn00SysOpt screen
//  AUTHOR :         Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#include "project.h"
#include "UI/screens.h"
#include "VCInc.h"
 
 
typedef struct
{
    const char* name;                             // Display label
    const char* (*getValueStr)(void);             // Function to get current value as string
    void (*toggleFunc)(void);                     // Function to toggle the setting
} SYSTEM_OPT_DISPLAY_T;

//------------------------------------------------------------------------------
//Function Prototypes for getting value strings.Implement these to return the current setting as a string.
 
static const char* GetCommsModeStr(void);
static const char* GetStationTypeStr(void);
static const char* GetDataModeStr(void);
static const char* GetNozzleMapFlipStr(void);
static const char* GetBucketMapFlipStr(void);
static const char* GetTabMapFlipStr(void);
static const char* GetXmit232Str(void);
static const char* GetIntSteerStr(void);


//------------------------------------------------------------------------------
// Function Prototypes for toggling settings.These should call the appropriate toggle functions from your settings system.

static void ToggleCommsMode(void);
static void ToggleStationType(void);
static void ToggleDataMode(void);
static void ToggleNozzleMapFlip(void);
static void ToggleBucketMapFlip(void);
static void ToggleTabMapFlip(void);
static void ToggleXmit232(void);
static void ToggleIntSteer(void);

//------------------------------------------------------------------------------
//Define the system options for display and interaction. Ensure the order matches the enumeration.

static SYSTEM_OPT_DISPLAY_T m_SYSTEMOPTIONS_DISPLAY[SYSOPT_INDEX_MAX] =
{
    { "COMMS_MODE",      GetCommsModeStr,      ToggleCommsMode },
    { "STATION_TYPE",    GetStationTypeStr,    ToggleStationType },
    { "DATA_MODE",       GetDataModeStr,       ToggleDataMode },
    { "NOZZLEMAP_FLIP",  GetNozzleMapFlipStr,  ToggleNozzleMapFlip },
    { "BUCKETMAP_FLIP",  GetBucketMapFlipStr,  ToggleBucketMapFlip },
    { "TABMAP_FLIP",     GetTabMapFlipStr,     ToggleTabMapFlip },
    {"XMIT 232", GetXmit232Str, ToggleXmit232},
	{"IntSteer", GetIntSteerStr, ToggleIntSteer},
 
};
int HalfSysOps = SYSOPT_INDEX_MAX / 2;

//------------------------------------------------------------------------------
///Track the currently selected option index.

static int s_currentOptionIndex = 0; // Range: 0..SYSOPT_INDEX_MAX-1

//------------------------------------------------------------------------------
//Function Prototypes for internal screen operations.

static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);

static void _DrawStaticLabels(void);
static void _DrawDynamicValues(void);
static void _DrawHighlight(void);

//------------------------------------------------------------------------------
//Getter functions to retrieve current setting values as strings.Implement these based on your settings system.

static const char* GetCommsModeStr(void)
{
    static char buffer[16];
    uint8_t mode = SettingsGetCommsMode();

    switch (mode)
    {
    case comm_mode_4:
        return "comm_mode 4";
    case comm_mode_5:
        return "comm_mode 5";
    default:
        snprintf(buffer, sizeof(buffer), "Unknown(%u)", mode);
        return buffer;
    }
}

static const char* GetStationTypeStr(void)
{
    static char buffer[16];
    uint8_t stType = SettingsGetStationType();

    switch (stType)
    {
    case main_station:
        return "StaType main";
    case wing_station:
        return "StaType wing";
    default:
        snprintf(buffer, sizeof(buffer), "Unknown(%u)", stType);
        return buffer;
    }
}

static const char* GetDataModeStr(void)
{
    static char buffer[16];
    uint8_t dataMode = SettingsGetDataMode();

    switch (dataMode)
    {
    case rs232_mode:
        return "DatMode rs232";
    case CANbus_mode:
        return "DatMode CAN";
    case CANbus_GPSI_mode:
        return "DatMode GPSI";
    default:
        snprintf(buffer, sizeof(buffer), "Unknown(%u)", dataMode);
        return buffer;
    }
}

static const char* GetNozzleMapFlipStr(void)
{
    static char buffer[16];
    uint8_t val = SettingsGetNozzleMapFlip();

    switch (val)
    {
    case normal:
        return "NNozMap normal";
    case flipped:
        return "NozMap flipped";
    default:
        snprintf(buffer, sizeof(buffer), "Unknown(%u)", val);
        return buffer;
    }
}

static const char* GetBucketMapFlipStr(void)
{
    static char buffer[16];
    uint8_t val = SettingsGetBucketMapFlip();

    switch (val)
    {
    case normal:
        return "BktMap normal";
    case flipped:
        return "BktMap flipped";
    default:
        snprintf(buffer, sizeof(buffer), "Unknown(%u)", val);
        return buffer;
    }
}

static const char* GetTabMapFlipStr(void)
{
    static char buffer[16];
    uint8_t val = SettingsGetTabMapFlip();

    switch (val)
    {
    case normal:
        return "IntMap normal";
    case flipped:
        return "IntMap flipped";
    default:
        snprintf(buffer, sizeof(buffer), "Unknown(%u)", val);
        return buffer;
    }
}

static const char* GetXmit232Str(void)
{
	static char buffer[16];
	uint8_t val = SettingsGetXmitrs232OnOff();

	switch (val)
	{
	case 1:
		return "Xmit232 ON";
	case 0:
		return "Xmit232 OFF";
	default:
		snprintf(buffer, sizeof(buffer), "Unknown(%u)", val);
		return buffer;
	}
}

static const char* GetIntSteerStr(void)
{
	static char buffer[16];
	uint8_t val = SettingsGetInSteerOnOff();

	switch (val)
	{
	case 1:
		return "IntSteer ON";
	case 0:
		return "IntSteer OFF";
	default:
		snprintf(buffer, sizeof(buffer), "Unknown(%u)", val);
		return buffer;
	}
}

//------------------------------------------------------------------------------
//Toggle functions that call the corresponding settings toggle functions.

static void ToggleCommsMode(void)
{
    SettingsToggleCommsMode();
}

static void ToggleStationType(void)
{
    SettingsToggleStationType(nullptr); // Pass nullptr as per your function signature
}

static void ToggleDataMode(void)
{
    SettingsToggleDataMode();
}

static void ToggleNozzleMapFlip(void)
{
    SettingsToggleNozzleMapFlip();
}

static void ToggleBucketMapFlip(void)
{
    SettingsToggleBucketMapFlip();
}

static void ToggleTabMapFlip(void)
{
    SettingsToggleTabMapFlip();
}

static void ToggleXmit232(void)
{
	SettingsToggleXmitrs232OnOff();
}

static void ToggleIntSteer(void)
{
	SettingsToggleInSteerOnOff();
}

//------------------------------------------------------------------------------
//Public Functions (Called by Screen Framework)

void Scrn00SysOptEnter(void)
{
    // Called once when navigating to this screen
    // Ensure that the screen is updated with current settings
    SettingsLoad();
    Scrn00SysOptUpdate();
}

void Scrn00SysOptCreate(void)
{
    // Color background
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);

    // Setup button images (ensure these are defined appropriately)
    ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters); // Back to Start
    ButtonBarSetKeyImages(KEYINDEX_2, &down, &down);               // Previous Option
    ButtonBarSetKeyImages(KEYINDEX_3, &up, &up);                   // Next Option
    ButtonBarSetKeyImages(KEYINDEX_4, &toggle, &toggle);           // Toggle Option
    ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);             // Exit to Start

    // Setup buttons and their callbacks
    ButtonBarSetHeight(48);
    ButtonBarSetBackgroundColour(MAKERGB565(121, 137, 121));
    // Make buttons always visible
    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);

    // Register callbacks
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);

    // Draw static labels on LAYER_BACK
    _DrawStaticLabels();
}

void Scrn00SysOptUpdate(void)
{
    // Clear the FRONT layer with background color
    fill_lcd_screen(MAKERGB565(121, 137, 121), LAYER_FRONT);

    // Draw dynamic values on LAYER_FRONT
    _DrawDynamicValues();

    // Draw highlight rectangle around the selected item
    _DrawHighlight();
}

void Scrn00SysOptExit(void)
{
    // Called once when leaving this screen
    // Optionally perform cleanup if necessary
}

//------------------------------------------------------------------------------
//Local Functions - Button Callbacks

static void _Key1Release(void* userData)
{
    // "Back to Start" button pressed
    MMIScreenGoto(SCREENID_PASSCODE);
}

static void _Key2Release(void* userData)
{
    // "Next Option" button pressed
    s_currentOptionIndex++;
    if (s_currentOptionIndex >= SYSOPT_INDEX_MAX)
        s_currentOptionIndex = 0; // Wrap around to first option

    // Update the screen
    Scrn00SysOptUpdate();
}

static void _Key3Release(void* userData)
{
    // "Previous Option" button pressed
    if (s_currentOptionIndex == 0)
        s_currentOptionIndex = SYSOPT_INDEX_MAX - 1; // Wrap around to last option
    else
        s_currentOptionIndex--;

    // Update the screen
    Scrn00SysOptUpdate();
}

static void _Key4Release(void* userData)
{
    // "Toggle Option" button pressed
    // Call the toggle function for the current option
    if (s_currentOptionIndex >= 0 && s_currentOptionIndex < SYSOPT_INDEX_MAX)
    {
        m_SYSTEMOPTIONS_DISPLAY[s_currentOptionIndex].toggleFunc();
    }

    // Update the screen
    Scrn00SysOptUpdate();
}

static void _Key5Release(void* userData)
{
    // "Exit to Start" button pressed
    MMIScreenGoto(SCREENID_START);
}

//------------------------------------------------------------------------------
//Local Functions - Drawing Helpers

// Draw static labels on LAYER_BACK
static void _DrawStaticLabels(void)
{
    // Draw Title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 25,
        HORIZONTAL_ALIGNMENT_CENTRE,
        VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 5, "System Options", BLACK, 100, LAYER_FRONT);

    // Setup smaller font for labels
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15,
        HORIZONTAL_ALIGNMENT_LEFT,
        VERTICAL_ALIGNMENT_TOP, 0);

    // Define starting positions for labels
    const int leftX = 10;
    const int rightX = 150;
    const int startY = 60;
    const int lineSpacing = 30;

    // Left Column Labels (3 items)
    SimpleTextDraw(leftX, startY, "DatMode = ", BLACK, 100, LAYER_BACK);
    SimpleTextDraw(leftX, startY + lineSpacing, "232 Xmit = ", BLACK, 100, LAYER_BACK);
    SimpleTextDraw(leftX, startY + 2 * lineSpacing, "NozMap = ", BLACK, 100, LAYER_BACK);
    SimpleTextDraw(leftX, startY + 3 * lineSpacing, "BktMap = ", BLACK, 100, LAYER_BACK);

    // Right Column Labels (3 items)
    SimpleTextDraw(rightX, startY, "IntMap = ", BLACK, 100, LAYER_BACK);
    SimpleTextDraw(rightX, startY + lineSpacing, "IntSteer = ", BLACK, 100, LAYER_BACK);
    SimpleTextDraw(rightX, startY + 2 * lineSpacing, "StaType = ", BLACK, 100, LAYER_BACK);
    SimpleTextDraw(rightX, startY + 3 * lineSpacing, "Xmit 232 = ", BLACK, 100, LAYER_BACK);
}

static void _DrawDynamicValues(void)
{
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 5, "System Options ", BLACK, 100, LAYER_FRONT);

    // Setup font for dynamic text
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15,
        HORIZONTAL_ALIGNMENT_LEFT,
        VERTICAL_ALIGNMENT_TOP, 0);

    // Define starting positions for dynamic text
    const int leftDynamicX = 10;   // Fixed X position for left column dynamic text
    const int rightDynamicX = 155;  // Fixed X position for right column dynamic text
    const int startY = 60;
    const int lineSpacing = 30;

    // Left Column Dynamic Values (COMMS_MODE, STATION_TYPE, DATA_MODE)
    for (int i = 0; i < HalfSysOps; i++)
    {
        const char* displayText = m_SYSTEMOPTIONS_DISPLAY[i].getValueStr();
        int yPos = startY + (i * lineSpacing);
        SimpleTextDraw(leftDynamicX, yPos, displayText, BLACK, 100, LAYER_FRONT);
    }

    // Right Column Dynamic Values (NOZZLEMAP_FLIP, BUCKETMAP_FLIP, TABMAP_FLIP)
    for (int i = 4; i < SYSOPT_INDEX_MAX; i++)
    {
        const char* displayText = m_SYSTEMOPTIONS_DISPLAY[i].getValueStr();
        int yPos = startY + ((i - HalfSysOps) * lineSpacing); // Corrected from (i - 4) to (i - 3)
        SimpleTextDraw(rightDynamicX, yPos, displayText, BLACK, 100, LAYER_FRONT);
    }
}

static void _DrawHighlight(void)
{
    // Define rectangle positions based on selected item
    const int leftRectX1 = 5;
    const int leftRectX2 = 145;
    const int rightRectX1 = 145;
    const int rightRectX2 = 315;
    const int startY = 55;
    const int rectHeight = 30;

    if (s_currentOptionIndex < HalfSysOps)
    {
        // Left Column
        int y = startY + (s_currentOptionIndex * rectHeight);
        rectangleEx(leftRectX1, y, leftRectX2, y + 30, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    }
    else
    {
        // Right Column
        int y = startY + ((s_currentOptionIndex - HalfSysOps) * rectHeight);
        rectangleEx(rightRectX1, y, rightRectX2, y + 30, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    }
}