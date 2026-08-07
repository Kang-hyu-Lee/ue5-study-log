// Day 3 C++ Exercises — Conditionals & Boolean Logic
// Type these yourself, don't paste. Compile and run each with g++ to check your output.
// std::cout << "text"; prints text to the terminal (you've used this since Day 1's first program).

#include <iostream>
using namespace std;

int main() {

    // 1. Declare an int variable. Write an if/else-if/else chain that prints
    //    "Positive", "Negative", or "Zero" depending on its value.
    int var = 0;
    int health = 50;
    int score = 95;
    bool isAlive = true;
    char grade;

    if (var > 0) {
        cout << "Positive\n";
    } else if (var == 0){
        cout << "Zero\n";
    } else {
        cout << "Negative\n";
    }
    // 2. Write an else-if chain classifying an int `health` (0-100) into:
    //    >= 75 -> "Healthy", >= 25 -> "Wounded", else -> "Critical"
    //    (Same idea as the worked example in the concept file, different variable to prove you understand it, not memorized it.)
    if (health >= 75) {
        cout << "Healthy\n";
    } else if (health >= 25) {
        cout << "Wounded\n";
    } else {
        cout << "Critical\n";
    }

    // 3. Declare an int `score`. Write a SINGLE if condition (using &&) that checks
    //    score is between 0 and 100 INCLUSIVE, and prints "Valid score" if so.
    if (score >= 0 && score <= 100) {
        cout << "Valid score\n";
    }

    // 4. FIND THE BUG. This snippet has the classic = vs == mistake. Rewrite it correctly below.
    //    bool isAlive = true;
    //    if (isAlive = false) {
    //        std::cout << "Player died\n";
    //    }
    if (isAlive == false) {
        cout << "Player died\n";
    }

    // 5. TRACE, DON'T RUN (answer in a comment): given
    //    int x = 0;
    //    bool result = (x > 0) || (10 / x > 2);
    //    Does this crash from divide-by-zero? Why or why not? (Think short-circuit.)
    //    Answer: Yes because or will evaluate both sides && has to be used to prevent divide-by-zero


    // 6. Write an else-if chain that assigns a letter grade to an int `score` (0-100):
    //    >= 90 -> 'A', >= 80 -> 'B', >= 70 -> 'C', >= 60 -> 'D', else -> 'F'
    //    Order the conditions correctly — think about what happens if you order low-to-high instead.

    //if (score >= 90) {
    //    cout << "A\n";
    //} else if (score >= 80) {
    //    cout << "B\n";
    //} else if (score >= 70) {
    //    cout << "C\n";
    //} else if (score >= 60) {
    //    cout << "D\n";
    //} else {
    //    cout << "F\n";
    //}

    if (score >= 90) {
        grade = 'A';
    } else if (score >= 80){
        grade = 'B';
    } else if (score >= 70){
        grade = 'C';
    } else if (score >= 60){
        grade = 'D';
    } else {
        grade = 'F';
    }

    cout << "Grade: " << grade << "\n";



    return 0;
}
