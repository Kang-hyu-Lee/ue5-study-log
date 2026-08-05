// Day 1 Exercises — C++ Fundamentals
// TYPE THIS FILE YOURSELF — do not paste generated code.
// Write your answers directly below each problem's comment block.
// Try to compile and run each one before checking the Solutions file.

#include <iostream>
using namespace std;

int main() {

    // ---------------------------------------------------------
    // Problem 1: Declare an int variable named "score" and set
    // it to 95. Then print it to the screen labeled "Score: ".
    // ---------------------------------------------------------

    int score = 95;
    
    cout << "Score: " << score << endl;


    // ---------------------------------------------------------
    // Problem 2: Declare a double variable named "temperature"
    // set to 98.6, and a char variable named "grade" set to 'B'.
    // Print both, each on its own line, with labels.
    // ---------------------------------------------------------

    double temperature = 98.6;
    char grade = 'B';
    
    cout << "Temperature: " << temperature << endl;
    cout << "Grade: " << grade << endl;

    // ---------------------------------------------------------
    // Problem 3: Declare a bool variable named "isRaining" set
    // to false. Print it with a label. (Recall: cout prints
    // bool as 1/0, not true/false — see Concepts file Section 5.)
    // ---------------------------------------------------------

    bool isRaining = 0;

    cout << "Is Raining: " << isRaining << endl;

    // ---------------------------------------------------------
    // Problem 4: Declare THREE int variables: a, b, c, set to
    // 3, 4, and 5. Print a single line showing all three values
    // separated by spaces, in one cout statement using chained
    // << operators (see Concepts file Section 5 for how << chains).
    // ---------------------------------------------------------

    int a = 3;
    int b = 4;
    int c = 5;

    cout << "a: " << a << " b: " << b << " c: " << c << endl;

    cout << a << " " << b << " " << c << " " << endl; //solution

    // ---------------------------------------------------------
    // Problem 5 (float vs double): Declare a float named
    // "gravity" set to 9.8. Remember the f suffix rule from
    // Concepts file Section 4 — what happens if you forget it?
    // Try it once WITHOUT the f suffix and see if it still
    // compiles (it should — but note this for discussion).
    // ---------------------------------------------------------

    float gravity = 9.8f;

    cout << "gravity: " << gravity << endl;
    return 0;
}
