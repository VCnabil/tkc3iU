//------------------------------------------------------------------------------
//  Vector Controls C3i Software Version 1.0
//  Author : Colby Scarbrough
//  Last edited : November 7th 2024
//  TITLE :          graphs.h
//  DESCRIPTION :    LCD Bar graph encapsulation
//------------------------------------------------------------------------------
#include "project.h"
#include <iostream>

/*
DoubleSidedVerticalBarGraph::DoubleSidedVerticalBarGraph(std::string side, std::string name, int32_t x_location, int32_t y_location, bool flipped_over_y, bool flipped_over_x)
    : side(side), name(name), x_location(x_location), y_location(y_location), flipped_over_y(flipped_over_y), flipped_over_x(flipped_over_x) {
    m_eidBar = ElementGetNewId();
}

DoubleSidedVerticalBarGraph::DoubleSidedVerticalBarGraph()
    : side(""), name(""), x_location(0), y_location(), flipped_over_y(false), flipped_over_x(false), m_eidBar(0) {};

void DoubleSidedVerticalBarGraph::draw(int position, bool fault) const {
    position = flipped_over_x ? position : position * -1;

    if (flipped_over_y) {
        // Drawing the graph frame
        vlineEx(x_location + 12, y_location - 73, y_location + 77, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
        hlineEx(x_location + 12, y_location - 73, x_location - 32, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
        hlineEx(x_location + 12, y_location + 77, x_location - 32, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

        SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_RIGHT, VERTICAL_ALIGNMENT_TOP, 0);
        SimpleTextDraw(x_location - 25, y_location - 7, side.c_str(), BLACK, 100, LAYER_FRONT);
        SimpleTextDraw(x_location - 25, y_location + 8, name.c_str(), BLACK, 100, LAYER_FRONT);

        if (fault) return;

        // Draw the initial bar at zero position
        outimagearea(x_location, y_location, &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);

        // Handle positive positions (move downwards)
        if (position > 0) {
            for (int i = 0; i < position; i++) {
                double scaling = (i * i / 3 * 1.001);
                outimagearea(x_location - (int)scaling, y_location + 7 + (i * 7), &bar, 0, 0, 10 + (int)scaling, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            }
        }
        // Handle negative positions (move upwards)
        else if (position < 0) {
            for (int i = 0; i > position; i--) {
                double scaling = (i * i / 3 * 1.001);
                outimagearea(x_location - (int)scaling, y_location - 7 + (i * 7), &bar, 0, 0, 10 + (int)scaling, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            }
        }
    }
    else {
        // Similar logic for left-sided graph
        vlineEx(x_location - 2, y_location - 73, y_location + 77, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
        hlineEx(x_location - 2, y_location - 73, x_location + 42, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
        hlineEx(x_location - 2, y_location + 77, x_location + 42, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

        SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
        SimpleTextDraw(x_location + 35, y_location - 7, side.c_str(), BLACK, 100, LAYER_FRONT);
        SimpleTextDraw(x_location + 35, y_location + 8, name.c_str(), BLACK, 100, LAYER_FRONT);

        if (fault) return;

        // Draw the initial bar at zero position
        outimagearea(x_location, y_location, &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);

        // Handle positive positions (move downwards)
        if (position > 0) {
            for (int i = 0; i < position; i++) {
                outimagearea(x_location, y_location + 7 + (i * 7), &bar, 0, 0, 10 + (i * i / 3 * 1.001), 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            }
        }
        // Handle negative positions (move upwards)
        else if (position < 0) {
            for (int i = 0; i > position; i--) {
                outimagearea(x_location, y_location - 7 + (i * 7), &bar, 0, 0, 10 + (i * i / 3 * 1.001), 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            }
        }
    }
}

DoubleSidedHorizontalBarGraph::DoubleSidedHorizontalBarGraph(std::string side, std::string name, int32_t x_location, int32_t y_location, bool fullscreen, bool flipped_over_y)
    : side(side), name(name), x_location(x_location), y_location(y_location), fullscreen(fullscreen), flipped_over_y(flipped_over_y) {
    m_eidBar = ElementGetNewId();
}

DoubleSidedHorizontalBarGraph::DoubleSidedHorizontalBarGraph()
    : side(""), name(""), x_location(0), y_location(), fullscreen(false), flipped_over_y(false), m_eidBar(0) {};

void DoubleSidedHorizontalBarGraph::draw(int position, bool fault) const {
    if (flipped_over_y) position = position * -1;
    int width = fullscreen ? 2 : 1;



    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(x_location, y_location - 40, side.c_str(), BLACK, 100, LAYER_FRONT);
    SimpleTextDraw(x_location, y_location - 25, name.c_str(), BLACK, 100, LAYER_FRONT);

    hlineEx(x_location - width * 63, y_location + 12, x_location + width * 66, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    vlineEx(x_location - width * 63, y_location + 12, y_location - 24, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    vlineEx(x_location + width * 66, y_location + 12, y_location - 24, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    if (fault) return;

    outimagearea(x_location, y_location, &bar, 0, 0, width * 3, 10, 100, ALPHA_INVARIANT, LAYER_FRONT);

    // Handle positive positions (move right)
    if (position > 0) {
        for (int i = 0; i < position; i++) {
            double scaling = (i * i / 4 * 1.00001);
            outimagearea(x_location + width * 6 + (i * width * 6), y_location - scaling, &bar, 0, 0, width * 3, 10 + (int)scaling + (scaling > (int)scaling ? 1 : 0), 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    // Handle negative positions (move left)
    else if (position < 0) {
        for (int i = 0; i > position; i--) {
            double scaling = (i * i / 4 * 1.00001);
            outimagearea(x_location - width * 6 + (i * width * 6), y_location - scaling, &bar, 0, 0, width * 3, 10 + (int)scaling + (scaling > (int)scaling ? 1 : 0), 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }


}

SingleSidedVerticalBarGraph::SingleSidedVerticalBarGraph(std::string side, std::string name, int32_t x_location, int32_t y_location, bool flipped_over_y, bool flipped_over_x)
    : side(side), name(name), x_location(x_location), y_location(y_location), flipped_over_y(flipped_over_y), flipped_over_x(flipped_over_x) {
    m_eidBar = ElementGetNewId();
}

SingleSidedVerticalBarGraph::SingleSidedVerticalBarGraph()
    : x_location(0), y_location(0), flipped_over_y(false), flipped_over_x(false), m_eidBar(0) {};

void SingleSidedVerticalBarGraph::draw(int position, bool fault) const {
    if (flipped_over_y) {

        vlineEx(x_location - 2, y_location - 3, y_location + 147, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
        hlineEx(x_location - 2, y_location - 3, x_location + 58, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
        hlineEx(x_location - 2, y_location + 147, x_location + 58, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

        if (flipped_over_x) {
            SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
            SimpleTextDraw(x_location + 35, y_location + 115, side.c_str(), BLACK, 100, LAYER_FRONT);
            SimpleTextDraw(x_location + 35, y_location + 130, name.c_str(), BLACK, 100, LAYER_FRONT);

            if (fault) return;

            outimagearea(x_location, y_location + 140, &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            for (int i = 0; i < position; i++) {
                double scaling = (i * i / 8 * 1.001);
                outimagearea(x_location, (y_location + 140) - 7 - (i * 7), &bar, 0, 0, 10 + (int)scaling, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            }
        }
        else {
            SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
            SimpleTextDraw(x_location + 35, y_location - 3, side.c_str(), BLACK, 100, LAYER_FRONT);
            SimpleTextDraw(x_location + 35, y_location + 12, name.c_str(), BLACK, 100, LAYER_FRONT);

            if (fault) return;

            outimagearea(x_location, y_location, &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            for (int i = 0; i < position; i++) {
                double scaling = (i * i / 8 * 1.001);
                outimagearea(x_location, y_location + 7 + (i * 7), &bar, 0, 0, 10 + (int)scaling, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            }
        }
    }
    else {
        vlineEx(x_location + 12, y_location - 3, y_location + 147, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
        hlineEx(x_location + 12, y_location - 3, x_location - 48, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
        hlineEx(x_location + 12, y_location + 147, x_location - 48, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

        if (flipped_over_x) {
            SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
            SimpleTextDraw(x_location - 45, y_location + 116, side.c_str(), BLACK, 100, LAYER_FRONT);
            SimpleTextDraw(x_location - 45, y_location + 131, name.c_str(), BLACK, 100, LAYER_FRONT);

            if (fault) return;

            outimagearea(x_location, y_location + 140, &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);

            for (int i = 0; i < position; i++) {
                double scaling = (i * i / 8 * 1.001);
                outimagearea(x_location - (i * i / 8 * 1.001), (y_location + 140) - 7 - (i * 7), &bar, 0, 0, 10 + (int)scaling, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            }
        }
        else {

            SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
            SimpleTextDraw(x_location - 45, y_location - 3, side.c_str(), BLACK, 100, LAYER_FRONT);
            SimpleTextDraw(x_location - 45, y_location + 12, name.c_str(), BLACK, 100, LAYER_FRONT);

            if (fault) return;

            outimagearea(x_location, y_location, &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            for (int i = 0; i < position; i++) {
                double scaling = (i * i / 8 * 1.001);
                outimagearea(x_location - (i * i / 8 * 1.001), y_location + 7 + (i * 7), &bar, 0, 0, 10 + (int)scaling, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            }


        }

    }

}

SingleSidedHorizontalBarGraph::SingleSidedHorizontalBarGraph(int32_t x_location, int32_t y_location, bool flipped_over_y, bool flipped_over_x)
    : x_location(x_location), y_location(y_location), flipped_over_y(flipped_over_y), flipped_over_x(flipped_over_x) {
    m_eidBar = ElementGetNewId();
}

SingleSidedHorizontalBarGraph::SingleSidedHorizontalBarGraph()
    : x_location(0), y_location(0), flipped_over_y(false), flipped_over_x(false), m_eidBar(0) {};

void SingleSidedHorizontalBarGraph::draw(int position) const {
    outimagearea(x_location, y_location, &bar, 0, 0, 5, 10, 100, ALPHA_INVARIANT, LAYER_FRONT);

    if (flipped_over_x) {
        for (int i = 0; i < position; i++) {
            outimagearea(x_location + 8 + (i * 8), y_location - (i * i / 8 * 1.0001), &bar, 0, 0, 5, 10 + (i * i / 8 * 1.0005), 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    else {
        for (int i = 0; i < position; i++) {
            outimagearea(x_location + 8 + (i * 8), y_location - (i * i / 8 * 1.0001), &bar, 0, 0, 5, 10 + (i * i / 8 * 1.0005), 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }

}
*/
 


DoubleSidedVerticalBarGraph::DoubleSidedVerticalBarGraph(std::string side, std::string name, int32_t x_location, int32_t y_location, bool flipped_over_y, bool flipped_over_x)
    : side(side), name(name), x_location(x_location), y_location(y_location), flipped_over_y(flipped_over_y), flipped_over_x(flipped_over_x) {
    m_eidBar = ElementGetNewId();
}

DoubleSidedVerticalBarGraph::DoubleSidedVerticalBarGraph()
    : side(""), name(""), x_location(0), y_location(), flipped_over_y(false), flipped_over_x(false), m_eidBar(0) {};

void DoubleSidedVerticalBarGraph::draw(int position, bool fault) const {

    int centeredValue = position - 500; // -500..+500
    int maxSteps = 10;
    int scaledValue = (centeredValue * maxSteps) / 500;

    // If horizontally flipped, we can invert scaledValue
    if (flipped_over_x) {
        scaledValue = -scaledValue;
    }

    // Draw bounding lines, text, etc., same as normal...
    if (fault) return;

    // Draw a small reference bar at "center"
    //   e.g. outimagearea(x_location, y_location, &bar, 0, 0, 10, 4, ...)

    // If scaledValue>0 => draw steps downward (or upward, depending on design)
    if (scaledValue > 0) {
        for (int i = 1; i <= scaledValue; i++) {
            int y = y_location + (7 * i);  // each step 7 px below
            outimagearea(x_location, y, &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    // If scaledValue<0 => draw upward
    else if (scaledValue < 0) {
        for (int i = -1; i >= scaledValue; i--) {
            int y = y_location + (7 * i);
            outimagearea(x_location, y, &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
}

DoubleSidedHorizontalBarGraph::DoubleSidedHorizontalBarGraph(std::string side, std::string name, int32_t x_location, int32_t y_location, bool fullscreen, bool flipped_over_y)
    : side(side), name(name), x_location(x_location), y_location(y_location), fullscreen(fullscreen), flipped_over_y(flipped_over_y) {
    m_eidBar = ElementGetNewId();
}

DoubleSidedHorizontalBarGraph::DoubleSidedHorizontalBarGraph()
    : side(""), name(""), x_location(0), y_location(), fullscreen(false), flipped_over_y(false), m_eidBar(0) {};

void DoubleSidedHorizontalBarGraph::draw(int position, bool fault) const {
    
    // 1. Center around 500: new range -500..+500
    int centeredValue = position - 500; // e.g. position=700 => +200

    // 2. Scale to smaller step range, e.g. -10..+10
    //    If you prefer fewer or more steps, adjust the divisor or multiplier.
    int maxSteps = 10; // pick your limit
    int scaledValue = (centeredValue * maxSteps) / 500;
    // if centeredValue=+200 => scaledValue=+4
    // if centeredValue=-300 => scaledValue=-6, etc.

    // 3. "flipped_over_y" might invert the sign. 
    //    If you want that flip logic: 
    if (flipped_over_y) {
        scaledValue = -scaledValue;
    }

    // 4. Now 'scaledValue' is in range -maxSteps..+maxSteps
    //    Example: +4 => draw 4 steps to the right, -4 => left
    //    If you have "fullscreen", keep it, or remove it if not needed.
    int width = fullscreen ? 2 : 1;

    // Draw bounding lines, text, etc. (unchanged from your original)
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15,
        HORIZONTAL_ALIGNMENT_CENTRE,
        VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(x_location, y_location - 40, side.c_str(), BLACK, 100, LAYER_FRONT);
    SimpleTextDraw(x_location, y_location - 25, name.c_str(), BLACK, 100, LAYER_FRONT);

    // Horizontal bounding lines
    hlineEx(x_location - width * 63, y_location + 12,
        x_location + width * 66, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    vlineEx(x_location - width * 63, y_location + 12,
        y_location - 24, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);
    vlineEx(x_location + width * 66, y_location + 12,
        y_location - 24, NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    // If there's a fault, return
    if (fault) {
        return;
    }

    // 5. Draw a small bar at the "center" => x_location
    //    This is your reference. Up to you if you want it or not.
    outimagearea(x_location, y_location,
        &bar, 0, 0,
        width * 3, 10,
        100, ALPHA_INVARIANT, LAYER_FRONT);

    // 6. If scaledValue>0 => draw steps to the right
    if (scaledValue > 0) {
        for (int i = 1; i <= scaledValue; i++) {
            // +i steps to the right
            int x = x_location + (width * (6 * i));
            outimagearea(x, y_location,
                &bar, 0, 0,
                width * 3, 10,
                100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    // 7. If scaledValue<0 => draw steps to the left
    else if (scaledValue < 0) {
        for (int i = -1; i >= scaledValue; i--) {
            int x = x_location + (width * (6 * i)); // i is negative
            outimagearea(x, y_location,
                &bar, 0, 0,
                width * 3, 10,
                100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }

}

SingleSidedVerticalBarGraph::SingleSidedVerticalBarGraph(std::string side, std::string name, int32_t x_location, int32_t y_location, bool flipped_over_y, bool flipped_over_x)
    : side(side), name(name), x_location(x_location), y_location(y_location), flipped_over_y(flipped_over_y), flipped_over_x(flipped_over_x) {
    m_eidBar = ElementGetNewId();
}

SingleSidedVerticalBarGraph::SingleSidedVerticalBarGraph()
    : x_location(0), y_location(0), flipped_over_y(false), flipped_over_x(false), m_eidBar(0) {};

void SingleSidedVerticalBarGraph::draw(int position, bool fault) const {
    if (fault) {
        return; // skip drawing if fault
    }

    // Clamp the raw data to 0..1000
    if (position < 0) position = 0;
    if (position > 1000) position = 1000;

    // Scale down to a smaller step count
    const int maxSteps = 10;    // e.g. 10 increments total
    const int stepPixels = 7;     // each increment is 7px tall
    int scaledValue = (position * maxSteps) / 1000; // 0..maxSteps

    // We'll define a "total bar height" in pixels
    // so that if flipped, we know where the "bottom" is.
    const int barHeight = maxSteps * stepPixels; // e.g. 70px total

    // baseline
    outimagearea(x_location, y_location, &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);

    // ---------------------------------------------------------
    // If !flipped_over_y: baseline is at the 'top' (y_location)
    // We draw downward.
    // ---------------------------------------------------------

    if (!flipped_over_y)
    {
        // 1) Draw a small "baseline" rectangle at the top
        outimagearea(x_location, y_location,
            &bar, 0, 0,
            10, 4,       // width=10, height=4 (example)
            100, ALPHA_INVARIANT, LAYER_FRONT);

        // 2) Draw each step downward
        for (int i = 1; i <= scaledValue; i++)
        {
            int y = y_location + (i * stepPixels);
            outimagearea(x_location, y,
                &bar, 0, 0,
                10, 4,
                100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    // ---------------------------------------------------------
    // If flipped_over_y: baseline is at the 'bottom'
    // We draw upward from that bottom.
    // ---------------------------------------------------------
    else
    {
        // 1) Baseline rectangle at the "bottom"
        //    So we shift by barHeight from the top coordinate
        outimagearea(x_location, y_location + barHeight,
            &bar, 0, 0,
            10, 4,
            100, ALPHA_INVARIANT, LAYER_FRONT);

        // 2) Draw each step upward
        //    That means subtract from that bottom coordinate
        for (int i = 1; i <= scaledValue; i++)
        {
            int y = (y_location + barHeight) - (i * stepPixels);
            outimagearea(x_location, y,
                &bar, 0, 0,
                10, 4,
                100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
}

SingleSidedHorizontalBarGraph::SingleSidedHorizontalBarGraph(int32_t x_location, int32_t y_location, bool flipped_over_y, bool flipped_over_x)
    : x_location(x_location), y_location(y_location), flipped_over_y(flipped_over_y), flipped_over_x(flipped_over_x) {
    m_eidBar = ElementGetNewId();
}

SingleSidedHorizontalBarGraph::SingleSidedHorizontalBarGraph()
    : x_location(0), y_location(0), flipped_over_y(false), flipped_over_x(false), m_eidBar(0) {};

void SingleSidedHorizontalBarGraph::draw(int position) const {
    // clamp negative
    if (position < 0) position = 0;
    if (position > 1000) position = 1000;

    // scale
    int maxSteps = 10;
    int scaledValue = (position * maxSteps) / 1000;

    // If flipped_over_x => we draw from the right side
    // Suppose x_location is left. We'll do:
    //   if (!flipped_over_x), we step forward;
    //   if  (flipped_over_x), we step backward.

    // baseline
    outimagearea(x_location, y_location, &bar, 0, 0, 5, 10, 100, ALPHA_INVARIANT, LAYER_FRONT);

    if (!flipped_over_x)
    {
        // normal: left to right
        for (int i = 1; i <= scaledValue; i++) {
            int x = x_location + (i * 8);
            outimagearea(x, y_location, &bar, 0, 0, 5, 10, 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    else
    {
        // flipped: right to left
        // Maybe x_location is still the 'left coordinate', so
        // to draw from the "far right," you might do:
        //   x_location + (maxSteps * 8) - (i * 8)
        // or handle x_location as the right anchor. It's your design.

        int rightAnchor = x_location + (maxSteps * 8);
        for (int i = 1; i <= scaledValue; i++) {
            int x = rightAnchor - (i * 8);
            outimagearea(x, y_location, &bar, 0, 0, 5, 10, 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }

}



