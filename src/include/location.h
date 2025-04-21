/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 25/03/2025
  * @brief VRPT-SWTS
  */

#ifndef LOCATION_H
#define LOCATION_H

#include <cmath>
#include <iostream>

class Location {
public:
  Location(double x, double y, int id) : x_(x), y_(y), id_(id) {}
  
  // Calculate the distance to another location
  double distanceTo(const Location& other) const {
    return std::sqrt(std::pow(x_ - other.x_, 2) + std::pow(y_ - other.y_, 2));
  }

  bool operator==(const Location& other) const {
    return x_ == other.getX() && y_ == other.getY();
  }

  // Getters
  double getX() const { return x_; }
  double getY() const { return y_; }
  int getId() const { return id_; }

  // Print methods
  void printLocation() const {
    std::cout << "Location(" << x_ << ", " << y_ << ")" << std::endl;
  }

  void printId() const {
    std::cout << "Location ID: " << id_ << std::endl;
  }
private:
  double x_;
  double y_;
  int id_;

};


#endif // LOCATION_H