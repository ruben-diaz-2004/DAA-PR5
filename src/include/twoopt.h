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
#ifndef TWO_OPT_H
#define TWO_OPT_H

#include "localsearch.h"
#include "probleminstance.h"
#include "solution.h"

class TwoOpt : public LocalSearch {
public:
  // Constructor
  TwoOpt(ProblemInstance& problemInstance, Solution& solution)
      : LocalSearch(problemInstance, solution) {}

  // Method to execute the local search
  void runLocalSearch() override;
};

#endif // TWO_OPT_H