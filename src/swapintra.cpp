#include "include/swapintra.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>


void SwapIntra::runLocalSearch() {
    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    bool improvementFound = true;
    double bestTotalTime = solution.getTotalTime();
    while (improvementFound) {
        improvementFound = false;
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
                    // Create a temporary solution with the new route
                    std::vector<CollectionVehicle> tempRoutes = routes;
                    // Replace the route with the new one
                    tempRoutes[routeIndex] = createVehicleWithRoute(
                        routes[routeIndex].getId(),
                        problem.collectionVehicleCapacity(),
                        newRoute,
                        timeUsed,
                        finalLoad
                    );
                    // Calculate total time for the new solution
                    Solution tempSolution;
                    tempSolution.setCollectionRoutes(tempRoutes);
                    double newTotalTime = tempSolution.getTotalTime();
                    // If better, update the solution
                    if (newTotalTime < bestTotalTime) {
                        std::cout << "Improvement found! Old total time: " << bestTotalTime << " New total time: " << newTotalTime << std::endl;
                        bestTotalTime = newTotalTime;
                        routes = tempRoutes;
                        improvementFound = true;
                        // Print the route
                        std::cout << "Old route: ";
                        for (const auto& loc : currentRoute) {
                            std::cout << "[" << loc.getX() << ", " << loc.getY() << "] ";
                        }
                        std::cout << std::endl;
                        std::cout << "New route: ";
                        for (const auto& loc : newRoute) {
                            std::cout << "[" << loc.getX() << ", " << loc.getY() << "] ";
                        }
                        std::cout << std::endl;
                        std::cout << "Old route: ";
                        for (const auto& loc : currentRoute) {
                            std::cout << loc.getId() << " ";
                        }
                        std::cout << std::endl;
                        std::cout << "New route: ";
                        for (const auto& loc : newRoute) {
                            std::cout << loc.getId() << " ";
                        }
                        std::cout << std::endl;
                    }
                }
            }
        }
    }
    solution.setCollectionRoutes(routes);
}