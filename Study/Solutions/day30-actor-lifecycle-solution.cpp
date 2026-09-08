// Day 30 — Actor Lifecycle & Macros Solutions
// Compare against your own attempt AFTER trying each problem.

// ---------------------------------------------------------------------------
// PROBLEM 1 — Solution

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.generated.h"   // this line is what UHT actually needs present in a
                                        // real project header — the .generated.h include must
                                        // always be the LAST include in the file.

UCLASS()
class MYPROJECT_API AEnemyCharacter : public AActor
{
    GENERATED_BODY()   // first line inside the class body

public:
    // EditAnywhere: editable in the Details panel on any placed instance.
    // BlueprintReadWrite: Blueprint graphs can both read and write it.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health;

    // Even with ZERO specifiers, this UPROPERTY is required so the Garbage
    // Collector recognizes this pointer as a live reference to another
    // UObject — without it, the GC could destroy TargetActor's object while
    // this pointer still "points" at it, producing a dangling pointer.
    UPROPERTY()
    AActor* TargetActor;

    // BlueprintCallable: exposes this as a callable node in Blueprint graphs.
    UFUNCTION(BlueprintCallable)
    void TakeDamage(float Amount);
};

// ---------------------------------------------------------------------------
// PROBLEM 2 — Solution

/*
Explanation: AActor* TargetActor with no UPROPERTY() is invisible to the
Garbage Collector. The GC only tracks references it can see via reflection
(UPROPERTY-marked members). If nothing else references the actor TargetActor
points to, the GC may destroy it — TargetActor now points at freed/reused
memory. The code compiles fine and may even work for a while (undefined
behavior doesn't always crash immediately), which makes this exact class of
bug notoriously hard to track down — it can surface far away from the actual
mistake, e.g. as a crash inside an unrelated system that happens to touch
memory the destroyed object used to occupy.
*/

UCLASS()
class MYPROJECT_API ATurret : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY()
    AActor* TargetActor;   // fixed — now GC-visible
};

// ---------------------------------------------------------------------------
// PROBLEM 3 — Solution
//
//   4  Tick() runs for the first time
//   1  Constructor runs (CDO creation, at engine startup — before this session)
//   3  BeginPlay() runs
//   5  Tick() runs for the second time
//   2  Constructor runs again (this specific instance, when the level loads)
//
// Key point: constructor legitimately runs TWICE in different contexts —
// once for the CDO at engine startup (not tied to any level), and again when
// the actual placed instance is created as the level loads. BeginPlay only
// fires for the real instance, once, after that second construction.

// ---------------------------------------------------------------------------
// PROBLEM 4 — Solution
//
// Explanation: GetWorld() is unreliable in the constructor because the
// constructor also runs for CDO creation (engine startup, no level/world
// context exists at all) and during editor reconstruction. Calling
// GetWorld()->SpawnActor(...) here risks a null pointer dereference (crash)
// during CDO creation, or spawning actors unexpectedly inside the editor
// itself during reconstruction — outside any real play session.
//
// Corrected version — moved to BeginPlay(), where GetWorld() is guaranteed valid:

/*
void AMySpawner::BeginPlay()
{
    Super::BeginPlay();   // required first line
    GetWorld()->SpawnActor<AActor>(SomeClass, FVector::ZeroVector, FRotator::ZeroRotator);
}
*/

// ---------------------------------------------------------------------------
// PROBLEM 5 — Solution
//
//   a) AHealthPickup       (AActor-derived)
//   b) UInventoryManager   (UObject-derived, not AActor)
//   c) FDamageEventData    (plain struct, no UObject inheritance)
//   d) EWeaponType          (enum)
//   e) bIsSprinting         (boolean)
//   f) IInteractable        (interface)

// ---------------------------------------------------------------------------
// PROBLEM 6 — Solution
//
// AActor's own BeginPlay() performs real internal setup — it broadcasts the
// "actor has begun play" event that other engine systems (components,
// subsystems, gameplay framework code) listen for, and does its own
// bookkeeping marking the actor as having started play. If your override
// forgets to call Super::BeginPlay() first, none of that inherited behavior
// runs. There's no compile error and often no immediate crash — things that
// depend on that base setup just silently fail to initialize, which can
// surface much later as a seemingly unrelated bug (e.g. a component that
// never receives its own BeginPlay callback), making the missing Super call
// hard to connect to the actual symptom.
