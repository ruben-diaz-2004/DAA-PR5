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
#include <memory>
#include "zone.h"
#include "collectionvehicle.h"
#include "transportationvehicle.h"
#include "transferStation.h"
#include "depot.h"
#include "landfill.h"
#include "routingsolver.h"

class Zone;
class TransferStation;
class TransportationVehicle;

class ProblemInstance {
  private:
    // Problem parameters
    double maxCollectionRouteDuration_;
    double maxTransportRouteDuration_;
    int maxVehicles_;
    int numberOfZones_;
    double collectionVehicleCapacity_;
    double transportVehicleCapacity_;
    double vehicleSpeed_;

    // Locations
    std::vector<Zone> zones_;
    std::vector<TransferStation> transferStations_;
    Depot depot_;
    Landfill landfill_;

    // Vehicles
    std::vector<CollectionVehicle> collectionVehicles_;
    std::vector<TransportationVehicle> transportationVehicles_;

  public:
    ProblemInstance(std::string filename);

    // Getters for problem parameters
    double maxCollectionRouteDuration() const { return maxCollectionRouteDuration_; }
    double maxTransportRouteDuration() const { return maxTransportRouteDuration_; }
    int maxVehicles() const { return maxVehicles_; }
    int numberOfZones() const { return numberOfZones_; }
    double collectionVehicleCapacity() const { return collectionVehicleCapacity_; } 
    double transportVehicleCapacity() const { return transportVehicleCapacity_; }
    double vehicleSpeed() const { return vehicleSpeed_; }
    const std::vector<Zone>& zones() const { return zones_; }
    const std::vector<TransferStation>& transferStations() const { return transferStations_; }
    const Depot& depot() const { return depot_; }
    const Landfill& landfill() const { return landfill_; }
    const std::vector<CollectionVehicle>& collectionVehicles() const { return collectionVehicles_; }
    const std::vector<TransportationVehicle>& transportationVehicles() const { return transportationVehicles_; }
    const std::vector<Task>& tasks() const { return tasks_; }

    // Setters for problem parameters
    std::vector<Task> tasks_;
};

#endif