## Day 1 — 2026-08-04
Learned: PEMDAS + nested parentheses, right-triangle geometry (Pythagorean theorem),
         trig basics (SOH-CAH-TOA + when it doesn't apply), C++ program/compile pipeline,
         variable declaration + 5 core types, uninitialized-variable and narrowing pitfalls,
         signed vs unsigned integer overflow (UB vs defined wraparound)
Confused: n/a
Open question: how sin/cos/tan connects to the unit circle (Day 3 topic) — still unresolved

## Day 2 — 2026-08-05
Learned: what an algorithm is, informal Big-O (O(1)/O(log n)/O(n)/O(n²)),
nested loops (outer/inner) as the mechanism behind O(n²), C++ operators,
the integer-division trap (int/int truncates before assignment), fixing
it with static_cast on an operand (not the result), negative-division
truncates toward zero not floor, how to compile/run .cpp files in VS Code
via g++
Confused: n/a — clarified during session (0%/100% health bar bug,
outer/inner loop mechanics)
Open question: when does sorting-then-binary-search actually pay off vs.
just doing one linear scan, in a real gameplay scenario?

## Day 3 — 2026-08-07
Learned: log2(n) as the halving-count behind O(log n); unit circle trig (radians vs degrees, quadrant signs, cos/sin symmetry under negation — clicked after tracing +θ/-θ as mirror rotations); C++ if/else/else-if (order matters, first match wins), comparison vs assignment (== vs =, the classic bug), && / || short-circuit behavior; std::endl vs '\n' (buffer flushing, print-debugging use case); char ('...') vs string ("...") literal distinction and why 'A\n' triggers a multichar warning.
Confused: cos(-θ)=cos(θ)/sin(-θ)=-sin(θ) didn't click from the algebra alone — needed the visual (mirrored radius lines across the x-axis) before it landed.
Open question: exactly what triggers a buffer flush mid-loop (buffer capacity) — is that size fixed/inspectable, or implementation-defined and not worth reasoning about precisely?