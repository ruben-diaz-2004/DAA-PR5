#include "include/solution.h"
#include "include/transferStation.h"
#include "include/location.h"
#include <iostream>

void Solution::buildTasks(const ProblemInstance& problem) {
  tasks_.clear();
  double currentWaste = 0.0;
  double currentTime = 0.0;
  double vehicleTravelSpeed = problem.vehicleSpeed();
  std::vector<TransferStation> transferStations = problem.transferStations();

  for (const auto& vehicle : collectionRoutes_) {
    const std::vector<Location>& route = vehicle.getRoute();
    currentWaste = 0.0;
    currentTime = 0.0;
    for (int i = 0; i < route.size() - 1; ++i) {
      // Calculate travel time to the next location
      currentTime += problem.getDistance(route[i].getId(), route[i + 1].getId()) / vehicleTravelSpeed * 60;
      // Check if the next location is a zone

      for (const auto& zone : problem.zones()) {
        if (zone.getId() == route[i + 1].getId()) {
          currentWaste += zone.getWasteQuantity();
          currentTime += zone.getTime(); // Add service time
          break;
        }
      }

      // Check if the next location is a transfer station
      for (const auto& station : transferStations) {
        if (station.getId() == route[i + 1].getId()) {
          // Create a task for the current vehicle
          Task task(currentWaste, station, currentTime);
          tasks_.push_back(task);
          currentWaste = 0.0; // Reset waste after transferring
          break;
        }
      }
    }
  }
}