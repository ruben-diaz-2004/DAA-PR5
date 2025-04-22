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

#include "include/rvnd.h"

void RVND::RunVND()  {
  // Inicializar las búsquedas locales
  ReinsertIntra intra(instance, solution);
  ReinsertInter inter(instance, solution);
  SwapIntra swapIntra(instance, solution);
  SwapInter swapInter(instance, solution);
  TwoOpt twoOpt(instance, solution);

  bool improved = true;
  while (improved) {
    improved = false;

    // Ejecutar los métodos de forma secuencial
    Solution backupSolution = solution;
    double currentCost = solution.getTotalTime();

    intra.runLocalSearch();
    if (solution.getTotalTime() < currentCost) {
      improved = true;
      continue;
    } else {
      solution = backupSolution;
    }

    inter.runLocalSearch();
    if (solution.getTotalTime() < currentCost) {
      improved = true;
      continue;
    } else {
      solution = backupSolution;
    }

    swapIntra.runLocalSearch();
    if (solution.getTotalTime() < currentCost) {
      improved = true;
      continue;
    } else {
      solution = backupSolution;
    }

    swapInter.runLocalSearch();
    if (solution.getTotalTime() < currentCost) {
      improved = true;
      continue;
    } else {
      solution = backupSolution;
    }

    twoOpt.runLocalSearch();
    if (solution.getTotalTime() < currentCost) {
      improved = true;
    } else {
      solution = backupSolution;
    }
  }
}