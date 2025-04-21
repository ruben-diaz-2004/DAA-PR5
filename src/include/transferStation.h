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

#ifndef TRANSFER
#define TRANSFER

#include <string>
#include <utility>
#include "location.h"

class Location;

class TransferStation {
public:
  TransferStation() : id_(0), location_(Location(0,0,0)) {}
  TransferStation(int stationId, const Location& loc) : id_(stationId), location_(loc) {}

  Location getLocation() const { return location_; }
  int getId() const { return id_; }

private:
  int id_;
  Location location_;
};
    


#endif