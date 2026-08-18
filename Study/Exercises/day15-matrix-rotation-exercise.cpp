// Day 15 — Math Exercises: Matrix Multiplication & 2D Rotation
// Do these by hand on paper. No compiler needed for this file — it's a
// container for the problems so it lives in the repo with the rest of
// the day's work.
//
// Show your work for every problem (the row * column steps), not just
// the final matrix/vector. Check dimension compatibility BEFORE
// multiplying (hint: rule is A's cols must match B's rows).

// ---------- PART A: Matrix Multiplication ----------

// Problem 1
// A = [2 0]   B = [1 3]
//     [1 4]       [2 1]
// Find A * B.

// Problem 2
// Using the same A and B from Problem 1, find B * A.
// Compare to Problem 1's result. Are they equal? (they shouldn't be —
// this is testing whether you internalized non-commutativity)

// Problem 3
// A = [3 -1]   B = [0 2]
//     [2  5]       [4 1]
// Find A * B.

// Problem 4 — dimension check (no multiplication needed, just answer yes/no + why)
// Can you multiply a 2x3 matrix by a 2x2 matrix? Why or why not?
// If not, which order (if either) WOULD work?

// Problem 5 — dimension check
// You have a 2x2 rotation matrix and a 3x1 vector (x, y, z).
// Can you directly multiply them? What's the actual problem here
// (hint: re-read the Edge Case section in the concept file)?

// ---------- PART B: 2D Rotation ----------
// Use the rotation matrix formulas from the concept file.
// Known values you'll need:
// cos(0)=1, sin(0)=0 | cos(90)=0, sin(90)=1 | cos(180)=-1, sin(180)=0
// cos(270)=0, sin(270)=-1 | cos(45)=0.707, sin(45)=0.707 (approx, use these)

// Problem 6
// Rotate the vector (1, 0) by 180 degrees. Show x' and y' calculations.

// Problem 7
// Rotate the vector (0, 1) by 90 degrees. Show x' and y' calculations.
// Sanity check your answer against a clock face like the concept file did.

// Problem 8
// Rotate the vector (2, 3) by 45 degrees. Show x' and y' calculations
// using the approx values above.

// Problem 9 — degrees vs radians pitfall
// You write this C++ line to rotate 90 degrees:
//     float s = sin(90.0f);
// What's wrong with this line? What should it actually say?
// (You don't need to run code — just identify and explain the bug.)

// Problem 10 — applied / conceptual
// In your own words: why can't a plain 2x2 rotation matrix also move
// (translate) an object? What would you need to add to make that possible?
