#include "GVertical.h"
#include "project.h"    // or whatever you need for outimagearea, vlineEx, etc.
#include <iostream>     // if you need I/O
#include <cmath>        // if you ever need abs(), etc.

// Suppose 'bar' is declared somewhere in "project.h" as 'extern Image bar;'
// or as a global. Make sure you include it so you can use &bar below.

// ---------------------------------------------
// DoubleSidedVerticalBarGraph Implementation
// ---------------------------------------------
DVBarGraph::DVBarGraph(std::string side,
                                                         std::string name,
                                                         int32_t x_location,
                                                         int32_t y_location,
                                                         bool flipped_over_y,
                                                         bool flipped_over_x)
    : side(side),
      name(name),
      x_location(x_location),
      y_location(y_location),
      flipped_over_y(flipped_over_y),
      flipped_over_x(flipped_over_x)
{
    m_eidBar = ElementGetNewId();
}

// Default constructor
DVBarGraph::DVBarGraph()
    : side(""),
      name(""),
      x_location(0),
      y_location(0),
      flipped_over_y(false),
      flipped_over_x(false),
      m_eidBar(0)
{}

void DVBarGraph::draw(int position, bool fault) const
{
    // Example logic for a double-sided bar (center=500).
    // Scale or shift as you prefer:
    //    centeredValue = position - 500 => range -500..+500
    int centeredValue = position - 500;
    const int maxSteps = 10;
    int scaledValue = (centeredValue * maxSteps) / 500; // => -10..+10

    // Flip logic if needed
    if (flipped_over_x) {
        scaledValue = -scaledValue;
    }

    // If there's a fault, you may want to skip drawing further
    if (fault) {
        // draw bounding lines only or skip everything
        return;
    }

    // Example bounding lines
    vlineEx(x_location, y_location - 50, y_location + 50,
            NORMAL, SOLID, BLACK, 100, LAYER_FRONT);

    // Draw a baseline at the "center" => y_location
    outimagearea(x_location, y_location,
                 &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);

    // If scaledValue>0 => draw downward, else upward (example)
    if (scaledValue > 0) {
        for (int i = 1; i <= scaledValue; i++) {
            int y = y_location + (7 * i);
            outimagearea(x_location, y,
                         &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    else if (scaledValue < 0) {
        for (int i = -1; i >= scaledValue; i--) {
            int y = y_location + (7 * i); // i negative => goes above center
            outimagearea(x_location, y,
                         &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
}

// ---------------------------------------------
// SingleSidedVerticalBarGraph Implementation
// ---------------------------------------------
SVBarGraph::SVBarGraph(std::string side,
                                                         std::string name,
                                                         int32_t x_location,
                                                         int32_t y_location,
                                                         bool flipped_over_y,
                                                         bool flipped_over_x)
    : side(side),
      name(name),
      x_location(x_location),
      y_location(y_location),
      flipped_over_y(flipped_over_y),
      flipped_over_x(flipped_over_x)
{
    m_eidBar = ElementGetNewId();
}

SVBarGraph::SVBarGraph()
    : side(""),
      name(""),
      x_location(0),
      y_location(0),
      flipped_over_y(false),
      flipped_over_x(false),
      m_eidBar(0)
{}

void SVBarGraph::draw(int position, bool fault) const
{
    if (fault) return;

    // clamp 0..1000, scale
    if (position < 0)   position = 0;
    if (position > 1000) position = 1000;

    const int maxSteps = 10;
    int scaledValue = (position * maxSteps) / 1000;

    // If flipped_over_y => draw from bottom up, else top down
    // Example:
    const int stepPx = 7;
    const int barHeight = maxSteps * stepPx;

    if (!flipped_over_y) {
        // baseline at top
        outimagearea(x_location, y_location,
                     &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);

        // draw downward
        for (int i = 1; i <= scaledValue; i++) {
            int y = y_location + (i * stepPx);
            outimagearea(x_location, y, &bar, 0, 0, 10, 4,
                         100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    else {
        // baseline at bottom
        outimagearea(x_location, y_location + barHeight,
                     &bar, 0, 0, 10, 4, 100, ALPHA_INVARIANT, LAYER_FRONT);

        // draw upward
        for (int i = 1; i <= scaledValue; i++) {
            int y = (y_location + barHeight) - (i * stepPx);
            outimagearea(x_location, y, &bar, 0, 0, 10, 4,
                         100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
}
