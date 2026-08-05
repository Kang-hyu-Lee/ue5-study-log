# Glossary

Log new entries here whenever a `?`-flagged term comes up in a session. Format: **Term** — what it is, why it matters, one concrete example.

## General CS/Software

**API** — a defined way for one piece of software to talk to another (functions/endpoints you call without needing to know how the other side is built internally). Ex: UE5's own C++ classes expose an API you call without seeing the engine's internals.

**REST / RESTful** — a common style for web APIs where you interact with resources (like "a user" or "an item") via standard HTTP verbs (GET, POST, etc.). Ex: a game backend might expose `GET /player/123/inventory`.

**HTTP/HTTPS** — the protocol web requests travel over; HTTPS is the encrypted version. Relevant if your game ever talks to a server (leaderboards, accounts).

**Client-server architecture** — one central "server" holds the authoritative state, "clients" (players) connect to it. This is the core model behind UE5's replication system — the server owns the truth, clients are kept in sync.

**SQL / database** — a system for storing structured data in tables (rows/columns) and querying it. Ex: a player's save data or leaderboard scores often live in a database like this.

**Process vs Thread** — a process is a running program with its own memory; a thread is a unit of execution *within* a process, sharing memory with other threads of the same process. UE5 uses multiple threads (game thread, render thread) within one process.

**Branch / Merge conflict / Pull Request** — beyond `add`/`commit`/`push`: a branch is a parallel line of work off the main codebase; a pull request (PR) proposes merging it back in; a merge conflict happens when two branches changed the same lines differently and Git can't auto-resolve it.

**Framework vs Library** — a library is code you call when you need it; a framework calls *your* code (you plug into its structure). UE5 itself is a framework — it calls your `Tick()`, you don't call the engine's main loop.

**JSON** — a common plain-text format for structured data (key-value pairs), used constantly for config files, APIs, and save data.

**Compiler vs Interpreter** — a compiler translates your whole source file into machine code ahead of time (C++ is compiled); an interpreter runs code line-by-line as it goes (Python is interpreted). This is *why* C++ has a build/compile step and scripting languages often don't.

**IDE** — Integrated Development Environment — an editor with built-in compiling, debugging, and code navigation (Visual Studio, VS Code). Distinct from a plain text editor.

**Dependency / Package manager** — a dependency is external code your project relies on; a package manager (npm, pip, vcpkg) automates fetching and installing them.

**Unit test** — a small, automated test that checks one specific piece of code in isolation. Ties directly into the Unreal Automation Test framework your mentor prompt already requires.

**Stack trace / Debugger** — a stack trace shows the chain of function calls that led to a crash/error; a debugger lets you pause execution and inspect variables live, rather than guessing from print statements.

**Cache** — temporarily stored data kept around to avoid recomputing/refetching it. Ex: UE5's Derived Data Cache stores compiled shader/asset data so it doesn't rebuild from scratch every time.

**Outer loop / Inner loop** (flagged Day 2)
- In a *nested loop* (a loop written inside another loop), the **outer loop**
  controls the "for each X" — it runs once per item in the outer sequence.
  The **inner loop** runs *completely* every single time the outer loop
  advances one step.
- Example pattern: "for each name (outer), compare against every OTHER
  name (inner)" — this nested structure is why O(n²) algorithms exist:
  the inner loop's full run gets repeated once per outer loop step, so
  total work multiplies (n × n) instead of adding (n + n).
- Syntax for actual `for` loops isn't covered until Day 4 — this term was
  understood conceptually first, syntax comes later.

## Industry/Career

**PR (Pull Request) / Code review** — before code merges into the main codebase, someone else reviews the diff and comments/approves. Standard practice everywhere, including solo open-source contributions.

**Sprint / Agile / Scrum** — Agile is a general philosophy of iterative, short-cycle development; Scrum is a specific common implementation of it, where work is planned in fixed time blocks called sprints (often 1–2 weeks).

**CI/CD** — Continuous Integration / Continuous Deployment — automated pipelines that build/test code on every push (CI) and sometimes auto-deploy it (CD). Ex: a push to GitHub can trigger an automatic build + test run.

**Tech debt** — shortcuts or quick fixes that work now but will cost more effort to properly fix later. Not inherently bad — a real tradeoff teams make deliberately, but it accumulates if never addressed.

**Staging vs Production** — staging is a test environment that mirrors the real one; production is what actual users/players interact with. Code typically goes staging → tested → production.

**Standup** — a short daily team meeting (often 10–15 min) where each person says what they did, what they're doing next, and any blockers.

**Backlog** — the running list of planned-but-not-yet-started work (features, bugs, tasks), prioritized over time.

**MVP (Minimum Viable Product)** — the smallest version of something that's still usable/testable, built before adding polish or extra features. Ex: your Day 6 console calculator is an MVP of that mini-project.

**On-call** — being the designated person responsible for responding if something breaks in production, often outside normal hours.

**Postmortem / retro** — a structured review after a project, sprint, or incident: what went well, what didn't, what to change. Your existing Sunday review is essentially a personal retro.

**Ticket / issue tracker** — a system (Jira, GitHub Issues) for tracking individual units of work (bugs, features) as trackable items, each with status/owner/discussion.

## Gamedev-specific

**Tick rate** — how often the game updates its logic per second (distinct from frame rate/rendering). A server might tick at a fixed rate (e.g. 30/60 Hz) regardless of how fast clients render.

**Delta time** — the time elapsed since the last frame/tick, used to make movement/physics frame-rate-independent. Ex: `Position += Velocity * DeltaTime` moves the same real-world distance whether the game runs at 30fps or 144fps.

**Draw call** — one instruction sent to the GPU to render something. Fewer draw calls generally = better performance; this is why batching/instancing matters for optimization.

**LOD (Level of Detail)** — using simpler/lower-detail versions of a model as it gets farther from the camera, to save performance.

**Occlusion culling** — not rendering objects the camera can't actually see (blocked by other geometry), to save performance.

**Netcode / Replication** — the systems handling how game state syncs between server and clients over a network. UE5's replication system (which your mentor prompt already treats as a required security-relevant pillar) is UE5's built-in netcode layer.

**Game loop** — the core repeating cycle every game runs: process input → update state → render → repeat. Everything in a real-time game happens inside this loop.

**Frame budget / frame time** — the amount of time you have to do all per-frame work to hit a target frame rate (e.g. ~16.6ms for 60fps). "Over budget" means something is too slow for the target frame rate.

**Hitbox / Hurtbox** — the (often invisible) collision shapes used to detect "did an attack land" — hitbox is the attacking area, hurtbox is the vulnerable area being checked against.

**Client prediction / Server reconciliation** — in networked games, the client guesses/simulates the result of your input immediately (prediction) before the server confirms it, then corrects (reconciles) if the server disagrees — done to hide network latency.

**Build (debug vs shipping)** — a debug build includes extra checks/logging and runs slower, meant for development; a shipping build is optimized and stripped down, meant for players.
