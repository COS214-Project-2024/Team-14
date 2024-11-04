/**
 * @file CitizenSatisfaction.h
 * @brief Defines the CitizenSatisfaction class for monitoring citizen happiness
 */
#pragma once
#include "CityObserver.h"
#include "CitizenPrototype.h"
#include <string>
#include <sstream>
#include <iostream>

/**
 * @class CitizenSatisfaction
 * @brief A class that monitors and calculates citizen satisfaction metrics
 * @inherits CityObserver
 * 
 * Tracks overall citizen satisfaction based on various factors including
 * population density, economic growth, and base satisfaction levels.
 */
class CitizenSatisfaction : public CityObserver {
private:
    std::string currentStats;    ///< Current statistics in string format
    double overallSatisfaction;  ///< Combined satisfaction score
    double densityImpact;        ///< Impact of population density on satisfaction

public:
    /**
     * @brief Constructs a CitizenSatisfaction object
     * 
     * Initializes satisfaction metrics to zero
     */
    CitizenSatisfaction() : overallSatisfaction(0.0), densityImpact(0.0) {}

    /**
     * @brief Updates satisfaction metrics based on new city data
     * @param population Current city population
     * @param satisfaction Base satisfaction level
     * @param economicGrowth Current economic growth rate
     * 
     * Calculates new satisfaction metrics and updates all citizens
     */
    void update(int population, double satisfaction, double economicGrowth) override {
        densityImpact = (population > 1000000) ? -0.1 : 0.1;
        overallSatisfaction = satisfaction + (economicGrowth * 0.5) + densityImpact;

        auto& citizens = CitizenPrototype::citizens;
        for (auto citizen : citizens) {
            citizen->updateSatisfaction(overallSatisfaction);
        }

        std::stringstream ss;
        ss << "Citizen Satisfaction Analysis:\n"
           << "Base Satisfaction: " << satisfaction << "%\n"
           << "Economic Impact: +" << (economicGrowth * 0.5) << "%\n"
           << "Population Density Impact: " << (densityImpact * 100) << "%\n"
           << "Overall Satisfaction Score: " << overallSatisfaction << "%\n"
           << "Total Citizens: " << population;
        currentStats = ss.str();
    }

    /**
     * @brief Displays the current satisfaction report
     * 
     * Outputs formatted satisfaction statistics to standard output
     */
    void display() override {
        std::cout << "\n=== Citizen Satisfaction Report ===\n"
                  << currentStats << "\n"
                  << "=================================\n";
    }
};
