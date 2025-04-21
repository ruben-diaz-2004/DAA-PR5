/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 25/03/2025
  * @brief VRPT-SWTS
  */
#include "include/reinsertintra.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

void ReinsertIntra::runLocalSearch() {
  bool improvementFound = true;
  const double IMPROVEMENT_THRESHOLD = 0.0001;
  std::vector<CollectionVehicle> routes = solution.getCollectionRoutes();
  // std::cout << "Initial time: " << solution.getTotalTime() << std::endl;

  while (improvementFound) {
    improvementFound = false;
    for (size_t routeIndex = 0; routeIndex < routes.size(); routeIndex++) {
      std::vector<Location> currentRoute = routes[routeIndex].getRoute();
      // Recorremos los elementos (omitiendo el primer y último, asumiendo que son el depósito)
      // Nota: se asume que la posición 0 y la última son fijas (depósito o fin de ruta)
      for (size_t i = 1; i < currentRoute.size() - 1; i++) {
        // Solo consideramos el elemento si es una zona
        if (!isZone(currentRoute[i]) || !isZone(currentRoute[i-1])) {
          continue;
        }
        // Intentar reinsertar el elemento en cada posición anterior (por delante)
        for (size_t j = 1; j < i; j++) {
          std::vector<Location> newRoute = currentRoute;
          // Extraemos el elemento de la posición i
          Location elem = newRoute[i];
          newRoute.erase(newRoute.begin() + i);
          // Lo reinsertamos en la posición j (j < i)
          newRoute.insert(newRoute.begin() + j, elem);
          // Evaluamos la nueva ruta
          double timeUsed = 0.0;
          double finalLoad = 0.0;
          if (evaluateRoute(newRoute, timeUsed, finalLoad)) {
            // Evaluar la ruta original para calcular la mejora
            double oldTimeUsed = 0.0;
            double oldFinalLoad = 0.0;
            evaluateRoute(currentRoute, oldTimeUsed, oldFinalLoad);
            double improvement = oldTimeUsed - timeUsed;
            if (improvement > IMPROVEMENT_THRESHOLD) {
              // std::cout << "ReinsertIntra Improvement found! Old route time: " << oldTimeUsed 
              //           << " New route time: " << timeUsed 
              //           << " (Improvement: " << improvement << ")" << std::endl;
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
              
              // Actualizamos la ruta con la mejora encontrada
              routes[routeIndex].setRoute(newRoute);
              routes[routeIndex].subtractRemainingTime(-improvement);
              routes[routeIndex].resetLoad();
              routes[routeIndex].addLoad(finalLoad);
              
              improvementFound = true;
              // Rompemos el loop interno al aplicar una mejora en esta ruta
              break;
            }
          }
        }
        if (improvementFound) {
          // Si se encontró una mejora, se pasa a la siguiente ruta
          break;
        }
      }
    }
  }
  // Update the solution with the new routes
  solution.setCollectionRoutes(routes);
}