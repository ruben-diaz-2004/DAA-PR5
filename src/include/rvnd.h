#ifndef RVNS_H
#define RVNS_H

#include "solution.h"
#include "probleminstance.h"
#include "reinsertinter.h"
#include "reinsertintra.h"
#include "swapinter.h"
#include "swapintra.h"
#include <algorithm> // Para std::shuffle
#include <random>    // Para std::mt19937, std::random_device

class RVND {
public:
  RVND(ProblemInstance &instance, Solution &solution) 
      : instance(instance), solution(solution) {
    localSearchUsed.resize(4, false); // Initialize with 4 local search methods
  }


  
  void RunVND() {
    // Inicializar las búsquedas locales
    SwapIntra swapIntra(instance, solution);
    SwapInter swapInter(instance, solution);
  
    std::vector<int> methods = {0, 1}; // Índices de los métodos (solo swap)
    std::random_device rd;
    std::mt19937 g(rd());
  
    bool improved = true;
    while (improved) {
      improved = false;
      std::fill(localSearchUsed.begin(), localSearchUsed.end(), false);
      std::shuffle(methods.begin(), methods.end(), g); // Baraja los métodos
  
      for (int i : methods) {
        // Haz una copia de seguridad de la solución actual
        Solution backupSolution = solution;
        double currentCost = solution.getTotalTime();
  
        bool foundImprovement = false;
        if (i == 0) {
          swapIntra.runLocalSearch();
        } else if (i == 1) {
          swapInter.runLocalSearch();
        }
  
        foundImprovement = (solution.getTotalTime() < currentCost);
  
        if (foundImprovement) {
          improved = true;
          break; // Reinicia con todos los métodos
        } else {
          solution = backupSolution;
        }
      }
    }
  }
  // void RunVND() {
  //   // Inicializar las búsquedas locales
  //   ReinsertIntra intra(instance, solution);
  //   ReinsertInter inter(instance, solution);
  //   SwapIntra swapIntra(instance, solution);
  //   SwapInter swapInter(instance, solution);
  
  //   std::vector<int> methods = {0, 1, 2, 3}; // Índices de los métodos
  //   std::random_device rd;
  //   std::mt19937 g(rd());
  
  //   bool improved = true;
  //   while (improved) {
  //     improved = false;
  //     std::fill(localSearchUsed.begin(), localSearchUsed.end(), false);
  //     std::shuffle(methods.begin(), methods.end(), g); // Baraja los métodos
  
  //     for (int i : methods) {
  //       // Haz una copia de seguridad de la solución actual
  //       Solution backupSolution = solution;
  //       double currentCost = solution.getTotalTime();
  
  //       bool foundImprovement = false;
  //       if (i == 0) {
  //         intra.runLocalSearch();
  //       } else if (i == 1) {
  //         inter.runLocalSearch();
  //       } else if (i == 2) {
  //         swapIntra.runLocalSearch();
  //       } else if (i == 3) {
  //         swapInter.runLocalSearch();
  //       }
  
  //       foundImprovement = (solution.getTotalTime() < currentCost);
  
  //       if (foundImprovement) {
  //         improved = true;
  //         break; // Reinicia con todos los métodos
  //       } else {
  //         solution = backupSolution;
  //       }
  //     }
  //   }
  // }

private:
  ProblemInstance &instance;
  Solution &solution;
  std::vector<bool> localSearchUsed;
};

#endif // RVNS_H
