// Day 31 Exercises — Euler Angles, Gimbal Lock, Normalization, Quaternions
// Type these yourself. Do not paste. Explain each non-trivial line back before moving on.
// Predict output BEFORE running anything.

#include "CoreMinimal.h"
// FVector, FRotator, FQuat, FMath are all available via CoreMinimal.h

// ---------------------------------------------------------
// PROBLEM 1 — Manual Vector Normalization
// ---------------------------------------------------------
// Given (X, Y, Z), compute magnitude and unit vector WITHOUT using
// FVector::Normalize() or GetSafeNormal() — do the math by hand first.
// Hint: FMath::Sqrt(float) takes a float, returns a float.
// Test with: (6, 8, 0), (1, 1, 1), (0, 0, 0)  <- this one must NOT crash. Guard it.
void Problem1_ManualNormalize(float X, float Y, float Z)
{
	// TODO:
	// 1. magnitude = sqrt(X*X + Y*Y + Z*Z)
	// 2. if magnitude is ~0 (use an epsilon, e.g. 0.0001f), log a warning and return early
	// 3. otherwise compute unit vector components and UE_LOG them
	// Hint: UE_LOG(LogTemp, Warning, TEXT("Unit = (%f, %f, %f)"), ux, uy, uz);
}

// ---------------------------------------------------------
// PROBLEM 2 — Compare Against Built-in Normalize
// ---------------------------------------------------------
// Same three test vectors as Problem 1. Construct an FVector and call the
// built-in .GetSafeNormal(). Confirm it matches your manual math.
// Hint: FVector V(X, Y, Z); FVector Unit = V.GetSafeNormal();
void Problem2_BuiltInNormalize(float X, float Y, float Z)
{
	// TODO
}

// ---------------------------------------------------------
// PROBLEM 3 — Quaternion From Axis + Angle (manual)
// ---------------------------------------------------------
// Given an axis (already unit-length) and an angle in DEGREES, compute
// W, X, Y, Z manually using the half-angle formula from the concept file.
// Hint: FMath::DegreesToRadians(float) first — Cos/Sin need RADIANS.
// Test with: axis (0,1,0), angle 90 degrees. Predict the answer before running.
void Problem3_ManualQuatFromAxisAngle(FVector Axis, float AngleDegrees)
{
	// TODO:
	// 1. convert AngleDegrees to radians
	// 2. HalfAngle = radians / 2
	// 3. W = cos(HalfAngle)
	// 4. X,Y,Z = sin(HalfAngle) * Axis.X / Axis.Y / Axis.Z   (assumes Axis already unit length)
	// 5. UE_LOG the result
}

// ---------------------------------------------------------
// PROBLEM 4 — Quaternion From Axis + Angle (built-in)
// ---------------------------------------------------------
// Same test case as Problem 3, using the engine constructor:
// Hint: FQuat MyQuat(Axis, FMath::DegreesToRadians(AngleDegrees));
// FQuat's axis-angle constructor takes RADIANS — mismatching this with
// degrees is a common bug. Confirm it matches Problem 3.
void Problem4_BuiltInQuatFromAxisAngle(FVector Axis, float AngleDegrees)
{
	// TODO
}

// ---------------------------------------------------------
// PROBLEM 5 — Gimbal Lock Identification (conceptual — answer in a comment)
// ---------------------------------------------------------
// For each FRotator below, write "GIMBAL LOCK" or "SAFE" and WHY (which two
// axes become parallel, if any):
// A) Pitch=0,   Yaw=45,  Roll=0 Safe
// B) Pitch=90,  Yaw=30,  Roll=15 Gimbal lock Yaw and Roll
// C) Pitch=-90, Yaw=0,   Roll=60 Same as above
// D) Pitch=45,  Yaw=90,  Roll=0 Safe
//
// TODO: write your answer as a comment under each line above.

// ---------------------------------------------------------
// PROBLEM 6 — FRotator vs FQuat Composition Pitfall
// ---------------------------------------------------------
// Predict, in a comment, whether these two give the SAME final orientation, and why/why not:
// APPROACH A: FRotator Combined = RotatorA + RotatorB;   (component-wise add)
// APPROACH B: FQuat    Combined = QuatA * QuatB;          (quaternion multiply)
// No because Pitch, Yaw and Roll are dependent on each other, as in one can drag another, 
// so because they aren't fully independent, component-wise addition who treats them as independent will 
// give a different result from quaternions who consider this factor, also rotation composition is fundamentally multiplicative
// 
// TODO: write your prediction before checking the solution file.
