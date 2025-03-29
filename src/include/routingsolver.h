// RoutingSolver (Interface/Abstract Base Class)
#ifndef ROUTING_SOLVER_H
#define ROUTING_SOLVER_H

#include <vector>
#include "collectionvehicle.h"
#include "transportationvehicle.h"

class ProblemInstance;

class RoutingSolver {
protected:
    // Referencia al problema
    const ProblemInstance& problem;
    
    // Métodos auxiliares comunes
    TransferStation findClosestTransferStation(const Location& currentLocation) const;
    double calculateTravelTime(const Location& from, const Location& to) const;
    bool canVisitZone(const CollectionVehicle& vehicle, const Zone& zone, double remainingTime) const;

public:
    // Constructor simplificado
    explicit RoutingSolver(const ProblemInstance& problemInstance)
        : problem(problemInstance) {}
    

    // Métodos puros virtuales que deben implementar las clases derivadas
    virtual std::vector<CollectionVehicle> constructCollectionRoutes() = 0;

    // Getters y métodos adicionales
    // int getNumberOfZonesVisited() const;
};

#endif // ROUTING_SOLVER_H