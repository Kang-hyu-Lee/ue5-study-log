# What Is an Algorithm?

An algorithm is just a precise, step-by-step procedure to solve a problem.
"Precise" is the key word — a recipe that says "cook until done" isn't an
algorithm. A recipe that says "cook for 12 minutes at 350°F" is.

You don't need C++ syntax to think about algorithms — you need to be able to
count STEPS. That's all Big-O measures: how the number of steps grows as the
input gets bigger.

## Core Mechanism: What Big-O Actually Measures
Big-O describes the **shape of growth**, not a raw speed. It answers: "if I
double the input size, roughly how much MORE work happens?" It deliberately
ignores constant factors (a fast O(n) algorithm can beat a slow O(log n) one
at small sizes) and focuses purely on the trend as input size (n) →
very large.

## Worked Example (line by line, no code yet)

**Problem:** find the name "Kang" in a list of names.

**Approach A — Unsorted list, checking one at a time:**
- List: [Sam, Priya, Kang, Alex, Wei] (5 names)
- Step 1: is it Sam? No.
- Step 2: is it Priya? No.
- Step 3: is it Kang? Yes — found it. 3 steps for 5 names.

Now imagine 1,000,000 names, and "Kang" happens to be last in the list.
That's 1,000,000 steps. Worst case: **steps grow at the same rate as the
list size.** Double the list, worst case roughly doubles the steps. This
growth pattern is called **O(n)** — "linear time." n = size of input.

**Approach B — Sorted list, phone-book style:**
- List sorted alphabetically. You open to the middle. Is "Kang" before or
  after the midpoint word? Say midpoint is "Priya" — K < P, so you only
  look at the left half now.
- Repeat: cut the remaining section in half each time.
- Step 1: 1,000,000 names → 500,000 remain.
- Step 2: 500,000 → 250,000 remain.
- Step 3: 250,000 → 125,000 remain.
- ...you reach 1 name in about 20 steps, not 1,000,000.

This growth pattern is called **O(log n)** — "logarithmic time." Doubling
the input size only adds ONE extra step. Massively better at scale.

## The Big-O Categories You Need Right Now (informal, no math proof)

| Notation | Name | Intuition | Example |
|---|---|---|---|
| O(1) | Constant | Same number of steps no matter the input size | Looking up `myArray[3]` directly |
| O(log n) | Logarithmic | Cuts the problem in half each step | Phone-book search above |
| O(n) | Linear | Steps grow 1-to-1 with input size | Checking every name one at a time |
| O(n²) | Quadratic | Steps grow by the square of input size | Comparing every name to every OTHER name (nested loop — outer loop runs once per item, inner loop re-runs fully each time) |

You don't calculate exact numbers yet (that's Day 9's "formal Big-O rules").
Right now the skill is: **look at a problem and guess which category it
roughly falls into.**

## Common Pitfall / Misconception
Beginners assume "Big-O = actual speed." It doesn't. A poorly-optimized
O(n) algorithm can run SLOWER than a well-optimized O(n²) one at small
input sizes — Big-O ignores constants (e.g. "3n" and "n" are both just
"O(n)" even though 3n does 3x the work). Big-O only tells you which
algorithm wins **as n grows large**, not which is faster right now, today,
at your current input size.

## Edge Case Where the Naive Understanding Breaks
"Approach B (O(log n) binary search) is always better than Approach A
(O(n) linear scan)" — true at scale, FALSE for small or unsorted lists.
Binary search REQUIRES the list to already be sorted; sorting itself
costs time (you'll formally hit this on Day 9 — sorting is at best
O(n log n)). If you only search once, sorting-then-searching can cost
MORE total work than just doing one O(n) linear scan. The naive "log n
beats n, so always sort first" instinct breaks the moment you factor in
the one-time cost of sorting.

## Why This Matters for Game Dev / Interviews
- Every DSA interview question gets asked "what's the time complexity?"
  immediately after you solve it. If you can't answer, it signals vibe-coding.
- In UE5, algorithm choice affects frame rate directly — an O(n²) collision
  check between every actor and every other actor is why naive physics
  tanks performance with many objects (this is WHY spatial partitioning
  like quadtrees exists — future topic, tagged in your roadmap).
