#include "include/transportroutesolver.h"
#include "include/transportationvehicle.h"
#include "include/transferStation.h"


#include <iostream>
#include <vector>
#include <limits>


TransportRouteSolver::TransportRouteSolver(ProblemInstance& problemInstance, Solution& solution)
    : problem_(problemInstance), solution_(solution) {
    vehicleTravelSpeed_ = problemInstance.vehicleSpeed();
    vehicleCapacity_ = problemInstance.transportVehicleCapacity();
    maxRouteDuration_ = problemInstance.maxTransportRouteDuration();
    transferStations_ = problemInstance.transferStations();
    transportationVehicles_.reserve(problemInstance.maxVehicles());
}


std::vector<TransportationVehicle> TransportRouteSolver::constructTransportRoutes() {
    std::vector<TransportationVehicle> transportRoutes;
    // Sort tasks by arrival time
    std::sort(tasks_.begin(), tasks_.end(), [](const Task& a, const Task& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });
    // Iterate through each task
    for (const auto& task : tasks_) {
        // Find the best vehicle for the task
        TransportationVehicle bestVehicle = selectBestVehicle(transportationVehicles_, task);
        if (bestVehicle.canAcceptTask(task)) {
            // Assign the task to the vehicle
            bestVehicle.addTask(task);
            transportRoutes.push_back(bestVehicle);
        } else {
            // Create a new vehicle if no existing vehicle can accept the task
            TransportationVehicle newVehicle(
                transportationVehicles_.size() + 1,
                vehicleCapacity_,
                maxRouteDuration_
            );
            newVehicle.addTask(task);
            transportRoutes.push_back(newVehicle);
        }
    }
    // Return to landfill
    for (auto& vehicle : transportRoutes) {
        if (vehicle.getCurrentLoad() > 0) {
            vehicle.returnToLandfill(problem_.landfill().getLocation());
        }
    }
    

    return transportRoutes;
}

double TransportRouteSolver::calculateTotalTransportTime(const std::vector<TransportationVehicle>& routes) const {
    double totalTime = 0.0;
    for (const auto& vehicle : routes) {
        totalTime += vehicle.getRemainingTime();
    }
    return totalTime;
}

double TransportRouteSolver::calculateTravelTime(const Location& from, const Location& to) const {
    return problem_.getDistance(from.getId(), to.getId()) / vehicleTravelSpeed_ * 60; // Convert to minutes
}

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

TransportationVehicle TransportRouteSolver::selectBestVehicle(const std::vector<TransportationVehicle>& vehicles, const Task& task) const {
    double minTime = std::numeric_limits<double>::max();
    TransportationVehicle bestVehicle;

    for (const auto& vehicle : vehicles) {
        if (vehicle.canAcceptTask(task)) {
            double travelTime = calculateTravelTime(vehicle.getCurrentLocation(), task.getTransferStation().getLocation());
            if (travelTime < minTime) {
                minTime = travelTime;
                bestVehicle = vehicle;
            }
        }
    }

    return bestVehicle;
}