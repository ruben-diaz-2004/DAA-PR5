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


// Implementación del algoritmo voraz para rutas de transporte
std::vector<CollectionVehicle> GreedyRoutingSolver::constructCollectionRoutes() {
  std::cout << "Constructing transport routes..." << std::endl;
  std::vector<CollectionVehicle> routes;
  std::vector<Zone> unassignedZones = problem.zones();
  
  // Continue until all zones are assigned
  while (!unassignedZones.empty()) {
      // Create a new vehicle starting from the depot
      CollectionVehicle currentVehicle(routes.size() + 1, problem.collectionVehicleCapacity(), problem.maxTransportRouteDuration(), problem.vehicleSpeed());
      currentVehicle.addLocation(problem.depot().getLocation());
      
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
              std::cout << "No more zones can be visited. Moving to transfer station." << std::endl;
              std::cout << currentVehicle.getCurrentLoad() << " kg remaining." << std::endl;
              currentVehicle.addLocation(closestStation.getLocation());
              currentVehicle.resetLoad();
              
          } else {
            // Add best zone to route
            currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), bestZone->getLocation()));
            currentVehicle.addLocation(bestZone->getLocation());
            currentVehicle.addLoad(bestZone->getWasteQuantity());
            
            // Remove zone from unassigned list
            unassignedZones.erase(
                std::remove_if(unassignedZones.begin(), unassignedZones.end(), 
                    [&](const Zone& z) { return z.getLocation() == bestZone->getLocation(); }),
                unassignedZones.end()
            );
          }
        
      }
      
      // Add final transfer station if needed
      if (currentVehicle.getCurrentLoad() > 0) {
          TransferStation closestStation = findClosestTransferStation(currentVehicle.getCurrentLocation());
          currentVehicle.addLocation(closestStation.getLocation());
          currentVehicle.resetLoad();
      }
      
      // Return to depot
      currentVehicle.addLocation(problem.depot().getLocation());
      
      // Add completed route
      routes.push_back(currentVehicle);
  }
  
  // Print routes for debugging
  for (const auto& route : routes) {
      std::cout << "Route: ";
      std::cout << "Remaining time: " << route.getRemainingTime() << " minutes, ";
      std::cout << route.getCurrentLoad() << " kg, ";
      for (const auto& loc : route.getRoute()) {
        loc.printLocation();
        std::cout << " -> ";
      }
      std::cout << "Depot" << std::endl;
  }
  std::cout << "Total routes: " << routes.size() << std::endl;
  std::cout << "Greedy routing completed." << std::endl;
  return routes;
}