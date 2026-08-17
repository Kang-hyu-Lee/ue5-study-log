# Day 3 Math Exercises — Logs & Trig

Attempt on paper first. Don't peek at the solutions file until you've tried each one.

## Logs

1. Compute `log2(32)` by hand. (Ask yourself: 2 raised to what power gives 32?)
2. A binary search takes 5 comparisons worst-case to find (or rule out) an item. What's the maximum possible size of the array it searched? (This is the *inverse* of the usual direction — you're given the step count, find `n`.)
3. Use the change-of-base formula to rewrite `log2(x)` in terms of natural log (`ln`).
4. In one sentence: why is `log2(1) = 0`?

## Trig (Unit Circle)

5. Convert `90°` and `270°` to radians (leave in terms of π).
6. Fill in this table using the unit circle (no calculator):

   | Angle | cos | sin |
   |---|---|---|
   | 0°   | ? | ? |
   | 90°  | ? | ? |
   | 180° | ? | ? |
   | 270° | ? | ? |

7. This line of C++ appears in a project:
   ```cpp
   float result = std::cos(45);  // std::cos = a C++ standard library function that computes cosine.
                                   // See cppreference.com/w/cpp/numeric/math/cos — it takes ONE argument, in radians.
   ```
   The programmer intended to get the cosine of 45 *degrees*. What's actually wrong with this line, and what angle (in radians) is `std::cos` actually evaluating instead?
8. Using the unit circle's symmetry, explain why `cos(-θ) = cos(θ)` but `sin(-θ) = -sin(θ)`. (Hint: what does a negative angle do geometrically — which direction do you walk?)
