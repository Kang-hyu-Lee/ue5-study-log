# Vectors — Introduction

## Core Mechanism
A vector = magnitude (length) + direction. It is NOT a position by itself — a "position vector" (arrow from the origin to a point) is just one common use of a vector.

Representation: ordered components.
- 2D: (x, y)
- 3D: (x, y, z) — this is exactly what UE5's `FVector` stores

### Worked Example
A character has a movement input vector **A = (3, 4)** — right 3 units, up 4 units (a displacement, not a point). A knockback force vector **B = (1, -2)** gets added.

**Step 1 — Addition (component-wise):**
A + B = (3+1, 4+(-2)) = **(4, 2)**
Add matching components. Same axis, same slot. No cross-terms.

**Step 2 — Magnitude of A:**
|A| = sqrt(x² + y²) = sqrt(3² + 4²) = sqrt(9+16) = sqrt(25) = **5**
This IS the Pythagorean theorem from Day 1 — a vector's components are the legs of a right triangle; magnitude is the hypotenuse.

**Step 3 — Direction (unit vector / normalization):**
Â = (x/|A|, y/|A|) = (3/5, 4/5) = **(0.6, 0.8)**
Dividing every component by the magnitude strips out "how far" and keeps only "which way." A normalized vector's magnitude is always exactly 1.

## Pitfall
Vectors and points are stored identically in code (`FVector`), so nothing stops you from writing nonsense: adding two *positions* together gives a meaningless point. But subtracting two positions is legitimate and extremely common: `TargetPos - MyPos` = the direction vector pointing at the target. Same operation, correct only in one direction — know which one you're holding.

## Production Relevance
UE5 uses `FVector` for position, velocity, force, direction, and surface normals — one type, different meaning depending on context. Misreading which one you're holding (e.g. treating a velocity as a position) is a real, common bug class.

## Edge Case
Zero vector (0,0): magnitude = 0. Normalizing divides by magnitude → division by zero → NaN or crash. Real scenario: player gives no input this frame (idle) → their input vector is (0,0). Always guard before normalizing:
```
if (vector_length > 0) { normalize(); }
```
