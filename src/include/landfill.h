// Landfill

// Represents the final destination for waste
// Attributes:

// location: Geographical coordinates
// totalWasteReceived: Cumulative waste amount

#ifndef LANDFILL_H
#define LANDFILL_H

#include "Location.h"

class Landfill {
private:
    int id;
    Location location;
    double totalWasteReceived;

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
};

#endif // LANDFILL_H