#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <chrono>
#include "include/probleminstance.h"
#include "include/greedyroutingsolver.h"
#include "include/grasproutingsolver.h"
#include "include/parameters.h"
#include "include/solution.h"
#include "include/localsearch.h"
#include "include/swapintra.h"
#include "include/swapinter.h"
#include "include/reinsertintra.h"
#include "include/reinsertinter.h"
#include "include/twoopt.h"
#include "include/rvnd.h"

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
  
  // Para medir el tiempo de CPU
  auto start_time = std::chrono::high_resolution_clock::now();
  
  int num_vehicles = 0;
  double total_time = 0.0;

  switch (options.algorithm) {
    case 1: {
      std::cout << "Greedy algorithm selected." << std::endl;
      GreedyRoutingSolver greedySolver(instance, solution);
      std::vector<CollectionVehicle> greedyRoutes = greedySolver.constructCollectionRoutes();
      num_vehicles = greedyRoutes.size();
      total_time = solution.getTotalTime();
      std::cout << "Greedy algorithm completed." << std::endl;
      std::cout << "Total time after greedy: " << total_time << std::endl;
      // std::cout << "Local search algorithm selected." << std::endl;
      // ReinsertIntra intra(instance, solution);
      // intra.runLocalSearch();
      // total_time = solution.getTotalTime();
      // std::cout << "Local search completed." << std::endl;
      // std::cout << "Total time after local search: " << total_time << std::endl;

      std::cout << "Local search algorithm selected." << std::endl;
      TwoOpt inter(instance, solution);
      inter.runLocalSearch();
      total_time = solution.getTotalTime();
      std::cout << "Local search completed." << std::endl;
      std::cout << "Total time after local search: " << total_time << std::endl;

      // RVND rvnd(instance, solution);
      // rvnd.RunVND();
      // num_vehicles = solution.getNumVehicles();
      // total_time = solution.getTotalTime();
      // std::cout << "RVND algorithm completed." << std::endl;
      // std::cout << "Total time after RVND: " << total_time << std::endl;

      // Print the route
      std::cout << "Greedy route: ";
      for (const auto& vehicle : solution.getCollectionRoutes()) {
        std::cout << "Vehicle ID: " << vehicle.getId() << "Remaining time:" << vehicle.getRemainingTime() << ", Route: ";
        for (const auto& loc : vehicle.getRoute()) {
          std::cout << loc.getId() << " ";
        }
        std::cout << std::endl;
      }
      break;
    }
    case 2: {
      std::cout << "GRASP algorithm selected with n=" << options.graspN << std::endl;
      GraspRoutingSolver graspSolver(instance, options.graspN, options.iterations, solution);
      std::vector<CollectionVehicle> graspRoutes = graspSolver.constructCollectionRoutes();
      num_vehicles = graspRoutes.size();
      total_time = solution.getTotalTime();
      std::cout << "GRASP algorithm completed." << std::endl;
      std::cout << "Total time after GRASP: " << total_time << std::endl;

      // RVNS rvns(instance, solution);
      // rvns.RunVNS();
      // num_vehicles = solution.getNumVehicles();
      // total_time = solution.getTotalTime();
      // std::cout << "RVND algorithm completed." << std::endl;
      // std::cout << "Total time after RVNS: " << total_time << std::endl;

      std::cout << "Local search algorithm selected." << std::endl;
      SwapIntra inter(instance, solution);
      inter.runLocalSearch();
      total_time = solution.getTotalTime();
      std::cout << "Local search completed." << std::endl;
      std::cout << "Total time after local search: " << total_time << std::endl;

      break;
    }
    default: {
      std::cerr << "Error: invalid algorithm option." << std::endl;
      return 1;
    }
  }
  
  // Calcular tiempo de CPU
  auto end_time = std::chrono::high_resolution_clock::now();
  double cpu_time = std::chrono::duration<double>(end_time - start_time).count();
  
  // Extraer el nombre del archivo de la ruta completa
  std::string filename = argv[1];
  size_t last_slash = filename.find_last_of("/\\");
  if (last_slash != std::string::npos) {
    filename = filename.substr(last_slash + 1);
  }
  
  // Imprimir resultados en formato uniforme para facilitar el procesamiento posterior
  std::cout << "RESULTADO," << filename << "," << num_vehicles << "," << total_time << "," << cpu_time << std::endl;

  // Imprimir las tareas guardadas en solution
  std::cout << "Tasks:" << std::endl;
  for (const auto& task: solution.getTasks()) {
    std::cout << "Transfer Station: " << task.getTransferStation().getId() 
              << ", Waste Amount: " << task.getWasteAmount() 
              << ", Arrival Time: " << task.getArrivalTime() << std::endl;
  }
  return 0;
}