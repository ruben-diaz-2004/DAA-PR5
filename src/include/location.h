/**
 * @file location.h
 * @brief Location class definition
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <cmath>
#include <iostream>

class Location {
public:
    Location(double x = 0.0, double y = 0.0, int id = 0) : x(x), y(y), id(id) {}
    
    double distanceTo(const Location& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    bool operator==(const Location& other) const {
        return x == other.x && y == other.y;
    }

    double getX() const { return x; }
    double getY() const { return y; }

    void printLocation() const {
        std::cout << "Location(" << x << ", " << y << ")" << std::endl;
    }

    void printId() const {
        std::cout << "Location ID: " << id << std::endl;
    }
private:
    int id;
    double x;
    double y;
};


#endif // LOCATION_H