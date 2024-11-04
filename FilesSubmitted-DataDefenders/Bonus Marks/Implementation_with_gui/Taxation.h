/**
 * @file TaxationPolicy.h
 * @brief Defines the basic taxation policy class for managing tax collection
 */

#ifndef TAXATION_H
#define TAXATION_H

/**
 * @class TaxationPolicy
 * @brief Manages tax collection and budget calculation
 */
class TaxationPolicy {
    private:
        double collectedTaxes; /**< Stores the amount of collected taxes */

    public:
        /**
         * @brief Sets the amount of collected taxes
         * @param collectedTaxes The amount of taxes collected
         */
        void setTaxes(double collectedTaxes) 
        {
            this->collectedTaxes = collectedTaxes;
        }

        /**
         * @brief Calculates the available budget based on collected taxes
         * @return double The calculated budget amount
         */
        double calculatedBudget() 
        {
            return this->collectedTaxes;
        }
};

#endif