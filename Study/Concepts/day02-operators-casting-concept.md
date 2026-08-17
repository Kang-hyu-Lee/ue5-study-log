# Operators, Expressions, and Type Casting

## What's an "expression"?
An expression is anything that evaluates to a value. `5 + 3` is an
expression (evaluates to `8`). `x` alone is also an expression (evaluates
to whatever x currently holds). Operators are the symbols that combine
values inside an expression.

## Arithmetic Operators
| Operator | Meaning | Example | Result |
|---|---|---|---|
| `+` | addition | `5 + 2` | `7` |
| `-` | subtraction | `5 - 2` | `3` |
| `*` | multiplication | `5 * 2` | `10` |
| `/` | division | `5 / 2` | `2` ← gotcha, see below |
| `%` | modulo (remainder) | `5 % 2` | `1` |

These follow the SAME order of operations (PEMDAS) you already know from
Day 1 math — C++ doesn't invent new rules here, it reuses the ones you
have.

## Assignment Operators (shortcuts for "update and reassign")
| Operator | Meaning | Same as |
|---|---|---|
| `=` | assign | — |
| `+=` | add then assign | `x = x + value` |
| `-=` | subtract then assign | `x = x - value` |
| `*=` | multiply then assign | `x = x * value` |
| `/=` | divide then assign | `x = x / value` |

`=` (one equals sign) means "store this value into this variable." It is
NOT the math equals sign. `==` (two equals signs) means "are these equal?"
and is a comparison — you'll use it starting Day 3 with conditionals.

## Comparison Operators (produce a `bool` — true or false)
| Operator | Meaning |
|---|---|
| `==` | equal to |
| `!=` | not equal to |
| `<` `>` | less than / greater than |
| `<=` `>=` | less/greater than or equal to |

You won't DO anything with these yet (that's `if/else` on Day 3), but you
need to recognize `5 == 5` evaluates to `true` as a concept now.

## Core Mechanism: Why Integer Division Happens At All
C++ decides HOW to do division based on the types of the operands
BEFORE it knows what you're storing the result into. If both sides of
`/` are `int`, C++ performs integer division (result stays a whole
number, decimal truncated) — this decision is made at the moment of the
operation, not at the moment of assignment. This is why casting has to
happen INSIDE the expression, not after.

## The Integer Division Trap (worked example, line by line)

```cpp
int a = 7;
int b = 2;
double result = a / b;
cout << result;
```

Line by line:
1. `int a = 7;` → declares an int variable, stores 7.
2. `int b = 2;` → declares an int variable, stores 2.
3. `double result = a / b;` → THIS is the trap. `a / b` happens FIRST,
   before it ever touches `result`. Since both `a` and `b` are `int`,
   C++ does **integer division**: it drops the decimal entirely.
   `7 / 2` mathematically is `3.5`, but integer division truncates
   (chops, doesn't round) to `3`. THEN that `3` gets converted to a
   `double` and stored — so `result` becomes `3.0`, not `3.5`.
4. `cout << result;` → prints `3`, which is almost certainly not what
   you wanted.

## Type Casting — the fix

**Implicit casting** (automatic, C++ does it silently): assigning an `int`
to a `double` variable converts it for you — you saw this above where `3`
became `3.0`. Implicit casting is why the trap above is sneaky: no error,
no warning, just a silently wrong answer.

**Explicit casting** (you tell C++ exactly what to convert, on purpose):

```cpp
double result2 = static_cast<double>(a) / b;
cout << result2;
```

Line by line:
1. `static_cast<double>(a)` → converts `a` (currently `7`, an `int`) into
   `7.0`, a `double`, BEFORE the division happens.
2. `7.0 / b` → now one side is a `double`, so C++ promotes the WHOLE
   division to happen in decimal math: `7.0 / 2` = `3.5`.
3. `result2` correctly stores `3.5`.
4. `cout << result2;` → prints `3.5`.

**Rule of thumb:** if you're dividing two `int`s and you want a decimal
answer, cast at least ONE of them to `double` BEFORE the division, not
after.

## Common Pitfall / Misconception
Beginners assume casting the RESULT fixes it — e.g. writing
`static_cast<double>(a / b)`. This does NOT work: `a / b` has already
been computed as integer division (truncated to `3`) by the time the
cast runs on the outside. Casting the already-truncated `3` just gives
you `3.0`, not `3.5`. The cast must go on an OPERAND (`a` or `b`)
**before** the `/` runs, not wrapped around the whole expression after.

## Edge Case Where the Naive Understanding Breaks
Negative number integer division doesn't just "round down" the way you
might assume from math class. `-7 / 2` in C++ truncates TOWARD ZERO, not
toward negative infinity — so `-7 / 2` gives `-3` (not `-4`, which is
what flooring would give). If your gamedev code ever divides a negative
value (e.g. a damage/knockback direction calculation) assuming
"integer division always rounds down," you'll get an off-by-one bug that
only shows up with negative inputs — easy to miss in testing if you only
test positive cases.

## Why This Matters for UE5
Damage calculations, health percentages, movement speed multipliers —
almost all of these involve division. An uncaught integer-division bug
(e.g. computing `currentHealth / maxHealth` as a health-bar percentage
where both are `int`) is one of the most common silent gameplay bugs
beginners ship. It won't crash — it'll just always show 0% or 100% health
bars and you'll have no idea why.
