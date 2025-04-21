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
#ifndef DEPOT_H
#define DEPOT_H

#include "location.h"

class Depot {
public:
  Depot(const Location& loc = Location(0.0, 0.0, -1)) : location_(loc) {}
    
  Location getLocation() const { return location_; }

private:
  Location location_;
};

#endif