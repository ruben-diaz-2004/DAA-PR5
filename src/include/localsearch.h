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
#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "probleminstance.h"
#include "solution.h"
#include "collectionvehicle.h"

class LocalSearch {
public:
  // Constructor
  LocalSearch(ProblemInstance& problemInstance, Solution& solution)
      : problem(problemInstance), solution(solution) {}

  // Método para ejecutar la búsqueda local
    virtual void runLocalSearch() = 0;

protected:
  ProblemInstance& problem;
  Solution& solution;

  double calculateTravelTime(const Location& from, const Location& to) const;
  bool evaluateRoute(const std::vector<Location>& route, double& totalTime, double& finalLoad);
  bool isZone(const Location& location) const {
    for (const auto& zone : problem.zones()) {
      if (zone.getId() == location.getId()) {
        return true;
      }
    }
    return false;
  }
  CollectionVehicle createVehicleWithRoute(int id, double capacity, const std::vector<Location>& route, double timeUsed, double finalLoad);
};

#endif // LOCALSEARCH_H