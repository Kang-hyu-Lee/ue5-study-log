// Day 31 Applied Solutions — UActorComponent, Attaching, GetOwner()
// Read AFTER attempting every problem yourself.

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthRegenComponent.generated.h"

// ---------------------------------------------------------
// PROBLEM 1 — Component Declaration
// ---------------------------------------------------------
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
// ClassGroup/meta mirror Day 30's UCLASS() pattern — groups it sensibly in the
// editor's "Add Component" list and allows adding it from Blueprint too.
class UHealthRegenComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Health")
	float RegenRate;   // how much health regenerates per second

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth;   // upper bound regen won't exceed

	UHealthRegenComponent(); // constructor declaration — defined below

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
};

// ---------------------------------------------------------
// PROBLEM 2 — Constructor
// ---------------------------------------------------------
UHealthRegenComponent::UHealthRegenComponent()
{
	PrimaryComponentTick.bCanEverTick = true; // THIS component's own tick flag —
	                                            // separate from the owning Actor's flag.
	                                            // Both must be true for TickComponent to run.
	RegenRate = 5.0f;
	MaxHealth = 100.0f;
}

// ---------------------------------------------------------
// PROBLEM 3 — BeginPlay + GetOwner()
// ---------------------------------------------------------
void UHealthRegenComponent::BeginPlay()
{
	Super::BeginPlay(); // same non-negotiable rule as Actor's BeginPlay — parent setup
	                     // must run first, or you silently skip engine-internal init.

	AActor* Owner = GetOwner(); // safe here — BeginPlay guarantees the Actor and its
	                             // components are fully constructed/registered by now
	if (Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner: %s"), *Owner->GetName());
		// *Owner->GetName() : GetName() returns an FString; the leading * converts
		// FString -> a raw TCHAR* that UE_LOG's %s format specifier expects.
	}
}

void UHealthRegenComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// regen logic would go here, using DeltaTime the same way Day 30's Actor Tick did —
	// RegenRate * DeltaTime, not a fixed per-frame amount, to stay frame-rate independent.
}

// ---------------------------------------------------------
// PROBLEM 4 — Why GetOwner() in the constructor is risky
// ---------------------------------------------------------
// At constructor time, the component object itself exists, but the broader
// construction/registration sequence for the owning Actor (and any sibling
// components also being created) isn't guaranteed complete yet. Relying on
// GetOwner() returning a fully-usable Actor at that exact moment isn't a
// documented guarantee the way "it's safe by BeginPlay" is. Even if it happens
// to return a valid pointer in today's test, that's not the same as it being
// SAFE — the same category of trap as calling GetWorld() too early: it might
// work by coincidence today and break the moment initialization order shifts
// (e.g. you add another component, or move this one earlier in a component list).

// ---------------------------------------------------------
// PROBLEM 5 — Why no SetupAttachment()
// ---------------------------------------------------------
// SetupAttachment() exists to build a spatial PARENT-CHILD hierarchy of
// transforms (e.g. a weapon mesh attached to a hand socket, whose position
// is defined RELATIVE to its parent). Plain UActorComponent has no transform
// at all — there's no position to express "relative to a parent," so there's
// nothing for SetupAttachment() to do. USceneComponent (and its subclasses:
// UStaticMeshComponent, UCameraComponent, etc.) is the base class that adds
// a transform, and THAT is what needs SetupAttachment() to place it in the
// Actor's component hierarchy.
