#ifndef FIBONACCI_CALCULATOR_HPP
#define FIBONACCI_CALCULATOR_HPP

// FibonacciCalculator.hpp — Derived class that computes Fibonacci numbers

#include "Calculator.hpp"
#include <vector>
#include <unordered_map>
#include <utility>   // std::pair

// [INHERITANCE] FibonacciCalculator IS-A Calculator
// 'public' keeps Calculator's public members public in the derived class
class FibonacciCalculator : public Calculator {

// [ENCAPSULATION] private: strictest access — even child classes can't touch these
private:
    std::vector<std::pair<int, long long>> history_;    // session history
    std::unordered_map<int, long long> cache_;          // memoization cache

    // [ENCAPSULATION — private helpers] implementation details hidden from outside
    long long computeFib(int n);
    void displayHistory() const;

public:
    // [CONSTRUCTOR] seeds the memoization cache with base cases
    FibonacciCalculator();

    // [DESTRUCTOR — override] confirms we override the virtual destructor
    ~FibonacciCalculator() override;

    // [POLYMORPHISM — override] these override the pure virtual methods from Calculator
    // At runtime, calling calc->displayInfo() through a Calculator* uses the vtable
    // to dispatch to THESE implementations
    void displayInfo() const override;
    void run() override;
};

#endif // FIBONACCI_CALCULATOR_HPP
