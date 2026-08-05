# Day 1 — Algebra Basics & Order of Operations

## 1. What is a variable (in math)?
A **variable** is a letter (x, y, n, etc.) that stands in for a number — either one we don't know yet, or one that can change. `x = 5` means "the variable x currently holds the value 5."

This is the *math* meaning of "variable." Later today, in the C++ section, you'll meet the *programming* meaning — related, but not identical (a programming variable is a labeled box in memory). Keep these separate in your head for now; we'll connect them explicitly.

## 2. Order of Operations (PEMDAS)
When an expression has multiple operations, you can't just go left to right — there's a fixed priority order:

| Priority | Operation | Symbol(s) |
|---|---|---|
| 1 (highest) | Parentheses | `( )` |
| 2 | Exponents | `^` or `²`, `³` |
| 3 | Multiplication & Division | `×` `*` `÷` `/` — equal priority, left to right |
| 4 (lowest) | Addition & Subtraction | `+` `-` — equal priority, left to right |

Acronym: **PEMDAS** — Parentheses, Exponents, Multiplication/Division, Addition/Subtraction.

Key subtlety people miss: Multiplication and Division are the *same priority tier* — you do them left to right in the order they appear, not "all multiplication then all division." Same for Addition/Subtraction.

## 3. Worked Example (full step-by-step)

Compute: **3 + 4 × (2 + 1)² − 5**

**Step 1 — Parentheses first.** Find `(2 + 1)` and resolve it.
```
3 + 4 × (2 + 1)² − 5
= 3 + 4 × (3)² − 5
```

**Step 2 — Exponents next.** `(3)²` means 3 × 3 = 9.
```
= 3 + 4 × 9 − 5
```

**Step 3 — Multiplication/Division, left to right.** Only one multiplication here: `4 × 9 = 36`.
```
= 3 + 36 − 5
```

**Step 4 — Addition/Subtraction, left to right.** Read left to right: `3 + 36` first, then subtract 5.
```
= 39 − 5
= 34
```

**Final answer: 34**

Common mistake to watch for: doing `3 + 4` first because it's on the left, ignoring that multiplication outranks addition. If you did that you'd wrongly get `7 × 9 − 5 = 58`. The rule isn't "left to right for everything" — it's "left to right *within the same priority tier*."

## 4. Why this matters for UE5
Every piece of game math you'll do later — vector length, dot products, transform matrices — is just nested arithmetic expressions like the one above, but with variables (x, y, z components) instead of plain numbers. If you can't reliably evaluate `3 + 4 × (2 + 1)² − 5` by hand, you won't be able to sanity-check a vector math formula when something looks wrong in-engine. This is the boring foundation under the fun stuff.

## 5. Terms introduced here (reference)
- **Expression**: a combination of numbers/variables and operations, e.g. `3 + 4 × 9`, that evaluates to a single value.
- **Operator**: a symbol that performs an operation (`+`, `-`, `×`, `÷`, `^`).
- **Operand**: the value(s) an operator acts on (in `3 + 4`, both 3 and 4 are operands).
