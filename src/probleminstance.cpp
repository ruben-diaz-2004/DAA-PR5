

#include "include/probleminstance.h"
#include "include/instanceparser.h"


#include <iostream>
#include <string>


// Constructor
ProblemInstance::ProblemInstance(std::string filename) {
    ProblemInstanceParser parser;
    parser.loadFromFile(filename);

    // Set problem parameters
    maxCollectionRouteDuration = parser.getMaxCollectionRouteDuration();
    maxTransportRouteDuration = parser.getMaxTransportRouteDuration();
    maxVehicles = parser.getMaxVehicles();
    numberOfZones = parser.getNumberOfZones();
    collectionVehicleCapacity = parser.getCollectionVehicleCapacity();
    transportVehicleCapacity = parser.getTransportVehicleCapacity();
    vehicleSpeed = parser.getVehicleSpeed();

    // Set locations
    depot = parser.getDepot();
    landfill = parser.getLandfill();
    transferStations = parser.getTransferStations();
    zones = parser.getZones();

    std::cout << "Problem instance loaded successfully." << std::endl;
    std::cout << "Max Vehicles: " << maxVehicles << std::endl;
    std::cout << "Number of Zones: " << numberOfZones << std::endl;
    std::cout << "Collection Vehicle Capacity: " << collectionVehicleCapacity << std::endl;
    std::cout << "Transport Vehicle Capacity: " << transportVehicleCapacity << std::endl;
    std::cout << "Vehicle Speed: " << vehicleSpeed << std::endl;
    std::cout << "Max Collection Route Duration: " << maxCollectionRouteDuration << std::endl;
    std::cout << "Max Transport Route Duration: " << maxTransportRouteDuration << std::endl;
    std::cout << "Depot Location: (" << depot.getLocation().getX() << ", " << depot.getLocation().getY() << ")" << std::endl;
    std::cout << "Landfill Location: (" << landfill.getLocation().getX() << ", " << landfill.getLocation().getY() << ")" << std::endl;
    std::cout << "Transfer Stations: " << std::endl;
    for (const auto& station : transferStations) {
        std::cout << "  - Transfer Station ID: " << station.getId() 
                  << ", Location: (" << station.getLocation().getX() 
                  << ", " << station.getLocation().getY() << ")" << std::endl;
    }
    
}