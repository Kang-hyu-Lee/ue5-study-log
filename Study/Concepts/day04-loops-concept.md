# Loops — Concept Notes (Day 4)

## What Is a Loop?
- A block of code that repeats while some condition holds, so you don't hand-write the same instruction N times.
- Two flavors covered today: `for` and `while`. Same underlying idea, different shape — pick based on whether you know the iteration count up front.

## `for` Loop Syntax
```cpp
for (initialization; condition; increment) {
    // body — runs once per iteration
}
```
- **initialization** — runs once, before anything else (usually declares a counter, e.g. `int i = 0`).
- **condition** — checked *before* every iteration, including the first. If false, the loop body never runs (or stops running).
- **increment** — runs *after* the body finishes, each time, right before the condition is checked again.
- Use `for` when you know how many times you're iterating (e.g. "once per array element").

## `while` Loop Syntax
```cpp
while (condition) {
    // body
}
```
- Condition checked before each iteration, same as `for` — but there's no built-in slot for initialization or increment. You manage the counter yourself, outside and inside the loop.
- Use `while` when the number of iterations isn't known ahead of time (e.g. "keep asking for input until the user types 'quit'").

## Pitfall / Misconception
- **Infinite loop**: forgetting to update the loop variable (in a `while`) or writing an increment that never makes the condition false. The program hangs — doesn't crash, doesn't error, just runs forever.
- **Off-by-one**: iterating a 0-indexed array with `i <= size` instead of `i < size` — see the Arrays edge case, it's the exact same bug wearing a loop costume.

## Production / Interview Relevance
- Virtually every algorithm (search, traversal, sorting) is built on loops — interviewers watch loop bounds closely because off-by-one is the single most common "small bug, big consequence" mistake at this level.
- Conceptual preview: a game's core "tick every frame, forever until told to stop" pattern is structurally a loop — not the same code, but the same shape of reasoning. Full game-loop mechanics come later in UE5, not now.

## Edge Case
- Using a `float`/`double` as a loop counter and checking for exact equality (`while (x != 10.0)`) instead of a `<` comparison. Floating point values accumulate tiny rounding errors (ties back to Day 3's float-comparison pitfall), so `x` might overshoot `10.0` and never hit it *exactly* — resulting in an infinite loop. Always use `<` or `<=` for float-based loop conditions, never `==`/`!=`.

## Worked Example (line by line)

```cpp
#include <iostream>

int main() {
    int scores[5] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 5; i++) {        // i starts at 0, loop continues while i < 5, i increments after each pass
        std::cout << scores[i] << std::endl; // print element at the current index
    }

    int j = 0;
    while (j < 5) {                       // same result, different shape
        std::cout << scores[j] << std::endl;
        j++;                               // MUST manually increment — forgetting this = infinite loop
    }

    return 0;
}
```

**Line by line:**
- `for (int i = 0; i < 5; i++)` — declares `i` (scoped to the loop), checks `i < 5` before each pass, increments `i` after each pass. Runs for `i = 0, 1, 2, 3, 4` — exactly 5 times, matching the array's 5 valid indices.
- `scores[i]` inside the body — uses the loop counter directly as the array index. This is the single most common pairing you'll write: loop counter drives array access.
- `int j = 0;` then `while (j < 5)` — identical outcome to the `for` loop, but `j` is declared outside, and the `j++` increment is a separate line you must remember to write inside the body. This is *why* `for` is preferred when the iteration count is known: the increment can't be forgotten as easily since it's baked into the loop header.
