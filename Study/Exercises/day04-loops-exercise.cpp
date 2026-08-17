// Day 4 — Loops Exercises
// Attempt each WITHOUT looking at Solutions/loops.cpp first.
// Compile/run: g++ loops.cpp -o loops && ./loops

#include <iostream>

int main() {
    int nums[5] = {3, 6, 9, 12, 15};
    int sum = 0;
    int counter = 0;

    // 1. Use a for loop to print every element of `nums`.
    for (int i = 0; i < 5; i++){
        std::cout << nums[i] << '\n';
    }

    // 2. Use a for loop to print only the EVEN-INDEXED elements (index 0, 2, 4 -> values 3, 9, 15).
    //    hint: the modulo operator % gives the remainder of a division (e.g. 7 % 2 == 1).
    //    Not covered in the concept file yet — see cppreference.com "Arithmetic operators" if needed,
    //    or flag it with a "?" next session if it's still unclear after looking it up.
    for (int i = 0; i < 5; i++){
        if (i % 2 == 0){
            std::cout << nums[i] << '\n';
        }
    }

    // 3. Use a while loop to sum ALL elements of `nums` and print the total.
    while (counter < 5){
        sum += nums[counter];
        counter ++;
    }
    
    std::cout << sum << '\n';
    // 4. (harder) Use a for loop to print `nums` in REVERSE order without modifying the array itself.
    for (int i = 4; i >= 0; i--){
        std::cout << nums[i] << '\n';
    }

    return 0;
}
