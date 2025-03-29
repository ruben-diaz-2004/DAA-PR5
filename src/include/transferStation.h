// TransferStation

// Represents waste transfer stations (SWTS)
// Attributes:

// id: Unique identifier
// location: Geographical coordinates
// currentWasteLoad: Current waste stored
// maxCapacity: Maximum storage capacity
// Methods:

// void receiveWaste(double wasteAmount)
// double transferWaste()

#ifndef TRANSFER
#define TRANSFER

#include <string>
#include <utility>
#include "location.h"

class Location;

class TransferStation {
private:
  int id;
  Location location;

public:
  TransferStation() : id(0), location(Location()) {}
  TransferStation(int stationId, const Location& loc) : id(stationId), location(loc) {}

  Location getLocation() const { return location; }
  int getId() const { return id; }
};
    


#endif