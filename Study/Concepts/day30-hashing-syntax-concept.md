# Day 30 — Hashing Pt. 2: `std::unordered_map` / `std::unordered_set` Syntax

## Recap (Day 29)
You already know *why* hash maps are avg O(1): hash function → mod by bucket count → index.
Collisions handled by chaining (linked list per bucket) or open addressing (probe to next slot,
tombstone on delete). Today: the actual C++ syntax to use these, and when to pick hashing over a tree.

---

## 1. `std::unordered_map<KeyType, ValueType>`

```cpp
#include <unordered_map>   // required — this type is NOT in <map>, different header

std::unordered_map<std::string, int> PlayerScores;
```
This declares an empty hash map. `KeyType = std::string`, `ValueType = int`. No buckets exist with
meaningful data yet — the object manages bucket allocation internally, you never touch buckets directly.

### Inserting — two different tools, two different behaviors

```cpp
PlayerScores["Kang"] = 25;
```
`operator[]` on a map does one of two things depending on whether the key already exists:
- **Key exists:** overwrites the value.
- **Key does NOT exist:** silently CREATES a new entry, default-constructs the value (0 for int,
  empty string for std::string, etc.), THEN assigns 25 to it.

```cpp
PlayerScores.insert({"Kang", 25});
```
`insert()` takes a key-value pair (curly braces build a `std::pair` here). Unlike `operator[]`:
- **Key exists:** does nothing — existing value is left untouched, insert is a no-op.
- **Key does NOT exist:** inserts it.
- Returns a `std::pair<iterator, bool>` — the bool tells you whether the insertion actually happened.
  You can check it: `if (PlayerScores.insert({"Kang", 25}).second) { /* was new */ }`

**⚠ Pitfall (the classic one):** `operator[]` silently inserts. This code:
```cpp
if (PlayerScores["Boss"] > 5) { ... }
```
looks like a harmless read, but if `"Boss"` wasn't in the map, this line just ADDED it with value 0.
Your map's `.size()` just changed as a side effect of what looked like a check. This is a real,
common bug — always use `find()` or `count()` (below) when you only want to check, not create.

### Looking up

```cpp
auto It = PlayerScores.find("Kang");
if (It != PlayerScores.end()) {
    // found — It is an ITERATOR (a pointer-like object pointing at the key-value pair)
    int Score = It->second;   // ->first = key, ->second = value
} else {
    // not found — find() returns the special "end" sentinel iterator
}
```
`find()` never inserts. `end()` is not "the last element" — it's a sentinel one-past-the-last,
used purely as a "not found" signal. Comparing against it is the standard "did I find it" check.

```cpp
if (PlayerScores.count("Kang") > 0) { ... }
```
`count()` returns 0 or 1 for a map (keys are unique — no duplicates possible). Also never inserts.
Simpler to read than `find()` when you only need a yes/no, not the actual value.

### Erasing

```cpp
PlayerScores.erase("Kang");        // by key — no-op if key doesn't exist, no error
PlayerScores.erase(It);            // by iterator, if you already have one from find()
```

### Iterating

```cpp
for (auto& Pair : PlayerScores) {
    // Pair.first = key, Pair.second = value
}
```
`auto` = compiler deduces the type for you (here: `std::pair<const std::string, int>&`).
The `&` makes `Pair` a REFERENCE to the actual entry, not a copy — important for a big map,
otherwise every iteration copies a full key+value pair for no reason.
**No defined order** — iteration order is bucket order, which is arbitrary and can change
completely after a rehash (when the map grows and redistributes entries).

---

## 2. `std::unordered_set<T>`

Same hash-table engine, but stores only keys — no attached value. Used for pure existence checks:
"have I seen this before?"

```cpp
#include <unordered_set>
std::unordered_set<int> SpawnedIDs;
SpawnedIDs.insert(42);
if (SpawnedIDs.count(42) > 0) { /* already spawned */ }
SpawnedIDs.erase(42);
```
Same `insert()`/`find()`/`count()`/`erase()` semantics as the map, just no `["]`operator and no
`.second` — there's no value to hold.

---

## 3. Complexity — tied back to the syntax above

- `insert()`, `find()`, `count()`, `erase()` are all **average O(1)**, **worst-case O(n)**.
- The worst case happens when many keys collide into the same bucket (bad hash function, or
  adversarial input specifically crafted to collide — a real DoS vector in production systems
  that hash untrusted input).

## 4. Hashing (`unordered_map`) vs Tree (`std::map`)

`std::map` is a **balanced binary search tree** (red-black tree) under the hood — not a hash table.

| | `std::unordered_map` | `std::map` |
|---|---|---|
| Average lookup | O(1) | O(log n) |
| **Worst-case** lookup | O(n) | **O(log n), guaranteed** |
| Iteration order | undefined/arbitrary | sorted by key, always |
| Range queries (`lower_bound`, etc.) | not supported | supported |

**When to pick `map` over `unordered_map`:** you need sorted iteration, you need range queries
(e.g. "all scores between X and Y"), or you're in a context where an attacker could feed you
input designed to cause hash collisions and you need a worst-case guarantee, not just an average.

**When to pick `unordered_map`:** you don't care about order, you want the fastest average case,
no range queries needed. This is the common case for gameplay lookups (item ID → item data).

This directly previews Day 38: Unreal's `TMap` is Unreal's version of `unordered_map` — same
concepts, Epic's own container syntax.

## 5. Production/interview relevance
"What's the time complexity of X" trivia is common, but the sharper interview question is
**"given this access pattern, which structure and why"** — that's what the table above answers.
In production UE5 code, `TMap` shows up constantly for ID→data lookups (inventory, ability
systems, save data indexing).

## 6. Where do `insert()`, `find()`, etc. actually LIVE?

**Yes — for `unordered_map`, `unordered_set`, `vector`, and most STL containers, the full
implementation of every member function is inside the header file.** Not just a declaration —
the actual working code. This is different from how you're used to organizing your own classes.

**Normal C++ split (what you do for your own classes):** a `.h` file has the class **declaration**
(what functions exist, their signatures) and a `.cpp` file has the **definition** (the actual
function bodies). Each `.cpp` file gets compiled separately into machine code, and the linker
stitches the pieces together afterward. This works because a normal function's machine code is
the same regardless of who calls it.

**Why templates break that split.** `unordered_map<std::string, int>` and
`unordered_map<int, int>` are not "the same code used generically" — they are genuinely
**different, separately generated pieces of code**, one built to store strings-and-ints, one
built to store ints-and-ints. The compiler doesn't know which concrete versions you'll need until
it sees YOUR code actually using `unordered_map<SomethingSpecific, SomethingElse>`. That
generation step — the compiler stamping out real code for one specific set of types — is called
**template instantiation**, and it has to happen while your `.cpp` file is being compiled, using
your specific types. There's no way to pre-compile "unordered_map in general" into a `.cpp` once
and link against it later, because "in general" isn't real code — only a specific instantiation
is. So the compiler needs the FULL template definition visible at your call site, not just a
declaration — which means it has to live somewhere `#include`-able: the header.

**Pitfall/misconception:** it's tempting to think "I only wrote `#include <unordered_map>`, so
where's the actual logic — is it hidden in some library I'm linking against?" No — for the
container classes themselves, essentially all of it is template code that gets compiled fresh,
right there, every time you `#include` the header and use a new type combination.

**Production relevance:** this is a real cost, not just trivia. Every `.cpp` file that uses
`unordered_map<std::string, int>` re-instantiates (re-compiles) that specific version of the
class. The linker later deduplicates identical instantiations across files, but the compile-time
cost of generating them is paid repeatedly — this is a major reason heavily templated codebases
(the STL, and later Unreal's `TArray`/`TMap`, which follow the exact same header-only approach)
have longer compile times than plain non-template code. It's also why your own `AActor` classes
still use the normal `.h`/`.cpp` split — they're not templates, so the normal separate-compilation
rule applies to them fine.

**Edge case:** you CAN force a template to be compiled once, explicitly, for one specific type
(`template class std::vector<int>;` in exactly one `.cpp` file) to avoid repeated instantiation
cost across many files — called **explicit instantiation**. Not needed at your current stage,
just flagging that the "always re-instantiate everywhere" cost has a known workaround in real
large-scale codebases.

## 7. Edge case: custom key types
`std::unordered_map<MyStruct, int>` does **not** compile by default. The compiler has no built-in
way to hash a struct you defined, and no built-in `==` to resolve collisions once two keys land
in the same bucket. You'd need to provide a `std::hash<MyStruct>` specialization and an
`operator==`. Flagging this now, not teaching it in full — come back to it if a project needs a
struct as a map key.
