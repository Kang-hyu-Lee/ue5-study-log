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

## Day 10 — 2026-08-12
Learned: matrix-vector multiplication as row-wise dot products; matrices are non-commutative (A x B != B x A); pointers store addresses (&x), dereferencing (*ptr) reads/writes the pointed-to value; swapping values through pointers vs swapping what pointers point to; safe nullptr checks before dereferencing

Confused: which axis a reflection matrix flips across vs which coordinate it negates (flipping y negates the y-value but reflects across the x-axis, not the y-axis)

Open question: how does this row-by-row matrix math actually get stored/executed under the hood in FMatrix/FTransform — is it literally a 2D array, or something else?

## Day 11 — 2026-08-13

Learned: pointer arithmetic moves by sizeof(type) not by byte (Ptr + i == *(Ptr + i) == Ptr[i]); one-past-the-end pointers are legal to compute/compare but never dereference; wild vs dangling pointer distinction (never-valid vs was-valid-then-invalidated); null checks only catch pointers that are actually nullptr, not dangling ones; linked list traversal via Head->Next chains until nullptr; front-insert is O(1) for linked lists vs O(n) for arrays.

Confused: initially mixed up when a for-loop's boundary check runs relative to its body (lost index 0 walking backwards with != instead of >=); briefly treated pointer relational comparison as always illegal instead of only-illegal-across-different-objects; conflated "the loop needs a null check" with "the null check is why this specific broken-link case doesn't crash" — needed to separate what makes a loop terminate from what makes termination happen without an error.

Open question: none outstanding — all 18 exercises (12 pointer arithmetic/null/dangling + 6 linked list) resolved and correctly re-explained after correction.

## Day 12 — 2026-08-14
Learned: Node*& vs Node* for functions needing to reassign the caller's
pointer vs just read through it; Node vs Node* (value type on stack vs
address to heap object); reference parameters change whether the
caller's variable is mutated and avoid a copy — not just a naming
choice; pointer swap requires dereferencing (*A, *B) to touch the
pointed-to value, and a temp variable used to survive a mutation must
hold a copy of the VALUE, not another pointer into memory about to
change; pointer arithmetic step size is always sizeof(one element),
automatic based on pointer type — never sizeof(whole array); sizeof is
used once, up front, to compute total element count (e.g. for EndPtr),
not per-step; C-style strings use a '\0' terminator to mark the real
end of data within a fixed-size buffer, so traversal checks for the
terminator rather than a precomputed count; nested pointer-arithmetic
traversal (step between fixed-size elements, then step through one
element's contents) is a valid pattern, e.g. walking an array of
fixed-size name buffers.

Confused: initially thought references were just alternate names for
readability, not something that changes program behavior; thought void
functions couldn't use `return;` without a value; conflated per-step
size with total-array size when reasoning about sizeof in char-array
traversal.

Open question: is there a real-world (non-interview) case in UE5 code
where you'd choose Node** over Node*& deliberately, or is Node*&
always preferred in modern C++?

## Day 13 — 2026-08-15

Learned: structs vs. plain variables (bundling related data, dot-operator access,
default member initializers); self-referential struct sizing (pointer required —
value member creates infinite/uncomputable size); explicit field-by-field struct
construction over nested brace-init; multi-delete traversal pattern (Prev only
steps forward when nothing was deleted, since a delete already relinks Prev->Next
to the next candidate); precondition-vs-internal-handling tradeoff for signaling
"no valid result" (string has safe sentinels available, unlike double)

Confused: initially conflated "by reference" and "by value" terminology out loud
(said the words backwards while stating correct reasoning); briefly mixed up
which variable (Head vs Prev) needed which fix during DeleteCompleted's Bug 2 trace

Open question: none carried forward — DeleteCompleted's three

## Day 14 — 2026-08-16
Learned: refined pointer mutability distinction — plain TodoNode* CAN be locally
reassigned (e.g. walking a list with current = current->Next), it just doesn't
propagate that reassignment back to the caller; only TodoNode*& does that.

Confused: n/a — rest day, recall check only.

Open question: DeleteCompleted design questions carried forward unresolved —
(1) whether Node*& is needed, (2) Prev behavior after a mid-list delete in a
multi-delete pass, (3) handling repeated head deletions.

## Day 15 — 2026-08-17
Learned: matrix multiplication mechanics (row*column, non-commutative), 2D rotation matrix derivation from unit circle, why translation needs homogeneous coordinates (padding with 1 to smuggle a constant into a multiply-only operation), struct vs class default access difference, calling member functions with dot notation, why struct with virtual function breaks POD/memcpy safety

Confused: initially explained homogeneous coordinates as a "direction" problem rather than an "addition" problem — corrected after a second pass

Open question: how translation via homogeneous coordinates concretely shows up when Day 17 (local vs world space) is covered

## Day 16 — 2026-08-18
Learned: Array-based stack (Top as index, not pointer) and linked-list-based queue (Head/Tail) built from scratch; deep dive on pointer vs reference vs value parameter semantics using address/house tracing; stack vs heap memory, new/delete, memory leaks, dangling pointers, double-delete patterns; fixed the confirmed DeleteCompleted leak in todo-list.cpp

Confused: initial mix-up between plain-pointer reseating (needs T*&) vs writing-through-a-reference (T& is enough) — resolved through repeated address tracing across ArrayStack, Queue, and LinkedStack examples

Open question: none new — LinkedStack Push/Pop left unimplemented, carried to tomorrow

## Day 17 — 2026-08-19

Learned: local vs world space and parent-child transform chains (rotate then translate, tied directly to Day 15's rotation matrix and non-commutative order); constructors (default + parameterized, initializer-list syntax and its declaration-order gotcha); destructors and RAII (heap resource tied to object lifetime, freed automatically at scope exit); why an unparented actor's local and world position match (identity transform substituted, not a coincidence of the object itself).

Confused: initializer-list syntax for multiple members took a couple of passes to click — resolved. Rectangle::Area() had a leftover "2 *" copied from the Perimeter formula, caught by running the code rather than by inspection — fixed and re-verified, output now correctly (1, 4).

Open question: none this session — floating-point near-zero output (-3.49691e-07) was explained inline via the Day 16 float-comparison rule, not left open.

## Day 18 — 2026-08-20
Learned: recursion (base case + recursive case, trust-the-recursion / delegate-don't-iterate mindset, pre-order vs post-order via PrintReverse), encapsulation (private enforces invariants; member variables persist across calls vs local variables reset every call; pass-by-value copies vs pass-by-pointer/reference share the same object; most vexing parse with Type Name();)

Confused: initially tried to track state with local variables (Index/Sum/Counter) inside recursive functions before realizing each call gets a fresh copy — took several attempts across SumArray and CountNodes to unlearn

Open question: when would you actually choose pass-by-pointer over pass-by-reference for passing an object into a recursive helper, given both avoid the copy? Also: compiled program produced no output — unresolved, need to check compile/run steps.