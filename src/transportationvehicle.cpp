#include "include/transportationvehicle.h"
#include "include/task.h"
#include <algorithm>
#include <cmath>

// Default constructor
TransportationVehicle::TransportationVehicle() : 
    id(0), 
    capacity(0), 
    currentLoad(0), 
    maxRouteDuration(0), 
    remainingTime(0),
    currentLocation(Location(0,0,0)),
    vehicleTravelSpeed(30) // Initialize travel speed
{}

// Parameterized constructor
TransportationVehicle::TransportationVehicle(
    int vehicleId, 
    double vehicleCapacity, 
    double maxTime
) : 
    id(vehicleId), 
    capacity(vehicleCapacity), 
    currentLoad(0), 
    maxRouteDuration(maxTime),
    remainingTime(maxTime),
    currentLocation(Location(0,0,0)),
    vehicleTravelSpeed(30) // Initialize travel speed
{}

// Check if vehicle can accept a task
bool TransportationVehicle::canAcceptTask(const Task& task) const {
    // Condición (b): La capacidad restante del vehículo debe ser mayor o igual a la cantidad de residuos
    if (task.getWasteAmount() > getRemainingCapacity()) {
        return false;
    }
    
    // Si la ruta ya tiene tareas asignadas
    if (!assignedTasks.empty()) {
        // Condición (a): Si h' es la última tarea asignada a e, entonces el tiempo de viaje desde sh' hasta sh
        // debe ser menor o igual a la diferencia τh - τh'
        const Task& lastTask = assignedTasks.back();
        
        // Calcular tiempo de viaje entre la estación de transferencia de la última tarea y la nueva
        double travelTimeBetweenStations = lastTask.getTransferStation().getLocation().distanceTo(
            task.getTransferStation().getLocation()) / vehicleTravelSpeed * 60; // Convertir a minutos
        
        // Calcular la diferencia de tiempos de llegada
        double arrivalTimeDifference = task.getArrivalTime() - lastTask.getArrivalTime();
        
        // Verificar condición (a)
        if (travelTimeBetweenStations > arrivalTimeDifference) {
            return false;
        }
    }
    
    // Condición (c): La duración total de la ruta, considerando el regreso al vertedero,
    // no debe exceder un umbral L'
    
    // Para verificar esta condición, necesitamos:
    // 1. Calcular el tiempo de viaje desde la ubicación actual hasta la estación de transferencia de la tarea
    double travelTimeToTask = currentLocation.distanceTo(task.getTransferStation().getLocation()) / vehicleTravelSpeed * 60;
    double timeBetweenTasks = 0;
    if (!assignedTasks.empty()) {
        timeBetweenTasks = task.getArrivalTime() - assignedTasks.back().getArrivalTime();
    }
    
    // 2. Estimar el tiempo para volver al vertedero desde la estación de transferencia de la tarea
    // (idealmente, la ubicación del vertedero debería ser pasada como parámetro o almacenada en la clase)
    Location landfillLocation(10, 60, 0); // Reemplazar con la ubicación real del vertedero
    double timeToReturnToLandfill = task.getTransferStation().getLocation().distanceTo(landfillLocation) / vehicleTravelSpeed * 60;
    // std::cout << "Time to return to landfill: " << timeToReturnToLandfill << " minutes" << std::endl;
    
    // 3. Verificar si hay suficiente tiempo restante para:
    //    - Viajar a la tarea
    //    - Volver al vertedero
    
    // Tiempo total necesario para completar la tarea y volver al vertedero
    double totalTimeNeeded = timeBetweenTasks + travelTimeToTask + timeToReturnToLandfill;
    
    // Verificar condición (c)
    if (totalTimeNeeded > remainingTime) {
        return false;
    }
    
    // Si todas las condiciones se cumplen, el vehículo puede aceptar la tarea
    return true;
}

// Add a task to the vehicle
void TransportationVehicle::addTask(const Task& task) {
    // Verificar si podemos aceptar la tarea
    if (!canAcceptTask(task)) {
        throw std::runtime_error("Cannot accept task");
    }
    
    // Calcular el tiempo de viaje desde la ubicación actual hasta la estación de transferencia de la tarea
    double travelTime = currentLocation.distanceTo(task.getTransferStation().getLocation()) / vehicleTravelSpeed * 60;
    std::cout << "Travel time to task: " << travelTime << " minutes" << std::endl;
    
    // Actualizar el tiempo restante
    remainingTime -= travelTime; // Tiempo para llegar a la tarea
    if (!assignedTasks.empty()) {
        remainingTime -= task.getArrivalTime() - assignedTasks.back().getArrivalTime(); // Tiempo entre tareas
    }
    // Añadir la tarea a la lista de tareas asignadas
    assignedTasks.push_back(task);
    
    // Actualizar la ubicación actual y la ruta
    addLocation(task.getTransferStation().getLocation());
    
    // Actualizar la carga actual
    addLoad(task.getWasteAmount());
    std::cout << "Time remaining after adding task: " << remainingTime << " minutes" << std::endl;
}

// Add a location to the route
void TransportationVehicle::addLocation(const Location& location) {
    route.push_back(location);
    currentLocation = location;
}

// Return to landfill
void TransportationVehicle::returnToLandfill(const Location& landfillLocation) {
    // Calcular el tiempo de viaje desde la ubicación actual hasta el vertedero
    double travelTime = currentLocation.distanceTo(landfillLocation) / vehicleTravelSpeed * 60;
    
    // Actualizar el tiempo restante
    remainingTime -= travelTime;
    
    // Añadir el vertedero a la ruta
    addLocation(landfillLocation);
    
    // Vaciar la carga
    clearLoad();
}

// Add load to the vehicle
void TransportationVehicle::addLoad(double wasteAmount) {
    if (currentLoad + wasteAmount > capacity) {
        throw std::runtime_error("Exceeding vehicle capacity");
    }
    currentLoad += wasteAmount;
}

// Clear vehicle load
void TransportationVehicle::clearLoad() {
    currentLoad = 0;
}

// Getters
int TransportationVehicle::getId() const { return id; }
double TransportationVehicle::getCurrentLoad() const { return currentLoad; }
double TransportationVehicle::getRemainingCapacity() const { return capacity - currentLoad; }
const std::vector<Task>& TransportationVehicle::getAssignedTasks() const { return assignedTasks; }
const std::vector<Location>& TransportationVehicle::getRoute() const { return route; }
Location TransportationVehicle::getCurrentLocation() const { return currentLocation; }

// Calculate total route distance
double TransportationVehicle::calculateTotalDistance() const {
    double totalDistance = 0;
    for (size_t i = 1; i < route.size(); ++i) {
        totalDistance += route[i-1].distanceTo(route[i]);
    }
    return totalDistance;
}

// Get remaining route time
double TransportationVehicle::getRemainingTime() const {
    // Calcula el tiempo restante basado en la diferencia entre el momento de llegada de la primera tarea y el de la última
    // if (assignedTasks.empty()) {
    //     return maxRouteDuration;
    // }
    // double totalTime = 0;
    // totalTime += assignedTasks.back().getArrivalTime() - assignedTasks.front().getArrivalTime();
    // totalTime += calculateTotalDistance() / vehicleTravelSpeed * 60; // Convertir a minutos
    // return maxRouteDuration - totalTime;
    return remainingTime;
}