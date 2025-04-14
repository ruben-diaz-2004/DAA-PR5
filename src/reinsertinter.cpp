#include "include/reinsertinter.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void ReinsertInter::runLocalSearch() {
    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    bool improvementFound = true;
    double bestTotalTime = solution.getTotalTime();
    while (improvementFound) {
        improvementFound = false;
        for (size_t sourceRouteIdx = 0; sourceRouteIdx < routes.size(); sourceRouteIdx++) {
            std::vector<Location> sourceRoute = routes[sourceRouteIdx].getRoute();
            if (sourceRoute.size() < 4) { // depot + at least 2 zones + return
                continue;
            }
            for (size_t removePos = 1; removePos < sourceRoute.size() - 1; removePos++) {
                if (!isZone(sourceRoute[removePos])) {
                    continue;
                }
                Location zoneToReinsert = sourceRoute[removePos];
                std::vector<Location> newSourceRoute = sourceRoute;
                newSourceRoute.erase(newSourceRoute.begin() + removePos);
                double sourceTimeUsed = 0.0;
                double sourceFinalLoad = 0.0;
                if (evaluateRoute(newSourceRoute, sourceTimeUsed, sourceFinalLoad)) {
                    for (size_t targetRouteIdx = 0; targetRouteIdx < routes.size(); targetRouteIdx++) {
                        if (sourceRouteIdx == targetRouteIdx) {
                            continue;
                        }
                        std::vector<Location> targetRoute = routes[targetRouteIdx].getRoute();
                        for (size_t insertPos = 1; insertPos < targetRoute.size(); insertPos++) {
                            if (insertPos > 1 && !isZone(targetRoute[insertPos-1])) {
                                continue;
                            }
                            std::vector<Location> newTargetRoute = targetRoute;
                            newTargetRoute.insert(newTargetRoute.begin() + insertPos, zoneToReinsert);
                            double targetTimeUsed = 0.0;
                            double targetFinalLoad = 0.0;
                            if (evaluateRoute(newTargetRoute, targetTimeUsed, targetFinalLoad)) {
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