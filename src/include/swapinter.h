// swapinter.h
#ifndef SWAPINTER_H
#define SWAPINTER_H

#include "localsearch.h"
#include "probleminstance.h"
#include "solution.h"

class SwapInter : public LocalSearch {
public:
  // Constructor
  SwapInter(ProblemInstance& problemInstance, Solution& solution)
      : LocalSearch(problemInstance, solution) {}

  // Method to execute the local search
  void runLocalSearch() override;
};

#endif // SWAPINTER_H