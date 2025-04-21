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
#ifndef MULTISTART_H
#define MULTISTART_H

#include "grasproutingsolver.h"
#include "solution.h"
#include "rvnd.h"
#include "probleminstance.h"
#include "transportroutesolver.h"


class MultiStart {
public:
  MultiStart(ProblemInstance& instance, int graspN, int iterations, Solution& solution)
      : instance(instance), graspN(graspN), iterations(iterations), solution(solution) {}
  void run();

private:
  ProblemInstance& instance;
  int graspN;
  int iterations;
  Solution& solution;
};


#endif // MULTISTART_H