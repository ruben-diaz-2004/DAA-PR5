#include "include/grasproutingsolver.h"

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


// Implementación del algoritmo voraz para rutas de transporte
std::vector<CollectionVehicle> GraspRoutingSolver::constructCollectionRoutes() {
  std::cout << "Constructing transport routes..." << std::endl;
  std::vector<CollectionVehicle> routes;
  std::vector<Zone> unassignedZones = problem.zones();
  std::vector<Task> tasks;
  std::cout << "Number of zones: " << unassignedZones.size() << std::endl;
  for (const auto& zone : unassignedZones) {
    std::cout << "Zone ID: " << zone.getId() << ", Waste Quantity: " << zone.getWasteQuantity() << " kg, ";
    std::cout << "Location: ";
    zone.getLocation().printLocation();
  }
  bool timeExceeded = false;
  bool capacityExceeded = false;

  // Continue until all zones are assigned
  while (!unassignedZones.empty()) {
    // Create a new vehicle starting from the depot
    CollectionVehicle currentVehicle(routes.size() + 1, problem.collectionVehicleCapacity(), problem.maxCollectionRouteDuration(), problem.vehicleSpeed());
    currentVehicle.addLocation(problem.depot().getLocation());
      
    // Continue adding zones to this vehicle's route
    while (!unassignedZones.empty()) {
      // Find the closest unassigned zone to the current vehicle's location 
      Zone zone = findNClosestZone(currentVehicle.getCurrentLocation(), unassignedZones, 2);
        // Check if zone can be visited within vehicle constraints
      switch (canVisitZone(currentVehicle, zone, currentVehicle.getRemainingTime())) {
        case 1: // Not enough capacity
          std::cout << "Not enough capacity for zone " << zone.getId() << std::endl;
          capacityExceeded = true;
          break;
        case 2: // Not enough time
          std::cout << "Not enough time for zone " << zone.getId() << std::endl;
          timeExceeded = true;
          break;
        default: // Can visit zone
          std::cout << "Visiting zone " << zone.getId() << std::endl;
          break;
      }

      if (timeExceeded) {
        std::cout << "Time exceeded for vehicle " << currentVehicle.getId() << std::endl;
        timeExceeded = false;
        break;
      } else if (capacityExceeded) {
          std::cout << "Capacity exceeded for vehicle " << currentVehicle.getId() << std::endl;
          capacityExceeded = false;
          // Find the closest transfer station
          TransferStation closestStation = findClosestTransferStation(currentVehicle.getCurrentLocation());
          // Add transfer station to route and reset vehicle
          currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), closestStation.getLocation()));
          // Add a new task
          Task newTask(currentVehicle.getCurrentLoad(), closestStation, problem.maxCollectionRouteDuration() - currentVehicle.getRemainingTime());
          tasks.push_back(newTask);
          currentVehicle.addLocation(closestStation.getLocation());
          currentVehicle.resetLoad();
      } else {
          // Add best zone to route
          currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), zone.getLocation()));
          currentVehicle.addLocation(zone.getLocation());
          currentVehicle.addLoad(zone.getWasteQuantity());
          
          // Remove zone from unassigned list
          unassignedZones.erase(std::remove_if(unassignedZones.begin(), unassignedZones.end(),
            [&zone](const Zone& z) { return z.getId() == zone.getId(); }), unassignedZones.end());
          std::cout << "Zone " << zone.getId() << " removed from unassigned zones." << std::endl;
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
  }
  
  // Print routes for debugging
  for (const auto& route : routes) {
      std::cout << "Vehicle: " << route.getId() << std::endl;
      std::cout << "Remaining time: " << route.getRemainingTime() << " minutes, ";
      std::cout << route.getCurrentLoad() << " kg, " << std::endl;
      for (const auto& loc : route.getRoute()) {
        std::cout << " -> ";
        loc.printId();
      }
  }
  std::cout << "Total routes: " << routes.size() << std::endl;
  std::cout << "Grasp routing completed." << std::endl;
  return routes;
}