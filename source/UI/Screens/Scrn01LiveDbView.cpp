//------------------------------------------------------------------------------
//  TITLE :          Scrn01LiveDbView.cpp
//  DESCRIPTION :    Implementation of Scrn01LiveDbView screen
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#include "Scrn01LiveDbView.h"
#include "UI/screens.h"
#include <iostream>
#include <string>

//-----------------------------
// //------------------------------------------------------------------------------
// LOCAL vars
//------------------------------------------------------------------------------
static int gStartIndex = 0; // Start index for displaying database elements
static const int gPageSize = 10; // Number of items per page
const int titleHeight = 25; // Space reserved for the title at the top
//-------------------------------------------------
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
 
void Scrn01LiveDbViewUpdate(void)
{
    const int lineHeight = 15; // Height of each line in pixels
    char buffer[128];          // Buffer to format each database element
    // Clear the screen
    fill_lcd_screen(ALPHA_COLOR, LAYER_FRONT);

    // Draw the title
    char titleBuffer[32];
    snprintf(titleBuffer, sizeof(titleBuffer), "Page %d", (gStartIndex / gPageSize) + 1);
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 0, titleBuffer, BLACK, 100, LAYER_BACK);

    // Display entries for the current page, starting after the title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 12, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    int lineIndex = 0;

    for (int i = gStartIndex; i < gStartIndex + gPageSize && i < DATABASEINDEX_MAX; ++i) {
        DBELEMENT_T dbElement;

        // Fetch the database element for the current index
        if (DataBase_Get(&dbElement, i, 0)) { // Assuming instance 0
            // Get the description of the database element
            char description[64] = "Unknown";
            Database_GetItemDescription(description, sizeof(description), i);

            // Format the value based on its type
            switch (dbElement.DataType) {
            case DBVARTYPE_FLOAT:
                snprintf(buffer, sizeof(buffer), "%s: %.2f", description, dbElement.Data.flt);
                break;
            case DBVARTYPE_UNSIGNED_INT:
                snprintf(buffer, sizeof(buffer), "%s: %u", description, dbElement.Data.ui);
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

            // Draw the formatted string, starting below the title
            SimpleTextDraw(5, titleHeight + 5 + lineIndex * lineHeight, buffer, BLACK, 100, LAYER_FRONT);

            // Move to the next line
            ++lineIndex;
        }
    }
}
void Scrn01LiveDbViewEnter(void)
{
 
}
void Scrn01LiveDbViewCreate(void)
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
    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);
    // Draw a title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 0, "Scrn01LiveDbView", BLACK, 100, LAYER_FRONT);
}
void Scrn01LiveDbViewExit(void)
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
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // "Prev 10" button
    if (gStartIndex >= gPageSize) {
        gStartIndex -= gPageSize;
    }
    Scrn01LiveDbViewUpdate(); // Refresh the screen   
}
static void _Key3Release(void* userData)
{
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // "Next 10" button
    if (gStartIndex + gPageSize < DATABASEINDEX_MAX) {
        gStartIndex += gPageSize;
    }
    Scrn01LiveDbViewUpdate(); // Refresh the screen
}
static void _Key4Release(void* userData)
{
}
static void _Key5Release(void* userData)
{
}