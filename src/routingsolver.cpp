#include "./include/routingsolver.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

// Constructor
RoutingSolver::RoutingSolver(
    double capacity, 
    double routeDuration, 
    const std::vector<Zone>& collectionZones,
    const std::vector<TransferStation>& swtsStations,
    const Depot& startDepot
) : 
    vehicleCapacity(capacity),
    maxRouteDuration(routeDuration),
    zones(collectionZones),
    transferStations(swtsStations),
    depot(startDepot)
{}

// Find the closest transfer station to a given location
TransferStation RoutingSolver::findClosestTransferStation(const Location& currentLocation) const {
    TransferStation closestStation = transferStations.front();
    double minDistance = std::numeric_limits<double>::max();
    
    for (const auto& station : transferStations) {
        double distance = currentLocation.distanceTo(station.getLocation());
        if (distance < minDistance) {
            minDistance = distance;
            closestStation = station;
        }
    }
    
    return closestStation;
}

// Calculate travel time between two locations (simplified)
double RoutingSolver::calculateTravelTime(const Location& from, const Location& to) const {
    // In a real implementation, this would use actual distance and speed
    return from.distanceTo(to);
}

// Check if a vehicle can visit a zone within remaining time and capacity
bool RoutingSolver::canVisitZone(const CollectionVehicle& vehicle, const Zone& zone, double remainingTime) const {
    // Check if zone waste fits in vehicle capacity
    if (zone.getWasteQuantity() > vehicle.getRemainingCapacity()) {
        return false;
    }
    
    // Estimate time to visit zone, transfer station, and return to depot
    double zoneVisitTime = calculateTravelTime(vehicle.getCurrentLocation(), zone.getLocation());
    double transferStationTime = calculateTravelTime(zone.getLocation(), findClosestTransferStation(zone.getLocation()).getLocation());
    double returnToDepotTime = calculateTravelTime(findClosestTransferStation(zone.getLocation()).getLocation(), depot.getLocation());
    
    return zoneVisitTime + transferStationTime + returnToDepotTime <= remainingTime;
}

// Construct collection vehicle routes using greedy approach
std::vector<CollectionVehicle> RoutingSolver::constructGreedyCollectionRoutes() {
    std::vector<CollectionVehicle> routes;
    std::vector<Zone> unassignedZones = zones;
    
    // Continue until all zones are assigned
    while (!unassignedZones.empty()) {
        // Create a new vehicle starting from the depot
        CollectionVehicle currentVehicle(routes.size() + 1, vehicleCapacity, maxRouteDuration);
        currentVehicle.addLocation(depot.getLocation());
        
        // Continue adding zones to this vehicle's route
        while (!unassignedZones.empty()) {
            // Find the closest unassigned zone to the current vehicle's location
            Zone* bestZone = nullptr;
            double minDistance = std::numeric_limits<double>::max();
            
            for (auto& zone : unassignedZones) {
                double distance = currentVehicle.getCurrentLocation().distanceTo(zone.getLocation());
                if (distance < minDistance) {
                    // Check if zone can be visited within vehicle constraints
                    if (canVisitZone(currentVehicle, zone, currentVehicle.getRemainingTime())) {
                        minDistance = distance;
                        bestZone = &zone;
                    }
                }
            }
            
            // If no zone can be visited, move to transfer station and reset
            if (!bestZone) {
                // Find closest transfer station
                TransferStation closestStation = findClosestTransferStation(currentVehicle.getCurrentLocation());
                
                // Add transfer station to route and reset vehicle
                currentVehicle.addLocation(closestStation.getLocation());
                currentVehicle.resetLoadAndTime();
                
                break;  // Force creating a new vehicle
            }
            
            // Add best zone to route
            currentVehicle.addLocation(bestZone->getLocation());
            currentVehicle.addLoad(bestZone->getWasteQuantity());
            
            // Remove zone from unassigned list
            unassignedZones.erase(
                std::remove_if(unassignedZones.begin(), unassignedZones.end(), 
                    [&](const Zone& z) { return z.getLocation() == bestZone->getLocation(); }),
                unassignedZones.end()
            );
        }
        
        // Add final transfer station if needed
        if (currentVehicle.getCurrentLoad() > 0) {
            TransferStation closestStation = findClosestTransferStation(currentVehicle.getCurrentLocation());
            currentVehicle.addLocation(closestStation.getLocation());
        }
        
        // Return to depot
        currentVehicle.addLocation(depot.getLocation());
        
        // Add completed route
        routes.push_back(currentVehicle);
    }
    
    return routes;
}

// Get number of zones visited
int RoutingSolver::getNumberOfZonesVisited() const {
    return zones.size();
}