

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

    std::cout << "Problem instance loaded successfully." << std::endl;
    std::cout << "Max Vehicles: " << maxVehicles_ << std::endl;
    std::cout << "Number of Zones: " << numberOfZones_ << std::endl;
    std::cout << "Collection Vehicle Capacity: " << collectionVehicleCapacity_ << std::endl;
    std::cout << "Transport Vehicle Capacity: " << transportVehicleCapacity_ << std::endl;
    std::cout << "Vehicle Speed: " << vehicleSpeed_ << std::endl;
    std::cout << "Max Collection Route Duration: " << maxCollectionRouteDuration_ << std::endl;
    std::cout << "Max Transport Route Duration: " << maxTransportRouteDuration_ << std::endl;
    std::cout << "Depot Location: (" << depot_.getLocation().getX() << ", " << depot_.getLocation().getY() << ")" << std::endl;
    std::cout << "Landfill Location: (" << landfill_.getLocation().getX() << ", " << landfill_.getLocation().getY() << ")" << std::endl;
    std::cout << "Transfer Stations: " << std::endl;
    for (const auto& station : transferStations_) {
        std::cout << "  - Transfer Station ID: " << station.getId() 
                  << ", Location: (" << station.getLocation().getX() 
                  << ", " << station.getLocation().getY() << ")" << std::endl;
    }
    
}