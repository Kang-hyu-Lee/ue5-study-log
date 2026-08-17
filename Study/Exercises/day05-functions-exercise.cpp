// C++ Functions -- Exercises
// Type your attempts below each problem. Compile with g++ to test: g++ functions-exercises.cpp -o test && ./test
#include <iostream>
#include <cmath>

// 1. Write a function `int Square(int n)` that returns n squared.
//    Call it from main() with a few test values and print the results.
//    hint: printing needs std::cout << -- see Day 3 concepts file if you need a refresher,
//    or look up "std::cout" on cppreference.com

int Square(int n) {
    return (n*n); //return n * n
}

// 2. Write a function `double Add(double a, double b)` that returns the sum.
//    Call it with 2.5 and 3.5.

double Add(double a, double b){
    return (a + b); //return a + b
}

// 3. Write a function `bool IsPositive(int n)` that returns true if n > 0, false otherwise.
//    hint: bool return type -- see Day 3 conditionals/boolean logic concepts file.

bool IsPositive(int n){
//    if (n > 0){
//       return (true);
//    } else {
//        return (false);
//    }
    return n > 0; // > already outputs a bool 
}

// 4. Write a function `double Magnitude2D(double x, double y)` -- reuse today's math block formula.
//    Test it with x=6, y=8 (should return 10 -- recognize the pattern? another Pythagorean triple).

double Magnitude2D(double x, double y){
    return (std::sqrt(x * x + y * y));
}

// 5. PITFALL CHECK: write a function `void AddFive(int n)` that sets n = n + 5 inside the
//    function body, but does NOT return anything.
//    Call it in main() with a variable, then print that variable's value afterward.
//    Predict the output BEFORE running it. Were you right? Why?

void AddFive(int n) {
    n = n+5;
    // it will print whatever n was because this doesn't return anything meaning the value will stay the same
}

int main() {
    double d = Add(2.5, 3.5);
    double mag = Magnitude2D(6, 8);
    int n = 5;
    AddFive(n);
    std::cout << "Square of 2: " << Square(2) << "\n";
    std::cout << "Square of -2: " << Square(-2) << "\n";
    std::cout << "-5 is positive: " << IsPositive (-5) << "\n";
    std::cout << "5 is positive: " << IsPositive (5) << "\n";
    std::cout << "2.5 + 3.5 = " << d << "\n" << "Magnitude of (6, 8): " << mag << "\n" << "Value of n after AddFive(): " << n << "\n";
    return 0;
}
