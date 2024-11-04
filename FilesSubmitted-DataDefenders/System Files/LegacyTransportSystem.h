#pragma once
#include <string>

/**
 * @brief Legacy transport system implementation
 * @details Provides basic functionality for managing legacy transport vehicles
 *          including capacity, fuel usage, and repair cost tracking
 */
class LegacyTransportSystem {
public:
    /**
     * @brief Default constructor
     * @details Initializes a legacy transport system with default values:
     *          - Capacity: 50
     *          - Fuel Usage: 20.0
     *          - Vehicle Class: "legacy"
     *          - Repair Costs: 2000.0
     *          - Service Status: 1
     */
    LegacyTransportSystem() {
        oldCapacity = 50;
        fuelUsage = 20.0f;
        vehicleClass = "legacy";
        repairCosts = 2000.0f;
        serviceStatus = 1;
    }
    
    /**
     * @brief Virtual destructor
     */
    virtual ~LegacyTransportSystem() {}

    /**
     * @brief Operates the legacy transport
     * @return std::string Description of the operation with vehicle class
     */
    virtual std::string operateOldTransport() {
        return "Operating Legacy Transport: " + std::string(vehicleClass);
    }
    
    /**
     * @brief Gets the transport capacity
     * @return int The capacity of the transport system
     */
    virtual int getOldCapacity() const {
        return oldCapacity;
    }
    
    /**
     * @brief Gets the fuel usage rate
     * @return float The fuel usage in units per operation
     */
    virtual float getOldFuelUsage() const {
        return fuelUsage;
    }
    
    /**
     * @brief Gets the vehicle classification
     * @return const char* The vehicle class identifier
     */
    virtual const char* getVehicleClass() const {
        return vehicleClass;
    }
    
    /**
     * @brief Gets the repair costs
     * @return float The repair costs in monetary units
     */
    virtual float getRepairCosts() const {
        return repairCosts;
    }
    
    /**
     * @brief Gets the service status
     * @return int The service status of the transport system
     */
    virtual int getServiceStatus() const {
        return serviceStatus;
    }

protected:
    int oldCapacity;
    float fuelUsage;  // liters per 100km
    const char* vehicleClass;
    float repairCosts;
    int serviceStatus;  // 1 for working, 0 for not working
};