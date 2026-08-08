// Day 4 — Loops Solutions
// Review AFTER attempting Exercises/loops.cpp yourself.

#include <iostream>

int main() {
    int nums[5] = {3, 6, 9, 12, 15};

    // 1. Print every element.
    for (int i = 0; i < 5; i++) {
        std::cout << nums[i] << std::endl;
    }

    // 2. Print only even-indexed elements (0, 2, 4).
    for (int i = 0; i < 5; i++) {
        if (i % 2 == 0) {          // i % 2 == 0 means i divides evenly by 2 -> i is even
            std::cout << nums[i] << std::endl; // -> 3, 9, 15
        }
    }

    // 3. Sum all elements with a while loop.
    int sum = 0;
    int j = 0;
    while (j < 5) {
        sum = sum + nums[j];       // accumulate: add current element to running total
        j++;                        // don't forget this — infinite loop otherwise
    }
    std::cout << sum << std::endl; // -> 45

    // 4. Print in reverse WITHOUT modifying the array.
    for (int i = 4; i >= 0; i--) { // start at last valid index, count DOWN, stop once i < 0
        std::cout << nums[i] << std::endl; // -> 15, 12, 9, 6, 3
    }

    return 0;
}

/*
Why #4 matters:
- Notice the array itself never changes — we're just changing the ORDER we visit indices in.
  This distinction (traversal order vs. actual data mutation) comes up constantly once you hit
  sorting/searching algorithms in Phase 2 — many algorithms are just "visit elements in a clever
  order," not "rearrange the underlying storage."
*/
