

#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "collectionvehicle.h"
#include "task.h"




class Solution {
  public:
  Solution() = default;
  Solution(const std::vector<CollectionVehicle>& collectionRoutes, const std::vector<Task>& tasks)
      : collectionRoutes_(collectionRoutes), tasks_(tasks) {}
  Solution(const Solution& other) = default;

  Solution& operator=(const Solution& other) = default;
  Solution(Solution&& other) = default;
  Solution& operator=(Solution&& other) = default;
  ~Solution() = default;

  // Calculate the total time used by all vehicles in the solution
  double getTotalTime() const {
    double totalTime = 0.0;
    for (const auto& vehicle : collectionRoutes_) {
      totalTime += (480 - vehicle.getRemainingTime());
    }
    return totalTime;
  }

  // Getters
  const std::vector<CollectionVehicle>& getCollectionRoutes() const { return collectionRoutes_; }
  const std::vector<Task>& getTasks() const { return tasks_; }
  // Setters
  void setCollectionRoutes(const std::vector<CollectionVehicle>& collectionRoutes) { collectionRoutes_ = collectionRoutes; }
  void setTasks(const std::vector<Task>& tasks) { tasks_ = tasks; }
  // Add a collection route
  void addCollectionRoute(const CollectionVehicle& route) { collectionRoutes_.push_back(route); }
  // Add a task
  void addTask(const Task& task) { tasks_.push_back(task); }

  private:
  std::vector<CollectionVehicle> collectionRoutes_;
  std::vector<Task> tasks_;
};

#endif // SOLUTION_H