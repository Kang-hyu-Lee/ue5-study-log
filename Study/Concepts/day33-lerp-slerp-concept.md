# Day 33 — Interpolation & Easing: Lerp / Slerp

Ties directly to Day 31 (quaternions, `FQuat`, gimbal lock) and Day 17 (local/world space). Today gives you the tool to actually *move between* two rotations/positions smoothly, not just represent one.

---

## 1. What interpolation actually is

- Interpolation = finding an in-between value between a start (A) and end (B), controlled by a parameter `t` in `[0, 1]`.
- `t = 0` → exactly A. `t = 1` → exactly B. `t = 0.5` → halfway.
- This is a **general-purpose tool**, not rotation-specific — you'll use it for camera position, UI fade alpha, health-bar animation, color blending, anything with a "from → to" shape.

## 2. Lerp (Linear Interpolation) — the mechanism

**Formula:** `Lerp(A, B, t) = A + t * (B - A)`, equivalently `(1 - t) * A + t * B`.

- Read it as: start at A, then walk `t` fraction of the way toward B.
- Works component-wise for scalars, `FVector` (x,y,z each lerped independently), colors (r,g,b,a).
- UE5 syntax: `FMath::Lerp(A, B, Alpha)` — templated, works on float, FVector, FLinearColor, etc.

**Pitfall #1 — unclamped t:**
- Nothing in the formula stops you passing `t = 1.5` or `t = -0.3`. That's **extrapolation**, not interpolation — you overshoot past B or undershoot past A.
- `FMath::Lerp` does NOT clamp for you. If you want interpolation guaranteed, clamp first: `FMath::Clamp(Alpha, 0.f, 1.f)`.

## 3. Why plain lerp breaks for rotations

- A rotation (as `FQuat`) is a **unit-length** 4D vector — that unit-length constraint is what makes it a valid rotation at all (Day 31: axis+angle packed into 4 components, magnitude must be 1).
- If you lerp two quaternions component-wise (`Lerp(Q1, Q2, t)`), the result is almost certainly **not unit length** anymore — you've walked in a straight line through 4D space, cutting *inside* the hypersphere both quaternions live on.
- Two consequences:
  1. You must **renormalize** after lerping quaternions, or the rotation is invalid/distorted. This fixed-up version is called **nlerp** (normalized lerp) — see §5.
  2. Even after renormalizing, straight-line-then-project-back-to-sphere does NOT produce constant angular velocity — the rotation speeds up in the middle of the interpolation and slows at the ends. Usually invisible for short/fast rotations, visible for slow deliberate ones (cutscene camera, weapon aim smoothing).
- Lerping **Euler angles** component-wise (pitch/yaw/roll each lerped) is worse — this is exactly the gimbal-lock-adjacent problem from Day 31: it doesn't take the shortest rotational path and can visibly "wobble" through an unintended axis.

## 4. Slerp (Spherical Linear Interpolation) — the mechanism

Slerp interpolates **along the surface of the 4D unit hypersphere** instead of cutting straight through it — so the result is always unit length, and angular velocity is constant.

**Formula:**
```
Slerp(Q0, Q1, t) = [sin((1-t)θ) / sin(θ)] * Q0 + [sin(t*θ) / sin(θ)] * Q1
```
where `θ` is the angle between Q0 and Q1, found via `cos(θ) = dot(Q0, Q1)`.

You will never hand-write this in UE5 — `FQuat::Slerp(Q1, Q2, Alpha)` does it — but you need the mechanism to reason about the two pitfalls below.

**Pitfall #2 — the double-cover sign flip:**
- A quaternion `Q` and its negation `-Q` represent the **exact same rotation** (this is "double cover" — every rotation has two quaternion representations).
- If `dot(Q0, Q1) < 0`, the two quaternions are on "opposite sides," and naive slerp will take the **long way around** (up to 359° instead of the short way).
- Fix: if dot < 0, negate one quaternion before interpolating (flips it to the equivalent short-path representation). `FQuat::Slerp` already does this internally — but if you ever hand-roll interpolation logic, this is the bug that causes a rotation to visibly spin the "wrong way."

**Pitfall #3 — near-parallel numerical instability:**
- When `θ` is very small (Q0 and Q1 are nearly identical), `sin(θ)` approaches 0 → you're dividing by ~0 → floating point garbage.
- Standard fix: when `θ` is below some small threshold, fall back to plain lerp + renormalize (nlerp) instead — the visual difference is imperceptible at that angle anyway. UE5's implementation does this fallback for you.

**Edge case:** at `θ = π` exactly (Q0 and Q1 are 180° apart), the interpolation axis is **undefined** — there are infinitely many shortest paths. Rare in practice, but it's why some engines nudge one quaternion slightly to break the tie rather than crash/NaN.

## 5. Nlerp vs Slerp — the actual engineering trade-off

| | Nlerp (lerp + normalize) | Slerp |
|---|---|---|
| Cost | Cheap (no trig) | Expensive (sin/cos/division) |
| Angular velocity | Not constant (speeds up mid-interpolation) | Constant |
| Commutative/associative blending (e.g. animation layering) | Yes | No |
| When used | Most per-frame gameplay smoothing (camera follow, aim assist) — the non-constant-speed is imperceptible at typical frame-to-frame deltas | Cutscenes, deliberate slow rotations, anywhere the constant-speed property is visually load-bearing |

- Production reality: most UE5 gameplay code uses `FQuat::Slerp` anyway because it's implemented efficiently and the correctness is worth it; nlerp is the thing you reach for specifically when profiling shows quaternion interpolation as a hot path (animation blending across many bones, e.g.).

## 6. Easing (brief — not today's core, but the natural next question)

- Lerp/slerp with a **linear** `t` (i.e., `t` increases at constant rate per frame) gives constant-speed motion — mechanically correct but can look robotic (real motion accelerates/decelerates).
- Easing = remapping `t` through a non-linear function *before* feeding it to Lerp/Slerp — e.g. `t² ` (ease-in, starts slow), `1-(1-t)²` (ease-out), smoothstep (`3t²-2t³`, eases both ends).
- Not scheduled as its own day — flagging so "why does my camera feel stiff" has an answer later without it being an untaught surprise.

## 7. Applied pattern for today (UE5)

Typical per-Tick smoothing pattern:
```cpp
CurrentRotation = FQuat::Slerp(CurrentRotation, TargetRotation, FMath::Clamp(DeltaTime * InterpSpeed, 0.f, 1.f));
```
- `DeltaTime * InterpSpeed` as the alpha is a common approximation (frame-rate-independent-ish, not mathematically exact exponential decay, but standard in shipped code) — you'll build this live in chat.

---

## Restate-back check (do this before moving on)
1. In your own words: why does lerping two quaternions directly produce an invalid rotation, and what fixes it?
2. What breaks if you slerp two quaternions without checking the dot product sign first?
3. One case where nlerp is preferred over slerp, and why.
