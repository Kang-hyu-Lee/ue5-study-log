# Arrays — Concept Notes (Day 4)

## What Is an Array?
- A fixed-size block of memory holding multiple elements of the **same type**, laid out **contiguously** (back-to-back, no gaps).
- Analogy: a row of numbered mailboxes. Each box holds one value, boxes are the same size, and they sit right next to each other.
- Declared with a size known at compile time (for now — dynamic sizing comes later with pointers/`std::vector`).

## Indexing
- Elements are accessed with `arrayName[index]`.
- **Zero-based**: the first element is index `0`, not `1`. An array of size `N` has valid indices `0` through `N-1`.
- This trips up every beginner at least once — "element 3" and "index 3" are NOT the same element (index 3 is the *4th* element).

## Memory Layout Intuition
- The array variable really just stores the **base address** (where index 0 lives).
- To find any element: `address = base_address + (index * sizeof(element_type))`.
- Zero-based indexing exists *because* this formula is cleaner — index 0 means "no offset from base," so the math needs no `-1` correction.

## Pitfall / Misconception
- **Off-by-one error**: looping with `i <= size` instead of `i < size` reads one element past the end.
- In C++, **out-of-bounds access does not throw an error or crash reliably** — it's undefined behavior (UB). Unlike Python or Java, there's no automatic bounds check. The program might print garbage, might "work" by accident, might crash — and that inconsistency is what makes this bug dangerous: it can pass testing and fail in production.

## Production / Interview Relevance
- **Cache locality**: because array elements are contiguous, the CPU can pull several elements into cache at once. This makes arrays fast for tight loops — relevant in game engines when iterating over things like entity lists or component data every frame.
- **O(1) access**: because of the direct address formula above, getting `array[i]` takes the same amount of time regardless of array size or which index you ask for — no searching required. (Ties back to Day 2's Big-O intuition — this is the textbook example of a constant-time operation.)

## Edge Case
- `array[size]` (exactly one past the last valid index) is the classic edge case. It's **not** automatically caught — the compiler will happily generate code for it, and it may silently read whatever garbage value happens to sit in adjacent memory. This is why the loop condition `i < size` (not `<=`) matters so much — it's not a style preference, it's correctness.

## Worked Example (line by line)

```cpp
#include <iostream>

int main() {
    int scores[5] = {10, 20, 30, 40, 50}; // declare array named "scores", type int, 5 elements, initialized in order

    std::cout << scores[0] << std::endl; // index 0 = first element -> prints 10
    std::cout << scores[4] << std::endl; // index 4 = LAST element (size 5, so last valid index is 5-1=4) -> prints 50

    scores[2] = 99;                       // overwrite index 2 (currently 30) with 99 — arrays are mutable
    std::cout << scores[2] << std::endl; // -> prints 99, confirms the overwrite

    return 0;
}
```

**Line by line:**
- `int scores[5] = {10, 20, 30, 40, 50};` — declares the array. `int` is the element type (all 5 slots must be `int`). `[5]` fixes the size at compile time. The `{}` list initializes each slot in order: index 0 gets 10, index 1 gets 20, etc.
- `scores[0]` — computes `base_address + (0 * sizeof(int))`, i.e. reads the very first slot. Result: `10`.
- `scores[4]` — the last valid index for a 5-element array. Reaching for `scores[5]` here would be the out-of-bounds edge case above.
- `scores[2] = 99;` — this is an **assignment into the array**, not a declaration. It finds the address for index 2 and overwrites the value stored there. The original `30` is gone.
