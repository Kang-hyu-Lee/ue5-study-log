// C++ Functions -- Solutions

#include <iostream>
#include <cmath>

// 1. Square a number
int Square(int n) {
    return n * n;
}

// 2. Add two doubles
double Add(double a, double b) {
    return a + b;
}

// 3. Check if positive
bool IsPositive(int n) {
    return n > 0; // the comparison itself IS a bool -- no need for if/else here
}

// 4. Magnitude, reusing today's math formula
double Magnitude2D(double x, double y) {
    return std::sqrt(x * x + y * y);
}

// 5. Pitfall check -- pass by value
void AddFive(int n) {
    n = n + 5; // only modifies the LOCAL COPY of n
}

int main() {
    // 1.
    std::cout << "Square(4) = " << Square(4) << "\n";   // 16
    std::cout << "Square(-3) = " << Square(-3) << "\n"; // 9

    // 2.
    std::cout << "Add(2.5, 3.5) = " << Add(2.5, 3.5) << "\n"; // 6

    // 3.
    std::cout << "IsPositive(5) = " << IsPositive(5) << "\n";   // 1 (true)
    std::cout << "IsPositive(-5) = " << IsPositive(-5) << "\n"; // 0 (false)

    // 4.
    std::cout << "Magnitude2D(6, 8) = " << Magnitude2D(6, 8) << "\n"; // 10

    // 5. Pitfall check
    int x = 5;
    AddFive(x);
    std::cout << "x after AddFive(x) = " << x << "\n";
    // x is STILL 5. AddFive received a COPY of x into its parameter n.
    // Modifying n inside the function has zero effect on the caller's x.
    // Fixing this for real requires a reference (int&) or pointer (int*) parameter --
    // both coming later on your roadmap.

    return 0;
}
