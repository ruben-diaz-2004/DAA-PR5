

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

  // Print loaded data for debugging
  // std::cout << "Depot Location: (" << depot_.getLocation().getId() << std::endl;
  // std::cout << "Landfill Location: (" << landfill_.getLocation().getId() << ")" << std::endl;
  // for (const auto& zone : zones_) {
  //     std::cout << "Zone ID: " << zone.getId() << ", Location: (" 
  //               << zone.getLocation().getX() << ", " 
  //               << zone.getLocation().getY() << ")" << std::endl;
  // }
  // for (const auto& station : transferStations_) {
  //     std::cout << "Transfer Station ID: " << station.getId() << ", Location: (" 
  //               << station.getLocation().getX() << ", " 
  //               << station.getLocation().getY() << ")" << std::endl;
  // }

  // Initialize the distance matrix
  initializeDistanceMatrix();
}

#include <cmath> // For sqrt

// Method to initialize the distance matrix
void ProblemInstance::initializeDistanceMatrix() {
  // Calculate total number of locations (depot + zones + transfer stations)
  int totalLocations = 1 + zones_.size() + transferStations_.size();
  
  // Initialize the matrix with correct size
  distanceMatrix_.resize(totalLocations, std::vector<double>(totalLocations, 0.0));
  
  // Create a vector with all locations for easier access
  std::vector<Location> allLocations;
  std::vector<int> locationIds;
  
  // Add depot (ID: -1)
  allLocations.push_back(depot_.getLocation());
  locationIds.push_back(-1);
  
  // Add zones
  for (const auto& zone : zones_) {
      allLocations.push_back(zone.getLocation());
      locationIds.push_back(zone.getId());
  }

  // Add transfer stations
  for (const auto& station : transferStations_) {
      allLocations.push_back(station.getLocation());
      locationIds.push_back(station.getId());
  }
  
  // Verificar tamaños
  if (allLocations.size() != totalLocations) {
      std::cerr << "Error: allLocations size (" << allLocations.size() 
                << ") doesn't match totalLocations (" << totalLocations << ")" << std::endl;
  }
  
  // Calculate distances for each pair of locations
  for (size_t i = 0; i < allLocations.size(); i++) {
    for (size_t j = 0; j < allLocations.size(); j++) {
      if (i == j) {
        distanceMatrix_[i][j] = 0.0;  // Distance to itself is 0
      } else {
        // Calculate Euclidean distance
        double dx = allLocations[i].getX() - allLocations[j].getX();
        double dy = allLocations[i].getY() - allLocations[j].getY();
        distanceMatrix_[i][j] = std::sqrt(dx*dx + dy*dy);
      }
    }
  }
    

  // std::cout << "Distance matrix initialized with " << distanceMatrix_.size() << " locations" << std::endl;
  // std::cout << "Depot (ID -1) is at index " << mapLocationIdToIndex(-1) << std::endl;
  // if (!zones_.empty())
  //     std::cout << "First zone (ID " << zones_[0].getId() << ") is at index " << mapLocationIdToIndex(zones_[0].getId()) << std::endl;
  // if (!transferStations_.empty())
  //     std::cout << "First transfer station (ID " << transferStations_[0].getId() << ") is at index " << mapLocationIdToIndex(transferStations_[0].getId()) << std::endl;
}

// Method to get the distance between two locations
double ProblemInstance::getDistance(int fromId, int toId) const {
  // Map the location IDs to matrix indices
  int fromIndex = mapLocationIdToIndex(fromId);
  int toIndex = mapLocationIdToIndex(toId);
  
  if (fromIndex >= 0 && toIndex >= 0 && 
    fromIndex < static_cast<int>(distanceMatrix_.size()) && 
    toIndex < static_cast<int>(distanceMatrix_[0].size())) {
    return distanceMatrix_[fromIndex][toIndex];
  }
  else {
    throw std::out_of_range("Invalid location ID(s) for distance calculation.");
  }
}

// Helper method to map location IDs to matrix indices
int ProblemInstance::mapLocationIdToIndex(int locationId) const {
  // Index 0 is reserved for depot (ID -1)
  if (locationId == -1) return 0;
  
  // Indices 1 to zones_.size() are for zones
  for (size_t i = 0; i < zones_.size(); i++) {
    if (zones_[i].getLocation().getId() == locationId) {
      return 1 + i;
    }
  }
  
  // Indices after zones are for transfer stations
  for (size_t i = 0; i < transferStations_.size(); i++) {
    if (transferStations_[i].getLocation().getId() == locationId) {
      return 1 + zones_.size() + i;
    }
  }
  
  // For debugging
  std::cerr << "Could not find index for location ID: " << locationId << std::endl;
  
  // If not found, return -1 (invalid index)
  return -1;
}