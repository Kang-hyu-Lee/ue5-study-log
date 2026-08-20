// Day 17 — Coordinate Systems (Local vs World Space) — SOLUTIONS

#include <iostream>
#include <cmath>
using namespace std;

// ============================================================
// PROBLEM 1 — SOLUTION
// ============================================================
// Parent rotation = 0 degrees means the rotation matrix is the IDENTITY
// rotation (cos(0)=1, sin(0)=0), so step 1 (rotate the local offset)
// leaves the offset completely unchanged: (3,1) rotated by 0 degrees is
// still (3,1).
// Step 2: WorldPos = ParentWorldPos + RotatedOffset = (10,4) + (3,1) = (13, 5)
// ANSWER: child world position = (13, 5)

// ============================================================
// PROBLEM 2 — SOLUTION
// ============================================================
// x' = x*cos(180) - y*sin(180) = 4*(-1) - 0*0 = -4
// y' = x*sin(180) + y*cos(180) = 4*0 + 0*(-1) = 0
// Rotated offset = (-4, 0)
// WorldPos = ParentWorldPos + RotatedOffset = (0,0) + (-4,0) = (-4, 0)
// ANSWER: child world position = (-4, 0)
// Sanity check: rotating "4 units forward" by a half-turn should point
// exactly backward — (-4,0) instead of (4,0) confirms that.

// ============================================================
// PROBLEM 3 — SOLUTION
// ============================================================
void LocalToWorld(float parentWorldX, float parentWorldY, float parentRotationDegrees,
                   float localX, float localY,
                   float& outWorldX, float& outWorldY)
{
    const float PI = 3.14159265f;
    float radians = parentRotationDegrees * (PI / 180.0f);

    // Step 1: rotate the local offset by the parent's rotation
    float rotatedX = localX * cos(radians) - localY * sin(radians);
    float rotatedY = localX * sin(radians) + localY * cos(radians);

    // Step 2: translate by the parent's world position
    outWorldX = parentWorldX + rotatedX;
    outWorldY = parentWorldY + rotatedY;
}

// ============================================================
// PROBLEM 4 — SOLUTION
// ============================================================
// a) The Actor's world position equals the parent's world position PLUS
//    the rotated local offset. Since local offset is (0,0,0), rotating it
//    does nothing (rotating a zero vector always gives a zero vector), so
//    WorldPos = ParentWorldPos = (100, 50, 0).
// b) RelativeLocation is relative to the PARENT, not the level origin.
//    Setting it to (0,0,0) snaps the actor back to wherever the PARENT is
//    (here, (100,50,0)) — not to the level's true (0,0,0). To move to the
//    level origin you'd need to either detach first, or compute the local
//    offset that CANCELS the parent's world position.

// ============================================================
// PROBLEM 5 — SOLUTION
// ============================================================
// With no parent, the "parent transform" defaults to the identity
// transform: zero translation, zero rotation, scale of 1. Feeding a local
// offset through an identity transform leaves it completely unchanged
// (rotate by 0 degrees = no change, translate by (0,0,0) = no change).
// So WorldPos = LocalPos exactly, every time — not because local and world
// stop being different concepts, but because the parent transform in this
// specific case happens to do nothing.

int main()
{
    float wx, wy;

    LocalToWorld(10.0f, 4.0f, 0.0f, 3.0f, 1.0f, wx, wy);
    cout << "Problem 1 world pos: (" << wx << ", " << wy << ")" << endl; // expect (13, 5)

    LocalToWorld(0.0f, 0.0f, 180.0f, 4.0f, 0.0f, wx, wy);
    cout << "Problem 2 world pos: (" << wx << ", " << wy << ")" << endl; // expect (-4, 0)

    return 0;
}
