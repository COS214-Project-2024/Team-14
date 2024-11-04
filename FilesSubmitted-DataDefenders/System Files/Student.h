/**
 * @file Student.h
 * @brief Student citizen implementation
 */

#pragma once
#include "CitizenPrototype.h"

/**
 * @class Student
 * @brief Represents student citizens in the city
 * @details Implements student-specific behaviors and attributes
 * 
 * @see CitizenPrototype
 */
class Student : public CitizenPrototype {
private:
    /**
     * @brief Flag indicating part-time job status
     */
    bool hasPartTimeJob;

public:
    /**
     * @brief Constructor
     * @param id Citizen identification number
     * @param salary Initial salary
     */
    Student(int id, double salary) : CitizenPrototype(id, salary), hasPartTimeJob(false) {}

    /**
     * @brief Destructor
     */
    ~Student() override = default;
    
    /**
     * @brief Copy constructor
     * @param other Student to copy
     */
    Student(const Student& other) : CitizenPrototype(other), hasPartTimeJob(other.hasPartTimeJob) {}
    
    /**
     * @brief Clone the student
     * @return Student* Copy of the student
     */
    CitizenPrototype* clone() const override {
        return new Student(*this);
    }
    
    /**
     * @brief Get the role of the student
     * @return std::string Role of the student
     */
    const std::string getRole() const override {
        return "Student";
    }
    
    /**
     * @brief Perform the student's task
     */
    void performTask() override {
        std::cout << "Student #" << getID() << " is studying";
        if (hasPartTimeJob) {
            std::cout << " and working part-time";
        }
        if (getBuilding()) {
            std::cout << " in the ";
            getBuilding()->print();
        }
        std::cout << "\n";
    }
    
    /**
     * @brief Set the student's salary and part-time job status
     * @param newSalary New salary amount
     */
    void setSalary(double newSalary) override {
        if (newSalary > 0) {
            std::cout << "Student #" << getID() << " is primarily studying but has taken a part-time job with salary $" 
                     << newSalary << std::endl;
            salary = newSalary;
            hasPartTimeJob = true;
        } else {
            std::cout << "Student #" << getID() << " is focusing fully on studies without a part-time job" << std::endl;
            salary = 0;
            hasPartTimeJob = false;
        }
    }
};