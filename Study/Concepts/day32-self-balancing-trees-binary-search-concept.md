# Day 32 — Self-Balancing Trees & Binary Search (New Concepts)

These are taught fresh today, before the timed drill on tree traversal/BST bounds (which you've
already learned — that part is pure review, no re-teaching needed).

---

## 1. Why a Plain BST Isn't Automatically O(log n)

### The core mechanism
A BST's search speed depends entirely on its **shape**, not on the fact that it's "a BST."
Height determines search cost: `O(height)`. If the tree is balanced, height ≈ `log₂(n)`.
If it's skewed, height can be `n`.

**Concrete example — insert in sorted order: 1, 2, 3, 4, 5**

Every new value is bigger than everything before it, so it always goes to the right child:

```
1
 \
  2
   \
    3
     \
      4
       \
        5
```

This is a linked list wearing a tree costume. Searching for 5 means walking through
1→2→3→4→5 — that's `O(n)`, not `O(log n)`. The BST insert/search *code* is identical to
the balanced case — the algorithm didn't fail, the *input order* did.

**Contrast — insert 3, 1, 4, 2, 5 (mixed order):**

```
      3
     / \
    1   4
     \   \
      2   5
```

Same 5 values, same insert logic, height is now 3 instead of 5. Nothing about the BST
insert algorithm changed — only the order values arrived in.

### The pitfall (the one you corrected yourself on in Day 30)
"BST" and "O(log n) lookup" are NOT the same guarantee. A plain BST gives you O(log n)
*on average*, for *random* insertion order. Sorted or reverse-sorted input is the
**worst case**, degrading to O(n). This is exactly why `std::map`/`std::set` in C++
are specified to guarantee O(log n) even on adversarial input — they can't rely on
"hope the input is random."

### How self-balancing trees fix this
Self-balancing trees (red-black trees, AVL trees) add **extra rules enforced on every
insert/delete** that keep height at O(log n) regardless of input order, by triggering
**rotations** when a rule is violated.

**A single rotation, concretely.** Take the skewed case: inserting 1, 2, 3 gives:
```
1
 \
  2
   \
    3
```
Height 3 for 3 nodes — already bad. A **left rotation** around node 1 restructures this to:
```
  2
 / \
1   3
```
Height 2. The rotation is a local pointer-rearrangement (constant-time, O(1)): node 2
becomes the new local root, node 1 (old root) becomes its left child, and node 2's old
left subtree (empty here) becomes node 1's right child. No values are compared or moved —
only pointers change.

**AVL trees**: track a *balance factor* per node = height(left subtree) − height(right subtree).
If any node's balance factor becomes ±2 after an insert, rotate to fix it. Strict: height
difference between subtrees never exceeds 1.

**Red-black trees**: color each node red or black, and enforce invariants:
1. Root is always black.
2. A red node cannot have a red child (no two reds in a row on any path).
3. Every path from a node to any of its descendant null pointers passes through the
   same number of black nodes.

These invariants mathematically guarantee height ≤ `2 * log₂(n+1)` — still O(log n),
just with a looser constant than AVL (red-black rebalances less often, so inserts/deletes
are cheaper in practice — this is *why* `std::map` uses red-black, not AVL).

### Why it matters in production / interviews
- `std::map` and `std::set` are red-black trees under the hood — this is *why* they
  guarantee O(log n) worst case, not just average case.
- Interviewers essentially never ask you to *implement* AVL/red-black rotations from
  scratch — but "why is std::map O(log n) guaranteed?" is a very common follow-up, and
  "because it's a BST" is the wrong (incomplete) answer. The right answer names the
  self-balancing mechanism.
- UE5-specific: Unreal doesn't expose a built-in self-balancing tree container (`TMap`
  is hash-based, not tree-based) — so this is pure interview/CS-fundamentals knowledge,
  not something you'll write UE5 code against directly.

### Edge case where the naive understanding breaks
Someone who thinks "BST insert is always O(log n)" will be surprised when a leaderboard
or sorted-ID system that inserts IDs in already-sorted order (e.g., auto-incrementing
keys) silently degrades to linked-list performance. This is a real, recurring bug class —
not just a textbook trick question.

---

## 2. Binary Search

### The core mechanism
Binary search finds a target in a **sorted** array by repeatedly halving the search space.

**Concrete example** — array `[2, 5, 8, 12, 16, 23, 38, 45]` (8 elements, indices 0–7),
searching for `23`:

| Step | lo | hi | mid = (lo+hi)/2 | arr[mid] | Compare to 23 | Action |
|---|---|---|---|---|---|---|
| 1 | 0 | 7 | 3 | 12 | 23 > 12 | search right half: lo = mid+1 = 4 |
| 2 | 4 | 7 | 5 | 23 | 23 == 23 | found at index 5 |

Each step eliminates **half** the remaining candidates — that's where `O(log n)` comes
from: for `n` elements, you can halve at most `log₂(n)` times before one element remains.

### Why it needs sorted data
The halving logic relies on being able to say "if target is bigger than arr[mid], it can
ONLY be in the right half" — that's only true if the array is ordered. On unsorted data,
the target could be anywhere, so there's nothing to eliminate.

### Formal correctness (the actual proof, not just "it halves")
**Loop invariant**: at the start of every iteration, IF the target exists in the array,
it exists within `arr[lo..hi]` (inclusive).
- Initially true: lo=0, hi=n-1 covers the whole array.
- Each iteration either returns (found it) or narrows to a strictly smaller sub-range
  that's proven to still contain the target if it exists (because of the sorted-order
  comparison).
- Loop terminates because `hi - lo` strictly decreases each iteration.
- When `lo > hi`, the range is empty — target proven not present.

This is why the invariant matters more than "trust me, it halves": it's what lets you
*prove* the algorithm is correct, not just observe that it usually works.

### The off-by-one pitfalls (the actual bug-prone part)
1. **Loop condition**: must be `while (lo <= hi)`, not `lo < hi` — using `<` can skip
   the last remaining candidate when the range is exactly one element.
2. **Updating bounds**: after checking `arr[mid]`, you must move to `mid + 1` or
   `mid - 1` — **never** `lo = mid` or `hi = mid`. Using `mid` itself (not `mid±1`)
   causes an infinite loop when `lo` and `hi` become adjacent, since `mid` can
   re-equal `lo` forever.
3. **Mid calculation overflow**: `(lo + hi) / 2` can overflow if `lo + hi` exceeds the
   int range on huge arrays. Safer form: `lo + (hi - lo) / 2`. Rarely bites you at
   interview-problem array sizes, but it's a known "do you actually know why" check.

### Why it matters
- Direct bridge from BST bounds logic: BST search is binary search, just with pointers
  and node values instead of array indices and midpoints — same halving logic, same
  invariant, same off-by-one danger zone (comparing `<` vs `<=` against node bounds).
- O(log n) vs O(n) linear scan is the single most common "why does this scale" interview
  follow-up after any array question.

### Edge case where the naive version breaks
Vanilla binary search with `==` returns *an* index matching the target, not necessarily
the *first* or *last* occurrence if duplicates exist. E.g. searching `[2,5,5,5,5,9]` for
`5` might land on any of the four matching indices depending on how mid rounds — if a
problem needs "first occurrence of X," you need a modified binary search that keeps
searching left even after finding a match. This trips people up because the naive version
"looks correct" (it does return a valid index) while silently failing the actual spec.
