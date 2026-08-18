# Day 15 — Structs vs Classes

## 1. The mechanism: they are almost the same thing
In C++, `struct` and `class` are **the same language construct** with
exactly one default difference:

- `struct` members default to `public`
- `class` members default to `private`

That's it. Everything else — member functions, constructors, inheritance,
pointers, `Next`-style self-reference like in `TodoNode` — works
identically on both. This surprises people coming from other languages
where struct = data-only and class = the "real" object type; in C++ that's
a *convention*, not a rule the compiler enforces.

### Worked example — the exact same type, two ways
```cpp
// As a struct — everything public unless stated otherwise
struct TodoNode
{
    std::string Task;
    bool bComplete;
    TodoNode* Next;   // no access specifier needed — public by default
};

// As a class — identical fields, but now PRIVATE unless stated otherwise
class TodoNode
{
public:                  // <-- must explicitly say this or nothing outside
    std::string Task;    //     the class can touch these fields at all
    bool bComplete;
    TodoNode* Next;
};
```
Compile and behave identically — the only functional difference is what
happens if you *forget* the `public:` line in the class version: every
field becomes inaccessible outside the class, and code like
`node->Task = "buy milk";` fails to compile with an access error.

## 2. The convention (why the distinction still matters)
Even though the compiler treats them the same, professional codebases
(including Epic's) use the choice as a **signal to other programmers**:

- **struct** — "this is plain data, POD (Plain Old Data). Little or no
  behavior. Safe to copy freely, no hidden invariants to protect."
  Example: `TodoNode` (just holds a task string, a bool, a pointer).
- **class** — "this has behavior and internal state it protects.
  Fields are private on purpose — outside code shouldn't reach in and
  mutate them directly; it should go through member functions that keep
  the object in a valid state."

### Pitfall
Using `class` but making everything `public` anyway defeats the entire
point of choosing `class` — you get the compile-time inconvenience
(remembering `public:`) with none of the encapsulation benefit. If a type
has no behavior to protect, it should be a `struct`.

## 3. Why it matters in UE5 specifically
This isn't just style — Epic's engine architecture is *built* on this
distinction, extended with two macros:

- **`USTRUCT()`** — for plain data types: `FVector`, `FRotator`,
  `FTransform`. These are lightweight **value types** — copied by value,
  no garbage collection, no reflection overhead beyond what's tagged.
  Used constantly (every position, every rotation) so they're kept cheap.
- **`UCLASS()`** — for `UObject`-derived types: `AActor`, `APawn`, your
  gameplay classes. These are **reference types**, garbage-collected,
  reflected (visible to Blueprint, editor, serialization), heavier.

Choosing struct vs class for a new UE5 type is really choosing "is this a
cheap bag of data I'll copy around a lot, or a heavyweight object with
identity and lifetime the engine needs to track?" Get this wrong (e.g.
making a per-frame-created value type a UCLASS) and you create GC
pressure/performance problems; get it wrong the other way (UObject data
crammed into a USTRUCT) and you lose garbage collection safety for
pointers inside it.

## 4. Edge case — struct is not automatically "safe to memcpy"
A `struct` in C++ CAN have constructors, destructors, virtual functions,
and even inheritance — it is legal, it compiles. But the moment you add a
virtual function, the struct is no longer POD (plain old data): it gains
a hidden vtable pointer, and things like raw `memcpy`-ing it or blitting
it directly over the network as raw bytes stop being safe. UE5's
`USTRUCT()` network replication and serialization rely on structs staying
simple/blittable — this is a real, non-obvious bug source: "why did my
struct's network replication silently corrupt data" traces back to
someone adding behavior that broke POD-ness.

## 5. Interview framing
"What's the difference between struct and class in C++?" is a near-
guaranteed early screening question. The complete answer isn't just
"default access" — it's default access + the convention it signals +
(bonus, shows real depth) that UE5 encodes this exact distinction into
USTRUCT/UCLASS for GC and replication reasons.
