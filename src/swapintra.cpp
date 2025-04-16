#include "include/swapintra.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void SwapIntra::runLocalSearch() {
    bool improvementFound = true;
    double maxRouteDuration = problem.maxCollectionRouteDuration();
    // std::cout << "Max route duration: " << maxRouteDuration << std::endl;
    const double IMPROVEMENT_THRESHOLD = 0.0001;
    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    // std::cout << "Initial time: " << solution.getTotalTime() << std::endl;

    while (improvementFound) {
        improvementFound = false;
        
        for (size_t routeIndex = 0; routeIndex < routes.size(); routeIndex++) {
            std::vector<Location> currentRoute = routes[routeIndex].getRoute();
            
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
                    // Calculate the time difference
                    double oldTimeUsed = 0.0;
                    double oldFinalLoad = 0.0;
                    evaluateRoute(currentRoute, oldTimeUsed, oldFinalLoad);
                    
                    // If better (by at least the threshold), update the solution
                    double improvement = oldTimeUsed - timeUsed;
                    if (improvement > IMPROVEMENT_THRESHOLD) {
                        std::cout << "SwapIntra Improvement found! Old route time: " << oldTimeUsed 
                                  << " New route time: " << timeUsed 
                                  << " (Improvement: " << improvement << ")" << std::endl;
                        // std::cout << "Old Route IDs: ";
                        // for (const auto& loc : currentRoute) {
                        //     std::cout << loc.getId() << " ";
                        // }
                        // std::cout << std::endl;
                        // std::cout << "New Route IDs: ";
                        // for (const auto& loc : newRoute) {
                        //     std::cout << loc.getId() << " ";
                        // }
                        // std::cout << std::endl;
                        // Update the route in our collection
                        std::cout << routes[routeIndex].getRemainingTime() << std::endl;
                        routes[routeIndex].setRoute(newRoute);
                        routes[routeIndex].subtractRemainingTime(-improvement);
                        routes[routeIndex].resetLoad();
                        routes[routeIndex].addLoad(finalLoad);
                        std::cout << routes[routeIndex].getRemainingTime() << std::endl;
                        
                        improvementFound = true;

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
    // Update the solution with the new routes
    solution.setCollectionRoutes(routes);
}