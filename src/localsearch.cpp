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
#include "include/localsearch.h"

double LocalSearch::calculateTravelTime(const Location& from, const Location& to) const {
  // Calculate the travel time between two locations using the distance matrix
  double distance = problem.getDistance(from.getId(), to.getId());
  return distance / problem.vehicleSpeed() * 60;
}

// Helper function to evaluate if a route is feasible and calculate its time
bool LocalSearch::evaluateRoute(const std::vector<Location>& route, double& totalTime, double& finalLoad) {
  totalTime = 0.0;
  double currentLoad = 0.0;
  for (size_t j = 0; j < route.size() - 1; j++) {
    // Calculate travel time to next location
    double travelTime = calculateTravelTime(route[j], route[j+1]);
    totalTime += travelTime;
    // If this is a zone, add waste and service time
    if (isZone(route[j])) {
      for (const auto& zone : problem.zones()) {
        if (zone.getId() == route[j].getId()) {
          currentLoad += zone.getWasteQuantity();
          totalTime += zone.getTime(); // Add service time
          break;
        }
      }
    }
    // If this is a transfer station, reset load
    for (const auto& station : problem.transferStations()) {
      if (station.getId() == route[j].getId()) {
        currentLoad = 0.0;
        break;
      }
    }
    // Check constraints
    if (totalTime > problem.maxCollectionRouteDuration() || 
      currentLoad > problem.collectionVehicleCapacity()) {
      return false;
    }
  }
  finalLoad = currentLoad;
  return true;
}

// Helper function to create a new vehicle with a given route 
// CollectionVehicle LocalSearch::createVehicleWithRoute(int id, double capacity, const std::vector<Location>& route, double timeUsed, double finalLoad) {
//   CollectionVehicle vehicle(id, capacity, problem.maxCollectionRouteDuration(), problem.vehicleSpeed());
//   for (const auto& loc : route) {
//     vehicle.addLocation(loc);
//   }
//   vehicle.addLoad(finalLoad);
//   vehicle.subtractRemainingTime(timeUsed);
//   return vehicle;
// }