# Phase 2 Curriculum Roadmap — Weeks 5–9+ (UE5 C++, DSA Continues in Parallel)

Same lookup rule as Phase 1: open with "Day [N]." — Claude pulls Foundations/Applied topics from this file automatically. No date column is pre-assigned (Phase 1's fixed dates drifted once already); Week/Day number is the only anchor. Fill in actual calendar dates in your own log as you go.

**Carry-over debt from Phase Gate (Day 28)** — none were gate-blocking, but each gets a dedicated spaced-rep slot below, not just a passing mention:
- Tree traversal order recall → Day 32
- BST bounds logic → Day 32
- Epic naming prefix conventions → Day 30 (applied directly while writing first real UE5 classes)

---

## Week 5 — UE5 Bootstrap + Hashing

| Day | Foundations block | Applied block |
|---|---|---|
| 29 | DSA: Hashing pt.1 — what a hash map/set is, why O(1) average lookup, collision intuition (chaining vs open addressing, conceptual only) | UE5: project anatomy — `Source/`, `.uproject`, `.Build.cs`/`.Target.cs`, modules. Create first C++ Actor class via editor wizard, trace what gets generated. |
| 30 | DSA: Hashing pt.2 — `std::unordered_map`/`std::unordered_set` in C++ syntax, average vs worst-case complexity, when hashing beats a tree | UE5: `AActor` lifecycle — constructor vs `BeginPlay()` vs `Tick()` (why the constructor can't safely touch the world). `UCLASS`/`UPROPERTY`/`UFUNCTION` macros. **Epic naming convention review** — spaced-rep debt item, applied live to the code just written. |
| 31 | Math: Quaternions intro — why not raw Euler angles (gimbal lock), what a quaternion actually represents geometrically (no calculus needed) | UE5: `UActorComponent` — what a component is, attaching to an Actor, `GetOwner()` |
| 32 | **Spaced-rep timed drill:** tree traversal (in/pre/post order) + BST insert/bounds validation — both Phase Gate debt items, timed not just reviewed. Bridge to DSA: binary search intro (why it needs sorted data, ties to BST bounds logic just drilled) | UE5: Enhanced Input system basics — input actions/mapping contexts, binding a function to a key |
| 33 | Math: interpolation/easing — `lerp`, `slerp` (ties directly to yesterday's quaternions) | UE5: apply lerp/slerp to smooth Actor rotation — first real "quaternion in production code" moment |
| 34 | **Portfolio (Sat):** Actor that smoothly rotates/orbits using quaternion `slerp`, with `UPROPERTY(EditAnywhere)` exposed speed/axis params, built on a component | — |
| 35 | Rest + review. Flashcards: hashing complexity, quaternion "why," and confirm the 3 debt items actually stuck | — |

## Week 6 — Sorting & Searching + Gameplay Framework

| Day | Foundations block | Applied block |
|---|---|---|
| 36 | DSA: sorting fundamentals — merge sort (divide & conquer trace), why O(n log n) | UE5: `GameMode`/`GameState`/`PlayerController`/`PlayerState` — who owns what, server vs client relevance previewed (full depth waits for replication in Wk 9) |
| 37 | DSA: quicksort (partition logic, average vs worst case pivot choice) | UE5: `Cast<>` and `IsValid()` patterns — why raw C-style casts are wrong here |
| 38 | DSA: binary search — formal proof of correctness (not just "it halves"), off-by-one pitfalls | UE5: casting + hashing crossover — using `TMap` (Unreal's hash map) for a gameplay lookup (e.g. item ID → data) |
| 39 | Math: quaternion composition — combining rotations, order-matters pitfall | UE5: apply `TMap` lookup inside a small state-driven system |
| 40 | Spaced-rep: hashing + BST timed mix (2nd rotation) | UE5: wire the week's pieces into one flow |
| 41 | **Portfolio (Sat):** small state-driven mini-system (e.g. inventory or objective tracker) using `TMap` + `GameState` pattern | — |
| 42 | Rest + review | — |

## Week 7 — Two-Pointer/Sliding Window + Communication Patterns

| Day | Foundations block | Applied block |
|---|---|---|
| 43 | DSA: two-pointer technique — pattern class, not a data structure; classic problems (pair-sum, reverse-in-place) | UE5: delegates/events (`DECLARE_DYNAMIC_MULTICAST_DELEGATE`) — decoupling Actor communication |
| 44 | DSA: sliding window — fixed vs variable window, when it beats brute force | UE5: `UInterface` — C++ interfaces for cross-class contracts, ties to BP↔C++ boundary pillar |
| 45 | Math: quaternion → Euler conversion (when/why you'd need it despite Day 31's warning — mostly debugging/UI display) | UE5: combine delegate + interface — one Actor broadcasts, another responds without a hard reference |
| 46 | Spaced-rep: sorting/searching timed mix (2nd rotation) | UE5: apply pattern to a pickup/trigger interaction |
| 47 | Spaced-rep: two-pointer/sliding window (1st rotation, taught this week so light) | UE5: polish interaction system |
| 48 | **Portfolio (Sat):** event-driven interaction system (e.g. pickup broadcasts an event, HUD/inventory listens via interface) | — |
| 49 | Rest + review | — |

## Week 8 — Bit Manipulation + Collision Systems

| Day | Foundations block | Applied block |
|---|---|---|
| 50 | DSA: bit manipulation — AND/OR/XOR/shift, why bitmasks are O(1) flag checks | UE5: collision channels — `ECollisionChannel`, object types vs trace channels (this is literally bitmask flags under the hood) |
| 51 | DSA: bitmask patterns — combining flags, checking/toggling a single bit | UE5: overlap vs hit events, `OnComponentBeginOverlap` |
| 52 | Math: review week — vectors + quaternions combined practice (no new math, consolidation) | UE5: line traces / sweeps for gameplay queries |
| 53 | Spaced-rep: two-pointer/sliding window (2nd rotation) + hashing (3rd rotation) | UE5: custom collision response using bitmask flags |
| 54 | ⚠ Security note begins here: server authority basics preview (full depth Week 9) — why client-reported collision results can't be trusted blind | UE5: tie bitmask flags into the interaction system from Week 7 |
| 55 | **Portfolio (Sat):** custom collision-driven interaction using bitmask-based channel logic | — |
| 56 | Rest + review | — |

## Week 9 — Graphs + Replication/Security

| Day | Foundations block | Applied block |
|---|---|---|
| 57 | DSA: graphs intro — adjacency list vs matrix, when each is used | UE5: replication basics — `Replicated` `UPROPERTY`, `GetLifetimeReplicatedProps` |
| 58 | DSA: BFS — level-order traversal on a graph, shortest-path-in-unweighted-graph intuition | UE5: RPCs — `Server`/`Client`/`NetMulticast`, **mandatory `WithValidation` on Server RPCs from here on** |
| 59 | DSA: DFS — recursive vs iterative (stack), cycle detection | UE5: input sanitization on an RPC — treat all client input as hostile, concrete example |
| 60 | Spaced-rep: bit manipulation (2nd rotation) + BST/tree (3rd rotation) | UE5: apply replication to the collision/interaction system — server-authoritative pickup |
| 61 | Math consolidation / buffer day (use for whichever topic needs more reps this week) | UE5: Automation Test — write first test incl. ≥1 adversarial/edge case for the RPC above |
| 62 | **Portfolio (Sat):** server-authoritative, validated, tested pickup/interaction system — first piece with real security + testing rigor, strong interview talking point | — |
| 63 | Rest + review | — |

---

## Deferred, Not Forgotten (scheduled Week 10+, detailed when they get close)
- Heaps/priority queues → tied to A* pathfinding once UE5 navigation is introduced
- Light DP/greedy pattern exposure
- Spatial partitioning (quadtree/octree/BVH) — likely Phase 3, lower priority
- Statistics/probability, noise functions — pulled in only when a specific project (loot table, procedural gen) actually needs them

## Ongoing Spaced-Repetition Rule
Once a DSA topic has had its first full teaching day, it enters rotation — expect it to resurface as a timed drill roughly every 2 weeks (see the "Spaced-rep" rows above). This is why some weeks look lighter on brand-new DSA content: that slot is protecting older material from going stale before an actual interview.

## Monthly Portfolio / Internship Tracking (Phase 2 onward)
At each 4-week mark (end of Week 8, Week 12, ...): review the accumulated Saturday portfolio pieces as a set — is there a coherent "story" a recruiter could follow? Start logging actual internship posting deadlines against project readiness from here on, not just building in a vacuum.
