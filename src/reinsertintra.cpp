#include "include/reinsertintra.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>


void ReinsertIntra::runLocalSearch() {
    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    bool improvementFound = true;
    double bestTotalTime = solution.getTotalTime();

    while (improvementFound) {
        improvementFound = false;
        for (size_t routeIndex = 0; routeIndex < routes.size(); routeIndex++) {
            std::vector<Location> currentRoute = routes[routeIndex].getRoute();
            if (currentRoute.size() < 4) {
                continue;
            }
            for (size_t removePos = 2; removePos < currentRoute.size() - 1; removePos++) {
                if (!isZone(currentRoute[removePos])) {
                    continue;
                }
                Location elementToReinsert = currentRoute[removePos];
                for (size_t insertPos = 1; insertPos < removePos; insertPos++) {
                    if (!isZone(currentRoute[insertPos-1]) && insertPos > 1) {
                        continue;
                    }
                    std::vector<Location> newRoute = currentRoute;
                    newRoute.erase(newRoute.begin() + removePos);
                    newRoute.insert(newRoute.begin() + insertPos, elementToReinsert);
                    double timeUsed = 0.0;
                    double finalLoad = 0.0;
                    if (evaluateRoute(newRoute, timeUsed, finalLoad)) {
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
                        Solution tempSolution;
                        tempSolution.setCollectionRoutes(tempRoutes);
                        tempSolution.setTasks(solution.getTasks());
                        double newTotalTime = tempSolution.getTotalTime();
                        if (newTotalTime < bestTotalTime) {
                            bestTotalTime = newTotalTime;
                            routes = tempRoutes;
                            improvementFound = true;
                            // Break the inner loop as we've found an improvement
                            break;
                        }
                    }
                }
                if (improvementFound) {
                    break;
                }
            }
        }
    }
    solution.setCollectionRoutes(routes);
}