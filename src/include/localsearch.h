
#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "probleminstance.h"
#include "solution.h"
#include "collectionvehicle.h"

class LocalSearch {
public:
    // Constructor
    LocalSearch(ProblemInstance& problemInstance, Solution& solution)
        : problem(problemInstance), solution(solution) {}

    // Método para ejecutar la búsqueda local
     virtual void runLocalSearch() = 0;

protected:
    // Referencia al problema
    ProblemInstance& problem;
    Solution& solution;

    // Métodos auxiliares comunes
    TransferStation findClosestTransferStation(const Location& currentLocation) const;
    Zone findClosestZone(const Location& currentLocation, std::vector<Zone> unassignedZones) const;
    Zone findNClosestZone(const Location& currentLocation, std::vector<Zone> unassignedZones, int n) const;
    double calculateTravelTime(const Location& from, const Location& to) const;
    int canVisitZone(const CollectionVehicle& vehicle, const Zone& zone, double remainingTime) const;
};

#endif // LOCALSEARCH_H