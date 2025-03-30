// GreedyRoutingSolver.h
#ifndef GREEDY_ROUTING_SOLVER_H
#define GREEDY_ROUTING_SOLVER_H

#include "routingsolver.h"
#include <vector>


class GreedyRoutingSolver : public RoutingSolver {
private:
  std::vector<CollectionVehicle> routes;

public:
  // Constructor simplificado
  GreedyRoutingSolver(ProblemInstance& problemInstance)
      : RoutingSolver(problemInstance) {}
  
  // Implementación del algoritmo voraz
  std::vector<CollectionVehicle> constructCollectionRoutes() override;
};

#endif // GREEDY_ROUTING_SOLVER_H