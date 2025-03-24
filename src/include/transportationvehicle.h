// TransportationVehicle (Inherits from Vehicle)

// Represents large transportation vehicles (TV)
// Additional attributes:

// currentRoute: Vector of transfer stations and landfill
// Methods:

// bool canAcceptTask(Task task)
// void addTaskToRoute(Task task)
// void returnToLandfill()

#ifndef TRANSPORTATION_VEHICLE_H
#define TRANSPORTATION_VEHICLE_H

#include <vector>
#include <stdexcept>
#include "location.h"
#include "task.h"
#include "transferStation.h"

class TransportationVehicle {
private:
    int id;
    double capacity;      // Maximum load capacity
    double currentLoad;   // Current load
    double maxRouteDuration;
    double remainingTime;
    Location currentLocation;
    std::vector<Location> route;
    std::vector<Task> assignedTasks;

public:
    // Constructors
    TransportationVehicle();
    TransportationVehicle(int vehicleId, double vehicleCapacity, double maxTime);

    // Task management
    bool canAcceptTask(const Task& task) const;
    void addTask(const Task& task);
    
    // Route and location management
    void addLocation(const Location& location);
    void returnToLandfill(const Location& landfillLocation);

    // Load management
    void addLoad(double wasteAmount);
    void clearLoad();

    // Getters
    int getId() const;
    double getCurrentLoad() const;
    double getRemainingCapacity() const;
    const std::vector<Task>& getAssignedTasks() const;
    const std::vector<Location>& getRoute() const;
    Location getCurrentLocation() const;

    // Utility methods
    double calculateTotalDistance() const;
    double getRemainingTime() const;
};

#endif // TRANSPORTATION_VEHICLE_H