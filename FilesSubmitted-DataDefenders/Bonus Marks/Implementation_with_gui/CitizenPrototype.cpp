#include "CitizenPrototype.h"
#include "IncomeTax.h"
#include "Building.h"

std::vector<CitizenPrototype*> CitizenPrototype::citizens;
int CitizenPrototype::citizenCount = 0;

CitizenPrototype::CitizenPrototype(int id, double salary)
    : id(id), salary(salary), satisfaction(0.0), building(nullptr), incomeTax(new IncomeTax()) 
{
    citizens.push_back(this);
    ++citizenCount;
}

CitizenPrototype::~CitizenPrototype() {
    auto it = std::find(citizens.begin(), citizens.end(), this);
    if (it != citizens.end()) {
        citizens.erase(it);
    }
    delete incomeTax;
    incomeTax = nullptr;
}

CitizenPrototype::CitizenPrototype(const CitizenPrototype& other)
    : id(other.id),
      salary(other.salary),
      satisfaction(other.satisfaction),
      building(other.building),
      incomeTax(other.incomeTax ? new IncomeTax(*other.incomeTax) : nullptr)
{
    citizens.push_back(this);
    ++citizenCount;
}

void CitizenPrototype::setBuilding(Building* b) {
    building = b;
    if (building) {
        building->incrementOccupancy();
    }
}

CitizenPrototype& CitizenPrototype::operator=(const CitizenPrototype& other) {
    if (this != &other) {
        id = other.id;
        salary = other.salary;
        satisfaction = other.satisfaction;
        building = other.building;
        
        delete incomeTax;
        incomeTax = other.incomeTax ? new IncomeTax(*other.incomeTax) : nullptr;
    }
    return *this;
}

double CitizenPrototype::calculateTotalTax() const {
    return incomeTax ? incomeTax->calculateTotalTax() : 0.0;
}

double CitizenPrototype::calculateTax() const {
    return incomeTax ? incomeTax->calculateTax(salary) : 0.0;
}

void CitizenPrototype::cleanup() {
    std::vector<CitizenPrototype*> temp;
    temp.swap(citizens);
    for (auto* citizen : temp) {
        delete citizen;
    }
}