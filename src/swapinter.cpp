#include "include/swapinter.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void SwapInter::runLocalSearch() {
    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    bool improvementFound = true;
    double bestTotalTime = solution.getTotalTime();
    while (improvementFound) {
        improvementFound = false;
        for (size_t routeIndex1 = 0; routeIndex1 < routes.size(); routeIndex1++) {
            std::vector<Location> route1 = routes[routeIndex1].getRoute();
            if (route1.size() < 3) { // depot + at least 1 zone + return
                continue;
            }
            // For each zone in route1
            for (size_t pos1 = 1; pos1 < route1.size() - 1; pos1++) {
                if (!isZone(route1[pos1])) {
                    continue;
                }
                // For each other route j
                for (size_t routeIndex2 = 0; routeIndex2 < routes.size(); routeIndex2++) {
                    if (routeIndex1 == routeIndex2) {
                        continue;
                    }
                    std::vector<Location> route2 = routes[routeIndex2].getRoute();
                    if (route2.size() < 3) {
                        continue;
                    }
                    // For each zone in route2
                    for (size_t pos2 = 1; pos2 < route2.size() - 1; pos2++) {
                        // Skip if not a zone
                        if (!isZone(route2[pos2])) {
                            continue;
                        }
                        // Create copies of the routes to modify
                        std::vector<Location> newRoute1 = route1;
                        std::vector<Location> newRoute2 = route2;
                        // Swap the zones
                        Location temp = newRoute1[pos1];
                        newRoute1[pos1] = newRoute2[pos2];
                        newRoute2[pos2] = temp;
                        // Evaluate both new routes
                        double timeUsed1 = 0.0;
                        double finalLoad1 = 0.0;
                        double timeUsed2 = 0.0;
                        double finalLoad2 = 0.0;
                        bool route1Valid = evaluateRoute(newRoute1, timeUsed1, finalLoad1);
                        bool route2Valid = evaluateRoute(newRoute2, timeUsed2, finalLoad2);
                        // If both routes are valid after the swap
                        if (route1Valid && route2Valid) {
                            std::vector<CollectionVehicle> tempRoutes = routes; // Create temporary solution with the new routes
                            double vehicleCapacity = problem.collectionVehicleCapacity(); // Replace the routes with the new ones
                            tempRoutes[routeIndex1] = createVehicleWithRoute(
                                routes[routeIndex1].getId(),
                                vehicleCapacity,
                                newRoute1,
                                timeUsed1,
                                finalLoad1
                            );
                            tempRoutes[routeIndex2] = createVehicleWithRoute(
                                routes[routeIndex2].getId(),
                                vehicleCapacity,
                                newRoute2,
                                timeUsed2,
                                finalLoad2
                            );
                            Solution tempSolution;
                            tempSolution.setCollectionRoutes(tempRoutes);
                            tempSolution.setTasks(solution.getTasks());
                            double newTotalTime = tempSolution.getTotalTime();
                            // If better, update the solution
                            if (newTotalTime < bestTotalTime) {
                                bestTotalTime = newTotalTime;
                                routes = tempRoutes;
                                improvementFound = true;
                                break;
                            }
                        }
                    }                    
                    if (improvementFound) {
                        break;
                    }
                }
                if (improvementFound) {
                    break;
                }
            }
            if (improvementFound) {
                break;
            }
        }
    }
    solution.setCollectionRoutes(routes);
}