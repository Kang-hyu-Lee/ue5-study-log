// Day 24 — Vectors + Matrices Review SOLUTIONS
// Read only after attempting on paper + in your own exercise file first.

#include <iostream>
#include <cmath>
using namespace std;

struct FVector2D
{
    float X;
    float Y;
};

// ---------------------------------------------------------------
// Problem 1
// ---------------------------------------------------------------
float GetMagnitude(FVector2D V)
{
    return sqrt(V.X * V.X + V.Y * V.Y);
    // Why: Pythagorean theorem — straight-line distance from origin to (X,Y).
}

FVector2D Normalize(FVector2D V)
{
    float Mag = GetMagnitude(V);
    if (Mag < 0.0001f) // epsilon guard, not `Mag == 0.0f`
    {
        // Why epsilon and not exact 0: floating point math almost never produces
        // an EXACT 0.0f even when the "true" mathematical answer is zero — tiny
        // rounding error accumulates. Comparing == 0.0f would miss those cases
        // and you'd divide by 0.0000001f, blowing up to a huge/garbage vector.
        return FVector2D{0.0f, 0.0f};
    }
    return FVector2D{V.X / Mag, V.Y / Mag};
}

// ---------------------------------------------------------------
// Problem 2
// ---------------------------------------------------------------
bool IsInFront(FVector2D Forward, FVector2D ToTarget)
{
    float Dot = Forward.X * ToTarget.X + Forward.Y * ToTarget.Y;
    return Dot > 0.0f;
    // Why this works: Dot = |Forward||ToTarget|cos(theta). Since both are
    // normalized (length 1), Dot IS cos(theta) directly. cos is positive for
    // angles < 90 degrees either side of straight-ahead — i.e. "roughly in front."
}

// ---------------------------------------------------------------
// Problem 3
// ---------------------------------------------------------------
float Cross2D(FVector2D A, FVector2D B)
{
    return A.X * B.Y - A.Y * B.X;
    // Sign meaning: positive = B is counter-clockwise from A (turn left to face B).
    // negative = B is clockwise from A (turn right). Zero = A and B are parallel
    // (pointing same or exactly opposite direction) — no defined turn direction,
    // this is the edge case flagged in the concept file.
}

// ---------------------------------------------------------------
// Problem 4
// ---------------------------------------------------------------
FVector2D RotatePoint(FVector2D P, float AngleDegrees)
{
    float Radians = AngleDegrees * (3.14159265f / 180.0f);
    float CosA = cos(Radians);
    float SinA = sin(Radians);
    FVector2D Result;
    Result.X = P.X * CosA - P.Y * SinA;
    Result.Y = P.X * SinA + P.Y * CosA;
    return Result;
    // This IS the 2D rotation matrix from the concept file, just written as two
    // scalar equations instead of a matrix struct — same math, no matrix type needed.
}

// ---------------------------------------------------------------
// Problem 5
// ---------------------------------------------------------------
void CompareRotateTranslateOrder()
{
    FVector2D P = {2.0f, 0.0f};

    // Rotate first, then translate
    FVector2D RotatedFirst = RotatePoint(P, 90.0f);          // -> (0, 2)
    FVector2D RotateThenTranslate = {RotatedFirst.X + 3.0f, RotatedFirst.Y + 1.0f}; // -> (3, 3)

    // Translate first, then rotate
    FVector2D TranslatedFirst = {P.X + 3.0f, P.Y + 1.0f};    // -> (5, 1)
    FVector2D TranslateThenRotate = RotatePoint(TranslatedFirst, 90.0f); // -> (-1, 5)

    cout << "Rotate->Translate: (" << RotateThenTranslate.X << ", " << RotateThenTranslate.Y << ")\n";
    cout << "Translate->Rotate: (" << TranslateThenRotate.X << ", " << TranslateThenRotate.Y << ")\n";
    // (3,3) vs (-1,5) — different results. This is why FTransform order matters:
    // attaching a child actor with rotation-then-offset vs offset-then-rotation
    // puts it in a genuinely different world position.
}

// ---------------------------------------------------------------
// Problem 6
// ---------------------------------------------------------------
FVector2D Reflect(FVector2D V, FVector2D N)
{
    float Dot = V.X * N.X + V.Y * N.Y;
    FVector2D Result;
    Result.X = V.X - 2.0f * Dot * N.X;
    Result.Y = V.Y - 2.0f * Dot * N.Y;
    return Result;
    // Mechanism: Dot(V,N) is how much of V points INTO the surface (along N).
    // Subtracting 2x that component flips just that piece, leaving the
    // along-surface component untouched — the classic "bounce" formula used
    // in physics engines and simple ricochet/deflection gameplay logic.
}

int main()
{
    FVector2D V1 = {3.0f, 4.0f};
    cout << "Magnitude: " << GetMagnitude(V1) << "\n"; // 5.0 (3-4-5 triangle)

    FVector2D Zero = {0.0f, 0.0f};
    FVector2D NormZero = Normalize(Zero);
    cout << "Normalized zero vector: (" << NormZero.X << ", " << NormZero.Y << ")\n"; // (0,0), no crash

    FVector2D Forward = {1.0f, 0.0f};
    FVector2D ToTarget = {0.7f, 0.1f};
    cout << "In front? " << IsInFront(Forward, ToTarget) << "\n"; // 1 (true)

    FVector2D A = {1.0f, 0.0f};
    FVector2D B = {0.0f, 1.0f};
    cout << "Cross2D: " << Cross2D(A, B) << "\n"; // 1 -> B is CCW from A, turn left

    FVector2D Rotated = RotatePoint({1.0f, 0.0f}, 90.0f);
    cout << "Rotated (1,0) by 90deg: (" << Rotated.X << ", " << Rotated.Y << ")\n"; // ~(0,1)

    CompareRotateTranslateOrder();

    FVector2D Vel = {1.0f, -1.0f};
    FVector2D Normal = {0.0f, 1.0f}; // flat horizontal surface, normal points up
    FVector2D Bounced = Reflect(Vel, Normal);
    cout << "Reflected velocity: (" << Bounced.X << ", " << Bounced.Y << ")\n"; // (1, 1) — bounces up

    return 0;
}
