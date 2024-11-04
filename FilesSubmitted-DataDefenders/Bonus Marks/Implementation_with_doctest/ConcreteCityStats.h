/**
 * @file ConcreteCityStats.h
 * @brief Implements concrete statistics tracking for city metrics
 */

#pragma once
#include "CityStats.h"
#include <iostream>
#include "CitizenPrototype.h"

/**
 * @class ConcreteCityStats
 * @brief Concrete implementation of city statistics tracking
 * @details Manages and updates various city metrics including satisfaction and economic growth
 */
class ConcreteCityStats : public CityStats
{
private:
    double satisfaction;    ///< Current citizen satisfaction level
    double economicGrowth; ///< Current economic growth rate

public:
    /**
     * @brief Default constructor
     * @details Initializes satisfaction and economic growth to 0.0
     */
    ConcreteCityStats() : satisfaction(0.0), economicGrowth(0.0) {}

    /**
     * @brief Sets and updates city statistics
     * @param sat Initial satisfaction value
     * @param growth Economic growth value
     * @details Calculates actual satisfaction based on citizen data if available
     */
    void setStats(double sat, double growth)
    {
        int currentPopulation = CitizenPrototype::getCitizenCount();
        // For debugging
        std::cout << "Debug - Current citizen count: " << currentPopulation << "\n";
        std::cout << "Debug - Citizens vector size: " << CitizenPrototype::citizens.size() << "\n";
        
        double totalSatisfaction = 0.0;
        auto& citizens = CitizenPrototype::citizens;
        if (!citizens.empty()) {
            for (auto citizen : citizens) {
                totalSatisfaction += citizen->getSatisfaction();
            }
            satisfaction = totalSatisfaction / citizens.size();
        } else {
            satisfaction = sat;
        }
        
        economicGrowth = growth;

        std::cout << "\nUpdating city stats with:"
                  << "\nPopulation: " << currentPopulation
                  << "\nSatisfaction: " << satisfaction << "%"
                  << "\nEconomic Growth: " << (economicGrowth * 100) << "%\n";

        notify(currentPopulation, satisfaction, economicGrowth);
    }

    /**
     * @brief Gets the current population
     * @return Current population count, minimum 0
     */
    int getPopulation() const { 
        if (CitizenPrototype::getCitizenCount() < 0) {
            return 0;
        }
        
        return CitizenPrototype::getCitizenCount();    
    }

    /**
     * @brief Gets the current satisfaction level
     * @return Current satisfaction percentage
     */
    double getSatisfaction() const { return satisfaction; }

    /**
     * @brief Gets the current economic growth rate
     * @return Current economic growth rate
     */
    double getEconomicGrowth() const { return economicGrowth; }
};