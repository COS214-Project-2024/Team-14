/**
 * @file PopulationGrowth.h
 * @brief Defines the PopulationGrowth observer class for monitoring city population changes
 */

#pragma once
#include "CityObserver.h"
#include "CitizenPrototype.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

/**
 * @class PopulationGrowth
 * @brief Observer class that monitors and analyzes population growth in the city
 * 
 * This class implements the Observer pattern to track population changes
 * and calculate growth projections based on various factors.
 */
class PopulationGrowth : public CityObserver {
private:
    std::string currentStats;    ///< Current population statistics
    double growthRate;          ///< Current growth rate
    int projectedPopulation;    ///< Projected future population
    double migrationFactor;     ///< Factor affecting population due to migration

public:
    /**
     * @brief Constructs a new PopulationGrowth observer
     * 
     * Initializes all growth metrics to zero.
     */
    PopulationGrowth() : growthRate(0.0), projectedPopulation(0), migrationFactor(0.0) {}

    /**
     * @brief Updates the population growth statistics
     * @param population Current city population
     * @param satisfaction Citizen satisfaction level (0-100)
     * @param economicGrowth Economic growth rate
     */
    void update(int population, double satisfaction, double economicGrowth) override {
        // Calculate population growth metrics
        migrationFactor = (satisfaction / 100.0) + economicGrowth;
        growthRate = 0.02 + (migrationFactor * 0.01); // Base growth rate + migration
        projectedPopulation = static_cast<int>(population * (1.0 + growthRate));

        std::stringstream ss;
        ss << "Population Growth Analysis:\n"
           << "Current Population: " << population << "\n"
           << "Natural Growth Rate: 2.0%\n"
           << "Migration Factor: " << (migrationFactor * 100) << "%\n"
           << "Overall Growth Rate: " << (growthRate * 100) << "%\n"
           << "Projected Population (1 year): " << projectedPopulation << "\n"
           << "Population Change: " << (projectedPopulation - population) << "\n"
           << "Total Citizens: " << CitizenPrototype::getCitizenCount();
        currentStats = ss.str();
    }

    /**
     * @brief Displays the current population growth statistics
     */
    void display() override {
        std::cout << "\n=== Population Growth Report ===\n"
                  << currentStats << "\n"
                  << "==============================\n";
    }
};