#pragma once
#include <string>

/**
 * @brief Class representing a modern transportation system
 * 
 * This class implements basic functionality for modern transport vehicles
 * including passenger capacity, fuel efficiency, and maintenance tracking.
 */
class ModernTransport {
public:
    /**
     * @brief Default constructor
     * 
     * Initializes a ModernTransport object with default values:
     * - Passenger capacity: 100
     * - Fuel efficiency: 15.0
     * - Transport type: "modern"
     * - Maintenance cost: 1000.0
     * - Operational status: true
     */
    ModernTransport() {
        passengerCapacity = 100;
        fuelEfficiency = 15.0;
        transportType = "modern";
        maintenanceCost = 1000.0;
        operational = true;
    }
    
    /**
     * @brief Virtual destructor
     */
    virtual ~ModernTransport() {}
    
    /**
     * @brief Performs the main operation of the transport system
     * @return std::string Operation status message
     */
    virtual std::string operationModernTransport() {
        return "Operating Modern Transport System: " + transportType;
    }
    
    /**
     * @brief Gets the maximum passenger capacity
     * @return int The maximum number of passengers
     */
    virtual int getPassengerCapacity() const {
        return passengerCapacity;
    }
    
    /**
     * @brief Gets the fuel efficiency rating
     * @return double The fuel efficiency in miles per gallon
     */
    virtual double getFuelEfficiency() const {
        return fuelEfficiency;
    }
    
    /**
     * @brief Gets the transport type identifier
     * @return std::string The transport type
     */
    virtual std::string getTransportType() const {
        return transportType;
    }
    
    /**
     * @brief Gets the maintenance cost
     * @return double The maintenance cost in currency units
     */
    virtual double getMaintenanceCost() const {
        return maintenanceCost;
    }
    
    /**
     * @brief Checks if the transport system is operational
     * @return bool Operational status
     */
    virtual bool isOperational() const {
        return operational;
    }

protected:
    int passengerCapacity;
    double fuelEfficiency;  // km per liter
    std::string transportType;
    double maintenanceCost;
    bool operational;
};