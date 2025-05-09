/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 25/03/2025
  * @brief VRPT-SWTS
  */
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
      double distance = problem.getDistance(currentLocation.getId(), station.getLocation().getId());
      if (distance < minDistance) {
          minDistance = distance;
          closestStation = station;
      }
  }
  return closestStation;
}

// Find the closest zone to a given location from a list of unassigned zones
Zone RoutingSolver::findClosestZone(const Location& currentLocation, std::vector<Zone> unassignedZones) const {
  if (unassignedZones.empty()) {
      throw std::runtime_error("No unassigned zones available.");
  }
  Zone closestZone = unassignedZones.front();
  double minDistance = problem.getDistance(currentLocation.getId(), closestZone.getLocation().getId());
  for (const auto& zone : unassignedZones) {
    double distance = problem.getDistance(currentLocation.getId(), zone.getLocation().getId());
    if (distance < minDistance) {
      minDistance = distance;
      closestZone = zone;
    }
  }
  return closestZone;
}

// Find the n closest zones to a given location from a list of unassigned zones
Zone RoutingSolver::findNClosestZone(const Location& currentLocation, std::vector<Zone> unassignedZones, int n) const {
  if (unassignedZones.size() < n) {
    n = unassignedZones.size();
  }
  // Find the n closest zones and return one randomly
  std::vector<std::pair<Zone, double>> distances;
  for (const auto& zone : unassignedZones) {
    double distance = problem.getDistance(currentLocation.getId(), zone.getLocation().getId());
    distances.emplace_back(zone, distance);
  }
  std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
    return a.second < b.second;
  });
  std::vector<Zone> closestZones;
  for (int i = 0; i < n; ++i) {
    closestZones.push_back(distances[i].first);
  }
  // Return a random zone from the closest zones
  int randomIndex = rand() % n;
  return closestZones[randomIndex];
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
  double totalTime = zoneVisitTime + transferStationTime + returnToDepotTime + zone.getTime();
  if (totalTime > remainingTime) {
      return 2; // Not enough time
  }
  return 0; // Can visit zone
}

// Calculate travel time between two locations using the distance matrix
double RoutingSolver::calculateTravelTime(const Location& from, const Location& to) const {
  // Get the distance from the matrix if available
  double distance = problem.getDistance(from.getId(), to.getId());
  // Calculate travel time based on distance and vehicle speed
  return distance / problem.vehicleSpeed() * 60; // Convert to minutes
}