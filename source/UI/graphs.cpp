//------------------------------------------------------------------------------
//  Vector Controls C3i Software Version 1.0
//  Author : Colby Scarbrough
//  Last edited : November 7th 2024
//  TITLE :          graphs.h
//  DESCRIPTION :    LCD Bar graph encapsulation
//------------------------------------------------------------------------------
#include "project.h"
#include <iostream>

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
               //double scaling = (i * i / 3 * 1.001);
                double scaling = (i / 3.0) * 1.001;
                outimagearea(x_location - (int)scaling, y_location + 7 + (i * 7), &bar, 0, 0, 10 + (int)scaling, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
            }
        }
        // Handle negative positions (move upwards)
        else if (position < 0) {
            for (int i = 0; i > position; i--) {
                //double scaling = (i * i / 3 * 1.001);
                double scaling = (i / 3.0) * 1.001;
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
          //  double scaling = (i * i / 4 * 1.00001);
            double scaling = (i / 8.0) * 1.001;
            outimagearea(x_location + width * 6 + (i * width * 6), y_location - scaling, &bar, 0, 0, width * 3, 10 + (int)scaling + (scaling > (int)scaling ? 1 : 0), 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    // Handle negative positions (move left)
    else if (position < 0) {
        for (int i = 0; i > position; i--) {
           // double scaling = (i * i / 4 * 1.00001);
            double scaling = (i / 8.0) * 1.001;
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