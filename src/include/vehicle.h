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

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
  Vehicle(std::string id, double capacity, double maxRouteDuration);
  virtual bool canAcceptLoad(double wasteAmount) = 0;
  virtual void addLoad(double wasteAmount) = 0;
  virtual void clearLoad() = 0;
  std::string getId();
  double getCapacity();
  double getCurrentLoad();
  double getMaxRouteDuration();

protected:
  std::string id_;
  double capacity;
  double currentLoad;
  double maxRouteDuration;
};


#endif