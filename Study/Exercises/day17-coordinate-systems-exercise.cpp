// Day 17 — Coordinate Systems (Local vs World Space) — EXERCISES
// Do the hand-trace FIRST as comments, then write code to verify.
// Read day17-coordinate-systems-concept.md before starting.

#include <iostream>
#include <cmath>     // hint: cos()/sin() take RADIANS, not degrees.
                      // radians = degrees * (PI / 180). Use 3.14159265f for PI.
using namespace std;

// ============================================================
// PROBLEM 1 — By-hand trace, no rotation
// ============================================================
// Parent world position: (10, 4). Parent rotation: 0 degrees.
// Child local position: (3, 1).
// By hand: what is the child's world position? (No rotation means step 1
// of the concept file's worked example does nothing — why?)

// YOUR TRACE (as comments):
//Because the first step was applying the paret's rotation to the child's local offset but if the parent has no rotation then step is not necessary
//(10, 4) + (3, 1) = (13, 5)

// ============================================================
// PROBLEM 2 — By-hand trace, with rotation
// ============================================================
// Parent world position: (0, 0). Parent rotation: 180 degrees.
// Child local position: (4, 0).
// By hand, using the rotation matrix from the concept file:
//   x' = x*cos(theta) - y*sin(theta)
//   y' = x*sin(theta) + y*cos(theta)
// What is the child's world position? (cos(180)=-1, sin(180)=0)

// YOUR TRACE (as comments):
//Rotated offset = (4(-1) - 0(0), 4(0) + 0(-1)) = (-4, 0)
//(0, 0) + (-4, 0) = (-4, 0)

// ============================================================
// PROBLEM 3 — Write code to verify Problems 1 and 2
// ============================================================
// Write a function:
//   void LocalToWorld(float parentWorldX, float parentWorldY, float parentRotationDegrees,
//                      float localX, float localY,
//                      float& outWorldX, float& outWorldY);
// hint: outWorldX/outWorldY are OUTPUT parameters passed by reference (&) —
// see Day 12 concept file — the function writes results INTO the caller's
// variables instead of returning one value.
//
// Implement the two-step process from the concept file (rotate, then
// translate) inside this function. Call it once for Problem 1's numbers and
// once for Problem 2's numbers, print the results, and confirm they match
// your hand traces.

// YOUR CODE HERE:
void LocalToWorld(float parentWorldX, float parentWorldY, float parentRotationDegrees, float localX, float localY, float& outWorldX, float& outWorldY){
    float Radians = parentRotationDegrees * (3.14159265f/ 180);
    float RotatedOffsetX = localX * cos(Radians) - localY * sin(Radians);
    float RotatedOffsetY = localX * sin(Radians) + localY * cos(Radians);
    outWorldX = parentWorldX + RotatedOffsetX;
    outWorldY = parentWorldY + RotatedOffsetY;
}

// ============================================================
// PROBLEM 4 — Conceptual (answer as a comment, no code)
// ============================================================
// An Actor in UE5 has RelativeLocation (0,0,0) and is attached to a parent
// that is at world position (100, 50, 0) with some rotation applied.
// a) What is the Actor's world position?
// b) If a teammate says "just set RelativeLocation to (0,0,0) to reset it
//    to the level origin" — what's wrong with that statement?

// YOUR ANSWER (as comments):
//(100, 50, 0)
//It will reset it to where the parent position is because this actor is a child of that parent so its (0, 0, 0) is actually the world position of it's parent
//Correction: A zero offset, when rotated by anything, is still zero, so WorldPos = ParentWorldPost + 0 = ParentWorldPos. Another local offset than (0,0,0) would change the result

// ============================================================
// PROBLEM 5 — Edge case
// ============================================================
// Explain, as a comment: why does an UNPARENTED actor's local position and
// world position always match? Connect your answer to what "parent
// transform" means when there IS no parent.

// YOUR ANSWER (as comment):
//Because if there is no parent the actor's position goes through an identity transform, meaning that it has no rotation, no translation and a scale of 1. Leading it to have local position identical to world position.

int main()
{
    // Call your Problem 3 function here for both test cases and print results.
    float WorldX = 0;
    float WorldY = 0;
    LocalToWorld(10, 4, 0, 3, 1, WorldX, WorldY);

    cout << "Current position is: " << "( " << WorldX << ", " << WorldY << " )" << endl;

    LocalToWorld(0, 0, 180, 4, 0, WorldX, WorldY);

    cout << "Current position is: " << "( " << WorldX << ", " << WorldY << " )" << endl;
    return 0;
}
