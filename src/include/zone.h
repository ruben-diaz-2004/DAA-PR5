// Zone Class

// Represents a collection zone
// Attributes:

// id: Unique identifier
// wasteQuantity: Amount of waste to be collected
// location: Geographical coordinates
// Methods:

// Getters and setters for attributes

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