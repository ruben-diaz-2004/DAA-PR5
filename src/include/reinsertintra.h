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