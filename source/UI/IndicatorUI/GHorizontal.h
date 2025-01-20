#ifndef GHORIZONTAL_H
#define GHORIZONTAL_H

#include <string>
#include <cstdint>

// Forward declarations or #include "project.h" if needed
struct Image; // or whatever type 'bar' is

class DHBarGraph
{
private:
    int32_t x_location;
    int32_t y_location;
    bool fullscreen;
    bool flipped_over_y;
    uint32_t m_eidBar;
    std::string name;
    std::string side;

public:
    DHBarGraph(std::string side,
                                  std::string name,
                                  int32_t x_location,
                                  int32_t y_location,
                                  bool fullscreen,
                                  bool flipped_over_y);
    DHBarGraph();

    void draw(int position, bool fault) const;
};

class SHBarGraph
{
private:
    int32_t x_location;
    int32_t y_location;
    bool flipped_over_y;
    bool flipped_over_x;
    uint32_t m_eidBar;

public:
    SHBarGraph(int32_t x_location,
                                  int32_t y_location,
                                  bool flipped_over_y,
                                  bool flipped_over_x);
    SHBarGraph();

    void draw(int position) const;
};

#endif // GHORIZONTAL_H
