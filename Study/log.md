## Day 1 — 2026-08-04

Learned: PEMDAS + nested parentheses, right-triangle geometry (Pythagorean theorem), trig basics (SOH-CAH-TOA + when it doesn't apply), C++ program/compile pipeline, variable declaration + 5 core types, uninitialized-variable and narrowing pitfalls, signed vs unsigned integer overflow (UB vs defined wraparound)

Confused: n/a

Open question: how sin/cos/tan connects to the unit circle (Day 3 topic) — resolved

## Day 2 — 2026-08-05

Learned: what an algorithm is, informal Big-O (O(1)/O(log n)/O(n)/O(n²)), nested loops (outer/inner) as the mechanism behind O(n²), C++ operators, the integer-division trap (int/int truncates before assignment), fixing it with static_cast on an operand (not the result), negative-division truncates toward zero not floor, how to compile/run .cpp files in VS Code via g++

Confused: n/a — clarified during session (0%/100% health bar bug, outer/inner loop mechanics)

Open question: when does sorting-then-binary-search actually pay off vs. just doing one linear scan, in a real gameplay scenario?

## Day 3 — 2026-08-06

Learned: log2(n) as the halving-count behind O(log n); unit circle trig (radians vs degrees, quadrant signs, cos/sin symmetry under negation — clicked after tracing +θ/-θ as mirror rotations); C++ if/else/else-if (order matters, first match wins), comparison vs assignment (== vs =, the classic bug), && / || short-circuit behavior; std::endl vs '\n' (buffer flushing, print-debugging use case); char ('...') vs string ("...") literal distinction and why 'A\n' triggers a multichar warning

Confused: cos(-θ)=cos(θ)/sin(-θ)=-sin(θ) didn't click from the algebra alone — needed the visual (mirrored radius lines across the x-axis) before it landed

Open question: exactly what triggers a buffer flush mid-loop (buffer capacity) — is that size fixed/inspectable, or implementation-defined and not worth reasoning about precisely?

## Day 4 — 2026-08-07
Learned: arrays (contiguous memory, zero-based indexing, O(1) access, sizeof(arr)/sizeof(arr[0]) idiom), for/while loop syntax, reverse traversal, corrected change-of-base formula (log_b(a) = ln(a)/ln(b)), '\n' vs std::endl (flush cost, when std::endl is actually needed)

Confused: had change-of-base formula inverted at recall check — resolved during session

Open question: sizeof(arr)/sizeof(arr[0]) is the classic way to get array length, but is there a cleaner modern C++ way I should know for interviews?

## Day 5 — 2026-08-08

Learned: vector magnitude/direction/addition/normalization (and why magnitude = hypotenuse via Pythagorean theorem); C++ function declaration, parameters, pass-by-value, return values; the distinction between position vectors and displacement vectors, including why position+position is meaningless but position+displacement or displacement+displacement are valid

Confused: initially unclear how a single vector "contains" a triangle (resolved via diagram — the components ARE the two legs, the vector itself is the hypotenuse); also unclear why adding two positions is invalid when the type system allows it (resolved — position+position has no valid interpretation, only position+displacement or displacement+displacement do)

Open question: n/a — both points of confusion were resolved within the session

## Day 6/7 — 2026-08-09

Learned: while(true) + break/continue for interactive loop control; cin >> chaining;
function boundary design (Divide() validated at call site via precondition, not
inside the function); why b == 0 is a safe exact float comparison (0.0 has no
fractional binary expansion) while decimal fractions like 0.1 are not

Confused: initially conflated return 1 (exit code, terminates whole program) with
signaling a per-input error to the user (should stay inside the loop via continue)

Open question: how would this pattern change once I have std::optional or references
to signal success/failure without overloading the return value?

Addendum: found and fixed op == '+' || '-' || '*' || '/' — each || operand needs
its own full comparison (op == X), not a bare literal, since a bare non-zero char
implicitly converts to true and silently short-circuits the whole condition.

## Day 8 — 2026-08-10

Learned: dot product (component agree/disagree mechanism, sign = alignment)
and cross product (rotation direction, sign flips on operand swap) in 2D;
C++ array declaration/indexing/looping with correct bounds; why functions
must be defined at file scope, not nested inside main, and the two ways
to make a function visible to main (define-above vs. forward-declare)

Confused: n/a — both concepts resolved cleanly once broken down with
plain-number examples

Open question: n/a

## Day 9 — 2026-08-11
Learned: formal Big-O rules (drop constants, drop lower-order terms, sequential=add, nested=multiply, separate inputs stay separate), std::string operations and cin/getline buffer behavior

Confused: initially mislabeled which rule applies to single-loop O(1)-body simplification (said Rule 2, actually Rule 1); mixed up .substr(start) vs .substr(start, length)

Open question: how much Big-O theory should actually drive gamedev decisions vs. profiling real n at realistic scale