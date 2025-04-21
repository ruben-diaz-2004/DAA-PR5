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