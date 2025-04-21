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

#ifndef ZONE_H
#define ZONE_H

#include <string>
#include <utility>
#include "location.h"

class Location;

class Zone {
public:
  Zone(int id, const Location& loc, double waste, double time) : id_(id), location_(loc), wasteQuantity_(waste), time_(time) {}

  int getId() const { return id_; }
  Location getLocation() const { return location_; }
  double getWasteQuantity() const { return wasteQuantity_; }
  double getTime() const { return time_; }

private:
  int id_;
  Location location_;
  double wasteQuantity_;
  double time_;
};

#endif