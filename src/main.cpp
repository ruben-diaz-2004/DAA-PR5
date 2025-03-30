#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include "include/probleminstance.h"
#include "include/greedyroutingsolver.h"
#include "include/grasproutingsolver.h"

int main(int argc, char* argv[]) {
  // Check if input file is provided
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
    return 1;
  }

  try {
    ProblemInstance instance(argv[1]);

    instance.setSolver(std::make_unique<GreedyRoutingSolver>(instance));
    // instance.setSolver(std::make_unique<GraspRoutingSolver>(instance));
    instance.solve();
  
  
  } catch (const std::exception& e) {
      std::cerr << "Error parsing instance file: " << e.what() << std::endl;
  }

  return 0;
}