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