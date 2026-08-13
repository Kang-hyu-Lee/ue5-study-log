// Pointers Pt.1 — Solutions (Day 10)

#include <iostream>

int main() {
    // 1. Full version — value AND address for both the variable and pointer
    int Score = 100;
    int* ScorePtr = &Score;

    std::cout << "Score value: "   << Score      << '\n'; // 100 — the value
    std::cout << "&Score:       "  << &Score      << '\n'; // Score's address
    std::cout << "ScorePtr:     "  << ScorePtr    << '\n'; // SAME address as &Score
    std::cout << "*ScorePtr:    "  << *ScorePtr   << '\n'; // 100 — dereferenced,
                                                             // same as Score's value
    // &Score and ScorePtr print identically because ScorePtr was initialized
    // to hold exactly that address. *ScorePtr and Score print identically
    // because they're two paths to the same memory.

    // 2. Modify through the pointer
    *ScorePtr = 250;                 // "go to what ScorePtr points at, set it to 250"
    std::cout << "Score after: " << Score << '\n'; // 250 — changed without
                                                     // ever writing "Score = 250"

    // 3. Swap via pointers only
    int Lives = 3;
    int* LivesPtr = &Lives;
    int Temp = 0;

    Temp        = *ScorePtr;   // save Score's current value (250)
    *ScorePtr   = *LivesPtr;   // Score's slot now gets Lives' value (3)
    *LivesPtr   = Temp;        // Lives' slot now gets the saved value (250)

    std::cout << "Score: " << Score << '\n'; // 3
    std::cout << "Lives: " << Lives << '\n'; // 250
    // Note what did NOT change: ScorePtr still points at Score's address,
    // LivesPtr still points at Lives' address. Only the VALUES living at
    // those addresses got swapped — the pointers themselves never moved.
    // This distinction (swapping values through pointers vs swapping what
    // the pointers point to) is a common interview follow-up question.

    // 4. Safe null check
    int* NothingPtr = nullptr;
    if (NothingPtr == nullptr) {
        std::cout << "pointer is null\n";
    } else {
        std::cout << "pointer is not null\n";
    }
    // Comparing NothingPtr == nullptr never touches the memory it (doesn't)
    // point to — safe. Writing *NothingPtr anywhere before this check would
    // be undefined behavior, same failure mode as a wild pointer.

    return 0;
}
