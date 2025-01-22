//------------------------------------------------------------------------------
//  TITLE :          scrn00Test2.cpp
//  DESCRIPTION :    Implementation of scrn00Test screen
//  AUTHOR :         Nabil Lamriben 1/10/2025
//------------------------------------------------------------------------------
#include "scrn00Test2.h"
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
 


void Scrn00Test2Update(void)
{
    
}

 
 

void Scrn00Test2Enter(void)
{
 
}

void Scrn00Test2Create(void)
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
    //ButtonBarSetKeyText(KEYINDEX_2, FONT_INDEX_TTMAIN, 9, BLACK, "PN=", "222");
    //ButtonBarSetKeyText(KEYINDEX_3, FONT_INDEX_TTMAIN, 9, BLACK, "PN=", "333");
    //ButtonBarSetKeyText(KEYINDEX_5, FONT_INDEX_TTMAIN, 9, BLACK, "to", "db test");
    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);
    // Draw a title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 0, "Test page 2", BLACK, 100, LAYER_BACK);
}



void Scrn00Test2Exit(void)
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
  //  MMIScreenGoto(SCREENID_TEST);
}
