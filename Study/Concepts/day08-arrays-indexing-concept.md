# Arrays — Indexing in Code

You already have the concept from Day 4 (contiguous memory layout,
zero-based indexing, O(1) access). This is the coding side: syntax,
loops over arrays, and the most common indexing mistake.

## Core syntax, breaking down every symbol

```cpp
int scores[5];        // declare an array named "scores" holding 5 ints
                       // [5] = the SIZE, fixed at compile time, cannot
                       // change later

int scores[5] = {10, 20, 30, 40, 50};
                       // declare AND initialize in one line
                       // {...} = initializer list — values go in order,
                       // index 0 first

scores[0] = 10;        // assign to index 0 (the FIRST element — arrays
                       // start at 0, not 1)
scores[4] = 50;        // index 4 is the LAST valid index for a size-5
                       // array (valid indices: 0,1,2,3,4)

int x = scores[2];     // READ index 2 into variable x (x becomes 30)
```

## Looping over an array
```cpp
for (int i = 0; i < 5; i++) {
    std::cout << scores[i] << '\n';   // i takes values 0,1,2,3,4 — all
                                        // valid indices, none out of bounds
}
```
`i < 5` (strictly less than) is what keeps you in bounds — this is the
same initializer/condition/increment structure from Day 4's for-loop
lesson, just now indexing into an array with `i` instead of only counting
with it.

## Pitfall — off-by-one on the upper bound
```cpp
for (int i = 0; i <= 5; i++) {   // BUG: <= 5 means i reaches 5
    scores[i] = 0;                 // scores[5] is OUT OF BOUNDS — valid
                                    // indices are 0-4 only
}
```
This compiles fine and often *runs* without crashing — it silently
corrupts whatever memory sits next to your array. That's the undefined
behavior from Day 4, now showing up as a bug you'll write yourself if
you're not careful. Correct version uses `i < 5`, not `i <= 5`.

**Why it matters:** this exact bug class (off-by-one / buffer overrun) is
a top real-world security and crash source. UE5's `TArray` adds
bounds-checking in debug builds specifically because raw C++ arrays give
you zero protection.

**Edge case:** array size must be a compile-time constant for a raw C++
array — `int scores[n]` where `n` is a variable read from user input will
not reliably compile (non-standard on most compilers). This is exactly
the limitation `std::vector` (dynamic array) solves — flagging for later,
not teaching yet.

## Passing arrays to functions (uses Day 5's function syntax)
```cpp
void PrintScores(int arr[], int size) {
    // arrays don't carry their own size once passed to a function —
    // the array "decays" to just a memory address, so you must pass
    // the size separately as its own parameter
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << '\n';
    }
}
```
**Pitfall:** forgetting to pass `size` and trying `sizeof(arr)` *inside*
the function — this gives the size of a pointer (usually 8 bytes), not
the array's actual element count, because the array already decayed.
`sizeof` for array length only works in the scope where the array was
originally declared (see Day 4's open question — still unresolved,
flagged for later).
