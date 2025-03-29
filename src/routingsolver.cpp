#include "include/routingsolver.h"
#include <algorithm>
#include <limits>
#include <stdexcept>
#include "include/probleminstance.h"

// Find the closest transfer station to a given location
TransferStation RoutingSolver::findClosestTransferStation(const Location& currentLocation) const {
    TransferStation closestStation = problem.transferStations().front();
    double minDistance = std::numeric_limits<double>::max();
    
    for (const auto& station : problem.transferStations()) {
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
    double returnToDepotTime = calculateTravelTime(findClosestTransferStation(zone.getLocation()).getLocation(), problem.depot().getLocation());
    
    return zoneVisitTime + transferStationTime + returnToDepotTime <= remainingTime;
}

