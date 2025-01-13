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
    const int maxLines = 10; // Max lines to fit on the screen
    const int lineHeight = 15; // Height of each line in pixels
    int lineIndex = 0; // Current line being displayed
    char buffer[128]; // Buffer to format each database element

    // Clear the screen
    fill_lcd_screen(ALPHA_COLOR, LAYER_FRONT);
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 12, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);

    // Iterate through all database elements
    for (int dbIndex = 0; dbIndex < DATABASEINDEX_MAX; ++dbIndex) {
        DBELEMENT_T dbElement;

        // Fetch the database element for the current index
        if (DataBase_Get(&dbElement, dbIndex, 0)) { // Assuming instance 0
            // Get the description of the database element
            char description[64] = "Unknown";
            Database_GetItemDescription(description, sizeof(description), dbIndex);

            // Format the value based on its type
            switch (dbElement.DataType) {
            case DBVARTYPE_FLOAT:
                snprintf(buffer, sizeof(buffer), "%s: %.2f", description, dbElement.Data.flt);
                break;
            case DBVARTYPE_INT:
                snprintf(buffer, sizeof(buffer), "%s: %d", description, dbElement.Data.i);
                break;
            case DBVARTYPE_UNSIGNED_LONG:
                snprintf(buffer, sizeof(buffer), "%s: %lu", description, dbElement.Data.ulg);
                break;
            default:
                snprintf(buffer, sizeof(buffer), "%s: <Unsupported Type>", description);
                break;
            }

            // Draw the formatted string
            SimpleTextDraw(5, 5 + lineIndex * lineHeight, buffer, BLACK, 100, LAYER_FRONT);

            // Move to the next line
            lineIndex++;
            if (lineIndex >= maxLines) {
                // Stop if we've reached the maximum visible lines
                return;
            }
        }
    }
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
    ButtonBarSetKeyText(KEYINDEX_5, FONT_INDEX_TTMAIN, 9, BLACK, "to", "test2");
    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);

    // Draw a title
  //  SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
  //  SimpleTextDraw(lcd_get_width() / 2, 0, "Test page ", BLACK, 100, LAYER_BACK);
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
