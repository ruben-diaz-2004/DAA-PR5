#include "./include/instanceparser.h"
#include <iostream>

void ProblemInstanceParser::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    // Clear any existing data
    transferStations.clear();
    zones.clear();

    // Parse file sections
    parseHeader(file);
    parseLocations(file);
    parseZones(file);

    file.close();
}

void ProblemInstanceParser::parseHeader(std::ifstream& file) {
    std::string line;
    std::string key;
    double value;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        
        // Skip empty or comment lines
        if (line.empty() || line[0] == '/' || line[0] == '#') continue;

        // Parse key-value pairs
        if (iss >> key >> value) {
            if (key == "L1") maxCollectionRouteDuration = value;
            else if (key == "L2") maxTransportRouteDuration = value;
            else if (key == "num_vehicles") maxVehicles = static_cast<int>(value);
            else if (key == "num_zones") numberOfZones = static_cast<int>(value);
            else if (key == "Q1") collectionVehicleCapacity = value;
            else if (key == "Q2") transportVehicleCapacity = value;
            else if (key == "V") vehicleSpeed = value;
        }

        // Stop parsing header when we encounter a numeric line (zone data)
        if (std::isdigit(line[0])) {
            file.seekg(std::streampos(file.tellg()) - line.length() - 1);
            break;
        }
    }
}

void ProblemInstanceParser::parseLocations(std::ifstream& file) {
    std::string line;
    std::string key;
    double x, y;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        
        // Skip empty or comment lines
        if (line.empty() || line[0] == '/' || line[0] == '#') continue;

        // Parse location lines
        if (iss >> key >> x >> y) {
            if (key == "Depot") {
                depot = Depot(Location(x, y));
            }
            else if (key == "IF") {
                transferStations.emplace_back(TransferStation(0, Location(x, y)));
            }
            else if (key == "IF1") {
                transferStations.emplace_back(TransferStation(1, Location(x, y)));
            }
            else if (key == "Dumpsite") {
                landfill = Landfill(0, Location(x, y));
            }

            // Stop parsing locations when we encounter a numeric line (zone data)
            if (std::isdigit(line[0])) {
                file.seekg(std::streampos(file.tellg()) - line.length() - 1);
                break;
            }
        }
    }
}

void ProblemInstanceParser::parseZones(std::ifstream& file) {
    std::string line;
    int zoneId;
    double x, y, d1, d2;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        
        // Skip empty or comment lines
        if (line.empty() || line[0] == '/' || line[0] == '#') continue;

        // Parse zone data
        if (iss >> zoneId >> x >> y >> d1 >> d2) {
            // Zone demand is calculated as (D2 - D1)
            double demand = d2 - d1;
            zones.emplace_back(Zone(zoneId, Location(x, y), demand));
        }
    }
}