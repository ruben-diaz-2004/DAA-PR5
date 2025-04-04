#include "include/greedyroutingsolver.h"

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "include/collectionvehicle.h"
#include "include/zone.h"
#include "include/location.h"
#include "include/probleminstance.h"
#include "include/transportationvehicle.h"
#include "include/depot.h"
#include "include/landfill.h"
#include "include/routingsolver.h"

std::vector<CollectionVehicle> GreedyRoutingSolver::constructCollectionRoutes() {
  std::vector<CollectionVehicle> routes;
  std::vector<Zone> unassignedZones = problem.zones();
  std::vector<Task> tasks;
  
  // Continue until all zones are assigned
  while (!unassignedZones.empty()) {
    // Create a new vehicle starting from the depot
    CollectionVehicle currentVehicle(routes.size() + 1, problem.collectionVehicleCapacity(), problem.maxCollectionRouteDuration(), problem.vehicleSpeed());
    currentVehicle.addLocation(problem.depot().getLocation());
    
    bool vehicleCanTakeMoreZones = true;
    
    // Continue adding zones to this vehicle's route
    while (!unassignedZones.empty() && vehicleCanTakeMoreZones) {
      // Find the closest unassigned zone to the current vehicle's location 
      Zone closestZone = findClosestZone(currentVehicle.getCurrentLocation(), unassignedZones);
      
      // Check if zone can be visited within vehicle constraints
      int visitResult = canVisitZone(currentVehicle, closestZone, currentVehicle.getRemainingTime());
      
      if (visitResult == 0) { // Can visit zone        
        // Add zone to route
        currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), closestZone.getLocation()) + closestZone.getTime());
        currentVehicle.addLocation(closestZone.getLocation());
        currentVehicle.addLoad(closestZone.getWasteQuantity());
        
        // Remove zone from unassigned list
        unassignedZones.erase(std::remove_if(unassignedZones.begin(), unassignedZones.end(),
          [&closestZone](const Zone& z) { return z.getId() == closestZone.getId(); }), unassignedZones.end());
      } 
      else if (visitResult == 1) { // Not enough capacity
        // Find the closest transfer station
        TransferStation closestStation = findClosestTransferStation(currentVehicle.getCurrentLocation());
        // Add transfer station to route and reset vehicle load
        currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), closestStation.getLocation()));
        // Add a new task
        Task newTask(currentVehicle.getCurrentLoad(), closestStation, problem.maxCollectionRouteDuration() - currentVehicle.getRemainingTime());
        tasks.push_back(newTask);
        
        currentVehicle.addLocation(closestStation.getLocation());
        currentVehicle.resetLoad();
      }
      else { // Not enough time
        vehicleCanTakeMoreZones = false;
      }
    }
    
    // Add final transfer station if needed
    if (currentVehicle.getCurrentLoad() > 0) {
      TransferStation closestStation = findClosestTransferStation(currentVehicle.getCurrentLocation());
      currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), closestStation.getLocation()));
      
      // Add a new task
      Task newTask(currentVehicle.getCurrentLoad(), closestStation, problem.maxCollectionRouteDuration() - currentVehicle.getRemainingTime());
      tasks.push_back(newTask);
      
      currentVehicle.addLocation(closestStation.getLocation());
      currentVehicle.resetLoad();
    }
    
    // Return to depot
    currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), problem.depot().getLocation()));
    currentVehicle.addLocation(problem.depot().getLocation());
    
    // Add completed route
    routes.push_back(currentVehicle);
    
    // Safety check - if we can't assign any zones, break to avoid infinite loop
    if (routes.size() >= problem.maxVehicles() && !unassignedZones.empty()) {
      break;
    }
  }
  
  std::cout << "Total routes: " << routes.size() << std::endl;
  solution_.setCollectionRoutes(routes);
  solution_.setTasks(tasks);
  
  std::cout << "Greedy routing completed." << std::endl;
  return routes;
}