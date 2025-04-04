#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include "include/probleminstance.h"
#include "include/greedyroutingsolver.h"
#include "include/grasproutingsolver.h"
#include "include/parameters.h"
#include "include/solution.h"

int main(int argc, char* argv[]) {
  // Check if input file is provided
  if (argc < 2) {
    std::cerr << "Error: No input file provided." << std::endl;
    std::cerr << "Usage: " << argv[0] << " <input_file> [-greedy | -grasp <n>]" << std::endl;
    return 1;
  }

  parameters options = parse_args(argc, argv);
  ProblemInstance instance(argv[1]);
  Solution solution = Solution();

  switch (options.algorithm) {
    case 1: {
      std::cout << "Greedy algorithm selected." << std::endl;
      GreedyRoutingSolver greedySolver(instance, solution);
      std::vector<CollectionVehicle> greedyRoutes = greedySolver.constructCollectionRoutes();
      break;
    }
    case 2: {
      std::cout << "GRASP algorithm selected with n=" << options.graspN << std::endl;
      GraspRoutingSolver graspSolver(instance, options.graspN, options.iterations, solution);
      std::vector<CollectionVehicle> graspRoutes = graspSolver.constructCollectionRoutes();
      
      // Imprimir la mejor solución encontrada
      std::cout << "GRASP routing completed with best solution:" << std::endl;
      std::cout << "- Total collection vehicles: " << graspRoutes.size() << std::endl;
      std::cout << "- Total tasks: " << solution.getTasks().size() << std::endl;
      break;
    }
    default: {
      std::cerr << "Error: invalid algorithm option." << std::endl;
      return 1;
    }
  }

  return 0;
}