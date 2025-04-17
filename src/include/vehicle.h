// Vehicle (Abstract Base Class)

// Base class for different vehicle types
// Attributes:

// id: Unique vehicle identifier
// capacity: Maximum load capacity
// currentLoad: Current load
// maxRouteDuration: Maximum allowed route time
// Methods:

// virtual bool canAcceptLoad(double wasteAmount)
// virtual void addLoad(double wasteAmount)
// virtual void clearLoad()

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
  Vehicle(std::string id, double capacity, double maxRouteDuration);
  virtual bool canAcceptLoad(double wasteAmount) = 0;
  virtual void addLoad(double wasteAmount) = 0;
  virtual void clearLoad() = 0;
  std::string getId();
  double getCapacity();
  double getCurrentLoad();
  double getMaxRouteDuration();

protected:
  std::string id_;
  double capacity;
  double currentLoad;
  double maxRouteDuration;
};


#endif