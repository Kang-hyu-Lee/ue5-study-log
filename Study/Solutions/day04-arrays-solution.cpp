// Day 4 — Arrays Solutions
// Review AFTER attempting Exercises/arrays.cpp yourself.

#include <iostream>

int main() {
    // 1. Declare `temps` with 6 elements, print index 3.
    int temps[6] = {72, 68, 75, 80, 65, 70};
    std::cout << temps[3] << std::endl; // -> 80 (4th element, index 3)

    // 2. Overwrite index 0, then confirm.
    temps[0] = 100;
    std::cout << temps[0] << std::endl; // -> 100

    // 3. Print last element without hardcoding the size.
    int elementCount = sizeof(temps) / sizeof(temps[0]);
    // sizeof(temps)     -> total bytes used by the whole array (6 * sizeof(int))
    // sizeof(temps[0])  -> bytes used by ONE int element
    // dividing gives element count (6), which stays correct even if the array size changes later
    std::cout << temps[elementCount - 1] << "std::endl"; // -> 70 (last valid index = count - 1)

    return 0;
}

/*
Why this matters:
- Hardcoding sizes (e.g. temps[5]) works until someone resizes the array and forgets to update
  every hardcoded index elsewhere in the code — a real, common bug class.
- sizeof(arr)/sizeof(arr[0]) is a classic C++ idiom for "how many elements does this array have,"
  used constantly before ranged-for loops and std::size() (C++17) became common. Worth recognizing
  even though later code will often use cleaner alternatives.
*/
