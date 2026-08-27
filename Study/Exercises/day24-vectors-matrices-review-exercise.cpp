// Day 24 — Vectors + Matrices Review Exercises
// Application-level, not procedural drill. Predict the answer on paper BEFORE running.
// Type this file yourself — do not paste.

#include <iostream>
#include <cmath>
using namespace std;

struct FVector2D
{
    float X;
    float Y;
};

// ---------------------------------------------------------------
// Problem 1: Magnitude + normalization with a zero-vector guard
// ---------------------------------------------------------------
// Write a function that returns the magnitude of a vector.
// hint: sqrt() is in <cmath>, already #included above.
float GetMagnitude(FVector2D V)
{
    // TODO
    return sqrt(V.X * V.X + V.Y * V.Y);
}

// Write a function that returns a normalized copy of V.
// If |V| is ~0 (use a small epsilon, not == 0.0f), return {0,0} instead of dividing.
// hint: compare against a small constant like 0.0001f, not directly against 0.
FVector2D Normalize(FVector2D V)
{
    // TODO
    float Mag = GetMagnitude(V);
    if(Mag < 0.0001f){
        return FVector2D{0, 0};
    }else{
        return FVector2D{V.X / Mag, V.Y / Mag};
    }
}

// ---------------------------------------------------------------
// Problem 2: Dot product — "is this in front of me?"
// ---------------------------------------------------------------
// Given Forward (facing direction, already normalized) and ToTarget (direction to
// some target, already normalized), return true if the target is roughly in front
// (dot product > 0).
// hint: dot = A.X*B.X + A.Y*B.Y
bool IsInFront(FVector2D Forward, FVector2D ToTarget)
{
    // TODO
    return((Forward.X * ToTarget.X + Forward.Y * ToTarget.Y) > 0);
}

// ---------------------------------------------------------------
// Problem 3: 2D cross product sign — which way to turn
// ---------------------------------------------------------------
// Return the 2D cross product scalar: A.X*B.Y - A.Y*B.X
// Then in main, use its SIGN to decide "turn left" vs "turn right".
float Cross2D(FVector2D A, FVector2D B)
{
    // TODO
    return A.X * B.Y - A.Y * B.X;
}

// ---------------------------------------------------------------
// Problem 4: Apply a 2D rotation matrix to a point (by hand, no matrix struct)
// ---------------------------------------------------------------
// Rotate point P by AngleDegrees around the origin.
// hint: convert degrees to radians first: radians = degrees * (PI / 180.0f).
//       PI isn't in <cmath> reliably across compilers — just hardcode 3.14159265f.
// hint: x' = x*cos - y*sin ; y' = x*sin + y*cos
FVector2D RotatePoint(FVector2D P, float AngleDegrees)
{
    // TODO
    float rad = AngleDegrees * 3.14159265f/180;
    return FVector2D{P.X * cos(rad) - P.Y * sin(rad), P.X * sin(rad) + P.Y * cos(rad)};
    
}

// ---------------------------------------------------------------
// Problem 5: Rotate THEN translate vs translate THEN rotate
// ---------------------------------------------------------------
// Given P = {2, 0}, rotate 90 degrees CCW, then translate by {3, 1}.
// Then separately: translate {2,0} by {3,1} FIRST, then rotate the result 90 degrees.
// Print both final points. They should differ — this proves non-commutativity
// with real numbers, not just the rule from the concept file.
void CompareRotateTranslateOrder()
{
    // TODO — use RotatePoint() and simple component addition for translate
    FVector2D P{2, 0};
    FVector2D RotV = RotatePoint(P, 90);
    RotV.X += 3;
    RotV.Y += 1;
    cout << "Rotate then translate: " << "(" << RotV.X << ", " << RotV.Y << ")" << endl;
    P.X += 3;
    P.Y += 1;
    RotV = RotatePoint(P,90);
    cout << "Translate then rotate: " << "(" << RotV.X << ", " << RotV.Y << ")" << endl;
}

// ---------------------------------------------------------------
// Problem 6: Application — reflect a vector off a surface
// ---------------------------------------------------------------
// Given an incoming velocity V and a surface normal N (both already normalized),
// the reflection formula is: R = V - 2 * Dot(V, N) * N
// Implement this. This is a real physics/gamedev formula (bounce direction).
// hint: you'll need a dot product helper — reuse or reimplement inline.
float DotProduct(FVector2D V, FVector2D N)
{
    return V.X * N.X + V.Y * N.Y;
}

FVector2D Reflect(FVector2D V, FVector2D N)
{
    // TODO
    return FVector2D{V.X - 2 * DotProduct(V,N) * N.X, V.Y - 2 * DotProduct(V,N) * N.Y};
}

int main()
{
    // Call each function above with test values, print results, and manually
    // verify against your paper prediction before trusting the output.
    FVector2D A;
    A.X = 1;
    A.Y = 3;
    FVector2D B;
    B.X = 2;
    B.Y = 4;
    cout << "Vector A is " << "(" << A.X << ", " << A.Y << ")" << endl;
    cout << "Vector B is " << "(" << B.X << ", " << B.Y << ")" << endl;
    cout << "Magnitude of A: " << GetMagnitude(A) << endl;
    cout << "Magnitude of B: " << GetMagnitude(B) << endl;
    
    FVector2D NormA = Normalize(A);
    FVector2D NormB = Normalize(B);
    cout << "Normalize A: " << "(" << NormA.X << ", " << NormA.Y << ")" << endl;
    cout << "Normalize B: " << "(" << NormB.X << ", " << NormB.Y << ")" << endl;
    
    cout << "Is A in front of B: " << IsInFront(A,B) << endl;
    
    float CrossV = Cross2D(A,B);
    if(CrossV > 0) { cout << "Left turn" << endl;}
    else if(CrossV < 0) { cout << "Right turn" << endl;}
    else { cout << "Go Straight" << endl;}

    CompareRotateTranslateOrder();

    return 0;
}
