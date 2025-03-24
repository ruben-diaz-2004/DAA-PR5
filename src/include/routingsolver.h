// RoutingSolver

// Implements routing algorithms
// Methods:

// vector<CollectionVehicle> constructGreedyCollectionRoutes()
// vector<TransportationVehicle> constructGreedyTransportRoutes()
// vector<CollectionVehicle> applyGRASP()
// vector<CollectionVehicle> applyGVNS()

#ifndef ROUTING_SOLVER_H
#define ROUTING_SOLVER_H

#include <vector>
#include "Zone.h"
#include "CollectionVehicle.h"
#include "TransferStation.h"
#include "Depot.h"

class RoutingSolver {
private:
    // Problem parameters
    double vehicleCapacity;
    double maxRouteDuration;
    std::vector<Zone> zones;
    std::vector<TransferStation> transferStations;
    Depot depot;

    // Helper methods
    TransferStation findClosestTransferStation(const Location& currentLocation) const;
    double calculateTravelTime(const Location& from, const Location& to) const;
    bool canVisitZone(const CollectionVehicle& vehicle, const Zone& zone, double remainingTime) const;

public:
    // Constructor
    RoutingSolver(
        double capacity, 
        double routeDuration, 
        const std::vector<Zone>& collectionZones,
        const std::vector<TransferStation>& swtsStations,
        const Depot& startDepot
    );

    // Main method to construct routes
    std::vector<CollectionVehicle> constructGreedyCollectionRoutes();

    // Getters and additional utility methods
    int getNumberOfZonesVisited() const;
};

#endif // ROUTING_SOLVER_H