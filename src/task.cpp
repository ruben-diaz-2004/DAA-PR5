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
#include "include/task.h"
#include "include/transferStation.h"

// Default constructor
Task::Task() : 
  wasteAmount_(0), 
  station_(TransferStation()), 
  arrivalTime_(0) 
{}

// Parameterized constructor
Task::Task(double amount, const TransferStation& transferStation, double time) :
  wasteAmount_(amount),
  station_(transferStation),
  arrivalTime_(time)
{}

// Print task details
void Task::printTask() const {
  std::cout << "Task Details:" << std::endl;
  std::cout << "Waste Amount: " << wasteAmount_ << std::endl;
  std::cout << "Transfer Station ID: " << station_.getId() << std::endl;
  std::cout << "Arrival Time: " << arrivalTime_ << std::endl;
}

// Getters
double Task::getWasteAmount() const { return wasteAmount_; }
const TransferStation& Task::getTransferStation() const { return station_; }
double Task::getArrivalTime() const { return arrivalTime_; }

// Setters
void Task::setWasteAmount(double amount) { wasteAmount_ = amount; }
void Task::setTransferStation(const TransferStation& transferStation) { station_ = transferStation; }
void Task::setArrivalTime(double time) { arrivalTime_ = time; }