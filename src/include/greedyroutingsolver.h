// GreedyRoutingSolver.h
#ifndef GREEDY_ROUTING_SOLVER_H
#define GREEDY_ROUTING_SOLVER_H

#include "routingsolver.h"
#include "solution.h"
#include <vector>


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