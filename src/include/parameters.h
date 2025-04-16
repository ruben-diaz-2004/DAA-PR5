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
  int algorithm = 3;     // 0: no algorithm selected, 1: greedy, 2: grasp
  int graspN = 3;        // Default value for graspN (candidatos)
  int iterations = 1000;  // Default number of GRASP iterations
};

parameters parse_args(int argc, char* argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);
  parameters options;
  
  // Skip the first argument (input file)
  for (auto it = args.begin() + 1, end = args.end(); it != end; ++it) {
    if (*it == "-greedy") {
      options.algorithm = 1;
    } else if (*it == "-grasp") {
      options.algorithm = 2;
      if (it + 1 != end) {
        options.graspN = std::stoi(*++it);
      }
      // if (it + 1 != end && isdigit((*++it)[0])) {
      //   options.iterations = std::stoi(*it);
      // }
    } else {
      std::cerr << "Error: invalid argument " << *it << std::endl;
      std::cerr << "Usage: " << argv[0] << " <input_file> [-greedy | -grasp <n>]" << std::endl;
    }
  }
  
  return options;
}

  
#endif // PARAMETERS_H