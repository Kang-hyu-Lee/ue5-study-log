# Dot Product & Cross Product (2D)

## Dot Product

**Formula (2D):**
For A = (a1, a2) and B = (b1, b2):

    A · B = (a1 × b1) + (a2 × b2)

Result is a single number (a *scalar*), not a vector.

**Worked example, line by line:**
```
A = (3, 4)
B = (2, -1)

Step 1: multiply matching components
  a1 × b1 = 3 × 2  = 6
  a2 × b2 = 4 × -1 = -4

Step 2: add the results
  A · B = 6 + (-4) = 2
```

**The core mechanism (why multiply-and-add produces something meaningful):**
Each term `a1×b1` asks "do A and B agree on the x-direction?" If both are
positive (both go right) or both negative (both go left), the product is
positive — they agree. If one's positive and one's negative, they
disagree — the product goes negative. Same logic for the y-term. Adding
the two terms combines "agree on x" + "agree on y" into one number. Mostly
agreement → positive total. Mostly disagreement → negative total. Exactly
balanced (perpendicular) → zero.

**Geometric meaning:**
    A · B = |A| × |B| × cos(θ)

θ = angle between the two vectors. The formula above is not a separate
idea — it's the proof of why the agree/disagree pattern always produces a
value scaled by the angle between the vectors.

| Sign of A·B | Meaning                                  |
|-------------|-------------------------------------------|
| Positive    | vectors point roughly same way (θ < 90°) |
| Zero        | vectors are perpendicular (θ = 90°)      |
| Negative    | vectors point roughly opposite (θ > 90°) |

**Why it matters (production/UE5):** cheapest tool for "is this thing in
front of me" checks — AI vision cones, backface culling. 2 multiplies + 1
add instead of a trig call.

**Pitfall:** dot product → scalar ("how aligned"). Cross product → answers
a different question entirely (see below). If you expected a direction
and got one number, you may have wanted cross product instead.

**Edge case — where naive understanding breaks:** dot product magnitude
scales with vector *length*, not just angle. A large A·B does NOT mean
"strongly aligned" — it might just mean the vectors are long. To get ONLY
the angle relationship, normalize both vectors first (Day 5), then dot
them: normalize(A) · normalize(B) = cos(θ) directly, bounded [-1, 1].

---

## Cross Product (2D simplified/scalar form)

**Formula (2D):**
    A × B = (a1 × b2) − (a2 × b1)

True cross product is a 3D operation returning a perpendicular vector. The
2D version is really just the z-component of that 3D result (2D vectors
are 3D vectors with z = 0).

**Worked example, line by line:**
```
A = (3, 4)
B = (2, -1)

Step 1: cross-multiply
  a1 × b2 = 3 × -1 = -3
  a2 × b1 = 4 × 2  = 8

Step 2: subtract
  A × B = -3 - 8 = -11
```

**The core mechanism:** cross product encodes *which way you'd spin* to
go from A's direction to B's direction — not how aligned they are. Swap A
and B and the sign flips, because "rotate from A to B" and "rotate from B
to A" are opposite rotations.

**Geometric meaning:** sign tells you rotational direction.

| Sign of A×B | Meaning                                  |
|-------------|--------------------------------------------|
| Positive    | B is counter-clockwise from A             |
| Negative    | B is clockwise from A                     |
| Zero        | A and B are parallel (same or opposite)   |

**Why it matters:** steering direction (turn left or right to face
target), polygon winding order, side-of-line tests (physics/collision).

**Pitfall:** thinking the 2D cross product returns a vector like the 3D
version does — it doesn't. It's a single signed scalar (the z-component
only).

**Edge case:** A × B == 0 means "parallel" — but that could be SAME
direction or OPPOSITE direction. Cross product alone can't tell you
which. You need dot product's sign too (positive dot = same direction,
negative dot = opposite) to disambiguate.

---

## Dot vs. Cross — when to reach for each
- Dot product → "how aligned are these two directions" (use for facing
  checks, projections, cos(θ))
- Cross product → "which rotational side is B on relative to A" (use for
  turn direction, winding order, left/right-of-line tests)

**Common combined gamedev pattern:** turning a character to face a target
without spinning the long way around —
1. `cross(forward, toTarget)` → sign tells you rotate left or right
2. `dot(forward, toTarget)` → tells you how close you already are (near 1
   = already facing it, near -1 = facing directly away)
