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
#include "include/landfill.h"

// Default constructor
Landfill::Landfill() : 
  id_(0), 
  location_(Location(0,0,0)), 
  totalWasteReceived_(0) 
{}

// Parameterized constructor
Landfill::Landfill(int landfillId, const Location& loc) :
  id_(landfillId),
  location_(loc),
  totalWasteReceived_(0)
{}

// Getters
int Landfill::getId() const { return id_; }
Location Landfill::getLocation() const { return location_; }
double Landfill::getTotalWasteReceived() const { return totalWasteReceived_; }

// Receive waste
void Landfill::receiveWaste(double wasteAmount) {
  totalWasteReceived_ += wasteAmount;
}

// Reset total waste received
void Landfill::resetTotalWasteReceived() {
  totalWasteReceived_ = 0;
}