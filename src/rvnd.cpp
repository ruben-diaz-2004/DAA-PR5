#include "include/rvnd.h"


void RVND::RunVND()  {
  // Inicializar las búsquedas locales
  ReinsertIntra intra(instance, solution);
  ReinsertInter inter(instance, solution);
  SwapIntra swapIntra(instance, solution);
  SwapInter swapInter(instance, solution);
  TwoOpt twoOpt(instance, solution);

  std::vector<int> methods = {0, 1, 2, 3, 4}; // Índices de los métodos
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
      switch (i) {
        case 0:
          intra.runLocalSearch();
          localSearchUsed[0] = true;
          break;
        case 1:
          inter.runLocalSearch();
          localSearchUsed[1] = true;
          break;
        case 2:
          swapIntra.runLocalSearch();
          localSearchUsed[2] = true;
          break;
        case 3:
          swapInter.runLocalSearch();
          localSearchUsed[3] = true;
          break;
        case 4:
          twoOpt.runLocalSearch();
          localSearchUsed[4] = true;
          break;
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