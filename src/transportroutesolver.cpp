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
#include "include/transportroutesolver.h"
#include "include/transportationvehicle.h"
#include "include/transferStation.h"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

TransportRouteSolver::TransportRouteSolver(ProblemInstance& problemInstance, Solution& sol)
  : problem_(problemInstance), solution_(sol) {
  vehicleTravelSpeed_ = problemInstance.vehicleSpeed();
  vehicleCapacity_ = problemInstance.transportVehicleCapacity();
  maxRouteDuration_ = problemInstance.maxTransportRouteDuration();
  transferStations_ = problemInstance.transferStations();
  tasks_ = solution_.getTasks();
}

std::vector<TransportationVehicle> TransportRouteSolver::constructTransportRoutes() {
  std::vector<TransportationVehicle> vehicles;
  // Paso 1: Ordenar tareas por tiempo de llegada (línea 1 del Algoritmo 2)
  std::sort(tasks_.begin(), tasks_.end(), [](const Task& a, const Task& b) {
    return a.getArrivalTime() < b.getArrivalTime();
  });
  // Paso 2: Encontrar la cantidad mínima de residuos (línea 3 del Algoritmo 2)
  double minWasteAmount = std::numeric_limits<double>::max();
  for (const auto& task : tasks_) {
    minWasteAmount = std::min(minWasteAmount, task.getWasteAmount());
  }
  // Copia de las tareas para procesar (línea 4-23 del Algoritmo 2)
  std::vector<Task> remainingTasks = tasks_;
  while (!remainingTasks.empty()) {
    // Obtener la primera tarea (líneas 5-6)
    Task currentTask = remainingTasks.front();
    remainingTasks.erase(remainingTasks.begin());
    // Seleccionar el mejor vehículo para la tarea usando selectBestVehicle (línea 7)
    TransportationVehicle* selectedVehicle = selectBestVehicle(vehicles, currentTask);
    if (selectedVehicle == nullptr) {
      // Crear un nuevo vehículo (líneas 8-13)
      TransportationVehicle newVehicle(
          vehicles.size() + 1,
          vehicleCapacity_,
          maxRouteDuration_
      );
      // Iniciar en el vertedero
      newVehicle.addLocation(problem_.landfill().getLocation());
      // Añadir la tarea al nuevo vehículo
      newVehicle.addTask(currentTask);
      // Añadir el nuevo vehículo a la lista
      vehicles.push_back(newVehicle);
    } else {
      // Añadir la tarea al vehículo existente (líneas 15-17)
      selectedVehicle->addTask(currentTask);
      // Verificar si se necesita ir al vertedero (líneas 18-21)
      if (selectedVehicle->getRemainingCapacity() < minWasteAmount) {
        selectedVehicle->returnToLandfill(problem_.landfill().getLocation());
      }
    }
  }
  // Asegurar que todos los vehículos terminen en el vertedero (líneas 24-28)
  for (auto& vehicle : vehicles) {
    if (vehicle.getCurrentLocation().getId() != problem_.landfill().getId()) {
      vehicle.returnToLandfill(problem_.landfill().getLocation());
    }
  }
  return vehicles;
}

// Método para calcular el tiempo total usado por los vehículos de transporte
double TransportRouteSolver::calculateTotalTransportTime(const std::vector<TransportationVehicle>& routes) const {
  double totalTime = 0.0;
  for (const auto& vehicle : routes) {
    // Usar el tiempo máximo menos el tiempo restante para obtener el tiempo usado
    totalTime += (maxRouteDuration_ - vehicle.getRemainingTime());
  }
  return totalTime;
}

// Método para calcular el tiempo de viaje entre dos ubicaciones
double TransportRouteSolver::calculateTravelTime(const Location& from, const Location& to) const {
  return from.distanceTo(to) / vehicleTravelSpeed_ * 60; // Convertir a minutos
}

// Método para encontrar la estación de transferencia más cercana a una ubicación
TransferStation TransportRouteSolver::findClosestTransferStation(const Location& currentLocation) const {
  double minDistance = std::numeric_limits<double>::max();
  TransferStation closestStation;
  for (const auto& station : transferStations_) {
    double distance = currentLocation.distanceTo(station.getLocation());
    if (distance < minDistance) {
      minDistance = distance;
      closestStation = station;
    }
  }
  return closestStation;
}

// Implementación del Algoritmo 3 según el pseudocódigo
TransportationVehicle* TransportRouteSolver::selectBestVehicle(std::vector<TransportationVehicle>& vehicles, const Task& task) const {
  TransportationVehicle* selectedVehicle = nullptr;
  double bestInsertionCost = std::numeric_limits<double>::max();
  // Para cada vehículo en la lista de vehículos (líneas 3-9 del Algoritmo 3)
  for (auto& vehicle : vehicles) {
    // Comprobar si el vehículo puede aceptar la tarea
    if (vehicle.canAcceptTask(task)) {
      // Calcular el costo de inserción (línea 4)
      // En este caso, usar la distancia/tiempo desde la ubicación actual hasta la estación de transferencia
      double cost = calculateTravelTime(
        vehicle.getCurrentLocation(), 
        task.getTransferStation().getLocation()
      );
      // Si el costo es mejor que el mejor encontrado hasta ahora (líneas 5-8)
      if (cost < bestInsertionCost) {
        selectedVehicle = &vehicle;
        bestInsertionCost = cost;
      }
    }
  }
  // Devolver el vehículo seleccionado o nullptr si no se encontró ninguno
  return selectedVehicle;
}