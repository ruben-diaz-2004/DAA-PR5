// Landfill

// Represents the final destination for waste
// Attributes:

// location: Geographical coordinates
// totalWasteReceived: Cumulative waste amount

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