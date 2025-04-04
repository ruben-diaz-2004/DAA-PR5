#include "include/grasproutingsolver.h"

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>  // For tracking execution time
#include "include/collectionvehicle.h"
#include "include/zone.h"
#include "include/location.h"
#include "include/probleminstance.h"
#include "include/transportationvehicle.h"
#include "include/depot.h"
#include "include/landfill.h"
#include "include/routingsolver.h"

// Implementación del algoritmo GRASP para rutas de transporte
std::vector<CollectionVehicle> GraspRoutingSolver::constructCollectionRoutes() {
  std::cout << "Running GRASP with " << iterations_ << " iterations..." << std::endl;
  
  Solution bestSolution;
  double bestTotalTime = std::numeric_limits<double>::max();
  
  // Variable para la semilla aleatoria
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  srand(seed);
  
  // Ejecutar GRASP varias veces
  for (int iter = 0; iter < iterations_; ++iter) {
    // Reiniciar la solución temporal para esta iteración
    Solution tempSolution;
    std::vector<CollectionVehicle> routes;
    std::vector<Zone> unassignedZones = problem.zones();
    std::vector<Task> tasks;
    
    // Construir rutas para esta iteración
    while (!unassignedZones.empty()) {
      CollectionVehicle currentVehicle(
        routes.size() + 1,
        problem.collectionVehicleCapacity(),
        problem.maxCollectionRouteDuration(),
        problem.vehicleSpeed()
      );
      currentVehicle.addLocation(problem.depot().getLocation());

      bool vehicleCanTakeMoreZones = true;

      while (!unassignedZones.empty() && vehicleCanTakeMoreZones) {
        Zone zone = findNClosestZone(currentVehicle.getCurrentLocation(), unassignedZones, graspN_);
        int visitResult = canVisitZone(currentVehicle, zone, currentVehicle.getRemainingTime());

        if (visitResult == 0) {
          // ✅ Visita válida: actualizar vehículo y quitar zona
          currentVehicle.subtractRemainingTime(
            calculateTravelTime(currentVehicle.getCurrentLocation(), zone.getLocation()) + zone.getTime()
          );
          currentVehicle.addLocation(zone.getLocation());
          currentVehicle.addLoad(zone.getWasteQuantity());

          // Eliminar la zona de la lista de no asignadas
          unassignedZones.erase(
            std::remove_if(unassignedZones.begin(), unassignedZones.end(),
                         [&zone](const Zone& z) { return z.getId() == zone.getId(); }),
            unassignedZones.end()
          );
        }
        else if (visitResult == 1) {
          // ❌ No hay capacidad: vaciar en estación
          TransferStation station = findClosestTransferStation(currentVehicle.getCurrentLocation());
          currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), station.getLocation()));
          Task task(currentVehicle.getCurrentLoad(), station, problem.maxCollectionRouteDuration() - currentVehicle.getRemainingTime());
          tasks.push_back(task);
          currentVehicle.addLocation(station.getLocation());
          currentVehicle.resetLoad();
        }
        else {
          // ❌ No hay tiempo suficiente: terminar ruta
          vehicleCanTakeMoreZones = false;
        }
      }

      // Si quedó carga, ir a estación más cercana
      if (currentVehicle.getCurrentLoad() > 0) {
        TransferStation station = findClosestTransferStation(currentVehicle.getCurrentLocation());
        currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), station.getLocation()));
        Task task(currentVehicle.getCurrentLoad(), station, problem.maxCollectionRouteDuration() - currentVehicle.getRemainingTime());
        tasks.push_back(task);
        currentVehicle.addLocation(station.getLocation());
        currentVehicle.resetLoad();
      }

      // Volver al depósito
      currentVehicle.subtractRemainingTime(calculateTravelTime(currentVehicle.getCurrentLocation(), problem.depot().getLocation()));
      currentVehicle.addLocation(problem.depot().getLocation());

      // Guardar ruta
      routes.push_back(currentVehicle);

      // Seguridad: no se pudieron asignar más zonas y alcanzamos el límite de vehículos
      if (routes.size() >= problem.maxVehicles() && !unassignedZones.empty()) {
        std::cout << "WARNING: Max number of vehicles reached, but some zones remain unassigned." << std::endl;
        break;
      }
    }
    
    // Guardar solución temporal
    tempSolution.setCollectionRoutes(routes);
    tempSolution.setTasks(tasks);
    
    // Calcular el tiempo total utilizado por los vehículos
    double totalTime = calculateTotalTime(routes);
    
    // Actualizar la mejor solución si corresponde
    if (totalTime < bestTotalTime) {
      bestTotalTime = totalTime;
      bestSolution = tempSolution;
      
      std::cout << "Iteration " << iter + 1 << ": Found better solution with total time: " 
                << bestTotalTime << " minutes, using " << routes.size() << " vehicles." << std::endl;
    }
    
    if (iter % 10 == 0 && iter > 0) {
      std::cout << "Completed " << iter << " iterations. Current best time: " 
                << bestTotalTime << " minutes." << std::endl;
    }
  }
  
  std::cout << "GRASP completed after " << iterations_ << " iterations." << std::endl;
  std::cout << "Best solution uses " << bestSolution.getCollectionRoutes().size() 
            << " vehicles with total time: " << bestTotalTime << " minutes." << std::endl;
  
  // Almacenar la mejor solución
  solution_ = bestSolution;
  
  return bestSolution.getCollectionRoutes();
}

// Método para calcular el tiempo total utilizado por todos los vehículos
double GraspRoutingSolver::calculateTotalTime(const std::vector<CollectionVehicle>& routes) const {
  double totalTime = 0.0;
  
  for (const auto& vehicle : routes) {
    // El tiempo usado es el tiempo máximo menos el tiempo restante
    totalTime += (problem.maxCollectionRouteDuration() - vehicle.getRemainingTime());
  }
  
  return totalTime;
}
