# Daily Study Schedule — Foundations → C++/UE5 → Industry Ready

**Anchor time: 6:00 PM start (earlier is fine, later isn't — protect the anchor).**
Total: ~2.5 hrs/day, 6 days/week. Consistency > intensity — do NOT extend sessions to "make up" a missed day; just resume the rhythm.

## Daily Block Structure (every session, no exceptions)

| Time (relative to start) | Block | What happens |
|---|---|---|
| +0:00–0:10 | **Recall warm-up** | Before opening any notes: write from memory what you learned last session. This is the single highest-leverage habit — it's what breaks vibe coding, because you can't "recall" something you never understood. |
| +0:10–1:10 | **Foundations block** | Math or DSA theory (rotates by day, see weekly split below). New concept → explain it back in your own words before moving on. |
| +1:10–1:20 | Break | Actually step away. |
| +1:20–2:30 | **Applied block** | C++/UE5 hands-on. Hard rule: **type every line yourself, never paste generated code.** If Claude gives you code, close it, then re-type it from the explanation. |
| +2:30–2:45 | **Git + log** | Commit with a real message, and write 2–3 lines: what you learned, what confused you, one open question. |
| +2:45–2:50 | **Tomorrow's first task** | Write the exact first thing you'll do tomorrow — removes the "what do I even start with" friction that kills consistency. |

## Weekly Split (general rhythm — see `phase1-curriculum-roadmap.md` for exact daily topics)

| Day | Foundations block focus | Applied block focus |
|---|---|---|
| Mon–Fri | Math or DSA theory, per the day's entry in the curriculum roadmap | C++ (Phase 1) or C++/UE5 (Phase 2+), per the roadmap |
| Sat | **Portfolio session (3–4 hrs, longer block)** | Combine the week's math/DSA/C++ into one small shippable piece — this is what becomes the portfolio |
| Sun | Rest, or 20-min flashcard review only | — |

## Phase Gate (don't skip ahead)
- **Weeks 1–4 (Phase 1):** Pure fundamentals. C++ syntax + algebra/trig/vectors + core DSA (arrays, linked lists, stacks/queues, recursion, trees). UE5 editor stays closed except brief familiarization.
- **Weeks 5+ (Phase 2):** UE5 C++ projects run in parallel with a continued DSA teaching track (not just review) — hashing, sorting/searching, graphs, heaps, two-pointer/sliding-window patterns, bit manipulation, and light DP/greedy get taught here, per the tracked list in `phase1-curriculum-roadmap.md`. Each new DSA topic still gets tied to a UE5-relevant use where one exists (e.g. bit manipulation → collision channel flags, heaps → A* pathfinding).
- **Math in Phase 2:** quaternions and interpolation/easing (lerp, slerp) get proactively taught here too — pervasive enough not to defer. Statistics/probability and noise functions are deliberately NOT scheduled — pull those in only when a specific project actually needs them (see `phase1-curriculum-roadmap.md` for the reasoning).
- **Ongoing, once each DSA topic has been taught once:** it enters spaced-repetition practice (a rotating timed problem, not a one-off) so nothing taught in Phase 2 goes stale before an actual interview.
- Monthly portfolio milestone + start tracking target internship postings/deadlines against project readiness, from Phase 2 onward.

## Weekly Review (do this every Sunday, 15 min)
- What did I actually retain without looking anything up?
- Which concept did I "vibe" through instead of understanding? → repeat it Monday.
- Is this week's portfolio piece something I could explain in an interview?
