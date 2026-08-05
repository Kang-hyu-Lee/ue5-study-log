// Day 2 — DSA Solutions: Algorithm & Big-O Intuition

// Q1. Worst case: the Ace of Spades is the last card flipped = 52 flips.
// O(n) — linear. You check roughly one card per unit of "list grew."

// Q2. O(log n) — logarithmic. Each cut halves the search space, same
// mechanism as the phone-book example: 52 -> 26 -> 13 -> ... very few
// cuts needed even though it FEELS like it should take longer with cards.

// Q3. Roughly QUADRUPLES, not doubles. With 30 students you're doing
// ~30*29 comparisons; with 60 students it's ~60*59 — the size squared
// roughly, not the size itself. This is O(n^2) — quadratic.

// Q4. O(1) — constant. Direct index access doesn't "search" at all;
// it jumps straight to the memory location. Same cost regardless of
// array size. (You'll understand WHY once we cover arrays/memory
// layout on Day 4.)

// Q5. Worst -> Best growth:
// O(n^2)  >  O(n)  >  O(log n)  >  O(1)
// (n^2 grows fastest as n increases, O(1) doesn't grow at all.)

// Q6. Wrong to be complacent, right that it's "fine" FOR NOW. Big-O
// describes how the algorithm scales, not its speed at one fixed size.
// An O(n^2) algorithm can absolutely be fine at n=5. The danger is
// assuming the input will always stay small — in gamedev, "5 items"
// often becomes "500 enemies on screen" the moment a system succeeds,
// and O(n^2) code that was invisible at n=5 becomes a frame-rate
// disaster at n=500. Interviewers are listening for exactly this
// scaling awareness, not just "did you get the right answer."
