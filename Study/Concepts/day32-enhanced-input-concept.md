# Day 32 — UE5 Enhanced Input System (Applied Block)

## Core Mechanism

The legacy input system bound a **string-named action directly to a hardcoded key**:
```cpp
PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
```
The key itself lived in project config, but the *binding logic* was still rigid — one
action name, resolved through a single global table.

Enhanced Input splits this into two separate asset types:

- **Input Action (`UInputAction`)** — an abstract action ("Jump", "Move", "Fire"), with
  no key attached. It only declares the *shape* of the value it produces:
  - `bool` — a simple press/release (jump, fire)
  - `float` — a single analog axis (a trigger's pull amount)
  - `Vector2D` — two combined axes (WASD movement, a thumbstick)
- **Input Mapping Context (`UInputMappingContext`)** — the actual key→action mapping
  ("W key → Move action, Y-axis positive"). Multiple contexts can be active
  simultaneously, each with a priority.

C++ code binds to the **action asset**, never to a key. Rebinding, adding a second
control scheme, or supporting a new input device becomes a **data change** (edit the
Mapping Context asset in the editor) — zero C++ changes required.

## Implementation — Binding in C++

Declare the assets as `UPROPERTY` so they're assignable in the editor, then bind inside
`SetupPlayerInputComponent` (called automatically by the engine when a pawn is possessed):

```cpp
// Character header (.h)
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
UInputMappingContext* DefaultMappingContext;

UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
UInputAction* JumpAction;

virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
```

```cpp
// Character .cpp
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
    }
}
```

`PlayerInputComponent` arrives as the base `UInputComponent*` type — the `Cast<>` to
`UEnhancedInputComponent` is required to access `BindAction`'s action-asset overload,
and it's a checked cast (returns `nullptr`, doesn't crash, if it somehow fails).

## The Pitfall — Mapping Context Must Be Activated at Runtime

Assigning `DefaultMappingContext` in the editor is **not enough** — it has to be
explicitly added to the player's input subsystem, typically in `BeginPlay()`:

```cpp
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);  // 0 = priority
        }
    }
}
```

**This is the single most common Enhanced Input bug.** Everything compiles cleanly, both
assets are correctly assigned in the editor, `BindAction` runs with no error — and
pressing the key does nothing, silently. No crash, no warning. The binding never fires
because the context was never told to be active. If input "just doesn't work" later,
this is the first thing to check — before assuming the binding, the asset, or the key
mapping itself is wrong.

## Why It Matters

- Rebindable controls — a near-universal shipped-game requirement — are close to free
  with Enhanced Input: editing a data asset, not writing custom save/load logic that
  maps player choices back onto hardcoded `BindAction` calls (which is what the legacy
  system required).
- Multiple Mapping Contexts with priorities is how systems like pause menus "steal"
  input: push a higher-priority UI context, and gameplay's binding to the same physical
  key stops firing — without touching a single line of gameplay input code.

## Edge Case

Two active Mapping Contexts can bind the **same physical key** to **different actions**.
Priority (the second argument to `AddMappingContext`) resolves the conflict — higher
priority wins. This is intentional and load-bearing (it's the pause-menu mechanism
above), but it also means a bug where "my key does the wrong thing" can be caused by an
unexpected second context being active with a higher priority than you assumed, silently
overriding the one you were looking at.
