#include "include/reinsertinter.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void ReinsertInter::runLocalSearch() {
    bool improvementFound = true;
    const double IMPROVEMENT_THRESHOLD = 0.0001;

    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    // std::cout << "Initial total time: " << solution.getTotalTime() << std::endl;

    while (improvementFound) {
        improvementFound = false;

        for (size_t i = 0; i < routes.size(); ++i) {
            for (size_t j = 0; j < routes.size(); ++j) {
                if (i == j) continue;

                std::vector<Location> routeFrom = routes[i].getRoute();
                std::vector<Location> routeTo = routes[j].getRoute();

                if (routeFrom.size() < 3 || routeTo.size() < 2) continue;

                for (size_t posFrom = 1; posFrom < routeFrom.size() - 1; ++posFrom) {
                    if (!isZone(routeFrom[posFrom])) continue;

                    Location node = routeFrom[posFrom];
                    std::vector<Location> newRouteFrom = routeFrom;
                    newRouteFrom.erase(newRouteFrom.begin() + posFrom);

                    for (size_t insertPos = 1; insertPos < routeTo.size() - 2; ++insertPos) {
                        std::vector<Location> newRouteTo = routeTo;
                        newRouteTo.insert(newRouteTo.begin() + insertPos, node);

                        double timeFrom = 0.0, loadFrom = 0.0;
                        double timeTo = 0.0, loadTo = 0.0;

                        if (evaluateRoute(newRouteFrom, timeFrom, loadFrom) &&
                            evaluateRoute(newRouteTo, timeTo, loadTo)) {

                            double oldTimeFrom = 0.0, oldLoadFrom = 0.0;
                            double oldTimeTo = 0.0, oldLoadTo = 0.0;
                            evaluateRoute(routeFrom, oldTimeFrom, oldLoadFrom);
                            evaluateRoute(routeTo, oldTimeTo, oldLoadTo);

                            double improvement = (oldTimeFrom + oldTimeTo) - (timeFrom + timeTo);
                            if (improvement > IMPROVEMENT_THRESHOLD) {
                                // std::cout << "ReinsertInter Improvement by reinserting node " << node.getId()
                                //           << " from route " << i << " to route " << j
                                //           << " at position " << insertPos
                                //           << "! Time improvement: " << improvement << std::endl;

                                routes[i].setRoute(newRouteFrom);
                                routes[i].resetLoad();
                                routes[i].addLoad(loadFrom);
                                routes[i].subtractRemainingTime(-(oldTimeFrom - timeFrom));

                                routes[j].setRoute(newRouteTo);
                                routes[j].resetLoad();
                                routes[j].addLoad(loadTo);
                                routes[j].subtractRemainingTime(-(oldTimeTo - timeTo));

                                improvementFound = true;
                                break;
                            }
                        }
                    }
                    if (improvementFound) break;
                }
                if (improvementFound) break;
            }
            if (improvementFound) break;
        }
    }

    solution.setCollectionRoutes(routes);
}