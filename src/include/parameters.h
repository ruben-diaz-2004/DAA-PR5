/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 19/02/2024
  * @brief Juego de la vida
  */
 
#ifndef PARAMETERS_H
#define PARAMETERS_H 
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


struct parameters {
  int algorithm;
  int graspN = 1;
};

parameters parse_args(int argc, char* argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);
  parameters options;
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    if (*it == "-greedy") {
      options.algorithm = 1;
    } else if (*it == "-grasp") {
      options.algorithm = 2;
      options.graspN = std::stoi(*++it);
    } else {
      std::cerr << "Error: invalid argument " << *it << std::endl;
    }
  }
  return options;
}

  
#endif // PARAMETERS_H