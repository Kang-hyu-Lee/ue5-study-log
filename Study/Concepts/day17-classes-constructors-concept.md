# Day 17 — Classes: Constructors, Destructors, Member Functions

Prerequisite recall (Day 15): a `class` is a `struct` that defaults to
`private` member access instead of `public`. Everything below applies to
both — access control itself isn't taught until Day 18.

## Member functions — the core mechanism

A member function is a function DEFINED INSIDE a class/struct that gets
implicit access to that specific object's data, without you passing the
object in as a parameter.

```cpp
struct Counter
{
    int Value;

    void Increment()          // member function
    {
        Value = Value + 1;    // "Value" here means THIS object's Value —
    }                          // no parameter needed to say which object
};
```

Compare to a free function doing the same thing:
```cpp
void IncrementFree(Counter& c) { c.Value = c.Value + 1; }
```
Both do the same work. The member function version is really
`IncrementFree(this Counter)` under the hood — the compiler secretly passes
a pointer to the calling object (called `this`) into every member function.
`Obj.Increment()` and `IncrementFree(Obj)` compile to nearly identical
machine code — the member-function syntax is convenience, not magic.

**Pitfall:** beginners sometimes think member functions can see OTHER
objects' data of the same type for free. They can't — `Increment()` only
ever has implicit access to the object it was called ON.

## Constructors — the core mechanism

A constructor is a special member function that runs AUTOMATICALLY every
time an object is created. Rules:
- Same name as the class, no return type (not even `void`).
- Its job: get every member into a valid starting state.

```cpp
struct Counter
{
    int Value;

    Counter()              // default constructor — no parameters
    {
        Value = 0;
    }

    Counter(int startValue) // parameterized constructor — overload
    {
        Value = startValue;
    }
};

Counter A;        // calls Counter() -> A.Value = 0
Counter B(5);      // calls Counter(int) -> B.Value = 5
```

### Initialization lists (the preferred form)

```cpp
Counter(int startValue) : Value(startValue) { }
```
The part after `:` is the initializer list — it initializes members BEFORE
the constructor body runs, directly, instead of default-constructing them
first and then reassigning inside the body. For simple types like `int` the
difference is invisible, but for members that are themselves objects with
their own constructors (e.g. a `TArray` or `FString` in UE5), the
initializer-list form avoids constructing-then-immediately-overwriting —
real, measurable cost at scale.

**Edge case that breaks the naive mental model:** members are initialized
in the ORDER THEY'RE DECLARED IN THE CLASS, not the order they appear in
the initializer list. Writing `: B(A), A(1)` when the class declares `A`
before `B` will initialize `A` first regardless — and if `B`'s init
expression depends on `A`, this can silently read a garbage/uninitialized
value if you assumed list-order. Compilers will even warn about this
(`-Wreorder`).

## Destructors — the core mechanism

A destructor is a special member function that runs AUTOMATICALLY right
before an object is destroyed — when a stack-allocated object goes out of
scope, or when `delete` is called on a heap-allocated one.

```cpp
struct Counter
{
    int Value;
    ~Counter()                          // destructor: ~ + class name, no params, no return
    {
        cout << "Counter destroyed" << endl;
    }
};
```

**Why it matters (direct tie to Day 16):** this is where `new`/`delete`
cleanup actually gets automated. If a class owns a heap pointer, the
destructor is the correct, single place to `delete` it — guaranteeing
cleanup happens exactly once, automatically, no matter how the object's
lifetime ends.

```cpp
struct Owner
{
    int* Data;
    Owner()  { Data = new int(0); }     // acquire the resource in the constructor
    ~Owner() { delete Data; }           // release it in the destructor — RAII
};
```
This pattern — acquire in constructor, release in destructor — is called
**RAII** (Resource Acquisition Is Initialization). It's the single biggest
reason C++ classes exist as more than "structs with functions": tying a
resource's lifetime to an object's lifetime means you literally cannot
forget to clean up, as long as the object itself is destroyed properly.

## Common pitfall: the vanishing default constructor

The compiler auto-generates a default (no-argument) constructor for you —
UNTIL you define ANY constructor yourself, at which point the free one
disappears completely.

```cpp
struct Counter
{
    int Value;
    Counter(int startValue) : Value(startValue) {}
};

Counter A;        // COMPILE ERROR — no matching constructor.
                   // The moment you wrote Counter(int), the implicit
                   // Counter() stopped existing.
```
If you need both, you must write both explicitly.

## Edge case: destructor + linked list = danger

Direct relevance to your `TodoNode` portfolio file. If you gave `TodoNode` a
destructor that does `delete Next;`, then deleting ONE node would trigger
its destructor, which deletes `Next`, which triggers ITS destructor, which
deletes ITS `Next` — a cascading chain reaction that destroys the ENTIRE
rest of the list from a single `delete`. That might be exactly what you
want when the whole list is torn down at once — but it's exactly WRONG for
`DeleteCompleted`, which needs to remove ONE node while leaving the rest of
the chain intact. This is a real, common bug source: a destructor that's
correct for "destroy everything" silently breaks "destroy one item."
Something to keep in mind if/when `TodoNode` gets converted from struct to
class later.

## UE5 tie-in

`UObject`-derived classes do NOT use raw C++ destructors for cleanup the way
shown here — they're managed by Unreal's garbage collector (flagged Day 16).
You'll still write regular constructors on them (`AMyActor()` sets default
property values), but you generally do NOT write a custom destructor to
free `UObject*` members — the GC handles that. Writing `delete` on a
`UObject*` yourself is a common, serious beginner mistake once Phase 2
starts. Plain C++ classes/structs (non-`UObject` — like your `TodoNode`,
like gameplay-logic-only helper classes) still follow everything in this
file exactly as written.

*(flagged Day 17)*
