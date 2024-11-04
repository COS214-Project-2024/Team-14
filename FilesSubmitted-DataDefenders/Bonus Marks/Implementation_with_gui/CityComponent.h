/**
 * @file CityComponent.h
 * @brief Defines the base CityComponent class for city structure elements
 */
#pragma once
#include <string>
#include <vector>

/**
 * @class CityComponent
 * @brief Abstract base class for city components in a composite pattern
 * 
 * Provides interface for managing hierarchical city structures with
 * population and area attributes.
 */
class CityComponent {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~CityComponent() = default;

    /**
     * @brief Adds a child component
     * @param component Pointer to component to add
     */
    virtual void add(CityComponent *component) = 0;

    /**
     * @brief Removes a child component
     * @param component Pointer to component to remove
     */
    virtual void remove(CityComponent *component) = 0;

    /**
     * @brief Gets the component name
     * @return String containing the component name
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Gets the component population
     * @return Double representing the population
     */
    virtual double getPopulation() const { return population; }

    /**
     * @brief Gets the component area
     * @return Double representing the area
     */
    virtual double getArea() const { return area; }

    /**
     * @brief Prints the component details
     * @param indent Indentation level for hierarchical display
     */
    virtual void print(int indent = 0) const = 0;

    /**
     * @brief Gets child components
     * @return Vector of pointers to child components
     */
    virtual std::vector<CityComponent *> getComponents() const {
        return std::vector<CityComponent *>();
    }

    /**
     * @brief Finds a component by name
     * @param name Name of component to find
     * @return Pointer to found component or nullptr
     */
    virtual CityComponent *findComponent(const std::string &name) {
        return nullptr;
    }

    /**
     * @brief Gets the building type
     * @return String containing the building type
     */
    virtual std::string getBuildingType() const {
        return "";
    }

protected:
    double population = 0.0;  ///< Component population
    double area = 0.0;        ///< Component area
};