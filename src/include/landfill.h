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

#ifndef LANDFILL_H
#define LANDFILL_H

#include "location.h"

class Landfill {
public:
  // Constructors
  Landfill();
  Landfill(int landfillId, const Location& loc);

  // Getters
  int getId() const;
  Location getLocation() const;
  double getTotalWasteReceived() const;

  // Waste management
  void receiveWaste(double wasteAmount);
  void resetTotalWasteReceived();
  
private:
  int id_;
  Location location_;
  double totalWasteReceived_;
};

#endif // LANDFILL_H