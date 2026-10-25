// FibonacciCalculator.cpp — Implementation of FibonacciCalculator

#include "FibonacciCalculator.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>  // std::max
#include <limits>
#include <cmath>
#include <iomanip>    // std::setprecision

using std::cout;
using std::cin;
using std::endl;
using std::string;



// [CONSTRUCTOR] — Object creation / lifecycle
// Construction order:
//   1. Base class constructor (Calculator) runs FIRST
//   2. Constructor body runs — we seed the cache here
FibonacciCalculator::FibonacciCalculator()
    : Calculator("Fibonacci Calculator")   // base class constructor call
{
    cache_[0] = 0;   // F(0) = 0  — base case
    cache_[1] = 1;   // F(1) = 1  — base case
    cout << "[Init] Cache seeded with F(0)=0 and F(1)=1.\n\n";
}



// [DESTRUCTOR] — Object cleanup / lifecycle
// Destruction order (reverse of construction):
//   1. ~FibonacciCalculator() runs FIRST (this)
//   2. ~Calculator() runs SECOND (base)
//   3. Members (history_, cache_) are auto-destroyed (RAII)
FibonacciCalculator::~FibonacciCalculator() {
    cout << "\n[Destructor] ~FibonacciCalculator() called.\n";
    cout << "[Destructor] Session: " << totalCalculations_ << " calculation(s).\n";

    if (!history_.empty()) {
        // Explicit clear just to make cleanup visible — RAII handles it anyway
        history_.clear();
        cache_.clear();
        cout << "[Destructor] History and cache cleared.\n";
    }
}



// [POLYMORPHISM — override] displayInfo()
// Overrides Calculator::displayInfo(). If you had multiple calculator
// types, each would provide its own version. Calling calc->displayInfo()
// through a Calculator* dispatches to the correct one at runtime.
void FibonacciCalculator::displayInfo() const {
    cout << "\n=== FIBONACCI CALCULATOR ===\n\n";

    cout << "  What is the Fibonacci Sequence?\n";
    cout << "  A series where each number is the sum of the two before it.\n\n";

    cout << "  Recurrence:  F(n) = F(n-1) + F(n-2)\n";
    cout << "  Base cases:  F(0) = 0,  F(1) = 1\n\n";

    cout << "  First terms: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...\n\n";

    cout << "  Golden Ratio (phi) = (1 + sqrt(5)) / 2 = "
         << std::fixed << std::setprecision(10)
         << ((1.0 + std::sqrt(5.0)) / 2.0) << "\n";
    cout << "  As n grows, F(n+1)/F(n) converges to phi.\n\n";
}


// [POLYMORPHISM — override] run() — main input loop
void FibonacciCalculator::run() {
    displayInfo();

    cout << "  Ready! Enter n (0-92) to compute F(n), or 'q' to quit.\n\n";

    while (true) {
        cout << "  n = ";

        string input;
        if (!std::getline(cin, input)) {
            cout << "\n  [EOF] Input closed. Exiting.\n";
            break;
        }

        // Trim whitespace
        size_t start = input.find_first_not_of(" \t\r\n");
        size_t end   = input.find_last_not_of(" \t\r\n");
        if (start == string::npos) {
            cout << "  [!] Empty input. Enter a number (0-92).\n\n";
            continue;
        }
        input = input.substr(start, end - start + 1);

        // Quit command
        if (input == "q" || input == "Q" || input == "quit" || input == "exit") {
            cout << "\n  Goodbye! Total calculations: " << totalCalculations_ << "\n";
            break;
        }

        // Parse input
        int n;
        try {
            size_t pos;
            long long parsed = std::stoll(input, &pos);

            if (pos != input.length()) {
                cout << "  [!] '" << input << "' is not a whole number.\n\n";
                continue;
            }
            if (parsed < 0) {
                cout << "  [!] Negative numbers not valid. F(n) needs n >= 0.\n\n";
                continue;
            }
            if (parsed > 92) {
                cout << "  [!] F(" << parsed << ") overflows 64-bit. Max n = 92.\n\n";
                continue;
            }
            n = static_cast<int>(parsed);

        } catch (const std::invalid_argument&) {
            cout << "  [!] '" << input << "' is not a number.\n\n";
            continue;
        } catch (const std::out_of_range&) {
            cout << "  [!] Number too large. Enter 0-92.\n\n";
            continue;
        }

        // Compute
        long long result = computeFib(n);

        // [ENCAPSULATION] history_ is private — modified only inside the class
        history_.push_back({n, result});
        totalCalculations_++;   // inherited protected member from Calculator

        // Display result
        cout << "\n  >>> F(" << n << ") = " << result << "\n\n";

        // Show session history
        displayHistory();
        cout << "\n";
    }
}


// [ENCAPSULATION — private method] computeFib()
// Recursive Fibonacci with memoization.
// Without memoization: O(2^n) — exponentially slow
// With memoization:    O(n)   — each value computed once
//
// cache_ is private, so this optimization is hidden from outside.
long long FibonacciCalculator::computeFib(int n) {
    auto it = cache_.find(n);
    if (it != cache_.end()) {
        return it->second;   // cache hit
    }

    // Cache miss — compute and store
    long long value = computeFib(n - 1) + computeFib(n - 2);
    cache_[n] = value;
    return value;
}


// [ENCAPSULATION — private method] displayHistory()
// history_ is private — this is the only way to see its contents.
void FibonacciCalculator::displayHistory() const {
    cout << "  Session History (" << history_.size() << " calculation"
         << (history_.size() != 1 ? "s" : "") << "):\n";

    for (int i = 0; i < (int)history_.size(); i++) {
        cout << "    " << (i + 1) << ". F("
             << history_[i].first << ") = "
             << history_[i].second << "\n";
    }
}
