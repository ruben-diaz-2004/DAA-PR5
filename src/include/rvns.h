#ifndef RVNS_H
#define RVNS_H

#include "solution.h"
#include "probleminstance.h"
#include "reinsertinter.h"
#include "reinsertintra.h"
#include "swapinter.h"
#include "swapintra.h"


class RVNS {
public:
  RVNS(ProblemInstance &instance, Solution &solution) 
      : instance(instance), solution(solution) {
    localSearchUsed.resize(4, false); // Initialize with 4 local search methods
  }

  void RunVNS() {
    // Initialize the local search methods
    ReinsertIntra intra(instance, solution);
    ReinsertInter inter(instance, solution);
    SwapIntra swapIntra(instance, solution);
    SwapInter swapInter(instance, solution);
    
    bool improved = true;
    while (improved) {
      improved = false;
      
      for (int i = 0; i < 4; i++) {
        if (localSearchUsed[i]) continue; // Skip this method if already used without improvement
        
        // Make a backup of the current solution
        Solution backupSolution = solution;
        double currentCost = solution.getTotalTime();
        
        // Run the appropriate local search based on index
        bool foundImprovement = false;
        if (i == 0) {
            intra.runLocalSearch();
            foundImprovement = (solution.getTotalTime() < currentCost);
        } else if (i == 1) {
            inter.runLocalSearch();
            foundImprovement = (solution.getTotalTime() < currentCost);
        } else if (i == 2) {
            swapIntra.runLocalSearch();
            foundImprovement = (solution.getTotalTime() < currentCost);
        } else if (i == 3) {
            swapInter.runLocalSearch();
            foundImprovement = (solution.getTotalTime() < currentCost);
        }
        
        // Check if solution improved
        if (foundImprovement) {
            // Solution improved, reset all flags and start over
            std::fill(localSearchUsed.begin(), localSearchUsed.end(), false);
            improved = true;
            break;
        } else {
            // No improvement, restore the backup solution and mark this method as used
            solution = backupSolution;
            localSearchUsed[i] = true;
        }
      }
      
      // If all methods have been tried without improvement, exit the loop
      if (std::all_of(localSearchUsed.begin(), localSearchUsed.end(), [](bool v) { return v; })) {
        break;
      }
    }
  }

private:
  ProblemInstance &instance;
  Solution &solution;
  std::vector<bool> localSearchUsed;
};

#endif // RVNS_H
