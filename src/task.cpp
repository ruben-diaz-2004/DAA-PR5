#include "include/task.h"
#include "include/transferStation.h"

// Default constructor
Task::Task() : 
    wasteAmount(0), 
    station(TransferStation()), 
    arrivalTime(0) 
{}

// Parameterized constructor
Task::Task(double amount, const TransferStation& transferStation, double time) :
    wasteAmount(amount),
    station(transferStation),
    arrivalTime(time)
{}

// Print task details
void Task::printTask() const {
    std::cout << "Task Details:" << std::endl;
    std::cout << "Waste Amount: " << wasteAmount << std::endl;
    std::cout << "Transfer Station ID: " << station.getId() << std::endl;
    std::cout << "Arrival Time: " << arrivalTime << std::endl;
}

// Getters
double Task::getWasteAmount() const { return wasteAmount; }
const TransferStation& Task::getTransferStation() const { return station; }
double Task::getArrivalTime() const { return arrivalTime; }

// Setters
void Task::setWasteAmount(double amount) { wasteAmount = amount; }
void Task::setTransferStation(const TransferStation& transferStation) { station = transferStation; }
void Task::setArrivalTime(double time) { arrivalTime = time; }