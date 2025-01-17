//------------------------------------------------------------------------------
//  TITLE :          Scrn00Indicatons.cpp
//  DESCRIPTION :    Implementation of Scrn00Indicatons screen
//  AUTHOR :         Nabil Lamriben 1/17/2025
//------------------------------------------------------------------------------
#include "Scrn00Indicatons.h"
#include "UI/screens.h"
#include "project.h"
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
DoubleSidedVerticalBarGraph bucket1;
DoubleSidedVerticalBarGraph bucket2;

DoubleSidedHorizontalBarGraph nozzle1;
DoubleSidedHorizontalBarGraph nozzle2;

SingleSidedVerticalBarGraph interceptor1;
SingleSidedVerticalBarGraph interceptor2;

/*
/*
void graphSetup() {
    // Reset or initialize all graph objects to default state
    bucket1 = DoubleSidedVerticalBarGraph();
    bucket2 = DoubleSidedVerticalBarGraph();
    nozzle1 = DoubleSidedHorizontalBarGraph();
    nozzle2 = DoubleSidedHorizontalBarGraph();
    interceptor1 = SingleSidedVerticalBarGraph();
    interceptor2 = SingleSidedVerticalBarGraph();

 
    uint32_t indication_config = 0;
    Database_Get_CurrentValue(db_VECTOR_I14_INDICConfig, &indication_config);
    switch (indication_config) {
    case 1:
        bucket1 = DoubleSidedVerticalBarGraph("BUCKET", "", 148, 80, false, SettingsGetBucketMapFlip() == flipped);
        nozzle1 = DoubleSidedHorizontalBarGraph("NOZZLE", "", 160, 200, true, SettingsGetNozzleMapFlip() == flipped);
        break;
    case 2:
        bucket1 = DoubleSidedVerticalBarGraph("Port", "BKT", 140, 80, true, SettingsGetBucketMapFlip() == flipped);
        bucket2 = DoubleSidedVerticalBarGraph("Stbd", "BKT", 174, 80, false, SettingsGetBucketMapFlip() == flipped);
        nozzle1 = DoubleSidedHorizontalBarGraph("Port", "NOZ", 80, 200, false, SettingsGetNozzleMapFlip() == flipped);
        nozzle2 = DoubleSidedHorizontalBarGraph("Stbd", "NOZ", 240, 200, false, SettingsGetNozzleMapFlip() == flipped);
        break;
    case 3:
        bucket1 = DoubleSidedVerticalBarGraph("Port", "BKT", 140, 80, true, SettingsGetBucketMapFlip() == flipped);
        bucket2 = DoubleSidedVerticalBarGraph("Stbd", "BKT", 174, 80, false, SettingsGetBucketMapFlip() == flipped);
        nozzle1 = DoubleSidedHorizontalBarGraph("NOZZLE", "", 160, 200, true, SettingsGetNozzleMapFlip() == flipped);
        break;
    case 4:
        bucket1 = DoubleSidedVerticalBarGraph("Port", "BKT", 140, 80, true, SettingsGetBucketMapFlip() == flipped);
        bucket2 = DoubleSidedVerticalBarGraph("Stbd", "BKT", 174, 80, false, SettingsGetBucketMapFlip() == flipped);
        nozzle1 = DoubleSidedHorizontalBarGraph("Port", "NOZ", 80, 200, false, SettingsGetNozzleMapFlip() == flipped);
        nozzle2 = DoubleSidedHorizontalBarGraph("Stbd", "NOZ", 240, 200, false, SettingsGetNozzleMapFlip() == flipped);
        interceptor1 = SingleSidedVerticalBarGraph("Port", "INT", 15, 10, true, SettingsGetTabMapFlip() == flipped);
        interceptor2 = SingleSidedVerticalBarGraph("Stbd", "INT", 300, 10, false, SettingsGetTabMapFlip() == flipped);
        break;
    case 5:
        bucket1 = DoubleSidedVerticalBarGraph("Port", "BKT", 140, 90, true, SettingsGetBucketMapFlip() == flipped);
        bucket2 = DoubleSidedVerticalBarGraph("Stbd", "BKT", 174, 90, false, SettingsGetBucketMapFlip() == flipped);
        nozzle1 = DoubleSidedHorizontalBarGraph("NOZZLE", "", 160, 200, true, SettingsGetNozzleMapFlip() == flipped);
        interceptor1 = SingleSidedVerticalBarGraph("Port", "INT", 15, 10, true, SettingsGetTabMapFlip() == flipped);
        interceptor2 = SingleSidedVerticalBarGraph("Stbd", "INT", 300, 10, false, SettingsGetTabMapFlip() == flipped);
        break;
    default:
        nozzle1 = DoubleSidedHorizontalBarGraph("NOZZLE", "", 160, 200, true, SettingsGetNozzleMapFlip() == flipped);
        break;
    }
}*/
    
void graphSetup(int argindication_config)
{
    // Reset or initialize all graph objects to default state
    bucket1 = DoubleSidedVerticalBarGraph();
    bucket2 = DoubleSidedVerticalBarGraph();
    nozzle1 = DoubleSidedHorizontalBarGraph();
    nozzle2 = DoubleSidedHorizontalBarGraph();
    interceptor1 = SingleSidedVerticalBarGraph();
    interceptor2 = SingleSidedVerticalBarGraph();


    uint32_t indication_config = 0;
    Database_Get_CurrentValue(db_VECTOR_I14_INDICConfig, &indication_config);
    switch (indication_config) {
    case 1:
        bucket1 = DoubleSidedVerticalBarGraph("BUCKET", "", 148, 80,
            false, SettingsGetBucketMapFlip() == flipped);
        nozzle1 = DoubleSidedHorizontalBarGraph("NOZZLE", "", 160, 200,
            true, SettingsGetNozzleMapFlip() == flipped);
        break;

    case 2:
        bucket1 = DoubleSidedVerticalBarGraph("Port", "BKT", 140, 80,
            true, SettingsGetBucketMapFlip() == flipped);
        bucket2 = DoubleSidedVerticalBarGraph("Stbd", "BKT", 174, 80,
            false, SettingsGetBucketMapFlip() == flipped);

        nozzle1 = DoubleSidedHorizontalBarGraph("Port", "NOZ", 80, 200,
            false, SettingsGetNozzleMapFlip() == flipped);
        nozzle2 = DoubleSidedHorizontalBarGraph("Stbd", "NOZ", 240, 200,
            false, SettingsGetNozzleMapFlip() == flipped);
        break;

    case 3:
        bucket1 = DoubleSidedVerticalBarGraph("Port", "BKT", 140, 80,
            true, SettingsGetBucketMapFlip() == flipped);
        bucket2 = DoubleSidedVerticalBarGraph("Stbd", "BKT", 174, 80,
            false, SettingsGetBucketMapFlip() == flipped);

        nozzle1 = DoubleSidedHorizontalBarGraph("NOZZLE", "", 160, 200,
            true, SettingsGetNozzleMapFlip() == flipped);
        break;

    case 4:
        bucket1 = DoubleSidedVerticalBarGraph("Port", "BKT", 140, 80,
            true, SettingsGetBucketMapFlip() == flipped);
        bucket2 = DoubleSidedVerticalBarGraph("Stbd", "BKT", 174, 80,
            false, SettingsGetBucketMapFlip() == flipped);

        nozzle1 = DoubleSidedHorizontalBarGraph("Port", "NOZ", 80, 200,
            false, SettingsGetNozzleMapFlip() == flipped);
        nozzle2 = DoubleSidedHorizontalBarGraph("Stbd", "NOZ", 240, 200,
            false, SettingsGetNozzleMapFlip() == flipped);

        interceptor1 = SingleSidedVerticalBarGraph("Port", "INT", 15, 10,
            true, SettingsGetTabMapFlip() == flipped);
        interceptor2 = SingleSidedVerticalBarGraph("Stbd", "INT", 300, 10,
            false, SettingsGetTabMapFlip() == flipped);
        break;

    case 5:
        bucket1 = DoubleSidedVerticalBarGraph("Port", "BKT", 140, 90,
            true, SettingsGetBucketMapFlip() == flipped);
        bucket2 = DoubleSidedVerticalBarGraph("Stbd", "BKT", 174, 90,
            false, SettingsGetBucketMapFlip() == flipped);

        nozzle1 = DoubleSidedHorizontalBarGraph("NOZZLE", "", 160, 200,
            true, SettingsGetNozzleMapFlip() == flipped);

        interceptor1 = SingleSidedVerticalBarGraph("Port", "INT", 15, 10,
            true, SettingsGetTabMapFlip() == flipped);
        interceptor2 = SingleSidedVerticalBarGraph("Stbd", "INT", 300, 10,
            false, SettingsGetTabMapFlip() == flipped);
        break;
    }
}



void graphDraw() {




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
        nozzle1.draw(portNozzlePosition, false);
        bucket1.draw(portBucketPosition, false);
        break;
    case 2:
        nozzle1.draw(portNozzlePosition, false);
        nozzle2.draw(stbdNozzlePosition, false);
        bucket1.draw(portBucketPosition, false);
        bucket2.draw(stbdBucketPosition, false);
        break;
    case 3:
            bucket1.draw(portBucketPosition, false);
            bucket2.draw(stbdBucketPosition, false);

            nozzle1.draw(portNozzlePosition, false);
    break;
    case 4:
		nozzle1.draw(portNozzlePosition, false);
		nozzle2.draw(stbdNozzlePosition, false);
		bucket1.draw(portBucketPosition, false);
		bucket2.draw(stbdBucketPosition, false);
		interceptor1.draw(portInterceptorPosition, false);
		interceptor2.draw(stbdInterceptorPosition, false);
    break;
    case 5:
		nozzle1.draw(portNozzlePosition, false);
		bucket1.draw(portBucketPosition, false);
		bucket2.draw(stbdBucketPosition, false);
		interceptor1.draw(portInterceptorPosition, false);
		interceptor2.draw(stbdInterceptorPosition, false);
        break;
        default:
            nozzle1.draw(portNozzlePosition, false);
			//nozzle2.draw(stbdNozzlePosition, false);
			//bucket1.draw(portBucketPosition, false);
			//bucket2.draw(stbdBucketPosition, false);
			break;



    }

}

// Lifecycle Functions
//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------
 
void Scrn00IndicatonsUpdate(void)
{
    // Clear the screen
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);

    fill_lcd_screen(MAKERGB565(121, 137, 121), LAYER_FRONT);
    // Display Station and Communication Mode String
    const char* info = GetStationAndComModeString();
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 4, info, BLACK, 100, LAYER_FRONT);

    graphDraw();
}
void Scrn00IndicatonsEnter(void)
{
   

}
     
void Scrn00IndicatonsCreate(void)
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
    ButtonBarSetKeyText(KEYINDEX_2, FONT_INDEX_TTMAIN, 9, BLACK, "", "");
    ButtonBarSetKeyText(KEYINDEX_3, FONT_INDEX_TTMAIN, 9, BLACK, "", "");
	ButtonBarSetKeyText(KEYINDEX_4, FONT_INDEX_TTMAIN, 9, BLACK, "", "");
    ButtonBarSetKeyText(KEYINDEX_5, FONT_INDEX_TTMAIN, 9, BLACK, "", "");
    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_WITH_TIMEOUT);
    // Draw a title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    //SimpleTextDraw(lcd_get_width() / 2, 0, "Scrn00Indicatons", BLACK, 100, LAYER_BACK);

    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 228, "TRANSIT / AUTOPILOT STRING", BLACK, 100, LAYER_FRONT);

   // graphSetup();
}
void Scrn00IndicatonsExit(void)
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
 