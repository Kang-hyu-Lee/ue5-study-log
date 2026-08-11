# Solutions — Dot Product & Cross Product

## 1. A = (2, 3), B = (4, 1)
    A · B = (2×4) + (3×1) = 8 + 3 = 11

## 2. A = (5, 0), B = (0, -5)
    A · B = (5×0) + (0×-5) = 0 + 0 = 0
Result is exactly zero → A and B are perpendicular (90° apart). Sanity
check: A points right, B points straight down — that IS 90°.

## 3. A = (-2, -2), B = (2, 2)
    A · B = (-2×2) + (-2×2) = -4 + -4 = -8
Negative → A and B point in roughly opposite directions. Sanity check: A
points down-left, B points up-right — directly opposite. Matches.

## 4. A = (2, 3), B = (4, 1)
    A × B = (2×1) - (3×4) = 2 - 12 = -10
Negative → rotating from A to B is clockwise.

## 5. B × A (same vectors, swapped)
    B × A = (4×3) - (1×2) = 12 - 2 = 10
Sign flipped from #4 (-10 → 10). This is expected: cross product encodes
"which way to rotate from the FIRST vector to the SECOND." Swapping which
vector is first reverses the rotation direction, so the sign always
flips when you swap operands.

## 6. A = (0, 5), B = (5, 5)
    A · B = (0×5) + (5×5) = 0 + 25 = 25   → positive, within 90° of each other
    A × B = (0×5) - (5×5) = 0 - 25 = -25  → negative, rotate CLOCKWISE from A to B
Sanity check: A points straight up (90°), B points up-right (45°). Going
from 90° down to 45° is clockwise, and 45° apart is well under 90° —
both results match the picture.

## 7. Applied — forward = (1, 0), toTarget = (0, -1)
    cross(forward, toTarget) = (1×-1) - (0×0) = -1 - 0 = -1   → negative → clockwise
    dot(forward, toTarget)   = (1×0) + (0×-1) = 0 + 0 = 0     → zero → perpendicular

The character should turn RIGHT (clockwise) to face the target. The dot
product being exactly zero means the character is currently facing
perpendicular to the target — not toward it, not away from it, a 90°
turn is needed either way you go, but the cross product's sign tells you
the shorter direction is clockwise.
