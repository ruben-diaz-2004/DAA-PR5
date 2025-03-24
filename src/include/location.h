/**
 * @file location.h
 * @brief Location class definition
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <cmath>

class Location {
private:
    double x, y;

public:
    Location(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    
    double distanceTo(const Location& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    bool operator==(const Location& other) const {
        return x == other.x && y == other.y;
    }

    double getX() const { return x; }
    double getY() const { return y; }
};


#endif // LOCATION_H