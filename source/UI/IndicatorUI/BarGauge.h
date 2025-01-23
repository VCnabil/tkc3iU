#ifndef BARGAUGE_H
#define BARGAUGE_H

#include <string>
#include <cstdint>

class BGage_DirectionVector
{
private:
    int32_t x_loc;              // X-coordinate of the gauge's location
    int32_t y_loc;              // Y-coordinate of the gauge's location
    std::string name;           // Name or label of the gauge

public:
    // Constructors
    BGage_DirectionVector( const std::string& name, int32_t x_pos, int32_t y_pos);
    BGage_DirectionVector();

    // Draw method to visualize the gauge
    void draw(int argVal) const;
    void drawPercent(float argpercent) const;
};

#endif // BARGAUGE_H


