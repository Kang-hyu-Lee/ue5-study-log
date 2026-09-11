// Day 31 Applied Exercises — UActorComponent, Attaching, GetOwner()
// NOTE: real UE5 classes need a .h/.cpp split and must be created via
// Tools > New C++ Class in the editor wizard (never hand-created files —
// this is a study/reference format only). Use the wizard to generate
// UHealthRegenComponent, then type the content below into the generated files.
// Type it yourself. Do not paste. Explain each non-trivial line back before moving on.

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthRegenComponent.generated.h"

// ---------------------------------------------------------
// PROBLEM 1 — Declare the Component
// ---------------------------------------------------------
// Fill in the class so it:
// - Inherits from UActorComponent
// - Has a UPROPERTY(EditAnywhere) float called RegenRate
// - Has a UPROPERTY(EditAnywhere) float called MaxHealth
// - Declares (but does not yet define) a constructor
// - Overrides BeginPlay() and TickComponent()
// Hint: TickComponent's exact signature is fixed by the engine — look it up on
// cppreference-adjacent UE5 docs or ask if stuck; it takes (float DeltaTime,
// ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction).
UCLASS(/* TODO: ClassGroup + meta, matching Day 30's UCLASS() pattern */)
class UHealthRegenComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// TODO: UPROPERTY float members here

	// TODO: constructor declaration here

protected:
	// TODO: virtual void BeginPlay() override; declaration
	// TODO: virtual void TickComponent(...) override; declaration
};

// ---------------------------------------------------------
// PROBLEM 2 — Constructor
// ---------------------------------------------------------
// In the .cpp, define the constructor:
// - Enable component ticking (hint: PrimaryComponentTick.bCanEverTick = true;)
// - Set default values for RegenRate and MaxHealth
// TODO

// ---------------------------------------------------------
// PROBLEM 3 — BeginPlay + GetOwner()
// ---------------------------------------------------------
// In BeginPlay():
// - Call Super::BeginPlay() first (same rule as Actor's BeginPlay from Day 30)
// - Call GetOwner() and log its name
// Hint: AActor* Owner = GetOwner(); if (Owner) { UE_LOG(LogTemp, Warning, TEXT("Owner: %s"), *Owner->GetName()); }
// TODO

// ---------------------------------------------------------
// PROBLEM 4 — Conceptual (answer in a comment)
// ---------------------------------------------------------
// Explain in your own words why calling GetOwner() inside THIS component's
// constructor (instead of BeginPlay) is risky, even though it might sometimes work.
// TODO: write your answer as a comment.
// Just like GetWorld for AActor, without the THIS's constructor and BeginPlay running to setup AActor that the component is attached to, it might return nullptr

// ---------------------------------------------------------
// PROBLEM 5 — Conceptual (answer in a comment)
// ---------------------------------------------------------
// This component never calls SetupAttachment(). Explain why not, and what
// UE5 base class WOULD need it instead.
// TODO: write your answer as a comment.
// SetupAttachment is a USceneComponent only concept, this component is a non-spatial (no transform) so it doesn't need to physically attach