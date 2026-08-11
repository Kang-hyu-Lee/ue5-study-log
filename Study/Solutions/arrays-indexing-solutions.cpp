// Solutions — Arrays, Indexing in Code
// Compile with: g++ arrays-indexing-solutions.cpp -o test && ./test

#include <iostream>

int SumArray(int arr[], int size) {   // #6 — size passed separately,
    int total = 0;                     // since arr decays to just an
    for (int i = 0; i < size; i++) {   // address once passed in
        total += arr[i];
    }
    return total;
}

int main() {

    // 1.
    int hp[4] = {100, 80, 60, 40};

    // 2.
    for (int i = 0; i < 4; i++) {
        std::cout << hp[i] << '\n';
    }

    // 3. BUGGY: for (int i = 0; i <= 4; i++) { std::cout << hp[i]; }
    //    i reaches 4, but valid indices are only 0-3 — hp[4] reads
    //    memory outside the array (undefined behavior).

    // 4.
    int damage[5] = {5, 10, 15, 20, 25};
    int total = 0;
    for (int i = 0; i < 5; i++) {
        total += damage[i];   // shorthand for: total = total + damage[i];
    }
    std::cout << "Total: " << total << '\n';

    // 5.
    int maxVal = damage[0];        // start assuming index 0 is the max
    for (int i = 1; i < 5; i++) {  // start at 1 — index 0 already used
        if (damage[i] > maxVal) {
            maxVal = damage[i];
        }
    }
    std::cout << "Max: " << maxVal << '\n';

    // 6.
    std::cout << "SumArray result: " << SumArray(damage, 5) << '\n';

    return 0;
}
