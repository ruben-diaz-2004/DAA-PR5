#include "include/twoopt.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void TwoOpt::runLocalSearch() {
  bool improvementFound = true;
    const double IMPROVEMENT_THRESHOLD = 0.0001;
    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
    std::cout << "Initial time: " << solution.getTotalTime() << std::endl;

    while (improvementFound) {
        improvementFound = false;

        for (size_t r1 = 0; r1 < routes.size(); ++r1) {
            for (size_t r2 = r1 + 1; r2 < routes.size(); ++r2) {
                std::vector<Location> route1 = routes[r1].getRoute();
                std::vector<Location> route2 = routes[r2].getRoute();

                for (size_t i = 1; i < route1.size() - 1; ++i) {
                    if (!isZone(route1[i])) continue;

                    for (size_t j = 1; j < route2.size() - 1; ++j) {
                        if (!isZone(route2[j])) continue;

                        // Crear nuevas rutas haciendo intercambio de segmentos
                        std::vector<Location> newRoute1(route1.begin(), route1.begin() + i);
                        newRoute1.insert(newRoute1.end(), route2.begin() + j, route2.end());

                        std::vector<Location> newRoute2(route2.begin(), route2.begin() + j);
                        newRoute2.insert(newRoute2.end(), route1.begin() + i, route1.end());

                        // Evaluar rutas
                        double time1 = 0.0, load1 = 0.0;
                        double time2 = 0.0, load2 = 0.0;

                        if (evaluateRoute(newRoute1, time1, load1) && evaluateRoute(newRoute2, time2, load2)) {
                            // Evaluar rutas originales
                            double oldTime1 = 0.0, oldLoad1 = 0.0;
                            double oldTime2 = 0.0, oldLoad2 = 0.0;
                            evaluateRoute(route1, oldTime1, oldLoad1);
                            evaluateRoute(route2, oldTime2, oldLoad2);

                            double oldTotal = oldTime1 + oldTime2;
                            double newTotal = time1 + time2;
                            double improvement = oldTotal - newTotal;

                            if (improvement > IMPROVEMENT_THRESHOLD) {
                                std::cout << "Improvement found between routes " << r1 << " and " << r2
                                          << "! Old total: " << oldTotal << " New total: " << newTotal 
                                          << " (Improvement: " << improvement << ")" << std::endl;

                                // Aplicar cambios
                                routes[r1].setRoute(newRoute1);
                                routes[r2].setRoute(newRoute2);

                                routes[r1].resetLoad();
                                routes[r2].resetLoad();
                                routes[r1].addLoad(load1);
                                routes[r2].addLoad(load2);

                                routes[r1].subtractRemainingTime(-(oldTime1 - time1));
                                routes[r2].subtractRemainingTime(-(oldTime2 - time2));

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
  // Actualizar la solución
  solution.setCollectionRoutes(routes);
  std::cout << "Final time after TwoOptInter: " << solution.getTotalTime() << std::endl;

}