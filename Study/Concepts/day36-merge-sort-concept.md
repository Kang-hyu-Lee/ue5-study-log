# Day 36 — Merge Sort (Divide & Conquer)

## 1. The idea in one line
A 1-element array is already sorted. Two sorted arrays can be combined into one sorted array in linear time. Merge sort applies those two facts recursively.

## 2. Mechanism — three steps
1. **Divide:** split the range in half at `mid`.
2. **Conquer:** recursively merge-sort the left half and the right half.
3. **Combine (merge):** walk both sorted halves with two indices (a two-pointer preview; that pattern gets a formal lesson on Day 43). At each step, copy the smaller front element into a buffer and advance that index. When one side runs out, copy the rest of the other side.

The **base case** is a range of size 0 or 1, which gets returned untouched. This is the same recursion shape as Days 18–19: a base case plus a smaller subproblem.

## 3. Full trace: `[38, 27, 43, 3, 9, 82, 10]` (n = 7)
```
SPLIT (mid = lo + (hi-lo)/2, half-open ranges [lo, hi))
[38 27 43 3 9 82 10]
[38 27 43]            [3 9 82 10]
[38] [27 43]          [3 9]      [82 10]
     [27] [43]        [3] [9]    [82] [10]      <- all size 1 = base case

MERGE (bottom-up as recursion returns)
     [27 43]          [3 9]      [10 82]
[27 38 43]            [3 9 10 82]
[3 9 10 27 38 43 82]
```
Detail of the final merge. `L = [27 38 43]`, `R = [3 9 10 82]`, and `i`/`j` are the front indices:
```
compare 27 vs 3  -> take 3   (j++)   out: 3
compare 27 vs 9  -> take 9   (j++)   out: 3 9
compare 27 vs 10 -> take 10  (j++)   out: 3 9 10
compare 27 vs 82 -> take 27  (i++)   out: 3 9 10 27
compare 38 vs 82 -> take 38  (i++)   ...
compare 43 vs 82 -> take 43  (i++)   L empty
copy leftover R  -> 82               out: 3 9 10 27 38 43 82
```

## 4. Why O(n log n) (no calculus, just counting)
Draw the recursion as levels, using n = 8:
```
level 0:  1 array of 8   -> merging costs ~8
level 1:  2 arrays of 4  -> 4 + 4       = ~8
level 2:  4 arrays of 2  -> 2+2+2+2     = ~8
level 3:  8 arrays of 1  -> base case, nothing to merge
```
- **Work per level:** every element is copied exactly once per level, so each level costs O(n).
- **Number of levels:** you halve until you reach size 1. The number of halvings is log₂ n (the Day 3 definition: "how many times do I divide by 2 to reach 1").
- **Total:** n × log n. For n = 1,000,000 that's about 20 levels, so roughly 20M operations instead of about 10¹² for an O(n²) sort.
- **Best case = worst case = average case = O(n log n).** Merge sort always splits and always merges, and there is no early exit.
- **Space:** O(n) auxiliary for the merge buffer, plus O(log n) for the recursion stack. **Merge sort is not in-place on arrays.**

## 5. Stability
A sort is **stable** if equal keys keep their original relative order.
- Merge sort is stable **only if** the merge takes from the LEFT on ties: `if (L[i] <= R[j])`.
- If you use `<` instead, ties take from the right, and stability silently breaks. The output is still sorted, and a basic test won't catch it.
- Why it matters: suppose you sort a leaderboard by name first, then stable-sort by score. Players with equal scores stay alphabetical. An unstable second sort scrambles them.

## 6. Pitfalls
- **`mid = (lo + hi) / 2` overflow.** If lo and hi are large ints, the sum overflows. Use `lo + (hi - lo) / 2`. This is a classic interview "gotcha", and it also appears in binary search on Day 38.
- **Inclusive vs half-open range confusion.** Choose `[lo, hi)`, where `hi` is one past the end, and stick with it everywhere. Mixing conventions gives infinite recursion (a range that never shrinks) or skipped elements.
- **Forgetting the leftover copy loops.** When one side empties, the other side's remainder never gets written, and you get missing or garbage values.
- **Allocating a new vector in every recursive call.** It's correct but slow, because of n log n heap allocations (Day 16: heap allocation isn't free). Allocate **one** buffer up front and pass it by reference.
- **Base case `if (hi - lo == 0)`.** This misses size 1, which then splits into [x] and [] forever. The base case is `hi - lo <= 1`.

## 7. Edge cases where naive understanding breaks
- **Empty array:** must not crash. `hi - lo = 0` hits the base case.
- **Already sorted input:** still O(n log n). Merge sort gains nothing from pre-sorted data, whereas insertion sort would be O(n). "Good algorithm" depends on the data.
- **All duplicates:** this is exactly where `<=` vs `<` decides stability.
- **`size_t` underflow:** with unsigned indices, `hi - 1` when `hi == 0` wraps to a huge number. Half-open ranges avoid ever computing `hi - 1`.

## 8. Linked lists: where merge sort shines
- Linked lists have no random access, so quicksort's partitioning is awkward and heapsort is impractical.
- Merge sort only needs sequential walking. Find the middle with slow/fast pointers, split, recurse, then merge by **relinking nodes**. That gives O(1) extra space besides the recursion stack; you don't need a buffer.
- The merge uses a **dummy head node**, which removes the special case of "the result list is empty, so what do I attach to?" This is the concrete reason dummy heads exist.

## 9. Production & interview relevance
- **C++:** `std::sort` is introsort (quicksort-based hybrid, unstable, covered tomorrow). `std::stable_sort` is merge-sort-based.
- **UE5:** `TArray::Sort()` is unstable, and `TArray::StableSort()` / `Algo::StableSort` are stable. Choose stable when equal-key order is visible to the player (leaderboards, inventory sorted by category then rarity).
- **External sorting:** when data doesn't fit in RAM (databases, log processing), you sort chunks and then merge them. This is merge sort at scale.
- **Likely interview follow-ups:**
  - "Sort a linked list in O(n log n)."
  - "Count inversions" (the merge step counts them for free).
  - "Merge k sorted lists" (revisited with heaps in Week 10+).
  - "Why is merge sort's space O(n)?"
  - "Merge sort vs quicksort?" You'll be able to answer this after tomorrow.

## Restate before moving on (in your own words, not these)
1. Why does each level cost O(n), and why are there log n levels?
2. What single character in the merge decides stability, and why?
3. Why is merge sort a good fit for linked lists specifically?
