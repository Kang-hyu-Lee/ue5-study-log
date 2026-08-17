# Day 3 C++ — Conditionals & Boolean Logic

## Core mechanism

- `bool` is one of C++'s data types (you met it Day 1 alongside int/float/etc.) — it holds exactly one of two values: `true` or `false`.
- An `if` statement runs a block of code **only if** a condition evaluates to `true`:
  ```cpp
  if (condition) {
      // runs only when condition is true
  }
  ```
- `else` runs when the condition was `false`:
  ```cpp
  if (condition) {
      // condition true
  } else {
      // condition false
  }
  ```
- `else if` chains let you test multiple conditions in order. **Only the first matching branch runs — everything after it is skipped, even if it would also be true.**
  ```cpp
  if (conditionA) {
      // ...
  } else if (conditionB) {
      // only reached if conditionA was false
  } else {
      // only reached if BOTH were false
  }
  ```

### Comparison operators (produce a `bool` result)
| Operator | Meaning |
|---|---|
| `==` | equal to |
| `!=` | not equal to |
| `<` `>` | less than / greater than |
| `<=` `>=` | less-or-equal / greater-or-equal |

### Logical operators (combine `bool` values)
| Operator | Meaning |
|---|---|
| `&&` | AND — true only if BOTH sides are true |
| `\|\|` | OR — true if AT LEAST ONE side is true |
| `!` | NOT — flips true↔false |

### Short-circuit evaluation
- `&&` stops evaluating the moment the left side is `false` — the right side never runs, because the answer is already known (false AND anything = false).
- `||` stops the moment the left side is `true` — right side never runs (true OR anything = true).
- This isn't just an optimization — it's a *safety pattern*. Example: `if (enemyCount > 0 && 100 / enemyCount < 5)`. If `enemyCount` is 0, the left side is false, so C++ never evaluates the right side — avoiding a divide-by-zero that would otherwise happen if both sides always ran.

## Common pitfall (THE classic C++ bug)

```cpp
int health = 100;
if (health = 0) {   // BUG: single = is ASSIGNMENT, not comparison
    // ...
}
```
`=` assigns; `==` compares. `if (health = 0)` doesn't check anything — it **sets** `health` to 0, and then evaluates the *result of that assignment* (which is `0`, treated as `false` here) as the condition. Worse: `if (health = 5)` would assign 5 to health, and since 5 is nonzero it's treated as `true` — the branch silently runs, and you've also silently corrupted `health`'s value, every single time. **This compiles with no error or warning by default in C++.** Always double-check `==` in conditions.

A second pitfall: omitting `{}` on multi-line blocks. In C++, without braces, `if` only owns the *single next line* — indentation is cosmetic, not enforced:
```cpp
if (isAlive)
    TakeDamage();
    LogEvent();   // NOT part of the if! Runs unconditionally, despite the indentation implying otherwise.
```
Always use `{}` even for one-line bodies — it costs nothing and prevents this exact trap.

## Why it matters (production/interview)

- Every branch of gameplay logic is built from this: is the player alive, is the ability off cooldown, is the input valid. State machines are chains of conditionals under the hood.
- Interviewers commonly trace through short-circuit examples and ask "does this crash / what executes" — you need to be able to walk left-to-right and stop the moment the answer is determined.

## Edge case

- **Never compare floats with `==` directly.** `if (health == 0.0f)` is unreliable because floating-point math accumulates tiny rounding errors — `health` might be `0.0000001` instead of exactly `0.0f` after some computation, and the comparison silently fails. Use a small tolerance instead: `if (std::abs(health) < 0.0001f)`. (You'll use this pattern constantly once physics/damage math is involved.)
- **Order matters in else-if chains.** Testing thresholds from low-to-high instead of high-to-low silently breaks the logic — e.g. `if (health >= 0) return "Critical"; else if (health >= 75) return "Healthy";` — the second branch is **dead code**, because any health ≥75 already satisfied `health >= 0` and returned "Critical" first. Always order from most-specific/most-restrictive to least when ranges overlap.

## Worked example — health status classifier (traced line by line)

```cpp
int health = 50;

if (health >= 75) {
    // condition: is 50 >= 75? NO. Skip this block, move to else-if.
} else if (health >= 25) {
    // condition: is 50 >= 25? YES. This block runs.
    // status = "Wounded"
} else {
    // never reached — a branch already matched above.
}
```
Trace: `health = 50`. First check `50 >= 75` → false, skip. Second check `50 >= 25` → true, this branch runs, "Wounded" is chosen, and the `else` is skipped entirely — even though evaluating it wasn't attempted, C++ never even looks at it once an earlier branch matched. This is exactly the "only first match wins" mechanism from Core mechanism above, now traced concretely.
