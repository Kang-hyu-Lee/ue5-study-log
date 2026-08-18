// Day 15 — Math Solutions: Matrix Multiplication & 2D Rotation
// Full worked answers. Check your paper work against this step-by-step,
// don't just compare final numbers.

// ---------- PART A ----------

// Problem 1: A * B
// A = [2 0]   B = [1 3]
//     [1 4]       [2 1]
//
// output[0][0] = (2*1)+(0*2) = 2+0 = 2
// output[0][1] = (2*3)+(0*1) = 6+0 = 6
// output[1][0] = (1*1)+(4*2) = 1+8 = 9
// output[1][1] = (1*3)+(4*1) = 3+4 = 7
//
// A * B = [2 6]
//         [9 7]

// Problem 2: B * A (same matrices, reversed order)
// output[0][0] = (1*2)+(3*1) = 2+3 = 5
// output[0][1] = (1*0)+(3*4) = 0+12 = 12
// output[1][0] = (2*2)+(1*1) = 4+1 = 5
// output[1][1] = (2*0)+(1*4) = 0+4 = 4
//
// B * A = [5 12]
//         [5  4]
//
// Confirmed NOT equal to A*B = [2 6] / [9 7]. Order changes the result —
// this is the non-commutativity property, not an arithmetic mistake.

// Problem 3: A * B
// A = [3 -1]   B = [0 2]
//     [2  5]       [4 1]
//
// output[0][0] = (3*0)+(-1*4) = 0-4 = -4
// output[0][1] = (3*2)+(-1*1) = 6-1 = 5
// output[1][0] = (2*0)+(5*4) = 0+20 = 20
// output[1][1] = (2*2)+(5*1) = 4+5 = 9
//
// A * B = [-4  5]
//         [20  9]

// Problem 4: dimension check
// 2x3 * 2x2 — NOT valid. Inner dimensions must match: (2x3) needs the
// second matrix to have 3 rows, but it has 2. The reverse order,
// 2x2 * 2x3, DOES work: inner dims (2 and 2) match, giving a 2x3 result.

// Problem 5: 2x2 rotation matrix * 3x1 vector
// NOT directly compatible (2x2 needs a 2-row operand, vector has 3 rows).
// But the deeper issue isn't just size-matching — a plain rotation matrix
// (2x2 or even a 3x3 "3D rotation") has no mechanism for translation at
// all. You'd need homogeneous coordinates (pad to a 4x4 matrix with the
// vector as (x,y,z,1)) to combine rotation AND translation in one
// multiplication — which is what FMatrix/FTransform actually use.

// ---------- PART B ----------

// Problem 6: rotate (1, 0) by 180 degrees
// x' = x*cos(180) - y*sin(180) = 1*(-1) - 0*0 = -1
// y' = x*sin(180) + y*cos(180) = 1*0 + 0*(-1) = 0
// Result: (1, 0) -> (-1, 0). Makes sense — 180 degrees flips it to point
// the opposite direction.

// Problem 7: rotate (0, 1) by 90 degrees
// x' = 0*cos(90) - 1*sin(90) = 0*0 - 1*1 = -1
// y' = 0*sin(90) + 1*cos(90) = 0*1 + 1*0 = 0
// Result: (0, 1) -> (-1, 0). Clock check: pointing up, rotated 90 degrees
// counterclockwise, now points left. Matches.

// Problem 8: rotate (2, 3) by 45 degrees (cos=sin=0.707)
// x' = 2*0.707 - 3*0.707 = 1.414 - 2.121 = -0.707
// y' = 2*0.707 + 3*0.707 = 1.414 + 2.121 = 3.535
// Result: approx (-0.707, 3.535)

// Problem 9: degrees vs radians bug
// sin(90.0f) in C++ interprets 90.0f as RADIANS, not degrees. 90 radians
// is ~5157 degrees after wrapping — the result is basically meaningless
// garbage for "rotate by 90 degrees" intent. Correct version:
//     float radians = 90.0f * (PI / 180.0f);
//     float s = sin(radians);
// This bug is dangerous specifically because it doesn't crash or throw —
// it silently produces a wrong-but-plausible-looking number.

// Problem 10: why a 2x2 rotation matrix can't translate
// A 2x2 (or 3x3 for 3D) rotation matrix only encodes rotation around the
// origin — every output is a linear combination (scaled sum) of the
// input's own x/y/z components, so there's no way to add a constant
// offset. To add translation you need homogeneous coordinates: extend
// the vector with an extra "1" component and use a matrix one dimension
// larger (3x3 for 2D, 4x4 for 3D), where the extra row/column carries the
// translation offset through the multiplication.
