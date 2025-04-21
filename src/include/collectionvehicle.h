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

#ifndef COLLECTION_VEHICLE_H
#define COLLECTION_VEHICLE_H

#include "vehicle.h"
#include "zone.h"
#include "location.h"

class Location;

class CollectionVehicle {
public:
  CollectionVehicle(int vehicleId, double vehicleCapacity, double maxTime, double speed) : 
    id_(vehicleId), capacity_(vehicleCapacity), remainingTime_(maxTime), speed_(speed) {}

  void addLocation(const Location& loc) {
    route_.push_back(loc);
  }

  void setRoute(const std::vector<Location>& newRoute) {
    route_ = newRoute;
  }

  void setRemainingTime(double time) {
    remainingTime_ = time;
  }

  void addLoad(double wasteAmount) {
    currentLoad_ += wasteAmount;
  }

  void subtractRemainingTime(double time) {
    remainingTime_ -= time;
  }

  void resetLoad() {
    currentLoad_ = 0.0;
  }

  Location getCurrentLocation() const {
    return route_.back();
  }

  int getId() const { return id_; }
  double getCurrentLoad() const { return currentLoad_; }
  double getRemainingCapacity() const { return capacity_ - currentLoad_; }
  double getRemainingTime() const { return remainingTime_; }
  std::vector<Location> getRoute() const { return route_; }

private:
  int id_;
  double capacity_;
  double currentLoad_ = 0.0;
  double remainingTime_;
  double speed_;
  std::vector<Location> route_;
};


#endif