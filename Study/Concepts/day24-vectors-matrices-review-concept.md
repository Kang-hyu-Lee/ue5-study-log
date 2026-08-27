# Day 24 — Vectors + Matrices Combined Review

This is application review, not new theory. You've seen every piece here before
(Day 5 vectors, Day 8 dot/cross, Day 10 matrices, Day 15 rotation). Today's exercises
push toward *slower application thinking* rather than fast procedural recall — per
the practice-sheet split rule (topic had a prior week → harder application, not volume).

---

## Vectors — recap

- **Magnitude**: `|V| = sqrt(x*x + y*y)` (2D) or `sqrt(x*x+y*y+z*z)` (3D). This is
  Pythagorean theorem generalized — it's the straight-line length of the vector.
- **Unit vector (normalization)**: `V / |V|`. Direction only, length forced to 1.
  **Pitfall**: normalizing a zero-length vector divides by zero — undefined behavior,
  not a crash you can predict. UE5's `FVector::Normalize()` returns `false` and leaves
  the vector unchanged if it's too close to zero, specifically to guard this.
- **Addition/subtraction**: component-wise. `A - B` gives the vector *from B to A*
  (memorize this direction — it's the #1 source of "why is my movement backwards" bugs).
- **Dot product**: `A·B = Ax*Bx + Ay*By (+ Az*Bz)` = `|A||B|cos(θ)`.
  - Mechanism: measures how much two vectors point the *same direction*. Positive =
    same-ish direction, 0 = perpendicular, negative = opposite-ish.
  - Production use: is this enemy in front of me? `Dot(Forward, ToEnemy) > 0`.
  - Pitfall: people forget the result depends on vector *length*, not just angle —
    if you need the angle itself, you must divide by `|A||B|` before `acos()`.
- **Cross product**: in 3D, `A×B` gives a vector *perpendicular* to both, magnitude
  = area of the parallelogram they form, direction by the right-hand rule.
  - 2D "cross product" is really just the z-component of the 3D cross — a scalar,
    `Ax*By - Ay*Bx`. Sign tells you if B is clockwise or counter-clockwise from A.
  - Pitfall: cross product is **not commutative** — `A×B = -(B×A)`. Order matters.
  - Edge case: parallel (or anti-parallel) vectors have zero cross product — no
    unique perpendicular direction exists, so "which way do I turn" logic breaks
    exactly when a target is directly ahead or directly behind.

## Matrices — recap

- A matrix here = a table of numbers that represents a **transform** (rotate, scale,
  translate) you can apply to a vector via multiplication.
- **Matrix multiplication**: row of the left matrix dotted with column of the right.
  Result `[i][j] = sum over k of Left[i][k] * Right[k][j]`.
  - Pitfall: matrix multiplication is **not commutative**. `Rotate * Translate` ≠
    `Translate * Rotate` — rotating then moving lands you somewhere different than
    moving then rotating. This is a constant source of UE5 transform-order bugs.
- **2D rotation matrix** (rotate by angle θ):
  ```
  | cosθ  -sinθ |   | x |
  | sinθ   cosθ | * | y |
  ```
  Multiplying this by a point vector gives the rotated point.
- **Homogeneous coordinates**: why we pad a 2D vector to 3 components (x, y, 1)
  instead of 2. A pure matrix multiply is a *linear* map — it can rotate and scale,
  but it can't add a constant offset (translation), because `M * 0 = 0` always,
  and translation needs `0 -> some offset`. Padding with a constant `1` and adding
  a translation row/column smuggles addition through multiplication:
  ```
  | 1  0  Tx |   | x |     | x + Tx |
  | 0  1  Ty | * | y |  =  | y + Ty |
  | 0  0  1  |   | 1 |     |   1    |
  ```
  3D transforms use 4×4 for the same reason. This is *why* `FTransform` in UE5
  isn't just a rotation matrix — translation genuinely needs the extra dimension.

## Worked example — rotate then translate a point

Point `P = (2, 0)`, rotate 90° CCW, then translate by `(3, 1)`.

1. Rotation matrix at θ=90°: `cos90=0, sin90=1` → `[[0,-1],[1,0]]`
2. Rotate: `x' = 0*2 + -1*0 = 0`, `y' = 1*2 + 0*0 = 2` → `(0, 2)`
3. Translate: `(0+3, 2+1) = (3, 3)`

If you'd translated *first* then rotated, you'd get a different final point — proving
the non-commutativity pitfall above with real numbers, not just the rule.

## Why it matters / interview angle

- "Why can't you just add a translation into a 2x2 rotation matrix?" → homogeneous
  coordinates answer, verbatim what's above.
- "What does the dot product of two normalized vectors give you directly?" → `cos(θ)`
  between them, no need to call `acos` unless you need the actual angle value.
- UE5 relevance: `FVector::DotProduct`, `FVector::CrossProduct`, `FMatrix`,
  `FTransform` (which is translation + rotation + scale bundled, order-aware).
