#include "BarGauge.h"
#include "project.h" 
#include <iostream>     
#include <cmath>       

// Constructor with parameters
BGage_DirectionVector::BGage_DirectionVector(const std::string& name, int32_t x_location, int32_t y_location, bool isflipped , int ratio)
	                                                  : name(name), x_loc(x_location), y_loc(y_location),  _isflipped(isflipped), _ratio(ratio)

 {}

// Default constructor
BGage_DirectionVector::BGage_DirectionVector(): x_loc(0), y_loc(0), name("Unnamed")
{}

// Draw method
void BGage_DirectionVector::draw(int argVal) const
{
    //gets raw value 0 - 1000
    // converts to percentatge 0.00f - 100.00f
 
    float percent = (argVal / 1000.0f) * 100.0f;
    // Define constants
    const int fullWidth = 340 / _ratio;       // Full width of the screen
    const int barHeight = 24 / _ratio;       // Half of max height (50 / 2)
    const int baselineY =  y_loc + (52  / _ratio); // Baseline position (50px below top-left corner)
    const int barWidth = 8 / _ratio;        // Width of each bar
    const int gap = 4 / _ratio;              // Gap between bars
    const int centerX = x_loc + (fullWidth / 2); // Center X position of the graph plus teh offset . 

    // Clamp percentage to range [0, 100]
    percent = std::max(0.0f, std::min(percent, 100.0f));
    // Calculate the number of bars on each side
    int numBarsRight = static_cast<int>((percent - 50) / 5); // Bars to the right of center (out of 10 ) 
    int numBarsLeft = static_cast<int>((50 - percent) / 5);  // Bars to the left of center  (out of 10 ) 
    //Draw vertical line at center  . 1 px taller than barHeight
    vlineEx(centerX, baselineY, baselineY - barHeight - 1, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    // Draw the center bar
    drawrectangle(centerX - (barWidth / 2), baselineY - barHeight, barWidth, barHeight, BLACK, LAYER_FRONT);


    if (_isflipped) {
        // Flipped: Reverse the logic of drawing left and right
        std::swap(numBarsRight, numBarsLeft);
    }

    // Draw bars to the right of the center
    for (int i = 0; i < numBarsRight; ++i) {
        int barX = centerX - (barWidth / 2) + (i + 1) * (barWidth + gap);
        drawrectangle(barX, baselineY - barHeight, barWidth, barHeight, BLACK, LAYER_FRONT);
    }

    // Draw bars to the left of the center
    for (int i = 0; i < numBarsLeft; ++i) {
        int barX = centerX + (barWidth / 2) - (i + 1) * (barWidth + gap) - barWidth;
        drawrectangle(barX, baselineY - barHeight, barWidth, barHeight, BLACK, LAYER_FRONT);
    }


    //draw far right vertical line 
    int FarRightVert_x = centerX + (10 * (barWidth + gap) + (barWidth / 2) + (gap / 2));
    int FarLeftVert_x = centerX - (10 * (barWidth + gap)) - (barWidth / 2) - (gap / 2);

    vlineEx(FarRightVert_x, y_loc, baselineY, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    vlineEx(FarLeftVert_x, y_loc, baselineY, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    // Draw horizontal baseline
    hlineEx(FarLeftVert_x, baselineY, FarRightVert_x, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    //place name aboc the center line 


    if (_ratio == 4)SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    else
        if (_ratio == 2)SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 14, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
        else
            SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 24, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);



    SimpleTextDraw(centerX, y_loc, name.c_str(), BLACK, 100, LAYER_FRONT);
     
}


void BGage_DirectionVector::drawFancy(int argVal) const
{
    // -------------------------
    // Basic "percent" math
    // -------------------------
    float percent = (argVal / 1000.0f) * 100.0f;
    percent = std::max(0.0f, std::min(percent, 100.0f));

    // -------------------------
    // Bar geometry
    // -------------------------
    const int fullWidth = 340 / _ratio;
    const int baselineY = y_loc + (52 / _ratio);
    const int centerX = x_loc + (fullWidth / 2);

    // This is the "maximum" bar height at extremes
    const int barHeightMax = 24 / _ratio;
    const int titletextsize = 24 / _ratio;    // Title text size

    // We want the center bar to start at half height
    const int barHeightCenter = barHeightMax / 2;

    // The width of each vertical bar, plus the gap
    const int barWidth = 8 / _ratio;
    const int gap = 4 / _ratio;

    // -------------------------
    // Compute how many bars to each side
    // (range is 0..10, in steps of 5% from 50)
    // -------------------------
    int numBarsRight = static_cast<int>((percent - 50) / 5);
    int numBarsLeft = static_cast<int>((50 - percent) / 5);

    // Flip logic if needed
    if (_isflipped) {
        std::swap(numBarsRight, numBarsLeft);
    }

    // -------------------------
    // Draw the center line, and center bar with half-height
    // -------------------------
    // The vertical center line
    vlineEx(centerX, baselineY, baselineY - barHeightCenter - 1, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    // The actual "center" bar (half-height)
    drawrectangle(centerX - (barWidth / 2),
        baselineY - barHeightCenter,
        barWidth,
        barHeightCenter,
        BLACK,
        LAYER_FRONT);

    // -------------------------
    // Draw bars to the RIGHT of center
    // We'll scale bar height from "center height" up to "barHeightMax" via a parabola
    // -------------------------
    // If we have N bars to the right, the furthest bar is i = numBarsRight
    // We'll treat i in [1..numBarsRight], where i=1 is next to center, i=numBarsRight is the farthest
    // Parabola factor t = i / (float)numBarsRight;  height = barHeightCenter + (barHeightMax - barHeightCenter)* t^2;
    if (numBarsRight > 0) {
        for (int i = 1; i <= numBarsRight; ++i)
        {
            float t = static_cast<float>(i) / static_cast<float>(numBarsRight);
            float barH = barHeightCenter + (barHeightMax - barHeightCenter) * (t * t); // parabola

            int barX = centerX - (barWidth / 2) + i * (barWidth + gap);

            // drawrectangle expects int dimension, so cast:
            drawrectangle(barX,
                baselineY - static_cast<int>(barH),
                barWidth,
                static_cast<int>(barH),
                BLACK,
                LAYER_FRONT);
        }
    }

    // -------------------------
    // Draw bars to the LEFT of center (mirrors the above logic)
    // -------------------------
    if (numBarsLeft > 0) {
        for (int i = 1; i <= numBarsLeft; ++i)
        {
            float t = static_cast<float>(i) / static_cast<float>(numBarsLeft);
            float barH = barHeightCenter + (barHeightMax - barHeightCenter) * (t * t);

            int barX = centerX + (barWidth / 2) - i * (barWidth + gap) - barWidth;

            drawrectangle(barX,
                baselineY - static_cast<int>(barH),
                barWidth,
                static_cast<int>(barH),
                BLACK,
                LAYER_FRONT);
        }
    }

    // -------------------------
    // Draw boundary lines exactly as in your original approach
    // -------------------------
    int FarRightVert_x = centerX + (10 * (barWidth + gap) + (barWidth / 2) + (gap / 2));
    int FarLeftVert_x = centerX - (10 * (barWidth + gap)) - (barWidth / 2) - (gap / 2);

    // Vertical boundary lines
    vlineEx(FarRightVert_x, y_loc, baselineY, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    vlineEx(FarLeftVert_x, y_loc, baselineY, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    // Horizontal baseline
    hlineEx(FarLeftVert_x, baselineY, FarRightVert_x, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    // Label text 

    if (_ratio == 4)SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    else
        if (_ratio == 2)SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 14, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
        else
            SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 24, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);

   
//    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, titletextsize,HORIZONTAL_ALIGNMENT_CENTRE,VERTICAL_ALIGNMENT_TOP,0);
    SimpleTextDraw(centerX, y_loc, name.c_str(), BLACK, 100, LAYER_FRONT);
}
  
void BGage_DirectionVector::drawFancy2(int argVal) const
{
    // -------------------------
    // Basic clamped percentage
    // -------------------------
    float percent = (argVal / 1000.0f) * 100.0f;
    percent = std::max(0.0f, std::min(percent, 100.0f));

    // -------------------------
    // Bar geometry
    // -------------------------
    const int fullWidth = 340 / _ratio;
    const int baselineY = y_loc + (52 / _ratio);
    const int centerX = x_loc + (fullWidth / 2);
    const int barHeightMax = 24 / _ratio;  // the maximum bar height
    const int barHeightCenter = barHeightMax / 2; // center bar = half max
    const int barWidth = 8 / _ratio;
    const int gap = 4 / _ratio;

    // -------------------------
    // Determine how many bars we need to show
    // The center is effectively "bar 0"
    // right side = 1..numBarsRight, left side = 1..numBarsLeft
    // each is in range [0..10]
    // -------------------------
    int numBarsRight = static_cast<int>((percent - 50) / 5);
    int numBarsLeft = static_cast<int>((50 - percent) / 5);

    // Flip logic if needed
    if (_isflipped) {
        std::swap(numBarsRight, numBarsLeft);
    }

    // Constrain them to [0..10]
    if (numBarsRight < 0)  numBarsRight = 0;
    if (numBarsRight > 10) numBarsRight = 10;
    if (numBarsLeft < 0)   numBarsLeft = 0;
    if (numBarsLeft > 10)  numBarsLeft = 10;

    // -------------------------
    // Precompute a "fixed" set of parabolic heights for bars 1..10
    // That way, bar i always has the same height regardless of how many total bars
    // are being drawn. (center bar is separate, always half-height)
    // We'll store them in an array barHeightValues[i], i = 0..9
    // for the i-th bar from center (1..10).
    // The largest bar (i=10) is at barHeightMax
    // The smallest (i=1) is a little bigger than barHeightCenter.
    // -------------------------
    float barHeightValues[10];
    for (int i = 0; i < 10; i++)
    {
        // i in [0..9], corresponds to bar #1..10 from center
        float t = static_cast<float>(i + 1) / 10.0f;
        // Parabolic growth from center height up to max height
        float thisHeight = barHeightCenter + (barHeightMax - barHeightCenter) * (t * t);
        barHeightValues[i] = thisHeight;
    }

    // -------------------------
    // Draw the center bar
    // Always half-height
    // -------------------------
    // Center line:
    vlineEx(centerX,
        baselineY,
        baselineY - barHeightCenter - 1,
        NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    // Center bar rectangle:
    drawrectangle(centerX - (barWidth / 2),
        baselineY - barHeightCenter,
        barWidth,
        barHeightCenter,
        BLACK,
        LAYER_FRONT);

    // -------------------------
    // Draw bars to the RIGHT
    // We have numBarsRight bars to the right
    // The i-th bar from center has height = barHeightValues[i-1]
    // i = 1..numBarsRight
    // -------------------------
    for (int i = 1; i <= numBarsRight; i++)
    {
        float barH = barHeightValues[i - 1]; // index i-1 in [0..9]
        int barX = centerX - (barWidth / 2) + i * (barWidth + gap);

        drawrectangle(barX,
            baselineY - static_cast<int>(barH),
            barWidth,
            static_cast<int>(barH),
            BLACK,
            LAYER_FRONT);
    }

    // -------------------------
    // Draw bars to the LEFT
    // We have numBarsLeft bars to the left
    // -------------------------
    for (int i = 1; i <= numBarsLeft; i++)
    {
        float barH = barHeightValues[i - 1]; // same concept
        int barX = centerX + (barWidth / 2) - i * (barWidth + gap) - barWidth;

        drawrectangle(barX,
            baselineY - static_cast<int>(barH),
            barWidth,
            static_cast<int>(barH),
            BLACK,
            LAYER_FRONT);
    }

    // -------------------------
    // Draw boundary lines / label
    // (same code as your original)
    // -------------------------
    int FarRightVert_x = centerX + (10 * (barWidth + gap) + (barWidth / 2) + (gap / 2));
    int FarLeftVert_x = centerX - (10 * (barWidth + gap)) - (barWidth / 2) - (gap / 2);

    vlineEx(FarRightVert_x, y_loc, baselineY, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    vlineEx(FarLeftVert_x, y_loc, baselineY, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    hlineEx(FarLeftVert_x, baselineY, FarRightVert_x, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    if (_ratio == 4)SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    else
        if (_ratio == 2)SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 14, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
        else
            SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 24, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);

    SimpleTextDraw(centerX, y_loc, name.c_str(), BLACK, 100, LAYER_FRONT);
}



//   wanlue = 815 
//   
//    |                                     Namecentered                                    |
//    |                                          .                                          |
//    |                                           _   _   _   _   _   _   _                 |
//    |                                          | | | | | | | | | | | | | |                |
//    |                                          |_| |_| |_| |_| |_| |_| |_|                |
//    |-------------------------------------------------------------------------------------|
// 
//  
//    |                                     Namecentered                                    |
//    |                                          .                                          |
//    |                   _   _   _   _   _   _   _                                         |
//    |                  | | | | | | | | | | | | | |                                        |
//    |                  |_| |_| |_| |_| |_| |_| |_|                                        |
//    |-------------------------------------------------------------------------------------|
//
// 
// 
// 
// 
// 

//    |                                     Namecentered                                    |
//    |           .           |                      .                                          |
//    |
//    |-------------------------------------------------------------------------------------|
// 
// 
// 
//    full range 
//    
//    |                                     Namecentered                                    |
//    |                                          .                                          |
//    |  _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _  |
//    | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//    | |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |
//    |-------------------------------------------------------------------------------------| 
// 
// 