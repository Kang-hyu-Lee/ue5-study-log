# Day 22 — Polymorphism & Virtual Functions

Builds directly on your `EditorSession` / `TextEditor` hierarchy from Day 20. That
project is the worked example today, not a toy.

## 1. Core Mechanism

Without `virtual`: which function runs is decided at COMPILE time, based on the
**declared type** of the pointer/reference — not the actual object it points to.
This is called static (or early) binding.

With `virtual`: which function runs is decided at RUN time, based on the **actual
type of the object**, regardless of what type of pointer/reference you're holding
it through. This is dynamic (or late) binding — the mechanism IS polymorphism.

**Worked example, using your own classes:**

```cpp
class EditorSession
{
public:
    virtual void PrintContent() const   // <-- "virtual" is the whole mechanism
    {
        cout << Content << endl;
    }
};

class TextEditor : public EditorSession
{
public:
    void PrintContent() const override   // <-- "override" — see Section 4
    {
        cout << "[TextEditor] " << Content << endl;
    }
};

int main()
{
    EditorSession* Ptr = new TextEditor("Hello World");
    Ptr->PrintContent();   // prints "[TextEditor] Hello World" — NOT the base version
}
```

`Ptr`'s DECLARED type is `EditorSession*`. Its ACTUAL type (what it points to) is
`TextEditor`. Because `PrintContent` is `virtual`, the call resolves to
`TextEditor::PrintContent` at runtime — even though the compiler only ever "sees"
an `EditorSession*`. Without `virtual`, it would call `EditorSession::PrintContent`
instead, because static binding only looks at the declared type.

**How it physically works — the vtable:**
Every object of a class with at least one `virtual` function gets a hidden pointer
(the "vptr") added by the compiler, pointing to a per-class table of function
addresses (the "vtable"). Calling a virtual function through a pointer/reference
is really: follow the vptr → look up the function's slot in the vtable → call
whatever address is actually stored there for THIS object's real class. This costs
one extra pointer of memory per object, and one extra indirection per virtual call
— cheap, but not free, which matters when profiling hot loops (e.g. thousands of
actors calling `Tick()` every frame).

## 2. Common Pitfall #1 — Missing Virtual Destructor

```cpp
class EditorSession
{
public:
    ~EditorSession() { /* no virtual */ }   // DANGER
};
```
```cpp
EditorSession* Ptr = new TextEditor("test");
delete Ptr;   // undefined behavior — TextEditor's destructor may never run
```
If the base destructor isn't `virtual`, `delete` through a base pointer only knows
to call the BASE destructor (static binding again — destructors follow the same
rule as any other function). Any resources `TextEditor` owns (like your
`CommandStack`/`LogQueue` members — though those are stack members here, so their
destructors run automatically regardless; this bites harder when a derived class
owns raw heap pointers) can leak silently. **Rule: if a class has ANY virtual
function, or is ever going to be deleted through a base pointer, its destructor
should be virtual.**

## 3. Common Pitfall #2 — Object Slicing (revisit from Day 19)

```cpp
void PrintIt(EditorSession Session)   // pass BY VALUE
{
    Session.PrintContent();   // ALWAYS calls EditorSession's version
}
PrintIt(MyTextEditor);   // TextEditor "sliced" down to just its EditorSession part
```
Polymorphism ONLY works through a pointer or reference. Pass-by-value copies just
the base-class portion of the object — the derived part is literally discarded
("sliced off"). This is the same slicing concept from Day 19's constructor work,
now showing up as a virtual-dispatch bug instead of a construction-order bug.

## 4. The `override` Keyword

```cpp
void PrintContent() const override
```
`override` isn't required to make polymorphism work — but always write it anyway.
It tells the COMPILER "I intend this to override a virtual base function — error
out if it doesn't actually match one." Without it, a typo (wrong signature, forgot
`const`, wrong name) silently creates an unrelated new function instead of an
override, and you get no error — just a confusing bug where the base version keeps
running. `override` converts a silent logic bug into a compile error.

## 5. Why It Matters in Production (UE5)

`AActor::BeginPlay()`, `Tick()`, `EndPlay()` — all `virtual` in Epic's base classes.
Your `Super::BeginPlay()` call from Day 19 makes sense in exactly this light: you're
in an OVERRIDE, and `Super::` explicitly calls the base version first before adding
your own behavior. Every Blueprint-callable/overridable C++ function in UE5 exists
because of this exact mechanism.

## 6. Edge Case Where the Naive View Breaks

**Calling a virtual function from a constructor or destructor does NOT dispatch
polymorphically.** During `EditorSession`'s constructor, the object is not yet a
`TextEditor` — the derived part hasn't been constructed yet — so a virtual call
inside `EditorSession()`'s constructor body will call `EditorSession`'s version,
even if the object being built is ultimately a `TextEditor`. Same logic in reverse
for destructors (derived part is already destroyed by the time the base destructor
runs). This trips up experienced developers, not just beginners — it's a legitimate
interview question.

## Preview (not needed yet)
`virtual void Foo() = 0;` — a "pure virtual" function — makes a class abstract
(can't be instantiated directly, forces derived classes to implement it). Flagging
the syntax now; not covered until it's actually needed.
