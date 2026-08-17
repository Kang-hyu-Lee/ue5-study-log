// Day 1 Solutions — C++ Fundamentals
// Only check this after attempting every problem in Exercises yourself.

#include <iostream>
using namespace std;

int main() {

    // ---------------- Problem 1 ----------------
    int score = 95;                    // declare int, store 95
    cout << "Score: " << score << endl;

    // ---------------- Problem 2 ----------------
    double temperature = 98.6;         // decimal -> double
    char grade = 'B';                  // single character -> single quotes
    cout << "Temperature: " << temperature << endl;
    cout << "Grade: " << grade << endl;

    // ---------------- Problem 3 ----------------
    bool isRaining = false;
    cout << "Is raining: " << isRaining << endl;   // prints 0, not "false" — expected

    // ---------------- Problem 4 ----------------
    int a = 3;
    int b = 4;
    int c = 5;
    // chaining multiple << in one statement — each sends the next piece to cout in order
    cout << a << " " << b << " " << c << endl;

    // ---------------- Problem 5 ----------------
    float gravity = 9.8f;   // correct: f suffix marks this literal as float
    // float gravityNoSuffix = 9.8;  // this ALSO compiles: 9.8 defaults to double,
    // and C++ silently narrows it to fit a float variable. It works today, but
    // relying on silent narrowing is a bad habit — always use f for float literals.
    cout << "Gravity: " << gravity << endl;

    return 0;
}

/*
Explanation notes:
- Problems 1-3 are direct applications of "type name = value;" from Concepts Section 4.
- Problem 4 shows that a single cout statement can chain as many << as you want —
  the compiler processes them left to right, printing each piece as it goes.
- Problem 5's point: C++ lets you skip the f suffix on a float literal because it
  auto-converts (narrows) the double 9.8 down to float precision. This is legal but
  is the first example you've seen of an "implicit conversion" — a concept that
  becomes important (and sometimes dangerous) later. For now: always write float
  literals with f explicitly, so your intent is unambiguous.
*/
