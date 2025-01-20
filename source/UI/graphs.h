//------------------------------------------------------------------------------
//  Vector Controls C3i Software Version 1.0
//  Author : Colby Scarbrough
//  Last edited : November 7th 2024
//  TITLE :          graphs.h
//  DESCRIPTION :    LCD Bar graph encapsulation
//------------------------------------------------------------------------------

#ifndef GRAPHS_H
#define GRAPHS_H

#include <string>
#include "project.h"

class DoubleSidedVerticalBarGraph {
private:
    int32_t x_location;  // X coordinate
    int32_t y_location;  // Y coordinate
    bool flipped_over_y;        // orientation
    bool flipped_over_x;
    uint32_t m_eidBar;
    std::string name;       //Device (bucket, nozzle, interceptor)
    std::string side;       //port or stbd, station 1 or 2

public:
    // Constructor that initializes the graph
    DoubleSidedVerticalBarGraph(std::string side, std::string name, int32_t x_location, int32_t y_location, bool flipped_over_y, bool flipped_over_x);

    // Default constructor
    DoubleSidedVerticalBarGraph();

    // Method to draw the bar graph on the screen
    void draw(int position, bool fault) const;
    void draw2(int position, bool fault) const;
};

class DoubleSidedHorizontalBarGraph {
private:
    int32_t x_location;  // X coordinate
    int32_t y_location;  // Y coordinate
    bool fullscreen;
    bool flipped_over_y;
    uint32_t m_eidBar;
    std::string name;       //Device (bucket, nozzle, interceptor)
    std::string side;       //port or stbd, station 1 or 2

public:
    // Constructor that initializes the graph's position and size
    DoubleSidedHorizontalBarGraph(std::string side, std::string name, int32_t x_location, int32_t y_location, bool fullscreen, bool flipped_over_y);

    // Default constructor
    DoubleSidedHorizontalBarGraph();

    // Method to draw the bar graph on the screen
    void draw(int position, bool fault) const;
    void draw2(int position, bool fault) const;
};

class SingleSidedVerticalBarGraph {
private:
    std::string name;
    std::string side;
    int32_t x_location;  // X coordinate
    int32_t y_location;  // Y coordinate
    bool flipped_over_y;
    bool flipped_over_x;
    uint32_t m_eidBar;

public:
    // Constructor that initializes the graph's position and size
    SingleSidedVerticalBarGraph(std::string side, std::string name, int32_t x_location, int32_t y_location, bool flipped_over_y, bool flipped_over_x);

    // Default constructor
    SingleSidedVerticalBarGraph();

    // Method to draw the bar graph on the screen
    void draw(int position, bool fault) const;
    void draw2(int position, bool fault) const;
};

class SingleSidedHorizontalBarGraph {
private:
    int32_t x_location;  // X coordinate
    int32_t y_location;  // Y coordinate
    bool flipped_over_y;        // orientation
    bool flipped_over_x;
    uint32_t m_eidBar;

public:
    // Constructor that initializes the graph's position and size
    SingleSidedHorizontalBarGraph(int32_t x_location, int32_t y_location, bool flipped_over_y, bool flipped_over_x);

    // Default constructor
    SingleSidedHorizontalBarGraph();

    // Method to draw the bar graph on the screen
    void draw(int position) const;
    void draw2(int position) const;
};

#endif