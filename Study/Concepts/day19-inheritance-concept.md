# Day 19 — C++: Intro to Inheritance

## Core mechanism

Inheritance lets one class (**derived**) reuse and extend the members of another class (**base**),
instead of copy-pasting fields/functions between related classes.

```cpp
class Entity
{
public:
    Entity(string InName, int InHealth) : Name(InName), Health(InHealth) {}
    void TakeDamage(int Amount) { Health -= Amount; }
    void PrintStatus() { cout << Name << " HP: " << Health << endl; }

protected:              // NEW keyword — see "protected" section below
    string Name;
    int Health;
};

class Player : public Entity                    // "Player IS-AN Entity"
{
public:
    Player(string InName, int InHealth, int InScore)
        : Entity(InName, InHealth), Score(InScore) {}  // base constructor called FIRST

    void AddScore(int Points) { Score += Points; }
    void PrintPlayerStatus()
    {
        PrintStatus();                          // inherited from Entity, callable directly
        cout << "Score: " << Score << endl;
    }

private:
    int Score;                                  // NEW field, only Player has this
};
```

Line by line, what's new vs. Day 17's plain classes:
- `class Player : public Entity` — the colon + `public` is the **inheritance specifier**. It says
  "Player is a kind of Entity" and everything public/protected in Entity becomes part of Player.
- `Entity(InName, InHealth)` in Player's constructor initializer list — you MUST explicitly call
  the base constructor if it takes arguments. C++ doesn't guess which base constructor to use.
- `PrintStatus()` called with no `Entity::` prefix inside `PrintPlayerStatus()` — inherited public
  functions are just... there, as if Player wrote them itself.
- `Score` — a field that exists ONLY on Player, not on Entity. Entity objects never have it.

## `protected` — the third access level

You know `public` (accessible anywhere) and `private` (accessible only inside the class). Add:
- **`protected`** — accessible inside the class AND inside any class that inherits from it, but
  NOT from outside code (e.g. `main()`).

Why it exists: if `Name`/`Health` were `private` in Entity, Player couldn't touch them directly
even though Player "is an" Entity — that defeats the point of inheriting. `protected` is the
middle ground: "family only."

```cpp
Entity E("Goblin", 30);
E.Health = 0;         // ERROR — Health is protected, not accessible from main()
```
Same rule as `private` for OUTSIDE code — `protected` only opens the door for derived classes.

## Construction/destruction order (this WILL be asked in an interview)

**Construction: base first, then derived.** Makes sense — Player can't finish building itself
until the Entity part it's built on top of already exists.
**Destruction: derived first, then base** — exact reverse. Player's own cleanup runs while its
Entity part is still valid, THEN Entity's destructor tears down what's left.

```
Player P("Hero", 100, 0);
// construction order: Entity::Entity() runs -> Player::Player() runs
// (P goes out of scope)
// destruction order: Player::~Player() runs -> Entity::~Entity() runs
```

## Public vs. protected vs. private INHERITANCE (the specifier itself)

`class Player : public Entity` — that `public` also has meaning, separate from member access:

| Inheritance type | Base's `public` members become... | Base's `protected` members become... |
|---|---|---|
| `public` (99% of what you'll use, incl. all UE5 classes) | `public` in derived | `protected` in derived |
| `protected` | `protected` in derived | `protected` in derived |
| `private` | `private` in derived | `private` in derived |

Rule of thumb: **always `public` inheritance** unless you have a specific, deliberate reason not
to (rare outside library-design edge cases). This is the only form UE5's `AActor`, `APawn`,
`ACharacter` chain uses.

## Pitfall #1 — Object slicing

```cpp
void PrintEntity(Entity E) { E.PrintStatus(); }   // takes Entity BY VALUE, not by reference

Player P("Hero", 100, 0);
PrintEntity(P);   // compiles fine — but P gets "sliced" down to just its Entity part.
                   // Score silently disappears for the duration of this call. No error, no warning.
```
Passing/assigning a derived object into a base-typed **variable** (not a pointer or reference)
copies only the base portion. This is a classic silent bug — the fix is to take the parameter by
reference or pointer (`Entity& E` or `Entity* E`), which you already know preserves the real
object instead of copying it.

## Pitfall #2 — no virtual destructor yet (preview only)

```cpp
Entity* E = new Player("Hero", 100, 0);   // base pointer holding a derived object — legal!
delete E;                                  // only Entity's destructor runs, NOT Player's
```
If Player's destructor `delete`s something on the heap, that memory leaks — Player's destructor
never gets called. The fix is the `virtual` keyword on the base destructor, which you'll cover on
Day 22 (polymorphism/virtual functions). Flagging it now so it's not a surprise: **any base class
meant to be deleted through a base pointer needs a virtual destructor.** UE5's `UObject` and
`AActor` already have this handled for you, but you need to know why when you write plain C++.

## Why this matters in production / UE5

Every gameplay class you'll ever write in UE5 is inheritance: `AActor → APawn → ACharacter →
AYourCustomCharacter`. `GENERATED_BODY()` (you'll see this macro in Phase 2) hooks Unreal's
reflection system into this exact C++ inheritance chain. Understanding base/derived construction
order matters directly: UE5 calls `BeginPlay()` up the chain, and forgetting to call
`Super::BeginPlay()` (the UE5 equivalent of calling the base constructor/function explicitly) is
one of the most common beginner bugs in the engine — things silently don't initialize.

## Edge case: multiple inheritance

C++ allows a class to inherit from more than one base (`class C : public A, public B`). This
opens the "diamond problem" (two paths to a shared ancestor cause ambiguity). Not covered now —
UE5 code avoids it almost entirely in favor of composition/interfaces (`UInterface`). Just know
it exists so it's not a surprise if you see `: public A, public B` in someone else's code someday.
