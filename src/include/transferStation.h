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