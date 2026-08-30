# Day 25 — Const Correctness + Epic Naming Convention Preview

## 1. Four different "const" positions — they mean different things

The most common beginner trap: `const` reads differently depending on WHERE it sits relative to the `*`. Read it **right to left** from the variable name.

```cpp
int Value = 10;
int Other = 20;

const int* PtrToConst = &Value;      // pointer to a CONST int
                                       // -> can repoint the pointer, CANNOT change *PtrToConst
PtrToConst = &Other;                  // OK — repointing is allowed
// *PtrToConst = 99;                  // ERROR — can't modify what it points to

int* const ConstPtr = &Value;         // CONST pointer to a (mutable) int
                                       // -> CANNOT repoint, CAN change what it points to
*ConstPtr = 99;                       // OK — modifying the int is allowed
// ConstPtr = &Other;                 // ERROR — can't repoint a const pointer

const int* const FullyConst = &Value; // CONST pointer to a CONST int — locked both ways
// *FullyConst = 5;                   // ERROR
// FullyConst = &Other;               // ERROR
```

**Memory trick:** read right-to-left starting at the variable name. `int* const ConstPtr` → "ConstPtr is a const pointer to an int." `const int* PtrToConst` → "PtrToConst is a pointer to a const int."

**Pitfall:** confusing these two is one of the most common junior C++ code review comments — "did you mean to lock the pointer or the data?" They are NOT interchangeable.

## 2. const references as function parameters

```cpp
void PrintName(const std::string& Name)   // pass by const reference
{
    std::cout << Name;
    // Name = "hacked";   // ERROR — can't modify, compiler enforces it
}
```

**Why this matters mechanically:** passing by value (`std::string Name`) COPIES the entire string every call — wasteful for large objects. Passing by plain reference (`std::string& Name`) avoids the copy but lets the function silently mutate the caller's data. `const std::string&` gets you BOTH: no copy, AND a compiler-enforced promise the function won't touch it.

**Production reason this matters:** it's an API contract readable at the call site without reading the function body — anyone calling `PrintName(PlayerName)` knows immediately, from the signature alone, that their string is safe. In a large UE5 codebase you will read far more function signatures than function bodies; const correctness front-loads that information.

**Edge case:** primitives (`int`, `float`, `bool`) are cheap to copy — passing `const int&` instead of just `int` is usually pointless overhead (a reference is itself a hidden pointer, so you're paying an indirection cost to "save" a copy that was already cheaper). Reserve `const&` for objects (structs, classes, strings, containers) where copying is expensive.

## 3. const member functions

```cpp
class FVector2
{
public:
    float X, Y;

    float GetLength() const     // <-- const AFTER the parameter list
    {
        return std::sqrt(X * X + Y * Y);
        // X = 5;   // ERROR — const method can't modify member data
    }

    void Normalize()            // NOT const — this one intentionally mutates X, Y
    {
        float Len = GetLength();
        X /= Len;
        Y /= Len;
    }
};
```

**Mechanism:** marking a member function `const` changes what `this` means inside it — normally `this` is `FVector2*`, inside a const method it becomes `const FVector2*`. That's WHY the compiler blocks member writes: you're holding a pointer-to-const.

**Pitfall/edge case:** if you have a `const FVector2 MyVec;` object, you can ONLY call const member functions on it. Calling `MyVec.Normalize()` on a const object is a compile error, even though `Normalize()` is a perfectly valid function on non-const objects. This is a real, common build error the first time you try to call a mutating method on something you (correctly) marked const elsewhere — e.g. a const reference parameter.

**Why it matters in production:** it lets the compiler catch "this function shouldn't be modifying state" bugs at compile time instead of at runtime, and it's REQUIRED to call any member function on a `const&` parameter — if `GetLength()` weren't marked `const`, you couldn't call it from inside another const method, and you couldn't call it on any object passed as `const FVector2&`. This cascades: one missing `const` can block an entire chain of otherwise-valid calls.

## 4. `mutable` — the escape hatch (brief, know it exists)

Occasionally a const method needs to modify ONE specific field that doesn't affect the object's logical state (e.g. a cache, or a debug counter). `mutable` on that field lets it be modified even inside const methods. Rare — flagging so it's not a mystery keyword if you see it, not something to reach for yet.

## 5. Epic naming convention — preview (full depth comes with UE5 setup in Phase 2)

Unreal enforces prefix-based naming so you can tell a type's CATEGORY from its name alone, without an IDE:

| Prefix | Meaning | Example |
|---|---|---|
| `A` | Actor-derived (spawnable in the world) | `APlayerCharacter` |
| `U` | UObject-derived (not necessarily spawnable — components, subsystems, etc.) | `UHealthComponent` |
| `F` | Plain struct / non-UObject class | `FVector2D`, `FHitResult` |
| `T` | Template class | `TArray`, `TMap` |
| `E` | Enum | `EMovementMode` |
| `I` | Interface | `IInteractable` |
| `S` | Slate UI widget | `SButton` |
| `b` | Boolean variable (prefix on the variable name itself, not a type prefix) | `bIsAlive`, `bHasJumped` |

**Why this matters beyond "Epic said so":** in a codebase with thousands of classes, seeing `AEnemy* Target` vs `UEnemyComponent* Target` tells you IMMEDIATELY whether `Target` is a full world-placeable actor or a component attached to something else — no lookup required. This is the same instinct as Hungarian notation but scoped specifically to Unreal's object model, and it's non-negotiable in any UE5 codebase you'll work in professionally.

**Not required yet:** your current portfolio (`todo-list.cpp`, upcoming inventory system) is plain console C++, no UE5 types involved — PascalCase for everything is correct for now (which you're already doing). This table is here so the prefixes aren't a surprise on Day 1 of Phase 2.

## 6. Common pitfall recap
- Confusing `const int*` (pointer to const data) with `int* const` (const pointer to data) — read right-to-left from the variable name.
- Using `const&` on cheap primitives — only worth it for objects.
- Forgetting a member function needs `const` to be callable on a `const` object or through a `const&` parameter — causes confusing "cannot convert" compiler errors.
- Treating Epic prefixes as cosmetic — they encode real type-category information other engineers (and you, in six months) rely on.
