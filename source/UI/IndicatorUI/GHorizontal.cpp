#include "GHorizontal.h"
#include "project.h"
#include <iostream>

// DoubleSidedHorizontalBarGraph
DHBarGraph::DHBarGraph(std::string side,
                                                             std::string name,
                                                             int32_t x_location,
                                                             int32_t y_location,
                                                             bool fullscreen,
                                                             bool flipped_over_y)
    : side(side),
      name(name),
      x_location(x_location),
      y_location(y_location),
      fullscreen(fullscreen),
      flipped_over_y(flipped_over_y)
{
    m_eidBar = ElementGetNewId();
}

DHBarGraph::DHBarGraph()
    : side(""),
      name(""),
      x_location(0),
      y_location(0),
      fullscreen(false),
      flipped_over_y(false),
      m_eidBar(0)
{}

void DHBarGraph::draw(int position, bool fault) const
{
    if (fault) {
        return;
    }

    // Center around 500 => range -500..+500
    int centeredValue = position - 500;
    const int maxSteps = 10;
    int scaledValue = (centeredValue * maxSteps) / 500; // => -10..+10

    if (flipped_over_y) {
        scaledValue = -scaledValue;
    }

    int width = fullscreen ? 2 : 1;

    // bounding lines, text, etc.
    // e.g., SimpleTextDraw(...);

    // Draw reference bar at center
    outimagearea(x_location, y_location,
                 &bar, 0, 0,
                 width * 3, 10,
                 100, ALPHA_INVARIANT, LAYER_FRONT);

    // draw steps to the right or left
    if (scaledValue > 0) {
        for (int i = 1; i <= scaledValue; i++) {
            int x = x_location + width*(6*i);
            outimagearea(x, y_location,
                         &bar, 0, 0,
                         width * 3, 10,
                         100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    else if (scaledValue < 0) {
        for (int i = -1; i >= scaledValue; i--) {
            int x = x_location + width*(6*i);
            outimagearea(x, y_location,
                         &bar, 0, 0,
                         width * 3, 10,
                         100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
}

// SingleSidedHorizontalBarGraph
SHBarGraph::SHBarGraph(int32_t x_location,
                                                             int32_t y_location,
                                                             bool flipped_over_y,
                                                             bool flipped_over_x)
    : x_location(x_location),
      y_location(y_location),
      flipped_over_y(flipped_over_y),
      flipped_over_x(flipped_over_x)
{
    m_eidBar = ElementGetNewId();
}

SHBarGraph::SHBarGraph()
    : x_location(0),
      y_location(0),
      flipped_over_y(false),
      flipped_over_x(false),
      m_eidBar(0)
{}

void SHBarGraph::draw(int position) const
{
    // clamp 0..1000
    if (position < 0) position = 0;
    if (position > 1000) position = 1000;

    const int maxSteps = 10;
    int scaledValue = (position * maxSteps) / 1000;

    // baseline
    outimagearea(x_location, y_location,
                 &bar, 0, 0,
                 5, 10,
                 100, ALPHA_INVARIANT, LAYER_FRONT);

    // if flipped_over_x => draw from right side, else from left
    if (!flipped_over_x)
    {
        // left to right
        for (int i = 1; i <= scaledValue; i++) {
            int x = x_location + (i*8);
            outimagearea(x, y_location,
                         &bar, 0, 0,
                         5, 10,
                         100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
    else
    {
        // right to left
        int rightEdge = x_location + (maxSteps*8);
        for (int i = 1; i <= scaledValue; i++) {
            int x = rightEdge - (i*8);
            outimagearea(x, y_location,
                         &bar, 0, 0,
                         5, 10,
                         100, ALPHA_INVARIANT, LAYER_FRONT);
        }
    }
}
