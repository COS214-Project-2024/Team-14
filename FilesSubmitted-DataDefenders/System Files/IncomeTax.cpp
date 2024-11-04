//IncomeTax.cpp
#include "IncomeTax.h"
#include "CitizenPrototype.h"
double IncomeTax::calculateTax(double amount) {
    if (amount < 10000)
        return amount * 0.10;
    else if (amount < 20000)
        return amount * 0.11;
    else if (amount < 30000)
        return amount * 0.12;
    else if (amount < 40000)
        return amount * 0.14;
    else if (amount < 50000)
        return amount * 0.15;
    else if (amount < 60000)
        return amount * 0.16;
    else if (amount < 70000)
        return amount * 0.17;
    else if (amount < 80000)
        return amount * 0.18;
    else if (amount < 90000)
        return amount * 0.19;
    else if (amount < 100000)
        return amount * 0.20;
    else
        return amount * 0.25;
}
double IncomeTax::calculateTotalTax() {
    double totalTax = 0.0;
    for (CitizenPrototype* citizen : CitizenPrototype::citizens) {
        totalTax += calculateTax(citizen->getSalary());
    }
    return totalTax;
}