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
private:
  int id;
  Location location;
  double wasteQuantity;

public:
  Zone(int id, const Location& loc, double waste) : id(id), location(loc), wasteQuantity(waste) {}

  int getId() const { return id; }
  Location getLocation() const { return location; }
  double getWasteQuantity() const { return wasteQuantity; }
};

#endif