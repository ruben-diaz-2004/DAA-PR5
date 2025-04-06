#include "include/reinsertintra.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>


void ReinsertIntra::runLocalSearch() {
    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    bool improvementFound = true;
    double bestTotalTime = solution.getTotalTime();

    // Continue until no more improvements are found
    while (improvementFound) {
        improvementFound = false;

        // For each route
        for (size_t routeIndex = 0; routeIndex < routes.size(); routeIndex++) {
            std::vector<Location> currentRoute = routes[routeIndex].getRoute();
            
            // Need at least 4 locations (depot + 2 zones + transfer station/depot)
            if (currentRoute.size() < 4) {
                continue;
            }

            // For each zone in the route (excluding depot and last location)
            for (size_t removePos = 2; removePos < currentRoute.size() - 1; removePos++) {
                // Skip if not a zone
                if (!isZone(currentRoute[removePos])) {
                    continue;
                }

                // Store the element to reinsert
                Location elementToReinsert = currentRoute[removePos];
                
                // Try reinserting the element in each valid position before its current position
                for (size_t insertPos = 1; insertPos < removePos; insertPos++) {
                    // Skip if insertion position is not valid (e.g., not between zones or after depot)
                    if (!isZone(currentRoute[insertPos-1]) && insertPos > 1) {
                        continue;
                    }
                    
                    // Create a new route with the element reinserted
                    std::vector<Location> newRoute = currentRoute;
                    
                    // Remove the element from its original position
                    newRoute.erase(newRoute.begin() + removePos);
                    
                    // Insert the element at the new position
                    newRoute.insert(newRoute.begin() + insertPos, elementToReinsert);
                    
                    // Evaluate the new route
                    double timeUsed = 0.0;
                    double finalLoad = 0.0;
                    
                    if (evaluateRoute(newRoute, timeUsed, finalLoad)) {
                        // Create a temporary solution with the new route
                        std::vector<CollectionVehicle> tempRoutes = routes;
                        
                        // Replace the route with the new one
                        double vehicleCapacity = problem.collectionVehicleCapacity();
                        tempRoutes[routeIndex] = createVehicleWithRoute(
                            routes[routeIndex].getId(),
                            vehicleCapacity,
                            newRoute,
                            timeUsed,
                            finalLoad
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
                
                // If we found an improvement, break out of the outer loop too to restart with the new routes
                if (improvementFound) {
                    break;
                }
            }
        }
    }
    
    // Update the solution with the best routes found
    solution.setCollectionRoutes(routes);
}