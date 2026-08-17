// Pointers Pt.1 — Exercises (Day 10)
// Type your attempts directly below each prompt. Compile with g++ and run
// to check actual addresses/values — don't just reason about it on paper.

#include <iostream>

int main() {
    // 1. Declare an int called score with value 100.
    //    Then declare a pointer to it called scorePtr.
    //    Print: score's value, score's address (&score), scorePtr's value,
    //    and *scorePtr. Confirm &score and scorePtr print the same address.
    int Score = 100;
    int* ScorePtr = &Score;

    std::cout << &Score << '\n';
    std::cout << ScorePtr << '\n';
    //Spec asked for 4 print statements;
    std::cout << Score << '\n';
    std::cout << *ScorePtr << '\n';

    // 2. Using scorePtr (NOT the name "score" directly), change score's
    //    value to 250. Print score afterward to confirm it changed.
    *ScorePtr = 250;

    std::cout << Score << '\n';

    // 3. Declare a second int called lives with value 3.
    //    Declare a pointer livesPtr pointing to it.
    //    Swap the VALUES of score and lives using ONLY the pointers
    //    (scorePtr and livesPtr) — never write "score" or "lives" by name
    //    in your swap logic. You'll need a temporary variable.
    //    Hint: this is the same swap-logic shape as any variable swap,
    //    just going through *scorePtr / *livesPtr instead of the plain
    //    variable names.
    int Lives = 3;
    int* LivesPtr = &Lives;
    int Temp = 0;
    
    Temp = *ScorePtr;
    *ScorePtr = *LivesPtr;
    *LivesPtr = Temp;

    std::cout << "Score: " << Score << '\n';
    std::cout << "Lives: " << Lives << '\n';

    // 4. Declare a pointer called nothingPtr and initialize it to nullptr
    //    (not left uninitialized). Write an if-check that prints
    //    "pointer is null" if nothingPtr == nullptr, WITHOUT dereferencing
    //    it. This is the safe pattern for checking a pointer before use —
    //    dereferencing nullptr is also undefined behavior, just like a
    //    wild pointer.

    int* NothingPtr = nullptr;
    if (NothingPtr == nullptr){
        std::cout << "pointer is null\n";
    }else {
        std::cout << "pointer is not null\n";
    }

    return 0;
}
