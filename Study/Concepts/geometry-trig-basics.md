# Day 1 (extension) — Geometry & Trigonometry Basics

You said algebra/PEMDAS is solid but geometry/trig is where things break down. This starts from zero on that side — don't skip sections even if a piece looks familiar.

## 1. Angles
An **angle** measures rotation between two lines meeting at a point, in **degrees** (°). Full circle = 360°.
- **Right angle** = exactly 90° (a perfect corner, like the corner of a book).
- **Acute angle** = less than 90°.
- **Obtuse angle** = more than 90° (but less than 180°).

## 2. Triangles — the core object
A **triangle** = 3 sides, 3 angles, angles always sum to **180°**.

A **right triangle** = one triangle where one of the 3 angles is exactly 90°. This is the single most important shape in this whole subject — vectors, rotation, and UE5's transform math all reduce to right-triangle relationships eventually.

In a right triangle, the sides have names relative to the 90° angle:
- **Hypotenuse** — the longest side, always opposite the 90° angle (never adjacent to it).
- The other two sides are called **legs**.

## 3. Pythagorean Theorem
For any right triangle, if `a` and `b` are the two legs and `c` is the hypotenuse:
```
a² + b² = c²
```
This lets you find any one side if you know the other two. It ONLY works on right triangles.

### Worked example — Pythagorean theorem
A right triangle has legs of length 3 and 4. Find the hypotenuse.
```
a² + b² = c²
3² + 4² = c²        # substitute known values
9 + 16 = c²          # 3²=9, 4²=16 (exponents, from yesterday's PEMDAS)
25 = c²              # addition
c = √25              # take the square root of both sides to undo the ²
c = 5
```
**Answer: hypotenuse = 5**

(Square root, `√`, is the operation that undoes squaring — `√25 = 5` because `5² = 25`. If you ever get a non-whole-number result like `√20`, that's normal; you'd either leave it as `√20` or approximate ≈ 4.47.)

## 4. Trigonometry — relating angles to side ratios
Trig starts from one question: **in a right triangle, if I know one non-90° angle, what does that tell me about the ratio between the sides?** The answer is fixed — every right triangle with the same angle has the same side ratios, regardless of size. That fixed relationship is what sine, cosine, and tangent describe.

Pick one of the non-90° angles and call it **θ** (theta — the standard letter used for "an angle" in math). Relative to θ, the two legs get new names:
- **Opposite** — the leg NOT touching angle θ.
- **Adjacent** — the leg that IS touching angle θ (but isn't the hypotenuse).
- **Hypotenuse** — same as before, the longest side, opposite the 90° angle.

(Which leg is "opposite" vs "adjacent" depends on WHICH angle you pick as θ — it changes if you pick the other non-90° angle instead.)

### SOH-CAH-TOA (memorize this — it's the whole toolkit for now)
| Ratio | Definition | Mnemonic |
|---|---|---|
| **sin(θ)** | Opposite ÷ Hypotenuse | **S**in = **O**pposite/**H**ypotenuse |
| **cos(θ)** | Adjacent ÷ Hypotenuse | **C**os = **A**djacent/**H**ypotenuse |
| **tan(θ)** | Opposite ÷ Adjacent | **T**an = **O**pposite/**A**djacent |

`sin`, `cos`, `tan` are **functions** — you feed them an angle, they give back a ratio (a plain number, no units). Your calculator/code has these built in; you don't compute them by hand from geometry.

### Worked example — using SOH-CAH-TOA
Right triangle: angle θ = 30°, hypotenuse = 10. Find the length of the side opposite θ.

Step 1 — Which ratio involves Opposite and Hypotenuse (the two things I have/want)? That's **sine** (SOH: Opposite/Hypotenuse).
```
sin(θ) = Opposite / Hypotenuse
sin(30°) = Opposite / 10
```
Step 2 — Look up (or calculator) `sin(30°) = 0.5`.
```
0.5 = Opposite / 10
```
Step 3 — Solve for Opposite (multiply both sides by 10 — this is algebra, from yesterday, applied to a trig equation):
```
Opposite = 0.5 × 10 = 5
```
**Answer: the opposite side = 5**

Notice the whole problem was: identify which ratio fits the two things you have/want → plug in → solve algebraically. That pattern repeats for every SOH-CAH-TOA problem.

**Common pitfall.** The #1 mistake at this stage: mislabeling which leg is "opposite" vs "adjacent" when the angle θ isn't obviously marked. Fix: always find the 90° angle first, then find θ — the side touching *both* θ and the right angle is adjacent; the side touching neither is opposite. Get this backwards and you'll use the wrong ratio (e.g. tan instead of the reciprocal) and get a nonsense answer that looks plausible.

**Edge case — SOH-CAH-TOA only works on right triangles.** If a triangle has no 90° angle, none of these ratios apply directly — you'd need the Law of Sines or Law of Cosines instead (not covered yet, flagged for later). Trying to force sin/cos/tan onto a non-right triangle is a common surface-level error once triangles stop being "obviously right-angled" in a problem or diagram.

## 5. Why this matters for UE5
- Rotating an object, aiming, calculating field-of-view cones, camera angles — all direct SOH-CAH-TOA / right-triangle applications.
- Vectors (next up in the roadmap) are built FROM this: a vector's x and y components are literally the "adjacent" and "opposite" legs of a right triangle formed with the angle it points at.
- The **unit circle** (coming later in the roadmap) is just this same sin/cos relationship, but for a triangle whose hypotenuse is always exactly 1 — makes the ratios directly equal to coordinates. You now have the prerequisite for that.

## 6. Terms introduced here (reference)
- **Degree (°)**: unit of angle measurement, 360° = full circle.
- **Right triangle**: a triangle with one 90° angle.
- **Hypotenuse**: longest side of a right triangle, opposite the 90° angle.
- **Leg**: either of the two shorter sides of a right triangle.
- **θ (theta)**: standard placeholder letter for "an angle."
- **Opposite / Adjacent**: leg names relative to a chosen angle θ (not fixed — depend on which angle you pick).
- **sin / cos / tan**: functions mapping an angle to a fixed side ratio.
- **√ (square root)**: the operation that undoes squaring.
