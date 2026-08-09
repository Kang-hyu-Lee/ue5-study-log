# Vectors — Solutions

**1.** |A| = sqrt(5² + 12²) = sqrt(25+144) = sqrt(169) = **13**
(This is the 5-12-13 Pythagorean triple — same family as the 3-4-5 you saw in the concept file.)

**2.** Â = (5/13, 12/13) ≈ **(0.385, 0.923)**
Divide each component by the magnitude found in Q1. Sanity check: 0.385² + 0.923² ≈ 1.0 — a unit vector always has magnitude 1.

**3.** A + B = (2+(-1), 3+4) = **(1, 7)**

**4.** Direction = Target − Current = (13−10, 14−10) = **(3, 4)**
Using Target − Current (not the reverse) gives a vector that points FROM current TOWARD target — the order matters.

**5.** |Direction| = sqrt(3² + 4²) = **5**
This is the *distance* to the target — same magnitude formula, different meaning depending on what the vector represents. Gameplay use: "am I close enough to the target to stop moving / attack / trigger something?"

**6.** Â = (0/0, 0/0) → division by zero → **undefined (NaN) or a crash**, depending on the language/engine's handling. Mechanically: normalization divides every component by the magnitude, and magnitude of (0,0) is 0 — you can never divide by zero safely. This is why idle/no-input frames need an explicit zero-check before normalizing.
