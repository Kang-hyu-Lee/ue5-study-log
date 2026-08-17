// Exercises — Arrays, Indexing in Code
// Attempt each yourself before checking Solutions. Type it, don't paste.
// Compile with: g++ arrays-indexing-exercises.cpp -o test && ./test

#include <iostream>

// 6. Write a function `int SumArray(int arr[], int size)` that takes
//    an array and its size, and returns the sum of its elements.
//    Call it on `damage` and print the result.
//    Hint: see the "Passing arrays to functions" section in
//    Study/Concepts/arrays-indexing.md — arrays lose their size
//    once passed to a function, so `size` must be a separate param.
int SumArray(int arr[], int size){
    int sum = 0;
    for (int i=0; i<size; i++){
            sum += arr[i];
    }
    return sum;
}

int main() {

    // 1. Declare an int array called `hp` of size 4, initialized to
    //    {100, 80, 60, 40}.
    int hp[4] = {100, 80, 60, 40};

    // 2. Write a for loop that prints every element of `hp` using
    //    CORRECT bounds (no off-by-one).
    for (int i=0; i<4; i++){
        std::cout << hp[i] << '\n';
    }

    // 3. Right below your correct loop, write ONE commented-out line
    //    showing what a buggy off-by-one loop condition would look like
    //    for `hp` — don't actually run it, just write it and comment it
    //    out, labeled "BUGGY:".

    //BUGGY: for (int i=0; i<=4; i++){}

    // 4. Declare an int array called `damage` of size 5, initialized to
    //    {5, 10, 15, 20, 25}. Write a loop that computes the SUM of all
    //    elements into a variable called `total`, then print `total`.
    int damage[5] = {5, 10, 15, 20, 25};

    // 5. Using `damage` from #4, write a loop that finds the LARGEST
    //    value in the array and prints it.
    //    Hint: start a variable `maxVal` at damage[0], then loop from
    //    index 1 onward, comparing each element and updating maxVal if
    //    a bigger one is found. (if/else — covered Day 3.)
    int maxVal = 0;
    for (int i=0; i<5; i++){
        if (maxVal < damage[i]) {
            maxVal = damage[i];
        }
    }

    std::cout << "Max Value: " << maxVal << '\n';
    // 6. Call the SumArray function you defined above main, passing in
    //    `damage`, and print the result.
    
    std::cout << "Sum of damage array: " << SumArray(damage, 5) << std::endl;
    return 0;
}
