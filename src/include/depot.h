// Depot

// Represents the starting/ending point for vehicles
// Attributes:

// location: Geographical coordinates
// Methods:

// CollectionVehicle createCollectionVehicle()
// TransportationVehicle createTransportationVehicle()

#ifndef DEPOT_H
#define DEPOT_H

#include <utility>
#include "collectionvehicle.h"
#include "transportationvehicle.h"
#include "location.h"

class Depot {
private:
    Location location;

public:
    Depot(const Location& loc = Location(0.0, 0.0, -1)) : location(loc) {}
    
    Location getLocation() const { return location; }
};

#endif