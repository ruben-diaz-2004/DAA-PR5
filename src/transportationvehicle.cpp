#include "./include/transportationvehicle.h"
#include "./include/task.h"
#include <algorithm>
#include <cmath>

// Default constructor
TransportationVehicle::TransportationVehicle() : 
    id(0), 
    capacity(0), 
    currentLoad(0), 
    maxRouteDuration(0), 
    remainingTime(0),
    currentLocation(Location())
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
    currentLocation(Location())
{}

// Check if vehicle can accept a task
bool TransportationVehicle::canAcceptTask(const Task& task) const {
    // Check if task waste fits in remaining capacity
    if (task.getWasteAmount() > getRemainingCapacity()) {
        return false;
    }

    // If there are already assigned tasks, check time constraints
    if (!assignedTasks.empty()) {
        const Task& lastTask = assignedTasks.back();
        double travelTime = currentLocation.distanceTo(task.getTransferStation().getLocation());
        
        // Check if there's enough time between last task and new task
        if (task.getArrivalTime() - lastTask.getArrivalTime() < travelTime) {
            return false;
        }
    }

    return true;
}

// Add a task to the vehicle
void TransportationVehicle::addTask(const Task& task) {
    if (!canAcceptTask(task)) {
        throw std::runtime_error("Cannot accept task");
    }

    assignedTasks.push_back(task);
    addLocation(task.getTransferStation().getLocation());
    addLoad(task.getWasteAmount());
}

// Add a location to the route
void TransportationVehicle::addLocation(const Location& location) {
    route.push_back(location);
    currentLocation = location;
}

// Return to landfill
void TransportationVehicle::returnToLandfill(const Location& landfillLocation) {
    addLocation(landfillLocation);
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
    return remainingTime;
}