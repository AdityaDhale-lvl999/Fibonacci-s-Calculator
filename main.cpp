// main.cpp — Entry point for the Fibonacci Calculator
//
// Compile (C++17):
//   g++ -std=c++17 -o fib_calc Calculator.cpp FibonacciCalculator.cpp main.cpp
//
// Run:
//   ./fib_calc (Linux/Mac)   or   .\fib_calc.exe (Windows)

#include "Calculator.hpp"
#include "FibonacciCalculator.hpp"

#include <iostream>
#include <memory>   // std::unique_ptr, std::make_unique

int main() {
    std::cout << "\n";

    // [POLYMORPHISM + RAII]
    // Base pointer (Calculator*) holds a derived object (FibonacciCalculator).
    // unique_ptr auto-deletes when it goes out of scope — no manual delete needed.
    std::unique_ptr<Calculator> calc = std::make_unique<FibonacciCalculator>();

    // [POLYMORPHISM — dynamic dispatch]
    // calc is a Calculator*, but at runtime the vtable routes to
    // FibonacciCalculator::run(), not the base (which is pure virtual anyway).
    calc->run();

    // [DESTRUCTOR CHAIN] — when calc goes out of scope:
    //   1. ~FibonacciCalculator() runs (derived)
    //   2. ~Calculator() runs (base)
    // This works because Calculator has a VIRTUAL destructor.

    std::cout << "\n[main] Program terminated normally.\n";
    return 0;
}
