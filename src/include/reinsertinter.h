// reinsertinter.h
#ifndef REINSERTINTER_H
#define REINSERTINTER_H

#include "localsearch.h"
#include "probleminstance.h"
#include "solution.h"

class ReinsertInter : public LocalSearch {
public:
  // Constructor
  ReinsertInter(ProblemInstance& problemInstance, Solution& solution)
      : LocalSearch(problemInstance, solution) {}

  // Method to execute the local search
  void runLocalSearch() override;
};

#endif // REINSERTINTER_H