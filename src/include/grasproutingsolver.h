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

#ifndef GRASP_ROUTING_SOLVER_H
#define GRASP_ROUTING_SOLVER_H

#include "routingsolver.h"
#include "solution.h"

class GraspRoutingSolver : public RoutingSolver {
public:
  // Constructor
  GraspRoutingSolver(ProblemInstance& problemInstance, int graspN, int iterations, Solution& solution)
      : RoutingSolver(problemInstance), graspN_(graspN), iterations_(iterations), solution_(solution) {}

  // Implementación del algoritmo GRASP
  std::vector<CollectionVehicle> constructCollectionRoutes() override;
  
private:
  int graspN_;           // Número de candidatos para la selección GRASP
  int iterations_;       // Número de iteraciones
  Solution& solution_;   // Referencia a la solución final

  // Método para calcular el tiempo total usado por los vehículos
  double calculateTotalTime(const std::vector<CollectionVehicle>& routes) const;
};

#endif // GRASP_ROUTING_SOLVER_H