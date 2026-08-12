# Big-O Notation — Formal Rules

Day 2 gave you the *intuition* (Big-O = "how does runtime grow as input grows"). Today: the actual rules for deriving it from code, mechanically, so you can defend it in an interview instead of guessing.

## What Big-O Formally Describes
Big-O describes the **shape of growth** as input size `n` gets very large — not exact operation counts. Two functions can do wildly different amounts of work and still be "the same" Big-O if they grow at the same rate. This is why we simplify aggressively (Rules 1–2 below): at large `n`, the small stuff becomes irrelevant to the shape.

## Rule 1 — Drop Constants
`O(3n)` → `O(n)`

A loop that walks an array 3 separate times is `3n` operations. But as `n` grows, `3n` and `n` still both grow *linearly* — same shape, just scaled. Big-O cares about shape, not the scale factor.

- Example: three separate `for` loops each doing one full pass over an `n`-element array → `3n` → **O(n)**, not O(3n).

## Rule 2 — Drop Lower-Order (Non-Dominant) Terms
`O(n² + n)` → `O(n²)`

When `n` is huge, `n²` completely dwarfs `n` (e.g. at n=1000: n²=1,000,000 vs n=1,000 — the `n` term is noise). Only the fastest-growing term matters.

- Example: a nested loop (`n²` work) followed by a separate single loop (`n` work) → total `n² + n` → dominant term wins → **O(n²)**.

## Rule 3 — Different Inputs Stay Separate Variables
`O(a + b)` is **not** the same as `O(n)` when `a` and `b` are sizes of two *unrelated* inputs.

- Example: looping through array A (size `a`) then array B (size `b`), where A and B are unrelated arrays passed into your function → **O(a + b)**. You cannot collapse this to O(n) — there is no single `n`, and interviewers specifically test whether you notice this.

## Rule 4 — Sequential Code → Add
Code that runs one block *after* another (not nested) adds complexities, then you apply Rule 2 to simplify.

- Example: `O(n)` loop, then later (not nested) an `O(n²)` loop → `O(n + n²)` → **O(n²)**.

## Rule 5 — Nested Loops → Multiply
A loop *inside* another loop multiplies, because the inner loop's full cost happens **once per outer iteration**.

- Mechanism: outer loop runs `n` times. For **each** of those `n` times, the inner loop runs `n` times. Total iterations = `n × n` = **O(n²)**.

**Rule 4 vs Rule 5 is the single most common beginner mix-up** — see Pitfall below.

## Common Complexity Classes (growth order, cheapest → most expensive)
```
O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(2ⁿ) < O(n!)
```
`O(log n)` shows up when a problem's size gets *cut down* each step (e.g. repeatedly halving a search range — you'll see this properly with binary search later). Rough intuition for now: doubling `n` barely moves `log n` at all.

## Worked Example — Line by Line
```cpp
int SumPairs(int arr[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {        // outer loop: runs n times total
        for (int j = 0; j < n; j++) {    // inner loop: runs n times FOR EACH outer pass
            total += arr[i] + arr[j];    // constant-time work: O(1) per iteration
        }
    }
    return total;
}
```
- Outer loop: `n` passes.
- Inner loop: `n` passes, but it happens *inside* the outer loop, so it re-runs fully every single outer iteration → `n` inner passes × `n` outer passes = `n²` total iterations of O(1) work.
- Total: **O(n²)** (Rule 5).

Now suppose right after this function's loop, you added one more separate line: a single loop printing all `n` array elements. That's `O(n²)` (the nested part) `+ O(n)` (the print loop) = `O(n² + n)` → Rule 2 drops the lower term → still **O(n²)**.

## Pitfall
Confusing "two loops back to back" (Rule 4, **add** → often stays the same order, e.g. `O(n)+O(n)=O(n)`) with "one loop inside another" (Rule 5, **multiply** → jumps order, e.g. `O(n)×O(n)=O(n²)`). This exact "what's the Big-O of two loops in sequence vs. nested" question is a standard interview trap — the code often *looks* superficially similar (two `for` loops in the function) but the placement (sequential vs. nested) changes the answer completely.

## Why It Matters
Interviewers don't just want the answer, they want you to *derive* it out loud — "there's a nested loop here so that's multiplicative, giving n², and the separate print loop after it is lower-order so it drops out." That derivation is what signals real understanding vs. memorized labels. In production code, algorithmic complexity dominates performance at scale far more than micro-optimizing constants (Rule 1 is *why* premature micro-optimization of constants is usually a waste of time — the algorithm class is what matters).

## Edge Case
Big-O as commonly used describes the **worst case** unless stated otherwise — it doesn't promise anything about typical/average performance. Example: searching an unsorted array for a value is O(n) worst case (value is last, or missing entirely) but O(1) best case (value is at index 0). Stating "O(n)" without qualifying worst/average/best is technically incomplete — good interview answers say "O(n) worst case" explicitly.
