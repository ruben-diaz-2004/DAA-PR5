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

// Getters
double Task::getWasteAmount() const { return wasteAmount; }
const TransferStation& Task::getTransferStation() const { return station; }
double Task::getArrivalTime() const { return arrivalTime; }

// Setters
void Task::setWasteAmount(double amount) { wasteAmount = amount; }
void Task::setTransferStation(const TransferStation& transferStation) { station = transferStation; }
void Task::setArrivalTime(double time) { arrivalTime = time; }