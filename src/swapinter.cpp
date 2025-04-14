#include "include/swapinter.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void SwapInter::runLocalSearch() {
    bool improvementFound = true;
    const double IMPROVEMENT_THRESHOLD = 0.0001;

    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    std::cout << "Initial total time: " << solution.getTotalTime() << std::endl;

    while (improvementFound) {
        improvementFound = false;

        for (size_t i = 0; i < routes.size(); ++i) {
            for (size_t j = i + 1; j < routes.size(); ++j) {
                std::vector<Location> route1 = routes[i].getRoute();
                std::vector<Location> route2 = routes[j].getRoute();

                if (route1.size() < 3 || route2.size() < 3) continue;

                for (size_t pos1 = 1; pos1 < route1.size() - 1; ++pos1) {
                    if (!isZone(route1[pos1])) continue;

                    for (size_t pos2 = 1; pos2 < route2.size() - 1; ++pos2) {
                        if (!isZone(route2[pos2])) continue;

                        // Clonar rutas
                        std::vector<Location> newRoute1 = route1;
                        std::vector<Location> newRoute2 = route2;
                        std::swap(newRoute1[pos1], newRoute2[pos2]);

                        double time1 = 0.0, load1 = 0.0;
                        double time2 = 0.0, load2 = 0.0;

                        if (evaluateRoute(newRoute1, time1, load1) &&
                            evaluateRoute(newRoute2, time2, load2)) {
                            
                            double oldTime1 = 0.0, oldLoad1 = 0.0;
                            double oldTime2 = 0.0, oldLoad2 = 0.0;
                            evaluateRoute(route1, oldTime1, oldLoad1);
                            evaluateRoute(route2, oldTime2, oldLoad2);

                            double improvement = (oldTime1 + oldTime2) - (time1 + time2);
                            if (improvement > IMPROVEMENT_THRESHOLD) {
                                std::cout << "Improvement found between route " << i 
                                          << " and route " << j 
                                          << "! Time improvement: " << improvement << std::endl;

                                // Mostrar rutas antiguas y nuevas para depurar
                                std::cout << "Old Route " << i << ": ";
                                for (const auto& loc : route1) std::cout << loc.getId() << " ";
                                std::cout << "\nNew Route " << i << ": ";
                                for (const auto& loc : newRoute1) std::cout << loc.getId() << " ";

                                std::cout << "\nOld Route " << j << ": ";
                                for (const auto& loc : route2) std::cout << loc.getId() << " ";
                                std::cout << "\nNew Route " << j << ": ";
                                for (const auto& loc : newRoute2) std::cout << loc.getId() << " ";
                                std::cout << std::endl;

                                // Actualizar rutas
                                routes[i].setRoute(newRoute1);
                                routes[i].resetLoad();
                                routes[i].addLoad(load1);
                                routes[i].subtractRemainingTime(-(oldTime1 - time1));

                                routes[j].setRoute(newRoute2);
                                routes[j].resetLoad();
                                routes[j].addLoad(load2);
                                routes[j].subtractRemainingTime(-(oldTime2 - time2));

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
    std::cout << "Final total time after inter-route swap: " << solution.getTotalTime() << std::endl;
}
