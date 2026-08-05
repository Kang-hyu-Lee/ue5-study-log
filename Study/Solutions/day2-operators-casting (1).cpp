// Day 2 — C++ Solutions: Operators, Expressions, Type Casting

#include <iostream>
using namespace std;

int main() {
    // Q1: x + y*2 → multiplication first (PEMDAS): 3*2=6, then 10+6=16
    int x = 10;
    int y = 3;
    cout << x + y * 2 << endl;   // 16

    // Q2: division first: 20/4=5, then 5-2=3
    int a = 20;
    int b = 4;
    int c = 2;
    cout << a / b - c << endl;   // 3

    // Q3: 17 % 5 → 17 divided by 5 is 3 remainder 2. Modulo gives the remainder.
    cout << 17 % 5 << endl;      // 2

    // Q4: integer division trap. 9/4 in int math = 2 (truncated, not 2.25).
    // That 2 then becomes 2.0 when stored in the double.
    int m = 9;
    int n = 4;
    double result = m / n;
    cout << result << endl;      // 2

    // Q5: cast BEFORE dividing so decimal math happens.
    double fixedResult = static_cast<double>(m) / n;
    cout << fixedResult << endl; // 2.25

    // Q6: += is shorthand for "add then reassign."
    int score = 100;
    score += 15;   // same as score = score + 15;
    cout << score << endl; // 115

    return 0;
}
