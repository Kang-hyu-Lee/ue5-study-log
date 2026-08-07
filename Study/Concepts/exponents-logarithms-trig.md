# Day 3 Math — Exponents & Logarithms, Trig from the Unit Circle

## Part A: Exponents & Logarithms

### Core mechanism
- Exponentiation: `a^b` = multiply `a` by itself `b` times. `2^4 = 2*2*2*2 = 16`.
- A logarithm is the *inverse question*: "what power do I raise the base to, to get this number?"
  - `log_b(x) = y` means `b^y = x`.
  - `log2(16) = 4` because `2^4 = 16`.
- The base you'll use constantly in CS: **log base 2**, because most "divide the problem in half" algorithms (binary search, balanced trees) halve their input each step.
- `e` (≈2.71828...) is a special irrational constant that shows up as the base of continuous/natural growth. You don't need calculus to use it here — just know `ln(x)` means `log_e(x)`.
- **Change of base formula** (lets you compute any log with any calculator/library): `log_b(x) = ln(x) / ln(b)`. C++'s `<cmath>` gives you `std::log` (natural log, base e) and `std::log2` (base 2) directly — you rarely need change-of-base in code, but you need it to *reason* about logs on paper.

### Worked example — why binary search is O(log n)
Binary search on a sorted array of 16 elements, looking for a value:
1. Check the middle. Wrong? Eliminate half. **16 → 8** remaining.
2. Check the new middle. Wrong? Eliminate half again. **8 → 4**.
3. **4 → 2**.
4. **2 → 1**. Found it or confirmed absent.

That's **4 steps** to go from 16 elements down to 1. Notice: `2^4 = 16`, equivalently `log2(16) = 4`. The number of halving-steps to shrink `n` down to 1 *is* `log2(n)`. That's not a metaphor — it's the literal definition of a logarithm applied to this exact process. This is why you'll see "O(log n)" and should immediately think "halving process," not just memorize the label.

### Common pitfall
- Thinking a "slow-sounding" name like logarithm means slow *growth*. It's the opposite — log n is one of the best complexities you can get (better than linear, much better than quadratic). The confusion comes from log being an unfamiliar function; the actual curve grows extremely slowly.
- Mixing up the order: `log_b(x)` is NOT the same as `x^b`. `log2(8) = 3`, not `8^2 = 64`. Keep straight which number is the base and which is the "answer" you're taking the log of.
- `log(0)` and `log` of a negative number are **undefined** in the reals — there's no power you can raise a positive base to that gives 0 or a negative result. If your code ever computes `log` of something that *could* be ≤0, that's a bug waiting to happen (silent NaN or domain error).

### Why it matters (production/interview)
- Any interview question about binary search, balanced BSTs, or heaps expects you to justify "why is this O(log n)" using the halving argument above, not just cite it.
- Big-O with log terms (`O(n log n)` — most efficient sorts) will come up constantly once we hit sorting in Phase 2.

### Edge case
- `log2(1) = 0` — zero halving steps needed, you're already at one element. Don't be surprised by a "zero" answer; it's correct, not a bug.
- Logs grow *so* slowly that `log2(1,000,000) ≈ 20`. An algorithm that's O(log n) barely slows down even as input size explodes — this is the whole reason it's prized.

---

## Part B: Trig from the Unit Circle

*(You already have SOH-CAH-TOA and right-triangle trig from Day 2. This generalizes it.)*

### Core mechanism
- The **unit circle**: a circle of radius 1, centered at the origin (0,0).
- Pick an angle `θ`, measured **counter-clockwise** starting from the positive x-axis.
- Walk out along that angle to where you hit the circle. That point's coordinates ARE `(cos θ, sin θ)` — by definition. Not "you compute cos and sin from a triangle and it happens to land there" — the unit circle definition makes this the actual definition, and it works for *any* angle, not just the 0–90° range a right triangle limits you to.
- **Radians**: the "natural" unit for angles, defined as arc length / radius. A full circle = `2π` radians = 360°. Half circle = `π` radians = 180°.
  - Conversion: `radians = degrees × (π / 180)`, `degrees = radians × (180 / π)`.

### Worked example
Find `cos(180°)` and `sin(180°)`:
1. Convert to radians: `180° × (π/180) = π` radians.
2. On the unit circle, walking 180° (half the circle) counter-clockwise from the positive x-axis lands you at the point `(-1, 0)` — directly opposite your start.
3. By definition, that point is `(cos(π), sin(π))`.
4. So `cos(180°) = -1`, `sin(180°) = 0`. No triangle needed — just the geometry of where you land on the circle.

### Common pitfall — the one that WILL bite you in code
- **C++'s `std::sin`/`std::cos` (and UE5's equivalents) take radians, not degrees.** If you pass in `45` expecting "45 degrees," the function silently interprets it as 45 *radians* (over 7 full rotations) and gives you a completely wrong, but valid-looking, number. No compiler error, no crash — just silently wrong physics/rotation. Always convert degrees → radians first.

### Why it matters (production/interview)
- Every rotation, facing direction, and camera calculation in UE5 is built on this. `GetActorForwardVector()` internally is doing exactly this cos/sin-from-angle computation.
- "Convert degrees to radians before calling a trig function" is a real, common bug class — worth being able to state confidently in an interview.

### Edge case
- **Periodicity**: angles wrap every `2π` (360°). `cos(θ) = cos(θ + 2π) = cos(θ + 4π)...` — rotating an extra full circle lands you in the same spot. Your code might compute an angle of 720° after some accumulation and it's mathematically identical to 0°, not some huge new position.
- **Quadrant signs**: `sin`/`cos` flip sign depending which quadrant of the circle you're in (e.g. both negative in the third quadrant, bottom-left). Don't assume a "reasonable-looking" positive number — check the quadrant when reasoning by hand.
- Symmetry: `cos(-θ) = cos(θ)` (mirrored across the x-axis, x-coordinate unchanged) but `sin(-θ) = -sin(θ)` (y flips). This is why cosine is called an "even" function and sine an "odd" function — you'll see this vocabulary again.
