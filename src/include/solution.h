

#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "collectionvehicle.h"
#include "task.h"
#include "probleminstance.h"

class Solution {
public:
  Solution() = default;
  Solution(const std::vector<CollectionVehicle>& collectionRoutes, const std::vector<Task>& tasks, const std::vector<TransportationVehicle>& transportationVehicles)
      : collectionRoutes_(collectionRoutes), tasks_(tasks), transportationVehicles_(transportationVehicles) {}
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
    // for (const auto& vehicle : transportationVehicles_) {
    //   totalTime += (480 - vehicle.getRemainingTime());
    // }
    return totalTime;
  }

  double getTransportationVehiclesTime() const {
    double totalTime = 0.0;
    for (const auto& vehicle : transportationVehicles_) {
      totalTime += (480 - vehicle.getRemainingTime());
    }
    return totalTime;
  }

  // Getters
  const std::vector<CollectionVehicle>& getCollectionRoutes() const { return collectionRoutes_; }
  const std::vector<TransportationVehicle>& getTransportationVehicles() const { return transportationVehicles_; }
  const std::vector<Task>& getTasks() const { return tasks_; }
  int getNumVehicles() const { return collectionRoutes_.size() + transportationVehicles_.size(); }
  int getNumCollectionVehicles() const { return collectionRoutes_.size(); }
  int getNumTransportationVehicles() const { return transportationVehicles_.size(); }
  // Setters
  void setCollectionRoutes(const std::vector<CollectionVehicle>& collectionRoutes) { collectionRoutes_ = collectionRoutes; }
  void setTransportationVehicles(const std::vector<TransportationVehicle>& vehicles) { transportationVehicles_ = vehicles; }
  void setTasks(const std::vector<Task>& tasks) { tasks_ = tasks; }
  // Add a collection route
  void addCollectionRoute(const CollectionVehicle& route) { collectionRoutes_.push_back(route); }
  // Add a task
  void addTask(const Task& task) { tasks_.push_back(task); }
  void clearTasks() { tasks_.clear(); }
  void buildTasks(const ProblemInstance& problem);

private:
  std::vector<CollectionVehicle> collectionRoutes_;
  std::vector<Task> tasks_;
  std::vector<TransportationVehicle> transportationVehicles_;
};

#endif // SOLUTION_H