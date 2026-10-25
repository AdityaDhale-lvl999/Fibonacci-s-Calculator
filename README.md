# Fibonacci Calculator

This is a simple C++ project I made to learn Object-Oriented Programming concepts. It calculates Fibonacci numbers using a class hierarchy that shows how inheritance, polymorphism, and encapsulation actually work in practice.

## How to Build

You need a C++17 compiler (g++, clang++, or MSVC).

```bash
g++ -std=c++17 -o fib_calc Calculator.cpp FibonacciCalculator.cpp main.cpp
```

Then run it:
```bash
.\fib_calc.exe   # Windows
./fib_calc       # Linux/Mac
```

## How it Works

You enter a number `n` (between 0 and 92), and it gives you the nth Fibonacci number. It uses memoization so repeated lookups are instant. Type `q` to quit. It also keeps a running history of everything you calculated in that session.

## OOP Concepts Used

Here's what I learned and where each concept shows up in the code:

- **Inheritance** — `FibonacciCalculator` extends `Calculator` as a base class. Check `FibonacciCalculator.hpp`.
- **Polymorphism** — `main.cpp` stores a `FibonacciCalculator` inside a `Calculator*` pointer, and calling `run()` still runs the right version thanks to virtual functions.
- **Encapsulation** — The Fibonacci cache and history are `private`. You can only see the history through `displayHistory()`, and nothing outside the class can mess with the cache.
- **Virtual Destructor** — Without this, deleting through a base pointer would skip the derived class cleanup. Defined in `Calculator.hpp`.
- **RAII** — `std::unique_ptr` in `main.cpp` handles memory automatically. No raw `new`/`delete` anywhere.
- **Constructors / Destructors** — You can trace the full object lifecycle: creation → usage → destruction (in reverse order).

## File Structure

- `Calculator.hpp / .cpp` — Abstract base class (can't instantiate directly)
- `FibonacciCalculator.hpp / .cpp` — The actual calculator with all the logic
- `main.cpp` — Entry point, creates and runs the calculator

## Notes

- Max value is F(92) because that's the largest Fibonacci number a `long long` can hold
- No external libraries needed, just the C++ standard library
