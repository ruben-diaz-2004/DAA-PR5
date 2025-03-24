// Task

// Represents a transportation task
// Attributes:

// wasteAmount: Amount of waste to transport
// transferStation: Station where waste is collected
// arrivalTime: Time of collection
// Methods:

// Getters for attributes

#ifndef TASK_H
#define TASK_H

#include "TransferStation.h"

class Task {
private:
    double wasteAmount;       // Amount of waste to transport
    TransferStation station;  // Transfer station associated with the task
    double arrivalTime;       // Time of arrival at the transfer station

public:
    // Constructors
    Task();
    Task(double amount, const TransferStation& transferStation, double time);

    // Getters
    double getWasteAmount() const;
    const TransferStation& getTransferStation() const;
    double getArrivalTime() const;

    // Setters
    void setWasteAmount(double amount);
    void setTransferStation(const TransferStation& station);
    void setArrivalTime(double time);
};

#endif // TASK_H