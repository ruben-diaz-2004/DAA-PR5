#include "include/twoopt.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void TwoOpt::runLocalSearch() {
    bool improvementFound = true;
    double maxRouteDuration = problem.maxCollectionRouteDuration();
    const double IMPROVEMENT_THRESHOLD = 0.0001;
    std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();

    while (improvementFound) {
        improvementFound = false;
        
        for (size_t routeIndex = 0; routeIndex < routes.size(); routeIndex++) {
            std::vector<Location> currentRoute = routes[routeIndex].getRoute();
            
            // Para cada par de aristas no adyacentes en la ruta
            // Nota: i y j representan las posiciones donde cortaremos
            for (size_t i = 1; i < currentRoute.size() - 2; i++) {
                for (size_t j = i + 2; j < currentRoute.size() - 1; j++) {
                    // Omitimos si no son zonas (no queremos invertir estaciones o depósitos)
                    if (!isZone(currentRoute[i]) || !isZone(currentRoute[j])) {
                        continue;
                    }
                    
                    // Creamos una nueva ruta aplicando 2-opt:
                    // 1. Mantener las posiciones 0 a i-1
                    // 2. Invertir las posiciones i a j
                    // 3. Mantener las posiciones j+1 hasta el final
                    std::vector<Location> newRoute = currentRoute;
                    std::reverse(newRoute.begin() + i, newRoute.begin() + j + 1);
                    
                    // Evaluamos la nueva ruta
                    double timeUsed = 0.0;
                    double finalLoad = 0.0;
                    if (evaluateRoute(newRoute, timeUsed, finalLoad)) {
                        // Calculamos el tiempo de la ruta actual
                        double oldTimeUsed = 0.0;
                        double oldFinalLoad = 0.0;
                        evaluateRoute(currentRoute, oldTimeUsed, oldFinalLoad);
                        
                        // Si es mejor (por al menos el umbral), actualizamos la solución
                        double improvement = oldTimeUsed - timeUsed;
                        if (improvement > IMPROVEMENT_THRESHOLD) {
                            // Actualizamos la ruta en nuestra colección
                            // std::cout << "TwoOpt Improvement found! Old route time: " << oldTimeUsed 
                            //           << " New route time: " << timeUsed 
                            //           << " (Improvement: " << improvement << ")" << std::endl;
                            routes[routeIndex].setRoute(newRoute);
                            routes[routeIndex].subtractRemainingTime(-improvement);
                            routes[routeIndex].resetLoad();
                            routes[routeIndex].addLoad(finalLoad);
                            
                            improvementFound = true;
                            break;
                        }
                    }
                }
                
                // Si encontramos una mejora, rompemos el bucle externo también
                if (improvementFound) {
                    break;
                }
            }
            
            // Si encontramos una mejora en esta ruta, pasamos a la siguiente iteración
            if (improvementFound) {
                break;
            }
        }
    }
    
    // Actualizamos la solución con las nuevas rutas
    solution.setCollectionRoutes(routes);
}