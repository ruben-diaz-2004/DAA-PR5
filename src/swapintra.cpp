#include "include/swapintra.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void SwapIntra::runLocalSearch() {
    bool improvementFound = true;
    
    while (improvementFound) {
        improvementFound = false;
        std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
        
        for (size_t routeIndex = 0; routeIndex < routes.size(); routeIndex++) {
            std::vector<Location> currentRoute = routes[routeIndex].getRoute();
            
            // Need at least 4 locations (depot + 2 zones + depot)
            if (currentRoute.size() < 4) {
                continue;
            }
            
            // For each pair of consecutive locations in the route (excluding depot and last location)
            for (size_t i = 1; i < currentRoute.size() - 2; i++) {
                // Skip if either location is not a zone
                if (!isZone(currentRoute[i]) || !isZone(currentRoute[i+1])) {
                    continue;
                }
                
                // Create a new route with swapped zones
                std::vector<Location> newRoute = currentRoute;
                std::swap(newRoute[i], newRoute[i+1]);
                
                // Evaluate the new route
                double timeUsed = 0.0;
                double finalLoad = 0.0;
                
                if (evaluateRoute(newRoute, timeUsed, finalLoad)) {
                    // Create a new vehicle with the improved route
                    CollectionVehicle newVehicle = createVehicleWithRoute(
                        routes[routeIndex].getId(),
                        problem.collectionVehicleCapacity(),
                        newRoute,
                        timeUsed,
                        finalLoad
                    );
                    
                    // Calculate the time difference
                    double currentRouteTime = routes[routeIndex].getRemainingTime();
                    double newRouteTime = newVehicle.getRemainingTime();
                    
                    // If better, update the solution
                    if (newRouteTime > currentRouteTime) {
                        std::cout << "Improvement found! Old route time: " << currentRouteTime 
                                  << " New route time: " << newRouteTime << std::endl;
                        
                        // Update the route in our collection
                        routes[routeIndex] = newVehicle;
                        
                        // Update the solution with the improved routes
                        solution.setCollectionRoutes(routes);
                        
                        improvementFound = true;
                        
                        // Debug output
                        std::cout << "Route IDs: ";
                        for (const auto& loc : newRoute) {
                            std::cout << loc.getId() << " ";
                        }
                        std::cout << std::endl;
                        
                        // We found an improvement, break and start over
                        break;
                    }
                }
            }
            
            // If we found an improvement, break the outer loop too
            if (improvementFound) {
                break;
            }
        }
    }
}