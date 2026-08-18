# Day 15 — Matrix Multiplication & 2D Rotation

## 1. Recap: what a matrix is (from Day 10)
A matrix is a grid of numbers, `rows x cols`. In games it's used to represent a
*transform* — a packaged instruction for "move/rotate/scale everything that
touches this matrix." A 2x2 matrix can represent a 2D rotation or scale.
A vector like `(x, y)` can be thought of as a 2x1 matrix (2 rows, 1 column).

## 2. Matrix multiplication — the mechanism
Rule: you can only multiply matrix A (size `m x n`) by matrix B (size `n x p`)
if A's **column count** matches B's **row count**. Result is `m x p`.

```
[a b]   [e f]   [a*e+b*g   a*f+b*h]
[c d] * [g h] = [c*e+d*g   c*f+d*h]
```

Each output cell = **dot product of a row from A with a column from B**.
Row 1 of A, Col 1 of B → output[0][0]. Row 1 of A, Col 2 of B → output[0][1]. Etc.

### Worked example
```
A = [1 2]      B = [5 6]
    [3 4]          [7 8]

output[0][0] = (1*5) + (2*7) = 5 + 14 = 19
output[0][1] = (1*6) + (2*8) = 6 + 16 = 22
output[1][0] = (3*5) + (4*7) = 15 + 28 = 43
output[1][1] = (3*6) + (4*8) = 18 + 32 = 50

A * B = [19 22]
        [43 50]
```

### Pitfall — order matters
Matrix multiplication is **NOT commutative**: `A*B != B*A` in general. Try
swapping the example above — you'll get a different result. This is not a
quirk, it's structural (row-times-column only works one direction).

**Why this bites you in gamedev:** transform composition order changes the
outcome. `Rotate * Translate` (rotate around origin, then move) is a
completely different motion than `Translate * Rotate` (move away from
origin, then rotate — produces an orbit). UE5's `FTransform` composition
order is a real, recurring source of bugs for people who assume it's
commutative like regular multiplication.

## 3. 2D Rotation Matrix — where it comes from
From the unit circle (Day 3): a point at angle θ on the unit circle is
`(cos θ, sin θ)`. Rotating a vector `(x, y)` by angle θ counterclockwise is
defined as:

```
x' = x*cos(θ) - y*sin(θ)
y' = x*sin(θ) + y*cos(θ)
```

As a matrix (so it composes with other transforms via multiplication):

```
[cos θ  -sin θ]   [x]   [x cos θ - y sin θ]
[sin θ   cos θ] * [y] = [x sin θ + y cos θ]
```

### Worked example — rotate (1, 0) by 90°
θ = 90°, cos(90°) = 0, sin(90°) = 1.

```
x' = 1*0 - 0*1 = 0
y' = 1*1 + 0*0 = 1
```

Result: `(1, 0) -> (0, 1)`. Check it against a clock face: pointing right,
rotated 90° counterclockwise, now points up. Matches.

### Pitfall — degrees vs radians
`cos`/`sin` in C++ (`<cmath>`) take **radians**, not degrees. `90°` must be
converted: `radians = degrees * (PI / 180.0f)`. Forgetting this is one of
the most common silent bugs in gamedev math code — it doesn't crash, it
just rotates by the wrong (usually tiny) amount, because e.g. `cos(90.0f)`
in C++ means 90 *radians* (~5157°), not 90 degrees.

## 4. Edge case — this only works in 2D as-is
A 2x2 rotation matrix can rotate a 2D vector, but it **cannot translate**
(move) anything — rotation matrices only rotate around the origin. To
combine rotation + translation into one matrix (needed for real transform
chains — object rotates around its own pivot, then moves in the world), you
need **homogeneous coordinates**: pad the vector to `(x, y, 1)` and use a
3x3 matrix. This is exactly what `FTransform`/`FMatrix` do internally in
UE5 — flagging it now so "why is the matrix 4x4 for 3D objects, not 3x3"
doesn't look mysterious later (extra row/column encodes translation +
perspective).

## 5. Why it matters
- Every object transform in UE5 (`FTransform`) is fundamentally rotation +
  scale + translation, composed via matrix math under the hood.
- Parent-child relationships (attach a weapon to a hand socket) are matrix
  multiplication chains: child's world transform = child's local transform
  * parent's world transform.
- Interview-relevant: "explain how a rotation matrix works" and "why isn't
  matrix multiplication commutative" are real questions for gameplay/engine
  programming roles.
