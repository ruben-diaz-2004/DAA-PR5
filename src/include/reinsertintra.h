#ifndef SWAPREINSERT_H
#define SWAPREINSERT_H

#include "localsearch.h"
#include "probleminstance.h"
#include "solution.h"

class ReinsertIntra : public LocalSearch {
public:
  // Constructor
  ReinsertIntra(ProblemInstance& problemInstance, Solution& solution)
      : LocalSearch(problemInstance, solution) {}

  // Método para ejecutar la búsqueda local
  void runLocalSearch() override;
    
};

#endif // SWAPREINSERT_H