#include <iostream>
#include <string>
#include "./include/probleminstance.h"
#include "./include/instanceparser.h"

int main(int argc, char* argv[]) {
    // Check if input file is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    ProblemInstanceParser parser;
    try {
        parser.loadFromFile("instance1.txt");
    
        // Access parsed data
        std::cout << "Max Vehicles: " << parser.getMaxVehicles() << std::endl;
        std::cout << "Number of Zones: " << parser.getNumberOfZones() << std::endl;
        std::cout << "Depot Location: (" 
                  << parser.getDepot().getLocation().getX() << ", " 
                  << parser.getDepot().getLocation().getY() << ")" << std::endl;
    
        // Iterate through zones
        for (const auto& zone : parser.getZones()) {
            std::cout << "Zone " << zone.getId() 
                      << " demand: " << zone.getWasteQuantity() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error parsing instance file: " << e.what() << std::endl;
    }

    return 0;
}