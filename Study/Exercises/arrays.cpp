// Day 4 — Arrays Exercises
// Attempt each WITHOUT looking at Solutions/arrays.cpp first.
// Compile/run: g++ arrays.cpp -o arrays && ./arrays

#include <iostream>

int main() {
    // 1. Declare an int array named `temps` with 6 elements: 72, 68, 75, 80, 65, 70
    //    Print the value at index 3.
    int temps[6] = {72, 68, 75, 80, 65, 70};
    
    std::cout << temps[3] << "\n";

    // 2. Change the value at index 0 to 100. Then print index 0 again to confirm the change.
    temps[0] = 100;
    std::cout << temps[0] << "\n";

    // 3. Print the LAST element of `temps` WITHOUT hardcoding the number 5 as the index.
    //    hint: sizeof(temps) gives total bytes of the whole array, sizeof(temps[0]) gives bytes
    //    of one element — dividing the two gives you the element count. Not covered in the concept
    //    file yet; look up "sizeof operator" on cppreference.com if the hint alone isn't enough.
    int index = sizeof(temps)/sizeof(temps[0]) - 1;
    std::cout << temps[index] << \n;

    return 0;
}
