#include "include/multistart.h"
#include <limits>



void MultiStart::run() {
    // Initialize the best solution
    Solution bestSolution = solution;
    double bestCost = std::numeric_limits<double>::max();
    int bestNumVehicles = std::numeric_limits<int>::max();
    RVND rvnd(instance, solution);
    TransportRouteSolver transportSolver(instance, solution);

    // Run the GRASP algorithm for a number of iterations
    for (int i = 0; i < iterations; ++i) {
        // Create a new GRASP solver instance
        GraspRoutingSolver graspSolver(instance, graspN, 1, solution);
        
        // Construct the collection routes using GRASP
        std::vector<CollectionVehicle> graspRoutes = graspSolver.constructCollectionRoutes();
        
        // Run RVND on the new solution
        rvnd.RunVND();

        // solution.buildTasks(instance);

        // Run the transport route solver
        std::vector<TransportationVehicle> transportRoutes = transportSolver.constructTransportRoutes();
        solution.setTransportationVehicles(transportRoutes);
        // Check if the new solution is better than the best one found so far
        int numVehicles = solution.getNumVehicles();
        double totalTime = solution.getTotalTime();
        if (numVehicles < bestNumVehicles || (numVehicles == bestNumVehicles && totalTime < bestCost)) {
            bestSolution = solution;
            bestCost = totalTime;
            bestNumVehicles = numVehicles;
        }
        // Print the current iteration results
        std::cout << "Iteration " << i + 1 << ": "
                  << "Vehicles: " << numVehicles 
                  << ", Total Time: " << totalTime 
                  << ", Best Cost: " << bestCost 
                  << ", Best Vehicles: " << bestNumVehicles 
                  << std::endl;
    }

    // Update the original solution with the best one found
    solution = bestSolution;
}