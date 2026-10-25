// Calculator.cpp — Implementation of the Calculator base class

#include "Calculator.hpp"

// [CONSTRUCTOR] uses member initializer list (preferred over assignment in body)
Calculator::Calculator(const std::string& name)
    : name_(name), totalCalculations_(0)
{
    std::cout << "[Session] " << name_ << " created.\n";
}

// [VIRTUAL DESTRUCTOR] called automatically in reverse construction order:
//   1. ~FibonacciCalculator() runs first (derived)
//   2. ~Calculator() runs second (this one — base)
Calculator::~Calculator() {
    std::cout << "[Session] " << name_ << " base resources released.\n";
}

// [ENCAPSULATION — getters] const means these won't modify the object
std::string Calculator::getName() const {
    return name_;
}

int Calculator::getTotalCalculations() const {
    return totalCalculations_;
}
