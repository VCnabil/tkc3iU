//------------------------------------------------------------------------------
//  TITLE :          Scrn01Indicatons.cpp
//  DESCRIPTION :    Implementation of Scrn01Indicatons screen
//  AUTHOR :         Nabil Lamriben 1/17/2025
//------------------------------------------------------------------------------
#include "Scrn01Indicatons.h"
#include "UI/screens.h"
#include <iostream>
#include <string>

//------------------------------------------------------------------------------
// LOCAL FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);


//Graphs
DVBarGraph bucket1_01;
DVBarGraph bucket2_01;

DHBarGraph nozzle1_01;
DHBarGraph nozzle2_01;

SVBarGraph interceptor1_01;
SVBarGraph interceptor2_01;




void graphSetup_01(int argindication_config)
{
    // Reset or initialize all graph objects to default state
    bucket1_01 = DVBarGraph();
    bucket2_01 = DVBarGraph();
    nozzle1_01 = DHBarGraph();
    nozzle2_01 = DHBarGraph();
    interceptor1_01 = SVBarGraph();
    interceptor2_01 = SVBarGraph();


    uint32_t indication_config = 0;
    Database_Get_CurrentValue(db_VECTOR_I14_INDICConfig, &indication_config);
    switch (indication_config) {
    case 1:
        bucket1_01 = DVBarGraph("BUCKET", "", 148, 80,
            false, SettingsGetBucketMapFlip() == flipped);
        nozzle1_01 = DHBarGraph("NOZZLE", "", 160, 200,
            true, SettingsGetNozzleMapFlip() == flipped);
        break;

    case 2:
        bucket1_01 = DVBarGraph("Port", "BKT", 140, 80,
            true, SettingsGetBucketMapFlip() == flipped);
        bucket2_01 = DVBarGraph("Stbd", "BKT", 174, 80,
            false, SettingsGetBucketMapFlip() == flipped);

        nozzle1_01 = DHBarGraph("Port", "NOZ", 80, 200,
            false, SettingsGetNozzleMapFlip() == flipped);
        nozzle2_01 = DHBarGraph("Stbd", "NOZ", 240, 200,
            false, SettingsGetNozzleMapFlip() == flipped);
        break;

    case 3:
        bucket1_01 = DVBarGraph("Port", "BKT", 140, 80,
            true, SettingsGetBucketMapFlip() == flipped);
        bucket2_01 = DVBarGraph("Stbd", "BKT", 174, 80,
            false, SettingsGetBucketMapFlip() == flipped);

        nozzle1_01 = DHBarGraph("NOZZLE", "", 160, 200,
            true, SettingsGetNozzleMapFlip() == flipped);
        break;

    case 4:
        bucket1_01 = DVBarGraph("Port", "BKT", 140, 80,
            true, SettingsGetBucketMapFlip() == flipped);
        bucket2_01 = DVBarGraph("Stbd", "BKT", 174, 80,
            false, SettingsGetBucketMapFlip() == flipped);

        nozzle1_01 = DHBarGraph("Port", "NOZ", 80, 200,
            false, SettingsGetNozzleMapFlip() == flipped);
        nozzle2_01 = DHBarGraph("Stbd", "NOZ", 240, 200,
            false, SettingsGetNozzleMapFlip() == flipped);

        interceptor1_01 = SVBarGraph("Port", "INT", 15, 10,
            true, SettingsGetTabMapFlip() == flipped);
        interceptor2_01 = SVBarGraph("Stbd", "INT", 300, 10,
            false, SettingsGetTabMapFlip() == flipped);
        break;

    case 5:
        bucket1_01 = DVBarGraph("Port", "BKT", 140, 80,
            true, SettingsGetBucketMapFlip() == flipped);
        bucket2_01 = DVBarGraph("Stbd", "BKT", 174, 80,
            false, SettingsGetBucketMapFlip() == flipped);

        nozzle1_01 = DHBarGraph("NOZZLE", "", 160, 200,
            true, SettingsGetNozzleMapFlip() == flipped);

        interceptor1_01 = SVBarGraph("Port", "INT", 15, 10,
            true, SettingsGetTabMapFlip() == flipped);
        interceptor2_01 = SVBarGraph("Stbd", "INT", 300, 10,
            false, SettingsGetTabMapFlip() == flipped);
        break;
    }
}

void graphDraw_01() {




    uint32_t indication_config = 0;
    uint32_t portNozzlePosition = 0;
    uint32_t stbdNozzlePosition = 0;
    uint32_t portBucketPosition = 0;
    uint32_t stbdBucketPosition = 0;
    uint32_t portInterceptorPosition = 0;
    uint32_t stbdInterceptorPosition = 0;
    Database_Get_CurrentValue(db_VECTOR_I14_INDICConfig, &indication_config);
    Database_Get_CurrentValue(db_VECTOR_port_nozzle, &portNozzlePosition);
    Database_Get_CurrentValue(db_VECTOR_stbd_nozzle, &stbdNozzlePosition);
    Database_Get_CurrentValue(db_VECTOR_port_bucket, &portBucketPosition);
    Database_Get_CurrentValue(db_VECTOR_stbd_bucket, &stbdBucketPosition);
    Database_Get_CurrentValue(db_VECTOR_port_trimtab, &portInterceptorPosition);
    Database_Get_CurrentValue(db_VECTOR_stbd_trimtab, &stbdInterceptorPosition);

    switch (indication_config) {
    case 1:
        nozzle1_01.draw(portNozzlePosition, false);
        bucket1_01.draw(portBucketPosition, false);
        break;
    case 2:
        nozzle1_01.draw(portNozzlePosition, false);
        nozzle2_01.draw(stbdNozzlePosition, false);
        bucket1_01.draw(portBucketPosition, false);
        bucket2_01.draw(stbdBucketPosition, false);
        break;
    case 3:
        bucket1_01.draw(portBucketPosition, false);
        bucket2_01.draw(stbdBucketPosition, false);
        nozzle1_01.draw(portNozzlePosition, false);
        break;
    case 4:
        nozzle1_01.draw(portNozzlePosition, false);
        nozzle2_01.draw(stbdNozzlePosition, false);
        bucket1_01.draw(portBucketPosition, false);
        bucket2_01.draw(stbdBucketPosition, false);
        interceptor1_01.draw(portInterceptorPosition, false);
        interceptor2_01.draw(stbdInterceptorPosition, false);
        break;
    case 5:
        nozzle1_01.draw(portNozzlePosition, false);
        bucket1_01.draw(portBucketPosition, false);
        bucket2_01.draw(stbdBucketPosition, false);
        interceptor1_01.draw(portInterceptorPosition, false);
        interceptor2_01.draw(stbdInterceptorPosition, false);
        break;
    default:
        nozzle1_01.draw(portNozzlePosition, false);
        bucket1_01.draw(0, false); // Default empty draw
        break;
    }

}

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------
 
void Scrn01IndicatonsUpdate(void)
{
    // Cache database values
    static uint32_t last_config = UINT32_MAX;
    uint32_t indication_config = 0;
    Database_Get_CurrentValue(db_VECTOR_I14_INDICConfig, &indication_config);

    if (indication_config != last_config) {
        graphSetup_01(indication_config);
        last_config = indication_config;
    }

    // Clear only the necessary layers or regions
    fill_lcd_screen(MAKERGB565(121, 137, 121), LAYER_FRONT);

    // Display station and communication mode
    const char* info = GetStationAndComModeString();
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 4, info, BLACK, 100, LAYER_FRONT);

    // Draw graphs
    graphDraw_01();
}
void Scrn01IndicatonsEnter(void)
{
 
}
void Scrn01IndicatonsCreate(void)
{
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);

    // Setup buttons and their callbacks
    ButtonBarSetHeight(48);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
    ButtonBarSetKeyText(KEYINDEX_1, FONT_INDEX_TTMAIN, 9, BLACK, "to", "start");
    ButtonBarSetKeyText(KEYINDEX_2, FONT_INDEX_TTMAIN, 9, BLACK, "INDIC", "00");

    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_WITH_TIMEOUT);

    // Draw a title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 228, "TRANSIT / AUTOPILOT STRING", BLACK, 100, LAYER_FRONT);

    // Initialize graphs
    uint32_t indication_config_update = 0;
    Database_Get_CurrentValue(db_VECTOR_I14_INDICConfig, &indication_config_update);
    graphSetup_01(indication_config_update);
}
void Scrn01IndicatonsExit(void)
{
    
}
//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------
static void _Key1Release(void* userData)
{
    MMIScreenGoto(SCREENID_START);
}
static void _Key2Release(void* userData)
{      
    MMIScreenGoto(SCREENID_SCRN00INDICATONS);
}
static void _Key3Release(void* userData)
{
}
static void _Key4Release(void* userData)
{
}
static void _Key5Release(void* userData)
{
}