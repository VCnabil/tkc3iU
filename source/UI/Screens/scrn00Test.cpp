//------------------------------------------------------------------------------
//  TITLE :          scrn00Test.cpp
//  DESCRIPTION :    Implementation of scrn00Test screen
//  AUTHOR :         Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#include "scrn00Test.h"
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
 



//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------

void Scrn00TestUpdate(void)
{
    VECTOR_stack_update(PORT_BUCKET);
    VECTOR_stack_update(STBD_BUCKET);
    VECTOR_stack_update(PORT_NOZZLE);
    VECTOR_stack_update(STBD_NOZZLE);
}


void ShowScreenDimensions(void)
{
    // Retrieve screen dimensions
    int screenWidth = lcd_get_width();
    int screenHeight = lcd_get_height();

    // Clear the screen
    fill_lcd_screen(ALPHA_COLOR, LAYER_FRONT);

    // Prepare text
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Width: %d", screenWidth);

    // Display width
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(screenWidth / 2, 20, buffer, BLACK, 100, LAYER_FRONT);

    // Display height
    snprintf(buffer, sizeof(buffer), "Height: %d", screenHeight);
    SimpleTextDraw(screenWidth / 2, 50, buffer, BLACK, 100, LAYER_FRONT);
}
 

void Scrn00TestEnter(void)
{
 
}

void Scrn00TestCreate(void)
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
    ButtonBarSetKeyText(KEYINDEX_2, FONT_INDEX_TTMAIN, 9, BLACK, "prev", "10");
    ButtonBarSetKeyText(KEYINDEX_3, FONT_INDEX_TTMAIN, 9, BLACK, "next", "10");

    ButtonBarSetKeyText(KEYINDEX_5, FONT_INDEX_TTMAIN, 9, BLACK, "to", "test2");
    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);

    // Draw a title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 0, "Scrn00Test", BLACK, 100, LAYER_FRONT);
 
}



void Scrn00TestExit(void)
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

    	MMIScreenGoto(SCREENID_TEST2);
  
}
