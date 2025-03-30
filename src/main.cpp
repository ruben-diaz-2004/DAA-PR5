#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include "include/probleminstance.h"
#include "include/greedyroutingsolver.h"
#include "include/grasproutingsolver.h"

int main(int argc, char* argv[]) {
  // Check if input file is provided
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
    return 1;
  }

  try {
    ProblemInstance instance(argv[1]);
    std::cout << "Problem instance loaded successfully." << std::endl;

    // Create a GreedyRoutingSolver instance
    // GreedyRoutingSolver greedySolver(instance);
    // std::vector<CollectionVehicle> greedyRoutes = greedySolver.constructCollectionRoutes();
    // std::cout << "Greedy routing completed." << std::endl;

    // Create a GraspRoutingSolver instance
    GraspRoutingSolver graspSolver(instance);
    std::vector<CollectionVehicle> graspRoutes = graspSolver.constructCollectionRoutes();
    
  
  } catch (const std::exception& e) {
      std::cerr << "Error parsing instance file: " << e.what() << std::endl;
  }

  return 0;
}