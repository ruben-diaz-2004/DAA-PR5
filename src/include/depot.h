#ifndef DEPOT_H
#define DEPOT_H

#include <utility>
#include "collectionvehicle.h"
#include "transportationvehicle.h"
#include "location.h"

class Depot {
public:
  Depot(const Location& loc = Location(0.0, 0.0, -1)) : location_(loc) {}
    
  Location getLocation() const { return location_; }

private:
  Location location_;
};

#endif