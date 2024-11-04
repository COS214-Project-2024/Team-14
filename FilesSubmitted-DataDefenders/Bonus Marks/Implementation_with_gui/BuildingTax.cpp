//BuildingTax.cpp
#include "BuildingTax.h"
#include "Building.h"

double BuildingTax::calculateTax(double amount) {
    if (amount < 10000)
        return amount * 0.001;
    else if (amount < 20000)
        return amount * 0.002;
    else if (amount < 30000)
        return amount * 0.003;
    else if (amount < 40000)
        return amount * 0.004;
    else if (amount < 50000)
        return amount * 0.005;
    else if (amount < 60000)
        return amount * 0.006;
    else if (amount < 70000)
        return amount * 0.007;
    else if (amount < 80000)
        return amount * 0.008;
    else if (amount < 90000)
        return amount * 0.009;
    else if (amount < 100000)
        return amount * 0.10;
    else
        return amount * 0.11;
}

double BuildingTax::calculateTotalTax() {
    double totalTax = 0.0;
    std::vector<Building*> buildingsCopy = Building::buildings;
    for (Building* building : buildingsCopy) {
        if (building) {  // Check if pointer is valid
            totalTax += calculateTax(building->getCost());
        }
    }
    return totalTax;
}
