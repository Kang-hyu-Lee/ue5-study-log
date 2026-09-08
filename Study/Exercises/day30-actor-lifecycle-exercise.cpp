// Day 30 — Actor Lifecycle & Macros Exercises
// Type this yourself (in your UE5 project or as a standalone reasoning exercise
// if you're not adding these specific classes to the project). Don't paste.

// ---------------------------------------------------------------------------
// PROBLEM 1 — Add the missing macros
// This stub is missing UCLASS(), GENERATED_BODY(), and the UPROPERTY()/
// UFUNCTION() macros. Requirements:
//   - Health should be editable in the editor AND readable/writable by Blueprint.
//   - TargetActor is a pointer to another AActor — think about why it needs
//     a macro even with zero specifiers (see concept file section 4 Pitfall).
//   - TakeDamage should be callable from a Blueprint graph.
// Hint: macro placement matters — UCLASS above the class, GENERATED_BODY as
// the FIRST line inside the class body, UPROPERTY/UFUNCTION directly above
// the specific member they apply to.
UCLASS()
class MYPROJECT_API AEnemyCharacter /* : public AActor */
{
    // GENERATED_BODY goes here — you fill it in
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health;
    UPROPERTY()
    AActor* TargetActor;

    UFUNCTION(BlueprintCallable)
    void TakeDamage(float Amount);
};

// ---------------------------------------------------------------------------
// PROBLEM 2 — Bug hunt
// TargetActor below has no UPROPERTY(). Explain in a comment what will
// eventually go wrong, and rewrite the declaration correctly.
// Hint: this isn't about compile errors — it compiles fine. Think about the
// Garbage Collector's perspective (concept file section 4).

class MYPROJECT_API ATurret /* : public AActor */
{
public:
    AActor* TargetActor;   // <-- bug is here

    // your explanation as a comment:
    // Garabage collector cannot see that we are referencing to this object so it may destroy the object but the pointer will become a dangling pointer

    // your fixed declaration:
    UPROPERTY()
    AActor* TargetActor;
};

// ---------------------------------------------------------------------------
// PROBLEM 3 — Order of operations
// Below is a SHUFFLED list of lifecycle-related events for a normal
// play-in-editor session where the actor is already placed in the level.
// Renumber them 1-5 in the correct chronological order.
//
//   4 Tick() runs for the first time
//   1 Constructor runs (CDO creation, at engine startup — before this session)
//   2 BeginPlay() runs
//   5 Tick() runs for the second time
//   3 Constructor runs again (this specific instance, when the level loads)
//


// ---------------------------------------------------------------------------
// PROBLEM 4 — Find and fix the lifecycle bug
// This constructor tries to spawn another actor into the world. Explain why
// that's broken, and rewrite it moved to the correct function.
// Hint: see concept file section 6a "Unsafe here."

/*
AMySpawner::AMySpawner()
{
    GetWorld()->SpawnActor<AActor>(SomeClass, FVector::ZeroVector, FRotator::ZeroRotator);
}
*/

// your explanation:
//We cannot have anything that requires the world in the constructor as GetWorld is unreliable in the constructor and may return a nullptr

// your corrected version (as a comment or real code, your call):
//

// ---------------------------------------------------------------------------
// PROBLEM 5 — Naming convention drill
// For each described item, write the correctly Epic-prefixed name.
// Hint: see concept file section 7 table.
//
//   a) A class deriving from AActor representing a health pickup   -> ____
//   b) A class deriving from UObject (not AActor) for an inventory manager -> ____
//   c) A plain struct holding a damage event's data (no UObject inheritance) -> ____
//   d) An enum for weapon types -> ____
//   e) A boolean tracking whether the player is currently sprinting -> ____
//   f) An interface for anything "interactable" -> ____

// ---------------------------------------------------------------------------
// PROBLEM 6 — SHORT ANSWER (write as a comment)
// Why must Super::BeginPlay() be called as the FIRST line when you override
// BeginPlay()? What specifically goes wrong if you forget it, and why is
// that kind of bug hard to notice?
//
// your answer:
//
