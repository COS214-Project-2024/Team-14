//Building.cpp
#include "Building.h"
#include "BuildingTax.h"
#include "Operational.h"
#include "SecurityUpgrade.h"
#include "EnergyEfficiencyUpgrade.h"
#include "CapacityUpgrade.h"
#include <iostream>
#include <iomanip>

Building::Building(const std::string &name, double area, int capacity, double cost)
    : name(name),maxCapacity(capacity),floorArea(area), currentOccupancy(0), maintenanceNeeded(false), energyUsage(0.0), Cost(cost), state(new Operational())
{
    buildingTax = new BuildingTax();
    buildings.push_back(this);
    parentNeighborhood = nullptr;
}

double Building::calculateTax() const
{
    return buildingTax->calculateTax(Cost);
}

double Building::calculateTotalTax() const
{
    return buildingTax->calculateTotalTax();
}

Building::~Building() {    
    auto it = std::find(buildings.begin(), buildings.end(), this);
    if (it != buildings.end()) {
        buildings.erase(it);
    }
    
    delete buildingTax;
    buildingTax = nullptr;
    delete state;
    state = nullptr;
}

void Building::setState(BuildingState *newState)
{
    delete state; // Clean up old state
    state = newState;
}

std::string Building::getState() const
{
    return state->getState();
}

void Building::setCost(long double cost)
{
    Cost = cost;
}

void Building::upgradeSecurity()
{
    SecurityUpgrade securityUpgrade(this);
    securityUpgrade.applyUpgrade();
}

void Building::upgradeEnergyEfficiency()
{
    EnergyEfficiencyUpgrade energyUpgrade(this);
    energyUpgrade.applyUpgrade();
}

void Building::upgradeCapacity()
{
    CapacityUpgrade capacityUpgrade(this);
    capacityUpgrade.applyUpgrade();
}

void Building::incrementOccupancy()
{
    if (currentOccupancy < maxCapacity)
    {
        currentOccupancy++;
    }
}

void Building::print(int indent) const
{
    std::cout << "\n===" << name << " Details ===\n";
    std::string indentation(indent, ' ');
    std::cout << std::string(indent, ' ') << "===" << name << " Details ===\n"
              << std::string(indent, ' ') << "  Type: " << getBuildingType() << "\n"
              << std::string(indent, ' ') << "  Floor Area: " << getFloorArea() << " sq m\n"
              << std::string(indent, ' ') << "  Capacity: " << currentOccupancy << "/" 
              << getMaxCapacity() << "\n"
              << std::string(indent, ' ') << "  Cost: R" << std::fixed 
              << std::setprecision(2) << getCost() << "\n"
              << std::string(indent, ' ') << "  Security Level: " << getSecurityLevel() << "\n"
              << std::string(indent, ' ') << "  Energy Efficiency: " << getEnergyLevel() << "\n"
              << std::string(indent, ' ') << "  Capacity Level: " << getCapacityLevel() << "\n"
              << std::string(indent, ' ') << "  State: " << getState() << "\n";
}