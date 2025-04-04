#include "include/landfill.h"

// Default constructor
Landfill::Landfill() : 
    id(0), 
    location(Location(0,0,0)), 
    totalWasteReceived(0) 
{}

// Parameterized constructor
Landfill::Landfill(int landfillId, const Location& loc) :
    id(landfillId),
    location(loc),
    totalWasteReceived(0)
{}

// Getters
int Landfill::getId() const { return id; }
Location Landfill::getLocation() const { return location; }
double Landfill::getTotalWasteReceived() const { return totalWasteReceived; }

// Receive waste
void Landfill::receiveWaste(double wasteAmount) {
    totalWasteReceived += wasteAmount;
}

// Reset total waste received
void Landfill::resetTotalWasteReceived() {
    totalWasteReceived = 0;
}