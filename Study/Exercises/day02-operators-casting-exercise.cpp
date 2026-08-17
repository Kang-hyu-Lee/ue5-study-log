// Day 2 — C++ Exercises: Operators, Expressions, Type Casting
// Type these into a .cpp file yourself and predict the output BEFORE running.

#include <iostream>
using namespace std;

int main() {
    // Q1. Predict the printed value, then run it to check.
    int x = 10;
    int y = 3;
    cout << x + y * 2 << endl;   // predict: 16

    // Q2. Predict the output. (Think PEMDAS from Day 1 math.)
    int a = 20;
    int b = 4;
    int c = 2;
    cout << a / b - c << endl;   // predict: 3

    // Q3. Modulo — predict the output.
    cout << 17 % 5 << endl;      // predict: 2

    // Q4. Integer division trap — predict BEFORE running.
    int m = 9;
    int n = 4;
    double result = m / n;
    cout << result << endl;      // predict: 2

    // Q5. Fix Q4 using static_cast so the true decimal answer prints.
    // Write your corrected line below:
    double d_result = static_cast<double>(m)/n;
    cout << d_result << endl;
    // double fixedResult = 2.25

    // Q6. Using an assignment operator (+=, -=, *=, or /=), rewrite this
    // line more concisely: score = score + 15;
    int score = 100;

    cout << score << endl;
    // your rewritten line here:
    score += 15;

    cout << score << endl;

    return 0;
}
