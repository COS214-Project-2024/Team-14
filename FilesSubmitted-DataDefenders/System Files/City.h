#pragma once
#include "CityComponent.h"
#include "District.h"
#include <vector>
#include <string>
#include <algorithm>

/**
 * @file City.h
 * @brief City management and organization
 */

/**
 * @class City
 * @brief Singleton class representing the entire city structure
 * @details Manages districts and overall city organization using composite pattern
 * 
 * @see District
 * @see Neighborhood
 * @see CityComponent
 */

class City : public CityComponent {
private:
    static City* instance;
    std::string name;
    std::vector<CityComponent*> districts;
    std::vector<CityComponent*> components;

    City(const std::string& cityName = "Default City") : name(cityName) {}

public:
    City(const City&) = delete;
    City& operator=(const City&) = delete;

    static City* getInstance() {
        if (instance == nullptr) {
            instance = new City();
        }
        return instance;
    }

    static void cleanup() {
        delete instance;
        instance = nullptr;
    }

    ~City() {
        for (auto* district : districts) {
            delete district;
        }
        districts.clear();
    }

    void add(CityComponent* component) override {
        districts.push_back(component);
    }

    void remove(CityComponent* component) override {
        auto it = std::find(districts.begin(), districts.end(), component);
        if (it != districts.end()) {
            districts.erase(it);
        }
    }

    std::string getName() const override {
        return name;
    }

    // New method to get all districts
    std::vector<CityComponent*> getComponents() const override {
        return districts;
    }

    // New method to find a specific district by name
    CityComponent* findComponent(const std::string& name) override {
        for (auto* district : districts) {
            if (district->getName() == name) {
                return district;
            }
        }
        return nullptr;
    }

    // Modified findOrCreateDistrict to use findComponent
    CityComponent* findOrCreateDistrict(const std::string& districtName) {
        // First try to find existing district
        CityComponent* existingDistrict = findComponent(districtName);
        if (existingDistrict) {
            return existingDistrict;
        }
        
        // If not found, create new district
        District* newDistrict = new District(districtName);
        add(newDistrict);
        return newDistrict;
    }

    void print(int indent = 0) const {
        std::string indentation(indent, ' ');
        std::cout << indentation << "City: " << name << "\n";
        
        for (auto* district : districts) {
            if (District* d = dynamic_cast<District*>(district)) {
                d->print(indent + 2);
            }
        }
    }
};

City* City::instance = nullptr;
