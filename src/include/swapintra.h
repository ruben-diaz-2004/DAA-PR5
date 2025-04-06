
#ifndef SWAPINTRA_H
#define SWAPINTRA_H

#include "localsearch.h"
#include "probleminstance.h"
#include "solution.h"

class SwapIntra : public LocalSearch {
public:
    // Constructor
    SwapIntra(ProblemInstance& problemInstance, Solution& solution)
        : LocalSearch(problemInstance, solution) {}

    // Método para ejecutar la búsqueda local
    void runLocalSearch() override;


};

#endif // SWAPINTRA_H