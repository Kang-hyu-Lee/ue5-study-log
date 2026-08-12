# Big-O Solutions — Day 9

---

**1.** `O(n)`
One loop, `n` iterations, each doing O(1) constant work (a single print). `n × O(1)` = `n × 1`, and that `1` is a constant multiplier — **Rule 1** drops it, leaving `O(n)`. (Not Rule 2 — Rule 2 is for dropping a lower-order *additive* term when two separate pieces of work are summed, which isn't happening in a single loop.)

---

**2.** `O(n)`
Two separate (sequential, not nested) loops, each `O(n)`. **Rule 4** adds them: `O(n) + O(n) = O(2n)`. **Rule 1** drops the constant: `O(2n) → O(n)`.

---

**3.** `O(n²)`
Nested loops — the inner loop runs fully (`n` times) for *every single* iteration of the outer loop (`n` times). **Rule 5**: `n × n = n²`. Structurally different from #2 because in #2 the loops are siblings (one finishes, then the other starts); here the inner loop is inside the outer loop's braces, so it restarts completely on every outer pass.

---

**4.** `O(n²)`
Step by step:
- Nested loop block → `O(n²)` (Rule 5).
- Separate loop after it → `O(n)`.
- Sequential, so **Rule 4** adds: `O(n² + n)`.
- **Rule 2** drops the lower-order term: `O(n² + n) → O(n²)`.

---

**5.** `O(sizeA + sizeB)`
Two independent parameters with no relationship enforced by the code — nothing ties `sizeA` and `sizeB` together, so **Rule 3** keeps them as separate terms rather than collapsing to one `n`. (Note: this is mathematically equivalent to `O(max(sizeA, sizeB))`, but `O(sizeA + sizeB)` is the preferred way to state it, since it shows both inputs genuinely contribute.)

---

**6.** `O(1) < O(log n) < O(n) < O(n log n) < O(n²)`
Constant time beats everything; each doubling of `n` barely moves `log n`; linear grows steadily; `n log n` is linear work done `log n` times (you'll see this for real once sorting algorithms are covered); quadratic is the steepest here (nested loop territory).

---

**7.** The constant `2` only scales the line — it doesn't change the *shape* of the growth curve. `2n` and `n` are both straight lines when plotted against `n`; one is just steeper. Big-O is about which growth *category* a function belongs to (constant / logarithmic / linear / quadratic / etc.), not the exact operation count, so multiplicative constants get dropped (**Rule 1**) because they never change which category you're in.
