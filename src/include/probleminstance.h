// ProblemInstance

// Manages the entire problem setup
// Attributes:

// zones: List of collection zones
// collectionVehicles: Available collection vehicles
// transportationVehicles: Available transportation vehicles
// transferStations: List of transfer stations
// depot: Starting point
// landfill: Waste destination
// Methods:

// void loadFromFile(string filename)
// void solve()
// void printResults()

#ifndef PROBLEMINSTANCE_H
#define PROBLEMINSTANCE_H

#include <string>
#include <vector>
#include "zone.h"
#include "collectionvehicle.h"
#include "transportationvehicle.h"
#include "transferStation.h"
#include "depot.h"
#include "landfill.h"

class ProblemInstance {
  private:
    std::vector<Zone> zones;
    std::vector<CollectionVehicle> collectionVehicles;
    std::vector<TransportationVehicle> transportationVehicles;
    std::vector<TransferStation> transferStations;
    Depot depot;
    Landfill landfill;
  public:
    ProblemInstance() = default;
    void loadFromFile(std::string filename);
    void solve();
    void printResults();
};

#endif