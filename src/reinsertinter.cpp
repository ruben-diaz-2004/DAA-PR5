#include "include/reinsertinter.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void ReinsertInter::runLocalSearch() {
    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    bool improvementFound = true;
    double bestTotalTime = solution.getTotalTime();

    // Continue until no more improvements are found
    while (improvementFound) {
        improvementFound = false;

        // For each source route
        for (size_t sourceRouteIdx = 0; sourceRouteIdx < routes.size(); sourceRouteIdx++) {
            std::vector<Location> sourceRoute = routes[sourceRouteIdx].getRoute();
            
            // Check if source route has enough locations
            if (sourceRoute.size() < 4) { // depot + at least 2 zones + return
                continue;
            }

            // For each zone in the source route
            for (size_t removePos = 1; removePos < sourceRoute.size() - 1; removePos++) {
                // Skip if not a zone
                if (!isZone(sourceRoute[removePos])) {
                    continue;
                }

                // Store the element to reinsert
                Location zoneToReinsert = sourceRoute[removePos];
                
                // Create a new source route with the element removed
                std::vector<Location> newSourceRoute = sourceRoute;
                newSourceRoute.erase(newSourceRoute.begin() + removePos);
                
                // Evaluate the new source route
                double sourceTimeUsed = 0.0;
                double sourceFinalLoad = 0.0;
                
                // Only proceed if removing the zone from the source route is valid
                if (evaluateRoute(newSourceRoute, sourceTimeUsed, sourceFinalLoad)) {
                    
                    // For each target route (different from source)
                    for (size_t targetRouteIdx = 0; targetRouteIdx < routes.size(); targetRouteIdx++) {
                        if (sourceRouteIdx == targetRouteIdx) {
                            continue;
                        }
                        
                        std::vector<Location> targetRoute = routes[targetRouteIdx].getRoute();
                        
                        // For each potential insertion position in the target route
                        for (size_t insertPos = 1; insertPos < targetRoute.size(); insertPos++) {
                            // Skip if insertion would be after a non-zone (except for depot)
                            if (insertPos > 1 && !isZone(targetRoute[insertPos-1])) {
                                continue;
                            }
                            
                            // Create a new target route with the element inserted
                            std::vector<Location> newTargetRoute = targetRoute;
                            newTargetRoute.insert(newTargetRoute.begin() + insertPos, zoneToReinsert);
                            
                            // Evaluate the new target route
                            double targetTimeUsed = 0.0;
                            double targetFinalLoad = 0.0;
                            
                            if (evaluateRoute(newTargetRoute, targetTimeUsed, targetFinalLoad)) {
                                // Create a temporary solution with both new routes
                                std::vector<CollectionVehicle> tempRoutes = routes;
                                double vehicleCapacity = problem.collectionVehicleCapacity();
                                
                                // Replace the source route
                                tempRoutes[sourceRouteIdx] = createVehicleWithRoute(
                                    routes[sourceRouteIdx].getId(),
                                    vehicleCapacity,
                                    newSourceRoute,
                                    sourceTimeUsed,
                                    sourceFinalLoad
                                );
                                
                                // Replace the target route
                                tempRoutes[targetRouteIdx] = createVehicleWithRoute(
                                    routes[targetRouteIdx].getId(),
                                    vehicleCapacity,
                                    newTargetRoute,
                                    targetTimeUsed,
                                    targetFinalLoad
                                );
                                
                                // Calculate total time for the new solution
                                Solution tempSolution;
                                tempSolution.setCollectionRoutes(tempRoutes);
                                tempSolution.setTasks(solution.getTasks());
                                
                                double newTotalTime = tempSolution.getTotalTime();
                                
                                // If better, update the solution
                                if (newTotalTime < bestTotalTime) {
                                    bestTotalTime = newTotalTime;
                                    routes = tempRoutes;
                                    improvementFound = true;
                                    
                                    // Break the inner loop as we've found an improvement
                                    break;
                                }
                            }
                        }
                        
                        // If improvement found, break out of the target route loop
                        if (improvementFound) {
                            break;
                        }
                    }
                }
                
                // If improvement found, break out of the zone position loop
                if (improvementFound) {
                    break;
                }
            }
            
            // If improvement found, break out of the source route loop
            if (improvementFound) {
                break;
            }
        }
    }
    
    // Update the solution with the best routes found
    solution.setCollectionRoutes(routes);
}