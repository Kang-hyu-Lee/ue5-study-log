// Day 31 Solutions — Euler Angles, Gimbal Lock, Normalization, Quaternions
// Read AFTER attempting every problem yourself. Compare your reasoning, not just the numbers.

#include "CoreMinimal.h"

// ---------------------------------------------------------
// PROBLEM 1 — Manual Vector Normalization
// ---------------------------------------------------------
void Problem1_ManualNormalize(float X, float Y, float Z)
{
	float MagnitudeSquared = X * X + Y * Y + Z * Z; // sum of squares — magnitude formula before the sqrt
	float Magnitude = FMath::Sqrt(MagnitudeSquared);

	if (Magnitude < 0.0001f) // epsilon guard: catches (0,0,0) AND near-zero float noise, avoids divide-by-zero -> NaN
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot normalize a zero-length vector."));
		return;
	}

	float UX = X / Magnitude;
	float UY = Y / Magnitude;
	float UZ = Z / Magnitude;
	UE_LOG(LogTemp, Warning, TEXT("Unit = (%f, %f, %f)"), UX, UY, UZ);

	// (6,8,0)  -> mag=10  -> (0.6, 0.8, 0)
	// (1,1,1)  -> mag=1.732 -> (0.577, 0.577, 0.577)
	// (0,0,0)  -> caught by guard, logs warning, returns early, never divides
}

// ---------------------------------------------------------
// PROBLEM 2 — Built-in Normalize
// ---------------------------------------------------------
void Problem2_BuiltInNormalize(float X, float Y, float Z)
{
	FVector V(X, Y, Z);
	FVector Unit = V.GetSafeNormal(); // "safe" = internally does the same epsilon guard as Problem 1,
	                                   // returns FVector::ZeroVector on a zero-length input instead of crashing/NaN
	UE_LOG(LogTemp, Warning, TEXT("Unit = (%f, %f, %f)"), Unit.X, Unit.Y, Unit.Z);

	// Matches Problem 1 exactly for (6,8,0) and (1,1,1).
	// For (0,0,0): GetSafeNormal() returns (0,0,0) quietly — no warning log, unlike our manual version.
	// This is the tradeoff of "safe" built-ins: safer at runtime, but silently masks the edge case
	// unless you specifically check for it — worth knowing which behavior you're relying on.
}

// ---------------------------------------------------------
// PROBLEM 3 — Manual Quaternion From Axis + Angle
// ---------------------------------------------------------
void Problem3_ManualQuatFromAxisAngle(FVector Axis, float AngleDegrees)
{
	float AngleRadians = FMath::DegreesToRadians(AngleDegrees); // Cos/Sin require radians, not degrees
	float HalfAngle = AngleRadians / 2.0f;                       // the "half-angle" in the quaternion formula

	float W = FMath::Cos(HalfAngle);
	float X = FMath::Sin(HalfAngle) * Axis.X;
	float Y = FMath::Sin(HalfAngle) * Axis.Y;
	float Z = FMath::Sin(HalfAngle) * Axis.Z;

	UE_LOG(LogTemp, Warning, TEXT("Quat = (X=%f, Y=%f, Z=%f, W=%f)"), X, Y, Z, W);

	// Test case: Axis=(0,1,0), Angle=90
	// AngleRadians = 1.5708, HalfAngle = 0.7854
	// W = cos(0.7854) = 0.707
	// X = sin(0.7854)*0 = 0
	// Y = sin(0.7854)*1 = 0.707
	// Z = sin(0.7854)*0 = 0
	// -> (X=0, Y=0.707, Z=0, W=0.707) — matches the concept file's worked example exactly.
}

// ---------------------------------------------------------
// PROBLEM 4 — Built-in Quaternion From Axis + Angle
// ---------------------------------------------------------
void Problem4_BuiltInQuatFromAxisAngle(FVector Axis, float AngleDegrees)
{
	FQuat MyQuat(Axis, FMath::DegreesToRadians(AngleDegrees)); // constructor does exactly Problem 3's math internally
	UE_LOG(LogTemp, Warning, TEXT("Quat = (X=%f, Y=%f, Z=%f, W=%f)"), MyQuat.X, MyQuat.Y, MyQuat.Z, MyQuat.W);

	// Identical result to Problem 3. The whole point of this pair: prove to yourself the
	// built-in isn't "magic" — it's the same half-angle formula you just did by hand.
	// The realistic bug this guards against: forgetting DegreesToRadians and passing
	// AngleDegrees straight in — the constructor won't error, it'll just silently build
	// the WRONG rotation (radians and degrees are both "just a float" to the compiler).
}

// ---------------------------------------------------------
// PROBLEM 5 — Gimbal Lock Identification
// ---------------------------------------------------------
// A) Pitch=0, Yaw=45, Roll=0    -> SAFE. Pitch is 0 (neutral), all three axes still independent.
// B) Pitch=90, Yaw=30, Roll=15  -> GIMBAL LOCK. Pitch at +/-90 is exactly the degenerate case:
//                                   Roll's axis (forward) rotates onto Yaw's axis (up). Yaw and
//                                   Roll now produce the same visual rotation.
// C) Pitch=-90, Yaw=0, Roll=60  -> GIMBAL LOCK. Same mechanism as B, just pitched the other way
//                                   (-90 instead of +90) — still the degenerate alignment.
// D) Pitch=45, Yaw=90, Roll=0   -> SAFE. Pitch is 45, not at the +/-90 extreme, so all three
//                                   axes are still distinguishable (Yaw itself being 90 is irrelevant —
//                                   it's PITCH crossing +/-90 that causes the lock, not Yaw).

// ---------------------------------------------------------
// PROBLEM 6 — FRotator vs FQuat Composition
// ---------------------------------------------------------
// APPROACH A (FRotator component-wise add) and APPROACH B (FQuat multiply) do NOT
// generally give the same final orientation.
// WHY: 3D rotation composition is not commutative scalar addition — adding Pitch+Pitch
// and Yaw+Yaw independently ignores how the two rotations actually interact in 3D space
// (the "order matters" pitfall from Euler angles, section 1). FQuat's `*` operator is
// specifically overloaded (forward ref: Day 39) to perform the CORRECT mathematical
// composition of two rotations. Adding FRotators only happens to look reasonable for
// small, single-axis-only cases — it breaks as soon as more than one axis is involved,
// which is most real gameplay rotation.
