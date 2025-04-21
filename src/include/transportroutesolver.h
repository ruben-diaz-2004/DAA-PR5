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
#ifndef TRANSPORTROUTESOLVER_H
#define TRANSPORTROUTESOLVER_H

#include "probleminstance.h"
#include "solution.h"
#include "collectionvehicle.h"
#include "transportationvehicle.h"
#include "transferStation.h"
#include "task.h"


class TransportRouteSolver {
public:
  TransportRouteSolver(ProblemInstance& problemInstance, Solution& solution);

  // Método para construir rutas de transporte
  std::vector<TransportationVehicle> constructTransportRoutes();
  // Método para calcular el tiempo total de transporte
  double calculateTotalTransportTime(const std::vector<TransportationVehicle>& routes) const;
  // Método para calcular el tiempo de viaje entre dos ubicaciones
  double calculateTravelTime(const Location& from, const Location& to) const;
  // Método para encontrar la estación de transferencia más cercana
  TransferStation findClosestTransferStation(const Location& currentLocation) const;
  TransportationVehicle* selectBestVehicle(std::vector<TransportationVehicle>& vehicles, const Task& task) const;
  
private:
  ProblemInstance& problem_;
  Solution& solution_;
  std::vector<Task> tasks_;
  double vehicleTravelSpeed_;
  double vehicleCapacity_;
  double maxRouteDuration_;
  std::vector<TransferStation> transferStations_;
  std::vector<TransportationVehicle> transportationVehicles_;
};




#endif // TRANSPORTROUTESOLVER_H