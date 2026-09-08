# Day 30 — `AActor` Lifecycle + Core Reflection Macros

## Recap (Day 29)
You created `MyFirstActor` via the wizard and saw `UCLASS()` / `GENERATED_BODY()` appear, but
only as "UHT generates code here." Today builds the actual mechanism, plus the macros that mark
individual members, plus when in an actor's life each thing is safe to use.

---

## 1. Why does UE5 need its own reflection system at all?

Standard C++ has **no reflection** — at runtime, a compiled C++ program has no built-in way to
ask "what member variables does this class have?" or "call this function by name." Unreal needs
that ability constantly:
- The **Garbage Collector** needs to know which member variables are references to other objects,
  so it doesn't destroy something you're still pointing at.
- **Blueprint** needs to see and call your C++ variables/functions from a visual graph.
- **Serialization** (save games, config files) needs to read/write your properties generically.
- **Replication** (networking, Week 9) needs to know which properties to sync across the network.

Epic solved this by writing their own preprocessing step: **UHT — Unreal Header Tool**. Before
your actual compiler (MSVC/Clang) ever sees your code, UHT scans your header files for specific
macros (`UCLASS`, `UPROPERTY`, `UFUNCTION`, `GENERATED_BODY`) and **generates extra C++ code** in
a hidden file (`YourClass.generated.h`) containing the reflection tables, boilerplate constructors,
etc. that make all of the above possible. You never see or edit that generated file — it's
regenerated automatically every time you build.

---

## 1b. What "reflection" actually means

**Reflection = a program's ability to inspect its own structure (what classes exist, what
properties/functions they have) WHILE RUNNING, instead of that structure only existing at
compile time and then disappearing.**

In plain C++, once your code is compiled, a class is just a memory layout — a fixed sequence of
bytes. Nothing in the compiled binary lets you ask, at runtime, "what member variables does this
object have?" or "call the function named by this string." The compiler knew that information
while compiling, but it doesn't leave it behind for your running program to query — that
information is normally gone after compilation.

**Concrete mechanism:** when you write `UPROPERTY()` above `Health`, UHT generates hidden metadata
(essentially a lookup table entry: "this class has a property named `Health`, it's a `float`, it
lives at this memory offset") alongside your compiled class. That metadata is what lets, for
example, a Blueprint "Set Health" node work at all — the Blueprint virtual machine doesn't have
your C++ class's structure baked into it at Blueprint-compile time. Instead, at runtime, it looks
up `Health` by NAME in that generated metadata table and writes to whatever memory offset the
table says — completely generically, without ever having seen your specific `AEnemyCharacter`
class when the Blueprint editor itself was built.

**Pitfall/misconception:** it's easy to think "reflection = the thing that powers Blueprint
exposure" and stop there. It's actually more foundational than that — the SAME metadata is what
the Garbage Collector uses to find which pointers are live references (section 4's pitfall),
what serialization uses to save/load a `SaveGame` object generically, and what the editor's
Details panel uses to generate property rows without anyone hand-writing UI code per class.
Blueprint exposure is one consumer of reflection, not the definition of it.

**Edge case:** reflection metadata only exists for members you explicitly marked. A completely
normal, functioning C++ member with no `UPROPERTY()`/`UFUNCTION()` is invisible to ALL of the
above — GC, Blueprint, serialization, editor — simultaneously, for the same underlying reason.
That's not four separate gotchas; it's one gotcha (missing reflection metadata) with four
different symptoms depending on which system tries to use it.

## 2. `UCLASS()` — marks the whole class

Goes on its own line, directly above the class declaration:

```cpp
UCLASS()
class MYPROJECT_API AMyFirstActor : public AActor
{
    GENERATED_BODY()
    ...
};
```

This tells UHT "generate reflection/lifecycle code for this entire class." It also accepts
specifiers in the parentheses that change behavior, e.g.:
- `UCLASS(Blueprintable)` — this C++ class can be subclassed as a Blueprint.
- `UCLASS(Abstract)` — this class can never be instantiated directly, only subclassed
  (used for base classes meant purely as a shared parent).

## 3. `GENERATED_BODY()` — the generated-code slot

Must be the **first line inside the class body**. Think of it as a placeholder slot: UHT
generates the actual reflection boilerplate (special constructors, internal bookkeeping) and the
build process pastes it in at this exact spot. You'll never see that code — it lives in the
hidden `.generated.h` — but it's genuinely compiled into your binary.

## 4. `UPROPERTY()` — marks one member VARIABLE

Goes directly above a single member variable:

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite)
float Health;

UPROPERTY()
AActor* TargetActor;
```

**⚠ Pitfall — this is one of the most common real UE5 bugs:** if a member variable is a raw
pointer to a `UObject`/`AActor` and it has **no** `UPROPERTY()`, the Garbage Collector cannot see
that you're referencing that object. The GC may destroy the object your pointer still points to.
Your code still compiles and looks completely correct — it just silently holds a **dangling
pointer** that crashes (or worse, doesn't crash but reads garbage memory) the next time you use
it. `UPROPERTY()` isn't just for editor/Blueprint exposure — even with zero specifiers, it's what
tells the GC "this pointer counts as a reference, don't collect what it points to."

Common specifiers:
- `EditAnywhere` — editable in the Editor's Details panel, on any instance of this actor.
- `VisibleAnywhere` — visible in the Details panel, but not editable.
- `BlueprintReadWrite` — Blueprint graphs can both read and write this variable.
- `BlueprintReadOnly` — Blueprint can read it, not write it.
- `Replicated` — marked for network sync (full depth Week 9).

## 5. `UFUNCTION()` — marks one member FUNCTION

Goes directly above a single member function:

```cpp
UFUNCTION(BlueprintCallable)
void TakeDamage(float Amount);
```

- `BlueprintCallable` — a Blueprint graph can call this C++ function as a node.
- `BlueprintImplementableEvent` — C++ declares the function's signature; the actual body is
  implemented in Blueprint, not C++ (C++ calls it, Blueprint provides the logic).
- `Server` / `Client` / `NetMulticast` — Remote Procedure Calls, networking (Week 9).

---

## 5b. Backfill — `CreateDefaultSubobject<T>()`
Mentioned above as "safe to call in the constructor" without explaining what it does. Normally in
plain C++ you'd create an object with `new`:
```cpp
MyComponent = new UStaticMeshComponent();   // DON'T do this for UE5 components
```
That would work syntactically but breaks Unreal's object system — a component created with raw
`new` is invisible to the Garbage Collector, invisible to reflection, and won't get its own
lifecycle callbacks (no `BeginPlay()` for it, etc.). Instead:
```cpp
MyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyComponent"));
```
This is a special Unreal factory function, only legal to call inside the constructor, that
creates the component through Unreal's own object system — properly registered with the GC,
reflection, and this actor's ownership hierarchy. The `<UStaticMeshComponent>` is a template
argument specifying which type to create (this is why it needs the `<T>` syntax — the function
needs to know the concrete type at compile time to create and return the right thing). The
string argument (`TEXT("MyComponent")`) is just this component instance's internal name, mainly
useful for debugging.
**Pitfall:** calling `CreateDefaultSubobject` outside the constructor is a runtime error, not a
silent bug — this ties directly into why the constructor is *the* place default subobjects get
built, even though (per section 6a) it can't safely touch the wider world.

## 6. The `AActor` Lifecycle — three key moments

### a. Constructor — `AMyFirstActor::AMyFirstActor()`
Runs when the **object** is being constructed in memory. This is NOT the same thing as "the actor
entering the game." Constructors also run when:
- The engine creates the **Class Default Object (CDO)** — a template instance Unreal builds for
  every UCLASS at engine startup, used as the source of default values. This happens even if you
  never place the actor in a level.
- The editor reconstructs the actor (e.g. after you tweak a Blueprint that uses this C++ class as
  its parent).

Because of this, **`GetWorld()` is unreliable in the constructor** — it may return `nullptr`.

**Safe here:** setting default property VALUES, creating component subobjects via
`CreateDefaultSubobject<T>()`.
**Unsafe here:** anything that needs "the world" — finding other actors, spawning actors, playing
sounds, physics queries.

### b. `BeginPlay()` — `virtual void BeginPlay() override`
Runs **once**, when this specific actor instance actually enters gameplay — either the level
starts with the actor already placed, or the actor is spawned at runtime. This is the "safe to
touch the world" moment — `GetWorld()` is guaranteed valid here.

```cpp
void AMyFirstActor::BeginPlay()
{
    Super::BeginPlay();   // MUST be first line
    // your world-dependent setup here
}
```

**Why `Super::BeginPlay()` first:** `AActor`'s own `BeginPlay()` does real internal work
(triggering the base class's own setup, broadcasting the "actor began play" event other systems
listen for). Skipping it doesn't produce a compile error or an obvious crash — it silently breaks
inherited behavior in ways that are hard to trace back to this missing line.

### c. `Tick(float DeltaTime)` — `virtual void Tick(float DeltaTime) override`
Runs **every frame**, if ticking is enabled (`PrimaryActorTick.bCanEverTick = true;` — usually set
in the constructor, off by default for performance). `DeltaTime` = seconds elapsed since the last
frame — multiply any "per-second" rate by `DeltaTime` to make movement/logic frame-rate
independent (e.g. `Location += Speed * DeltaTime;` moves at `Speed` units/second regardless of
whether the game runs at 30fps or 144fps).

**⚠ Pitfall:** putting expensive logic in `Tick()` is a classic beginner performance mistake —
it runs dozens of times per second, for every actor instance that has it enabled. Anything that
doesn't need per-frame precision (e.g. "check every half-second") should use a Timer instead.

### Order at a normal play-in-editor session
`Constructor` (object created, world not guaranteed) → ... → `BeginPlay()` (now safely in world)
→ `Tick()` repeatedly, every frame → `EndPlay()` when the actor is removed (not covered in depth
today — flagging it exists).

**⚠ Edge case:** because the constructor also runs for CDO creation and editor reconstruction, a
constructor that incorrectly tries to spawn actors or play sounds can fire **inside the editor
itself**, completely outside any actual play session — a genuinely confusing bug if you don't
know this is why it's happening.

---

## 7. Epic Naming Convention — spaced-rep review (Phase Gate debt)

| Prefix | Meaning | Example |
|---|---|---|
| `A` | Class derives from `AActor` | `AMyFirstActor` |
| `U` | Class derives from `UObject` but NOT `AActor` | `UActorComponent`, `UUserWidget` |
| `F` | Plain struct / non-UObject type | `FVector`, `FHitResult` |
| `E` | Enum | `EMovementMode` |
| `b` | Boolean variable | `bIsAlive`, `bCanEverTick` |
| `I` | Interface | `IInteractable` |
| `T` | Template class | `TArray`, `TMap` |

You'll apply these prefixes directly in today's exercise file — labeling, not re-learning.
