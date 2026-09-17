// Day 33 Exercises — Lerp / Slerp
// Type these yourself. Do not paste. Explain each line back before checking the solution file.
// These are conceptual/standalone C++ (not full UE5 project files) unless stated.

// ============================================================
// Problem 1 — Hand-write scalar lerp
// ============================================================
// Write a free function:
//   float MyLerp(float A, float B, float T);
// implementing Lerp from first principles (do NOT call FMath::Lerp).
// Test it: MyLerp(0.f, 10.f, 0.5f) should print 5.0

#include <iostream>

// Your code here:
float MyLerp(float A, float B, float T)
{
    return A + T * (B-A);
}


// ============================================================
// Problem 2 — Clamped lerp
// ============================================================
// Write:
//   float MyClampedLerp(float A, float B, float T);
// Same as Problem 1, but T outside [0,1] should be clamped first.
// Test: MyClampedLerp(0.f, 10.f, 1.5f) should print 10.0, not 15.0
// Hint: don't use FMath::Clamp — write the min/max logic by hand once so you understand it,
// you can use the built-in from tomorrow onward.

// Your code here:
float MyClampedLerp(float A, float B, float T)
{
    if(T < 0)
    {
        return MyLerp(A, B, 0);
    }
    else if (T > 1)
    {
        return MyLerp(A, B, 1);
    }
    else
    {
        return MyLerp(A, B, T);
    }
}

float MyClampedLerp(float A, float B, float T)
{
    if(T < 0) T = 0;
    else if(T > 1) T = 1;
    return MyLerp(A, B, T);
}


// ============================================================
// Problem 3 — Why component-wise Euler lerp is wrong (written answer, not code)
// ============================================================
// In a comment block below, answer in your own words (3-5 sentences):
// If you lerp two FRotator values (Pitch/Yaw/Roll) component by component,
// what specifically can go wrong with the path the rotation takes? Reference
// gimbal lock from Day 31 in your answer.

// Your answer here:
// Because a component by component lerp makes pitch, yaw, roll be lerped independently meaning that depending on initial or ending values, these 
// components can pass the object through an orientation where two of the axes line up, which is a gimbal lock. This can happen anytime during the walk
// because we never checked.


// ============================================================
// Problem 4 — Dot product sign flip (trace by hand)
// ============================================================
// You're given two SIMPLIFIED 2D "quaternion-like" unit vectors (pretend they're quaternions
// for the sake of the exercise — real FQuat is 4D, this is a trace exercise not a real rotation):
//   Q0 = (1, 0)
//   Q1 = (-0.9, -0.436)   // roughly 180-ish degrees away, deliberately "the long way"
// 1. Compute dot(Q0, Q1) by hand (show the arithmetic in a comment).
// 2. Is the dot product negative? What does that tell you about which path naive
//    interpolation would take?
// 3. What is the corrected Q1 you'd interpolate toward instead, and why?

// Your work here:
// 1. 1 * -0.9 + 0 * -0.436 = -0.9
// 2. yes it is negative which means it will take the long way around
// 3. either negate Q0 or Q1 because it flips it to the equivalent short path rotation


// ============================================================
// Problem 5 — Near-parallel instability (identify, don't fix)
// ============================================================
// Given the Slerp formula:
//   Slerp(Q0, Q1, t) = [sin((1-t)*theta)/sin(theta)] * Q0 + [sin(t*theta)/sin(theta)] * Q1
// If theta = 0.0001 radians (Q0 and Q1 nearly identical), what specifically breaks
// numerically if you evaluate this formula directly in code? Name the exact failure mode
// (not just "it breaks") and the standard fallback.

// Your answer here:
// It will be a divide by zero and will have a floating point garbage. So we fall back to plain lerp + normalize

// ============================================================
// Problem 6 — UE5 pattern (pseudo-code, no engine needed to attempt)
// ============================================================
// Write the Tick() smoothing line (from the concept file, section 7) from memory,
// WITHOUT looking at the concept file. Then compare against it yourself before
// checking the solution file.
// Bonus: what happens visually if you forget the FMath::Clamp on the alpha and
// InterpSpeed * DeltaTime exceeds 1.0 on a lag spike frame?

// Your code + answer here:
// CurrentRotation = FQuat::Slerp(CurrentRotation, TargetRotation, FQuat::Clamp(Interp*DeltaTime, 0.1f, 1.0f))
// Solution: CurrentRotation = FQuat::Slerp(CurrentRotation, TargetRotation, FMath::Clamp(DeltaTime * InterpSpeed, 0.f, 1.f));
// It will give a t > 1 which will make it an extrapolation which means the object will overshoot the target rotation and has to swing back
