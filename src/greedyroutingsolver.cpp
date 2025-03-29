#include "include/greedyroutingsolver.h"

#include <iostream>
#include <vector>
// // Construct collection vehicle routes using greedy approach
// std::vector<CollectionVehicle> RoutingSolver::constructGreedyCollectionRoutes() {
//   std::vector<CollectionVehicle> routes;
//   std::vector<Zone> unassignedZones = zones;
  
//   // Continue until all zones are assigned
//   while (!unassignedZones.empty()) {
//       // Create a new vehicle starting from the depot
//       CollectionVehicle currentVehicle(routes.size() + 1, vehicleCapacity, maxRouteDuration);
//       currentVehicle.addLocation(depot.getLocation());
      
//       // Continue adding zones to this vehicle's route
//       while (!unassignedZones.empty()) {
//           // Find the closest unassigned zone to the current vehicle's location
//           Zone* bestZone = nullptr;
//           double minDistance = std::numeric_limits<double>::max();
          
//           for (auto& zone : unassignedZones) {
//               double distance = currentVehicle.getCurrentLocation().distanceTo(zone.getLocation());
//               if (distance < minDistance) {
//                   // Check if zone can be visited within vehicle constraints
//                   if (canVisitZone(currentVehicle, zone, currentVehicle.getRemainingTime())) {
//                       minDistance = distance;
//                       bestZone = &zone;
//                   }
//               }
//           }
          
//           // If no zone can be visited, move to transfer station and reset
//           if (!bestZone) {
//               // Find closest transfer station
//               TransferStation closestStation = findClosestTransferStation(currentVehicle.getCurrentLocation());
              
//               // Add transfer station to route and reset vehicle
//               currentVehicle.addLocation(closestStation.getLocation());
//               currentVehicle.resetLoadAndTime();
              
//               break;  // Force creating a new vehicle
//           }
          
//           // Add best zone to route
//           currentVehicle.addLocation(bestZone->getLocation());
//           currentVehicle.addLoad(bestZone->getWasteQuantity());
          
//           // Remove zone from unassigned list
//           unassignedZones.erase(
//               std::remove_if(unassignedZones.begin(), unassignedZones.end(), 
//                   [&](const Zone& z) { return z.getLocation() == bestZone->getLocation(); }),
//               unassignedZones.end()
//           );
//       }
      
//       // Add final transfer station if needed
//       if (currentVehicle.getCurrentLoad() > 0) {
//           TransferStation closestStation = findClosestTransferStation(currentVehicle.getCurrentLocation());
//           currentVehicle.addLocation(closestStation.getLocation());
//       }
      
//       // Return to depot
//       currentVehicle.addLocation(depot.getLocation());
      
//       // Add completed route
//       routes.push_back(currentVehicle);
//   }
  
//   return routes;
// }

// // Get number of zones visited
// int RoutingSolver::getNumberOfZonesVisited() const {
//   return zones.size();
// }


// Implementación del algoritmo voraz para rutas de transporte
std::vector<CollectionVehicle> GreedyRoutingSolver::constructCollectionRoutes() {
  std::cout << "Constructing transport routes..." << std::endl;
  return std::vector<CollectionVehicle>();
}