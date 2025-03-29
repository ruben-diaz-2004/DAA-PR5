// CollectionVehicle (Inherits from Vehicle)

// Represents small collection vehicles (CV)
// Additional attributes:

// currentRoute: Vector of zones and transfer stations visited
// Methods:

// bool canVisitZone(Zone zone)
// void addZoneToRoute(Zone zone)
// void transferToTransferStation(TransferStation station)


#ifndef COLLECTION_VEHICLE_H
#define COLLECTION_VEHICLE_H

#include <vector>
#include "vehicle.h"
#include "zone.h"
#include "location.h"

class Location;

class CollectionVehicle {
private:
  int id;
  double capacity;
  double currentLoad = 0.0;
  double remainingTime;
  double speed;
  std::vector<Location> route;

public:
  CollectionVehicle(int vehicleId, double vehicleCapacity, double maxTime, double speed) : 
      id(vehicleId), capacity(vehicleCapacity), remainingTime(maxTime), speed(speed) {}

  void addLocation(const Location& loc) {
      route.push_back(loc);
  }

  void addLoad(double wasteAmount) {
      currentLoad += wasteAmount;
  }

    void subtractRemainingTime(double time) {
        remainingTime -= time;
    }

  void resetLoad() {
      currentLoad = 0.0;
  }

  Location getCurrentLocation() const {
      return route.back();
  }

  double getCurrentLoad() const { return currentLoad; }
  double getRemainingCapacity() const { return capacity - currentLoad; }
  double getRemainingTime() const { return remainingTime; }
  std::vector<Location> getRoute() const { return route; }
};


#endif