
#ifndef GRASP_ROUTING_SOLVER_H
#define GRASP_ROUTING_SOLVER_H

#include "routingsolver.h"
#include "solution.h"
#include <vector>


class GraspRoutingSolver : public RoutingSolver {
private:
  int graspN_;           // Número de candidatos para la selección GRASP
  int iterations_;       // Número de iteraciones
  Solution& solution_;   // Referencia a la solución final

  // Método para calcular el tiempo total usado por los vehículos
  double calculateTotalTime(const std::vector<CollectionVehicle>& routes) const;

public:
  // Constructor
  GraspRoutingSolver(ProblemInstance& problemInstance, int graspN, int iterations, Solution& solution)
      : RoutingSolver(problemInstance), graspN_(graspN), iterations_(iterations), solution_(solution) {}

  // Implementación del algoritmo GRASP
  std::vector<CollectionVehicle> constructCollectionRoutes() override;
};

#endif // GRASP_ROUTING_SOLVER_H