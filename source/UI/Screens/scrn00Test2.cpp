//------------------------------------------------------------------------------
//  TITLE :          scrn00Test2.cpp
//  DESCRIPTION :    Implementation of scrn00Test screen
//  AUTHOR :         Nabil Lamriben 1/10/2025
//------------------------------------------------------------------------------
#include "scrn00Test2.h"
#include "UI/screens.h"
#include <iostream>
#include <string>
#include <array>


//------------------------------------------------------------------------------
// LOCAL FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);
 
//------------------------------------------------------------------------------
// LOCAL VARIABLES
//------------------------------------------------------------------------------
static int TestValue = 0;
static int StepSize = 50;
static const std::array<int, 5> StepSizes = { 1, 5, 50, 100, 200 };
static size_t CurrentStepIndex = 2;
void InitializeScreenobjects();

BGage_DirectionVector G_full;
BGage_DirectionVector G_half_left;
BGage_DirectionVector G_half_right;

BGage_DirectionVector G_quarter_FarLeft;
BGage_DirectionVector G_quarter_Left;
BGage_DirectionVector G_quarter_Right;
BGage_DirectionVector G_quarter_FarRight;
//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------
void Scrn00Test2Create(void)
{

    G_full = BGage_DirectionVector("Nozzle1", 0, 50, false, 1);
    G_half_left = BGage_DirectionVector("Nozz L", 0, 104, true, 2, true);
    G_half_right = BGage_DirectionVector("Nozz R", lcd_get_width() / 2, 104, false, 2, false);
    G_quarter_FarLeft = BGage_DirectionVector("Nozz FL", (lcd_get_width() / 4) * 0, 158, true, 4, true);
    G_quarter_Left = BGage_DirectionVector("Nozz L", (lcd_get_width() / 4) * 1, 158, false, 4, false);
    G_quarter_Right = BGage_DirectionVector("Nozz R", (lcd_get_width() / 4) * 2, 158, false, 4, true);
    G_quarter_FarRight = BGage_DirectionVector("Nozz FR", (lcd_get_width() / 4) * 3, 158, true, 4);
    InitializeScreenobjects();
}

void Scrn00Test2Update(void)
{
 
    fill_lcd_screen(ALPHA_COLOR, LAYER_FRONT); //to clear the front layer wher all the drawing updates will happen
   
    std::string str = "Val: " + std::to_string(TestValue) + "    StepSize: " + std::to_string(StepSize);
    SimpleTextDraw(lcd_get_width() / 2, 20, str.c_str(), BLACK, 100, LAYER_FRONT);

 


    G_full.drawFancy2(TestValue);
    G_half_left.draw(TestValue);
    G_half_right.drawFancy(TestValue);
    G_quarter_FarLeft.drawFancy2(TestValue);
    G_quarter_Left.draw(TestValue);
    G_quarter_Right.drawFancy(TestValue);
    G_quarter_FarRight.drawFancy2(TestValue);
} 
 

void Scrn00Test2Enter(void)
{
 
}


void InitializeScreenobjects() {

    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // Setup buttons and their callbacks
    ButtonBarSetHeight(48);
    //btn1
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarSetKeyText(KEYINDEX_1, FONT_INDEX_TTMAIN, 12, BLACK, "to", "start");
    ButtonBarSetKeyImages(KEYINDEX_1, &png_BtnBorder_1, &png_BtnBorder_1);
    //btn2
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarSetKeyText(KEYINDEX_2, FONT_INDEX_TTMAIN, 12, BLACK, "TOGGLE", " ");
    ButtonBarSetKeyImages(KEYINDEX_2, &png_BtnBorder_1, &png_BtnBorder_1);
    //ButtonBarSetKeyImages(KEYINDEX_2, &png_toggle, &png_toggle);
    //btn3
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    //ButtonBarSetKeyText(KEYINDEX_3, FONT_INDEX_TTMAIN, 9, BLACK, "INC", " val");
    ButtonBarSetKeyImages(KEYINDEX_3, &png_up_s, &png_up_s);
    //btn4
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    //ButtonBarSetKeyText(KEYINDEX_4, FONT_INDEX_TTMAIN, 9, BLACK, "DEC", " val");
    ButtonBarSetKeyImages(KEYINDEX_4, &png_down_s, &png_down_s);
    //btn5
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
    // ButtonBarSetKeyText(KEYINDEX_5, FONT_INDEX_TTMAIN, 12, BLACK, "EXIT", "");
    // ButtonBarSetKeyImages(KEYINDEX_5, &png_BtnBorder_1, &png_BtnBorder_1);
    ButtonBarSetKeyImages(KEYINDEX_5, &exit_menu, &exit_menu);

    //set button action
    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_WITH_TIMEOUT);
    // Draw a title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);

    std::string strTitle = "Test Graphs";
    int _dimW = lcd_get_width();
    int _dimH = lcd_get_height();

    //concat title w: h:
    std::string str = strTitle + " w: " + std::to_string(_dimW) + " h: " + std::to_string(_dimH);
    SimpleTextDraw(lcd_get_width() / 2, 0, str.c_str(), BLACK, 100, LAYER_BACK);
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
    // Roll through step sizes: 1, 5, 50, 100, 200
    CurrentStepIndex = (CurrentStepIndex + 1) % StepSizes.size();
    StepSize = StepSizes[CurrentStepIndex];
}

static void _Key3Release(void* userData)
{
    // Increase value by the current step size
    TestValue += StepSize;
    if(TestValue > 1000){TestValue = 1000;}
}

static void _Key4Release(void* userData)
{
    // Decrease value by the current step size
    TestValue -= StepSize;
    if(TestValue < 0){TestValue = 0;}
}

static void _Key5Release(void* userData)
{
    MMIScreenGoto(SCREENID_TEST);
}
/*
  //draw 10 squares 10x10 1 px apart from each other on the x axis at y location =100
    for(int i = 0; i < 10; i++)
    {
        drawrectangle(10 +  (i * 20) +1 , 60, 10, 10,  BLACK,   LAYER_FRONT);
    }

    outimagearea(160, 120, &BarBitmap100, TestValue, 0, TestValue+50, 50, 100, ALPHA_INVARIANT, LAYER_FRONT);

*/