#include "include/grasproutingsolver.h"

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "include/collectionvehicle.h"
#include "include/zone.h"
#include "include/location.h"
#include "include/probleminstance.h"
#include "include/transportationvehicle.h"
#include "include/depot.h"
#include "include/landfill.h"
#include "include/routingsolver.h"


// Implementación del algoritmo voraz para rutas de transporte
std::vector<CollectionVehicle> GraspRoutingSolver::constructCollectionRoutes() {
  std::cout << "Constructing GRASP collection routes..." << std::endl;
  std::vector<CollectionVehicle> routes;
  std::vector<Zone> unassignedZones = problem.zones();
  std::vector<Task> tasks;

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

  std::cout << "Total routes: " << routes.size() << std::endl;
  solution_.setCollectionRoutes(routes);
  solution_.setTasks(tasks);
  std::cout << "GRASP routing completed." << std::endl;

  return routes;
}
