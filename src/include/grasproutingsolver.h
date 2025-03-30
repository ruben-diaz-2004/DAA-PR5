
#ifndef GRASP_ROUTING_SOLVER_H
#define GRASP_ROUTING_SOLVER_H

#include "routingsolver.h"
#include <vector>


class GraspRoutingSolver : public RoutingSolver {
private:
  std::vector<CollectionVehicle> routes;

public:
  // Constructor
  GraspRoutingSolver(ProblemInstance& problemInstance)
      : RoutingSolver(problemInstance) {}

  // Implementación del algoritmo GRASP
  std::vector<CollectionVehicle> constructCollectionRoutes() override;
};

#endif // GRASP_ROUTING_SOLVER_H