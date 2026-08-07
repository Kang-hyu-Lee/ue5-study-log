# Day 3 Math Solutions — Logs & Trig

## Logs

**1. `log2(32)`**
`2^5 = 32` (2→4→8→16→32, five doublings). So `log2(32) = 5`.

**2. Max array size for 5 comparisons**
This is the inverse of the binary search argument: 5 halving-steps means `2^5 = 32`. Max array size = **32**.

**3. Change of base**
`log2(x) = ln(x) / ln(2)`. Directly applying the formula: base is 2, so divide by `ln(2)` instead of `ln(base)` in general.

**4. Why `log2(1) = 0`**
Because `2^0 = 1` — zero doublings are needed to go from 1 to 1; you're already there, so the "how many halvings to shrink to 1" count is zero.

## Trig

**5. Radian conversion**
`90° × (π/180) = π/2` radians.
`270° × (π/180) = 3π/2` radians.

**6. Unit circle table**

| Angle | cos | sin |
|---|---|---|
| 0°   | 1  | 0  |
| 90°  | 0  | 1  |
| 180° | -1 | 0  |
| 270° | 0  | -1 |

Reasoning: at 0° you're at point (1,0) on the circle (start position). At 90° (quarter turn) you're at the top, (0,1). At 180° (half turn) you're at (-1,0). At 270° (three-quarter turn) you're at the bottom, (0,-1). Read cos as the x-coordinate, sin as the y-coordinate directly off those points.

**7. The `std::cos(45)` bug**
`std::cos` expects **radians**, not degrees. The literal `45` is interpreted as 45 *radians* — that's more than 7 full rotations (`45 / (2π) ≈ 7.16`). The function isn't broken and won't error; it just silently computes the cosine of a wildly different angle than intended (~45 radians reduces to roughly 25.8° after stripping off full rotations — not the 45° the programmer meant). Fix: `std::cos(45.0 * M_PI / 180.0)` (or a helper `DegreesToRadians()` function, which is exactly what UE5 provides — `FMath::DegreesToRadians()`).

**8. Symmetry of cos/sin under negation**
A negative angle `-θ` means "walk clockwise by θ instead of counter-clockwise." Geometrically, this reflects your position across the x-axis: the x-coordinate (cos) stays exactly the same, but the y-coordinate (sin) flips sign. That's the whole proof — no algebra needed, just "which way did I walk and what does that do to my (x,y) position."
