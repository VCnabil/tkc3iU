#include "BarGauge.h"
#include "project.h" 
#include <iostream>     
#include <cmath>       

// Constructor with parameters
BGage_DirectionVector::BGage_DirectionVector(const std::string& name, int32_t x_location, int32_t y_location): x_loc(x_location), y_loc(y_location), name(name)
 {}

// Default constructor
BGage_DirectionVector::BGage_DirectionVector(): x_loc(0), y_loc(0), name("Unnamed")
{}

// Draw method
void BGage_DirectionVector::draw(int argVal) const
{

  /*  fyi whe nwe pass in x and y they represent the top left corner.
        i want to drea a bargrapg of fullheight 50
        a horisontal baseline is drawn
        the value will be a float percent
        at 50 percent we draw 1 bar at the center . and above the baseline
        the center bargraph that is drawn needs to be itcelf centered at tathe midposition
        values above 50 percent will make more bars to the righ, separated by a gap.
        the full actual screen width is 340
        we draw 9 bars to the right of center bar when value is 100 %
        we drw 9 bars to the left of center bar when value is 0 %
        the height of the bars remains the same and should be half of the maxheight of the graph
        */
   
    int _margin = 1;
    int _GaugeHeight = 60;
    int _GaugeWidth = lcd_get_width()- _margin- _margin;
    int _GaugeMidXPos = lcd_get_width() / 2;
    int _GaugeStartX = _margin;

    int _GaugeMidYPos = y_loc + _GaugeHeight / 2;
    int _GaugeEndY = y_loc + _GaugeHeight;
    int _GaugeStartY = y_loc;

    int _GaugeMaxBars = 9;
    int _GaugeBarWidth = 10;
    int _GaugeBarHeight = 10;
     
}

void BGage_DirectionVector::drawPercent(float percent) const {

    // Define constants
    const int fullWidth = 340;       // Full width of the screen
    const int barHeight = 25;       // Half of max height (50 / 2)
    const int baselineY = y_loc + 50; // Baseline position (50px below top-left corner)
    const int barWidth = 8;        // Width of each bar
    const int gap = 4;              // Gap between bars
    const int totalBars = 9;        // Bars on each side of center
    const int centerX =   fullWidth / 2; // Center X position of the graph

    // Clamp percentage to range [0, 100]
    percent = std::max(0.0f, std::min(percent, 100.0f));
    // Calculate the number of bars on each side
    int numBarsRight = static_cast<int>((percent - 50) / 5); // Bars to the right of center
    int numBarsLeft = static_cast<int>((50 - percent) / 5);  // Bars to the left of center



    //Draw vertical line at center  . 1 px taller than barHeight
    vlineEx(centerX, baselineY, baselineY-barHeight-1,NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
   // vlineEx(158, 120, 100, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    // Draw bars to the right of the center
    for (int i = 0; i < numBarsRight; ++i)
    {
        int barX = centerX -(barWidth/2) + (i + 1) * (barWidth + gap);
        drawrectangle(barX, baselineY - barHeight, barWidth, barHeight, BLACK, LAYER_FRONT);
    }
    // Draw the center bar
    drawrectangle(centerX - (barWidth / 2), baselineY - barHeight, barWidth, barHeight, BLACK, LAYER_FRONT);

    // Draw bars to the left of the center
    for (int i = 0; i < numBarsLeft; ++i)
    {
        int barX = centerX + (barWidth / 2) - (i + 1) * (barWidth + gap) - barWidth;
        drawrectangle(barX, baselineY - barHeight, barWidth, barHeight, BLACK, LAYER_FRONT);
    }

    //draw far right vertical line 
    int FarRightVert_x = centerX + (10 * (barWidth + gap) + (barWidth / 2) + (gap /2) );
    int FarLeftVert_x = centerX - (10 * (barWidth + gap)) - (barWidth / 2) - (gap / 2) ;

    vlineEx(FarRightVert_x, y_loc, baselineY, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    vlineEx(FarLeftVert_x, y_loc, baselineY, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    // Draw horizontal baseline
    hlineEx(FarLeftVert_x, baselineY, FarRightVert_x, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
}

//
//
// |                                                |
// |___________.___________|___________.____________|