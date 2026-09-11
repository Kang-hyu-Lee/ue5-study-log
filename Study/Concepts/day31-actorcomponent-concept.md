# Day 31 (Applied) — UActorComponent, Attaching, GetOwner()

## 1. What Is a Component?

**Mechanism:** `UActorComponent` is the base class for a modular unit of BEHAVIOR or DATA that gets attached to (owned by) an `AActor`. Instead of one giant Actor subclass doing everything, you break behavior into components an Actor mixes and matches — e.g. a `HealthComponent`, an `InventoryComponent`, a custom tick-driven logic component.

Plain `UActorComponent` has **no transform** — no position/rotation of its own in the world. That's specifically what its subclass `USceneComponent` adds (meshes, cameras, anything spatial use `USceneComponent`). A pure logic component — "regenerate health over time," "track a cooldown" — doesn't need a transform, so it stays a plain `UActorComponent`.

**Creation mechanism:** same `CreateDefaultSubobject<T>("Name")` pattern from Day 30, called in the OWNING Actor's constructor. For a plain `UActorComponent`, that's it — being created this way automatically registers it in the Actor's component list. (`SetupAttachment()` is a `USceneComponent`-only concept — only things with a transform need a position in an attachment hierarchy; a non-spatial component has nothing to attach "at.")

**Pitfall:** forgetting `UPROPERTY()` on the component pointer member. Identical GC risk to Day 30's Actor lesson — a component pointer without `UPROPERTY()` isn't a garbage-collection root; the engine can collect the component out from under the Actor, leaving a dangling pointer.

## 2. GetOwner()

**Mechanism:** `GetOwner()` is a member function inherited from `UActorComponent`. Returns the `AActor*` this component is attached to — lets the component reach "outward" to coordinate with its owner (call a sibling component, or `Cast<>` the owner to a specific subclass to read its data).

**Pitfall (timing):** calling `GetOwner()` inside the component's own constructor is risky for the same class of reason `GetWorld()` was risky in the Actor's constructor — the Actor and its full set of components may not all be finished constructing/registering yet, so relying on `GetOwner()`'s result at that exact moment isn't guaranteed safe. Prefer `BeginPlay()` (the component has its own `BeginPlay()` override, separate from the Actor's) for anything that needs a fully-settled owner.

**Edge case:** a component created dynamically at runtime via `NewObject<>()` instead of in the constructor has different registration/attachment timing — `GetOwner()` behavior there is a later topic, not needed yet.

## 3. Component Ticking

**Mechanism:** a component only runs `TickComponent()` if BOTH are true:
1. `PrimaryComponentTick.bCanEverTick = true;` set on the **component itself**, in its constructor
2. The owning **Actor's** own `PrimaryActorTick.bCanEverTick` is also true

**Pitfall:** setting only the Actor's tick flag and assuming attached components tick automatically — they don't. Each ticks independently; both flags must be on.

## New Syntax This Session

- `CreateDefaultSubobject<T>("Name")` — reused from Day 30, same UObject-factory pattern, now applied to a `UActorComponent`-derived class instead of the Actor itself.
- `GetOwner()` — inherited member function, returns `AActor*` (or `nullptr` if called before the component is properly attached).
- `Cast<T>(ptr)` — used lightly here to downcast `GetOwner()`'s `AActor*` to a specific subclass when you need that subclass's own data/functions. Full safety rules (why raw C-style casts are wrong here) are a forward reference to Week 6 (Day 37) — for now, use only the exact pattern shown in the solution file.
