
#ifndef GRASP_ROUTING_SOLVER_H
#define GRASP_ROUTING_SOLVER_H

#include "routingsolver.h"
#include "solution.h"
#include <vector>


class GraspRoutingSolver : public RoutingSolver {
private:
  std::vector<CollectionVehicle> routes;
  int graspN_;
  Solution& solution_;

public:
  // Constructor
  GraspRoutingSolver(ProblemInstance& problemInstance, int graspN, Solution& solution)
      : RoutingSolver(problemInstance), graspN_(graspN), solution_(solution) {}

  // Implementación del algoritmo GRASP
  std::vector<CollectionVehicle> constructCollectionRoutes() override;

};

#endif // GRASP_ROUTING_SOLVER_H