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
#ifndef GREEDY_ROUTING_SOLVER_H
#define GREEDY_ROUTING_SOLVER_H

#include "routingsolver.h"
#include "solution.h"

class GreedyRoutingSolver : public RoutingSolver {
public:
  // Constructor simplificado
  GreedyRoutingSolver(ProblemInstance& problemInstance, Solution& solution)
      : RoutingSolver(problemInstance), solution_(solution) {}
  
  // Implementación del algoritmo voraz
  std::vector<CollectionVehicle> constructCollectionRoutes() override;
  
private:
  Solution& solution_;
};

#endif // GREEDY_ROUTING_SOLVER_H