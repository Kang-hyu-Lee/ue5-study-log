# Day 18 — Recursion (DSA)

## Core Mechanism
A recursive function calls itself to solve a smaller version of the same problem, until it hits a BASE CASE — a condition simple enough to answer directly without another call.

Every recursive function needs exactly two parts:
1. **Base case** — stops the recursion. Without this, the function calls itself forever until it crashes.
2. **Recursive case** — calls itself with a smaller/simpler input, moving *toward* the base case.

## How It Actually Runs: The Call Stack
Recall stacks (Day 16): LIFO — last in, first out. Every function call, recursive or not, pushes a new STACK FRAME onto the call stack. That frame holds that call's local variables and where execution resumes once the call returns. A recursive function pushes a new frame every time it calls itself, and frames only start popping (returning) once the base case is hit. This is not a metaphor — it is the literal mechanism, and it's why a missing base case is a real crash, not just a logic bug.

## Worked Example: Factorial

```cpp
int Factorial(int N)
{
    if (N <= 1)                    // base case
    {
        return 1;
    }
    return N * Factorial(N - 1);   // recursive case
}
```

Trace `Factorial(4)`, frame by frame:

```
Call Factorial(4)
  N=4, not <=1 -> return 4 * Factorial(3)     [must resolve Factorial(3) first]
    Call Factorial(3)
      N=3, not <=1 -> return 3 * Factorial(2)
        Call Factorial(2)
          N=2, not <=1 -> return 2 * Factorial(1)
            Call Factorial(1)
              N=1, BASE CASE -> return 1
            Factorial(1) returns 1
          Factorial(2) = 2 * 1 = 2, returns 2
        Factorial(3) = 3 * 2 = 6, returns 6
      Factorial(4) = 4 * 6 = 24, returns 24
```

At the deepest point, 4 stack frames exist simultaneously (N=4,3,2,1), each waiting on the one below it. The actual multiplication happens on the way back UP the stack (unwinding), not on the way down. This "unwind" direction is the part that trips people up — the print/compute-after-the-call pattern (post-order) only makes sense once you see this.

## Pitfall: Missing or Wrong Base Case
Forget the base case, or write a recursive case that never actually reaches it (e.g. always calling `N - 1` when N is already negative and the base case checks `N == 0`), and the function calls itself forever. Each call pushes another frame. Eventually you run out of stack memory — a **stack overflow**, a real runtime crash. This is the single most common recursion bug, and the first thing to check when a recursive function hangs or crashes.

## Why It Matters
- Classic interview topic — nearly every interview loop has at least one recursion or recursion-adjacent (tree/graph traversal) question.
- Real production use: file-system traversal, tree/graph traversal (your next DSA topics), UI hierarchy walks.
- Gamedev-relevant: Actor attach hierarchies (parent/child chains — the transforms you just did iteratively) and spatial trees (quadtree/octree/BVH, flagged for later in your roadmap) are naturally recursive structures.
- Blueprint note: Unreal Blueprints technically support recursion but it's discouraged in performance-critical code — each BP node call carries more overhead than C++, and deep BP recursion is a known perf footgun. Good interview talking point on BP vs C++ tradeoffs.

## Edge Case: Naive Recursion Can Recompute Work
Recursive Fibonacci — you'll likely meet this in interviews:

```cpp
int Fib(int N)
{
    if (N <= 1) return N;
    return Fib(N - 1) + Fib(N - 2);
}
```

This looks clean but is exponentially slow: `Fib(N-2)` gets recomputed many times across the branching call tree (`Fib(5)` calls `Fib(3)` twice, `Fib(2)` three times, and it gets worse fast). The naive mental model "recursion = automatically clean/efficient" breaks here. The fix is memoization — caching subresults so each unique subproblem is computed once — a Dynamic Programming technique on your Phase 2 DSA list. Flagging the connection now so it's not a cold introduction later.

## Recursion vs. Your Linked List Work
You already wrote iterative (loop-based) linked list traversal for the to-do list portfolio piece. Any iterative traversal can be rewritten recursively: walk to `Next`, recurse, then do the work either *before* the recursive call (pre-order) or *after* it (post-order — like the factorial multiply-on-the-way-back pattern above). Today's exercises use this directly on a small linked structure.
