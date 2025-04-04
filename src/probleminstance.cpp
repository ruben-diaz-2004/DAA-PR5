

#include "include/probleminstance.h"
#include "include/instanceparser.h"


#include <iostream>
#include <string>


// Constructor
ProblemInstance::ProblemInstance(std::string filename) {
    ProblemInstanceParser parser;
    parser.loadFromFile(filename);

    // Set problem parameters
    maxCollectionRouteDuration_ = parser.getMaxCollectionRouteDuration();
    maxTransportRouteDuration_ = parser.getMaxTransportRouteDuration();
    maxVehicles_ = parser.getMaxVehicles();
    numberOfZones_ = parser.getNumberOfZones();
    collectionVehicleCapacity_ = parser.getCollectionVehicleCapacity();
    transportVehicleCapacity_ = parser.getTransportVehicleCapacity();
    vehicleSpeed_ = parser.getVehicleSpeed();

    // Set locations
    depot_ = parser.getDepot();
    landfill_ = parser.getLandfill();
    transferStations_ = parser.getTransferStations();
    zones_ = parser.getZones(); 
}