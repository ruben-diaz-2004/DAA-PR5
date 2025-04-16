#ifndef RVNS_H
#define RVNS_H

#include "solution.h"
#include "probleminstance.h"
#include "reinsertinter.h"
#include "reinsertintra.h"
#include "swapinter.h"
#include "swapintra.h"
#include "twoopt.h"
#include <algorithm> // Para std::shuffle
#include <random>    // Para std::mt19937, std::random_device

class RVND {
public:
  RVND(ProblemInstance &instance, Solution &solution) 
      : instance(instance), solution(solution) {
    localSearchUsed.resize(4, false); // Initialize with 4 local search methods
  }

  void RunVND();

private:
  ProblemInstance &instance;
  Solution &solution;
  std::vector<bool> localSearchUsed;
};

#endif // RVNS_H
