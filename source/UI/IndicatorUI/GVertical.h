#ifndef GVERTICAL_H
#define GVERTICAL_H

#include <string>
#include <cstdint>  // for int32_t, uint32_t

// Forward-declare the image or function prototypes you need:
// e.g., extern some_image_t bar; or #include "project.h" if needed.
struct Image; // If 'bar' is a struct Image, or bring it in from "project.h"

class DVBarGraph
{
private:
    int32_t x_location;
    int32_t y_location;
    bool flipped_over_y;
    bool flipped_over_x;
    uint32_t m_eidBar;
    std::string name;
    std::string side;

public:
    DVBarGraph(std::string side,
                                std::string name,
                                int32_t x_location,
                                int32_t y_location,
                                bool flipped_over_y,
                                bool flipped_over_x);
    DVBarGraph();

    // Draw method
    void draw(int position, bool fault) const;
};

class SVBarGraph
{
private:
    std::string name;
    std::string side;
    int32_t x_location;
    int32_t y_location;
    bool flipped_over_y;
    bool flipped_over_x;
    uint32_t m_eidBar;

public:
    SVBarGraph(std::string side,
                                std::string name,
                                int32_t x_location,
                                int32_t y_location,
                                bool flipped_over_y,
                                bool flipped_over_x);
    SVBarGraph();

    // Draw method
    void draw(int position, bool fault) const;
};

#endif // GVERTICAL_H
