# Day 22 — Rate of Change Intuition (NOT Calculus)

This is algebra, not calculus. No derivatives, no limits. Just slope — but framed
the way you'll actually use it in a game engine.

## 1. Core Mechanism

Rate of change = how much one quantity changes per unit change in another.

**Average rate of change formula (this is just slope):**
```
rate = (y2 - y1) / (x2 - x1) = Δy / Δx
```
`Δ` (delta) means "change in." `Δy` = "final y minus initial y." Nothing more exotic
than that — you've used subtraction since Day 1, this is just naming the pattern.

**Physics application — velocity:**
```
velocity = Δposition / Δtime
```
If an object moves from x=2m to x=10m over 4 seconds:
```
velocity = (10 - 2) / 4 = 8 / 4 = 2 m/s
```
That's it. Velocity IS a rate of change — the rate at which position changes.

## 2. Worked Example — Frame-by-Frame

A UE5 game runs at ~60 frames/second. Each frame, the engine calls `Tick()` and
passes a `DeltaTime` — the actual seconds elapsed since the last frame (not always
exactly 1/60, since frames aren't perfectly uniform).

Say an object has `Velocity = 5.0` (units/sec) and `DeltaTime = 0.016` (about 1/60 sec):
```
NewPosition = OldPosition + Velocity * DeltaTime
NewPosition = OldPosition + 5.0 * 0.016
NewPosition = OldPosition + 0.08
```
This single line — `position += velocity * deltaTime` — is rate-of-change algebra
running every frame of every game you've played. You are not learning a toy concept;
this is the actual mechanism.

## 3. Common Pitfall

**Average rate of change over an interval ≠ instantaneous rate at a single point.**

`Δposition / Δtime` over a 4-second interval gives you the *average* velocity across
those 4 seconds — it hides any speeding up/slowing down that happened inside the
interval. True *instantaneous* velocity (velocity at one exact instant) is what
calculus derivatives compute (a limit as Δtime → 0). You're deliberately not doing
that yet — Phase 1 keeps you at the algebraic/discrete level, which is genuinely
what games use.

**Why this matters concretely:** a game doesn't compute continuous instantaneous
velocity — it approximates it using small discrete `DeltaTime` steps. The smaller
the tick interval, the closer the approximation gets to "true" instantaneous motion.

## 4. Why It Matters in Production

- Every `Tick(float DeltaTime)` you'll write in UE5 uses this exact pattern.
- **Framerate independence**: multiplying by `DeltaTime` (instead of a fixed number)
  is *why* a game moves an object the same real-world distance per second whether
  it's running at 30fps or 144fps. Without `DeltaTime`, a low-end machine's player
  would move slower than a high-end machine's — same input, different outcome. This
  is a real interview question: "why do we multiply by DeltaTime instead of a constant?"

## 5. Edge Case Where the Naive View Breaks

**Very small or zero `Δtime`.** If a frame is paused, hitches, or `DeltaTime` is
computed as `0` (e.g. first frame before any time has elapsed), any formula that
*divides* by `Δtime` (like computing velocity *from* position samples) will divide
by zero — undefined behavior / `inf`/`NaN` in float math. Production code guards
this explicitly (e.g. `if (DeltaTime > SMALL_EPSILON)`). Note: the *forward* formula
(`position += velocity * deltaTime`) is safe even at `DeltaTime = 0` — it's specifically
the *reverse* direction (deriving a rate from a time difference) that's dangerous.
