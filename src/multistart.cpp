/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 25/03/2025
  * @brief VRPT-SWTS
  */
#include "include/multistart.h"
#include <limits>

void MultiStart::run() {
  // Initialize the best solution
  double bestCost = std::numeric_limits<double>::max();
  int bestNumVehicles = std::numeric_limits<int>::max();
  int noImprovementCounter = 0; // Counter for iterations without improvement
  
  // Run the GRASP algorithm for a number of iterations
  for (int i = 0; i < iterations; ++i) {
    if (noImprovementCounter >= 200) {
      std::cout << "Stopping early due to no improvement in 200 iterations." << std::endl;
      break;
    }
    Solution backupSolution = solution;
    // Construct the collection routes using GRASP
    GraspRoutingSolver graspSolver(instance, graspN, 1, solution);
    std::vector<CollectionVehicle> graspRoutes = graspSolver.constructCollectionRoutes();
    // Run RVND on the new solution
    RVND rvnd(instance, solution);
    rvnd.RunVND();
    // solution.buildTasks(instance);
    // Run the transport route solver
    TransportRouteSolver transportSolver(instance, solution);
    solution.setTransportationVehicles(transportSolver.constructTransportRoutes());
    // std::cout << "Total transport routes: " << solution.getTransportationVehicles().size() << std::endl;
    // Check if the new solution is better than the best one found so far
    int numVehicles = solution.getNumVehicles();
    double totalTime = solution.getTotalTime();
    if (numVehicles < bestNumVehicles || (numVehicles == bestNumVehicles && totalTime < bestCost)) {
        bestCost = totalTime;
        bestNumVehicles = numVehicles;
        noImprovementCounter = 0; // Reset the counter on improvement
    } else {
        // If not, revert to the backup solution
        solution = backupSolution;
        noImprovementCounter++; // Increment the counter
    }
    // Print the current iteration results
    std::cout << "Iteration " << i + 1 << ": " << "CV: " << numVehicles << "TV: " << solution.getNumTransportationVehicles() << ", Total Time: " << totalTime 
              << ", Best Cost: " << bestCost << ", Best Vehicles: " << bestNumVehicles  << std::endl;
  }
}