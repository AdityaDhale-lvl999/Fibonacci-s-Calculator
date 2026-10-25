#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

// Calculator.hpp — Abstract base class for all calculator types

#include <string>
#include <iostream>

class Calculator {

// [ENCAPSULATION] protected: derived classes can access, outside code cannot
protected:
    std::string name_;
    int totalCalculations_;

public:
    // [CONSTRUCTOR] explicit prevents implicit string-to-Calculator conversions
    explicit Calculator(const std::string& name);

    // [VIRTUAL DESTRUCTOR] ensures correct cleanup when deleting via base pointer
    //   Calculator* ptr = new FibonacciCalculator();
    //   delete ptr;  // without virtual, ~FibonacciCalculator() would be SKIPPED
    virtual ~Calculator();

    // [POLYMORPHISM — pure virtual] makes Calculator abstract (cannot instantiate)
    // Derived classes MUST override these
    virtual void displayInfo() const = 0;
    virtual void run() = 0;

    // [ENCAPSULATION — getters] read-only access to internal state
    std::string getName() const;
    int getTotalCalculations() const;
};

#endif // CALCULATOR_HPP
