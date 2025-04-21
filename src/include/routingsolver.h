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
#ifndef ROUTING_SOLVER_H
#define ROUTING_SOLVER_H

#include <vector>
#include "collectionvehicle.h"
#include "transportationvehicle.h"

class ProblemInstance;

class RoutingSolver {
protected:
  // Referencia al problema
  ProblemInstance& problem;
  
  // Métodos auxiliares comunes
  TransferStation findClosestTransferStation(const Location& currentLocation) const;
  Zone findClosestZone(const Location& currentLocation, std::vector<Zone> unassignedZones) const;
  Zone findNClosestZone(const Location& currentLocation, std::vector<Zone> unassignedZones, int n) const;
  double calculateTravelTime(const Location& from, const Location& to) const;
  int canVisitZone(const CollectionVehicle& vehicle, const Zone& zone, double remainingTime) const;

public:
  // Constructor simplificado
  RoutingSolver(ProblemInstance& problemInstance)
      : problem(problemInstance) {}
  

  // Métodos puros virtuales que deben implementar las clases derivadas
  virtual std::vector<CollectionVehicle> constructCollectionRoutes() = 0;

  // Getters y métodos adicionales
  // int getNumberOfZonesVisited() const;
};

#endif // ROUTING_SOLVER_H