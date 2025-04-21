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

#ifndef TASK_H
#define TASK_H

#include "transferStation.h"

class Task {
public:
  // Constructors
  Task();
  Task(double amount, const TransferStation& transferStation, double time);

  void printTask() const;

  // Getters
  double getWasteAmount() const;
  const TransferStation& getTransferStation() const;
  double getArrivalTime() const;

  // Setters
  void setWasteAmount(double amount);
  void setTransferStation(const TransferStation& station);
  void setArrivalTime(double time);

private:
  double wasteAmount_;       // Amount of waste to transport
  TransferStation station_;  // Transfer station associated with the task
  double arrivalTime_;       // Time of arrival at the transfer station
};

#endif // TASK_H