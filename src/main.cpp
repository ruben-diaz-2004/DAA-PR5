#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include "include/probleminstance.h"
#include "include/greedyroutingsolver.h"
#include "include/grasproutingsolver.h"
#include "include/parameters.h"

int main(int argc, char* argv[]) {
  // Check if input file is provided
  parameters options = parse_args(argc, argv);
  ProblemInstance instance(argv[1]);

  switch (options.algorithm) {
    case 1: {
      std::cout << "Greedy algorithm selected." << std::endl;
      GreedyRoutingSolver greedySolver(instance);
      std::vector greedyRoutes = greedySolver.constructCollectionRoutes();
      std::cout << "Greedy routing completed." << std::endl;
      break;
    }
    case 2: {
      std::cout << "GRASP algorithm selected." << std::endl;
      GraspRoutingSolver graspSolver(instance, options.graspN);
      std::vector graspRoutes = graspSolver.constructCollectionRoutes();
      std::cout << "GRASP routing completed." << std::endl;
      break;
    }
    default: {
      std::cerr << "Error: invalid algorithm option." << std::endl;
      return 1;
    }
  }

  // ProblemInstance instance(argv[1]);
  // std::cout << "Problem instance loaded successfully." << std::endl;

  // // Create a GreedyRoutingSolver instance
  // // GreedyRoutingSolver greedySolver(instance);
  // // std::vector<CollectionVehicle> greedyRoutes = greedySolver.constructCollectionRoutes();
  // // std::cout << "Greedy routing completed." << std::endl;

  // // Create a GraspRoutingSolver instance
  // GraspRoutingSolver graspSolver(instance);
  // std::vector<CollectionVehicle> graspRoutes = graspSolver.constructCollectionRoutes();

  return 0;
}