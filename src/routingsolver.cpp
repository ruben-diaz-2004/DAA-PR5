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
    return from.distanceTo(to) / problem.vehicleSpeed() * 60; // Convert to minutes
}

// Check if a vehicle can visit a zone within remaining time and capacity
int RoutingSolver::canVisitZone(const CollectionVehicle& vehicle, const Zone& zone, double remainingTime) const {
    // Check if zone waste fits in vehicle capacity
    if (zone.getWasteQuantity() > vehicle.getRemainingCapacity()) {
        return 1; // Not enough capacity
    }
    
    // Estimate time to visit zone, transfer station, and return to depot
    double zoneVisitTime = calculateTravelTime(vehicle.getCurrentLocation(), zone.getLocation());
    double transferStationTime = calculateTravelTime(zone.getLocation(), findClosestTransferStation(zone.getLocation()).getLocation());
    double returnToDepotTime = calculateTravelTime(findClosestTransferStation(zone.getLocation()).getLocation(), problem.depot().getLocation());
    
    double totalTime = zoneVisitTime + transferStationTime + returnToDepotTime;
    if (totalTime > remainingTime) {
        return 2; // Not enough time
    }
    return 0; // Can visit zone
}

