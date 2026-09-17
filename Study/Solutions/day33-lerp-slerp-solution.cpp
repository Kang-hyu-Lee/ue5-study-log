// Day 33 Solutions — Lerp / Slerp
// Check AFTER attempting each problem yourself. Read the explanation, not just the code.

// ============================================================
// Problem 1 — Hand-write scalar lerp
// ============================================================
float MyLerp(float A, float B, float T)
{
    return A + T * (B - A);
    // Equivalent form: (1-T)*A + T*B — both are algebraically identical.
    // A + T*(B-A) is preferred in practice: fewer multiplications, and it's
    // numerically better behaved (less floating point error accumulation)
    // than expanding (1-T)*A + T*B.
}
// MyLerp(0.f, 10.f, 0.5f) => 0 + 0.5*(10-0) = 5.0  ✔

// ============================================================
// Problem 2 — Clamped lerp
// ============================================================
float MyClampedLerp(float A, float B, float T)
{
    float ClampedT = T;
    if (ClampedT < 0.f) ClampedT = 0.f;
    if (ClampedT > 1.f) ClampedT = 1.f;
    return A + ClampedT * (B - A);
}
// MyClampedLerp(0.f, 10.f, 1.5f) => T clamped to 1.0 => 0 + 1.0*(10-0) = 10.0  ✔
// This is exactly what FMath::Clamp(T, 0.f, 1.f) does under the hood — now you
// know the primitive, use the built-in from here on.

// ============================================================
// Problem 3 — Why component-wise Euler lerp is wrong
// ============================================================
// Lerping Pitch/Yaw/Roll independently treats three angles as if they were
// three unrelated scalars, but they're not — they're three SEQUENTIAL rotations
// applied around axes that themselves move as earlier rotations are applied
// (Day 31: this sequential dependency is exactly what causes gimbal lock —
// two axes can align and a degree of freedom collapses). Lerping each angle
// straight-line from start to end value doesn't correspond to a single smooth
// rotation through 3D space; it can make the object appear to rotate through
// an unintended combined axis, "wobble," or even briefly pass through a
// gimbal-locked orientation mid-interpolation where an axis is lost, even if
// neither the start nor end orientation is itself locked. Quaternion slerp
// avoids this because it interpolates a single axis+angle rotation directly,
// with no per-axis sequencing to go wrong.

// ============================================================
// Problem 4 — Dot product sign flip
// ============================================================
// Q0 = (1, 0), Q1 = (-0.9, -0.436)
// dot(Q0, Q1) = (1 * -0.9) + (0 * -0.436) = -0.9 + 0 = -0.9
//
// -0.9 is negative => naive interpolation would take the LONG path around
// (since Q1 as given points almost opposite Q0 — cos(theta) = -0.9 means
// theta is close to 180 degrees).
//
// Corrected Q1 to interpolate toward: negate it => Q1' = (0.9, 0.436).
// Why: Q1 and -Q1=(0.9,0.436) represent the same rotation (double cover,
// concept file section 4), but (0.9, 0.436) has a POSITIVE dot product with
// Q0 (dot = 0.9), meaning it's the short-path representation. Interpolating
// toward Q1' instead of Q1 produces the same final orientation but via the
// short way round — this is exactly the check FQuat::Slerp does internally
// before running the formula.

// ============================================================
// Problem 5 — Near-parallel instability
// ============================================================
// Failure mode: as theta -> 0, sin(theta) -> 0, and the formula divides by
// sin(theta) in both coefficient terms. This is a division-by-(near)zero —
// not necessarily a hard crash, but the coefficients blow up / become
// numerically unstable (garbage precision, potential NaN if theta underflows
// to exactly 0.0 in floating point).
// Standard fallback: when theta is below a small threshold (e.g. UE5 checks
// something like abs(dot) > 0.9995), skip the slerp formula entirely and use
// plain lerp + renormalize (nlerp) instead. At that small an angle the visual
// difference between slerp and nlerp is imperceptible, so there's no quality
// cost — only a numerical-safety gain.

// ============================================================
// Problem 6 — UE5 Tick() smoothing pattern
// ============================================================
void AExampleActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurrentRotation = FQuat::Slerp(
        CurrentRotation,
        TargetRotation,
        FMath::Clamp(DeltaTime * InterpSpeed, 0.f, 1.f)
    );

    SetActorRotation(CurrentRotation);
}
// Bonus answer: without the Clamp, a lag-spike frame (large DeltaTime) makes
// (DeltaTime * InterpSpeed) exceed 1.0. Slerp's formula is only mathematically
// meaningful for t in [0,1] — an alpha above 1.0 extrapolates PAST the target
// orientation (same extrapolation problem as Problem 2's unclamped lerp, just
// on the rotational sphere instead of a line). Visually: the object overshoots
// its target rotation and has to swing back, a visible "overshoot wobble" on
// frame-rate hitches. The Clamp is what guarantees "at worst, snap exactly to
// the target this frame" instead of "occasionally overshoot past it."
