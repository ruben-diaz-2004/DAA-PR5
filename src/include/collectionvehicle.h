// CollectionVehicle (Inherits from Vehicle)

// Represents small collection vehicles (CV)
// Additional attributes:

// currentRoute: Vector of zones and transfer stations visited
// Methods:

// bool canVisitZone(Zone zone)
// void addZoneToRoute(Zone zone)
// void transferToTransferStation(TransferStation station)


#ifndef COLLECTIONVEHICLE_H
#define COLLECTIONVEHICLE_H

#include <vector>
#include "vehicle.h"
#include "zone.h"

class CollectionVehicle {
private:
  int id;
  double capacity;
  double currentLoad = 0.0;
  double remainingTime;
  std::vector<Location> route;

public:
  CollectionVehicle(int vehicleId, double vehicleCapacity, double maxTime) : 
      id(vehicleId), capacity(vehicleCapacity), remainingTime(maxTime) {}

  void addLocation(const Location& loc) {
      route.push_back(loc);
  }

  void addLoad(double wasteAmount) {
      currentLoad += wasteAmount;
  }

  void resetLoadAndTime() {
      currentLoad = 0.0;
      // Reset time or reduce based on travel
  }

  Location getCurrentLocation() const {
      return route.back();
  }

  double getCurrentLoad() const { return currentLoad; }
  double getRemainingCapacity() const { return capacity - currentLoad; }
  double getRemainingTime() const { return remainingTime; }
};


#endif