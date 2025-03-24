#ifndef PROBLEM_INSTANCE_PARSER_H
#define PROBLEM_INSTANCE_PARSER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Location.h"
#include "Zone.h"
#include "TransferStation.h"
#include "Depot.h"
#include "Landfill.h"

class ProblemInstanceParser {
private:
    // Problem parameters
    double maxCollectionRouteDuration;
    double maxTransportRouteDuration;
    int maxVehicles;
    int numberOfZones;
    double collectionVehicleCapacity;
    double transportVehicleCapacity;
    double vehicleSpeed;

    // Locations
    Depot depot;
    Landfill landfill;
    std::vector<TransferStation> transferStations;
    std::vector<Zone> zones;

    // Parsing helpers
    void parseHeader(std::ifstream& file);
    void parseLocations(std::ifstream& file);
    void parseZones(std::ifstream& file);

public:
    // Constructor
    ProblemInstanceParser() = default;

    // Load and parse instance file
    void loadFromFile(const std::string& filename);

    // Getters for problem parameters
    double getMaxCollectionRouteDuration() const { return maxCollectionRouteDuration; }
    double getMaxTransportRouteDuration() const { return maxTransportRouteDuration; }
    int getMaxVehicles() const { return maxVehicles; }
    int getNumberOfZones() const { return numberOfZones; }
    double getCollectionVehicleCapacity() const { return collectionVehicleCapacity; }
    double getTransportVehicleCapacity() const { return transportVehicleCapacity; }
    double getVehicleSpeed() const { return vehicleSpeed; }

    // Getters for locations
    const Depot& getDepot() const { return depot; }
    const Landfill& getLandfill() const { return landfill; }
    const std::vector<TransferStation>& getTransferStations() const { return transferStations; }
    const std::vector<Zone>& getZones() const { return zones; }
};

#endif // PROBLEM_INSTANCE_PARSER_H