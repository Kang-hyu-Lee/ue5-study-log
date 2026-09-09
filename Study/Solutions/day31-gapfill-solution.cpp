// Day 31 Gap-Fill Solutions — TWeakObjectPtr, enum class, std::vector
// Read AFTER attempting every problem yourself.

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"
#include <vector>

// ---------------------------------------------------------
// PROBLEM 1 — TWeakObjectPtr Storage + Safe Use
// ---------------------------------------------------------
void Problem1_WeakPtrUsage(AActor* LastAttacker)
{
	TWeakObjectPtr<AActor> WeakAttacker = LastAttacker; // stores without creating a GC root

	// --- "later" block, simulating time passing / the actor possibly being destroyed ---
	if (WeakAttacker.IsValid()) // MUST check right before use, not assume from earlier
	{
		AActor* Attacker = WeakAttacker.Get();
		UE_LOG(LogTemp, Warning, TEXT("Last attacker: %s"), *Attacker->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Last attacker is no longer valid."));
	}
}

// ---------------------------------------------------------
// PROBLEM 2 — Why not a raw UPROPERTY() AActor*
// ---------------------------------------------------------
// A UPROPERTY() AActor* is a GC root — it FORCES the referenced actor to stay
// alive as long as this pointer exists, purely because something is pointing
// at it. "LastAttacker" is a reference we want to REMEMBER, not one that should
// keep an otherwise-dead enemy artificially alive forever after it despawns.
// TWeakObjectPtr gives us the memory (who it was) without that side effect —
// the actor can be destroyed/GC'd normally, and we just detect that via IsValid().

// ---------------------------------------------------------
// PROBLEM 3 — enum class + switch
// ---------------------------------------------------------
enum class EDoorState : uint8
{
	Closed,
	Open,
	Locked
};

void Problem3_DoorStateSwitch(EDoorState State)
{
	switch (State)
	{
		case EDoorState::Closed:
			UE_LOG(LogTemp, Warning, TEXT("Door is closed."));
			break;
		case EDoorState::Open:
			UE_LOG(LogTemp, Warning, TEXT("Door is open."));
			break;
		case EDoorState::Locked:
			UE_LOG(LogTemp, Warning, TEXT("Door is locked."));
			break;
	}
	// no `default:` needed here since all 3 enum values are handled explicitly —
	// the compiler can even warn you if a case is missing, since the enum's full
	// set of values is known at compile time.
}

// ---------------------------------------------------------
// PROBLEM 4 — Old-style enum naming collision
// ---------------------------------------------------------
// With old-style `enum EDoorState { Closed, Open, Locked };` and
// `enum EWeaponState { Closed, Open, Reloading };` in the SAME scope, this
// simply fails to compile: `Closed` and `Open` are declared twice at the same
// scope level — old-style enum values are NOT namespaced to their enum, they
// leak directly into the surrounding scope. `enum class` avoids this entirely
// because every value must be written as `EDoorState::Closed` or
// `EWeaponState::Closed` — the enum name itself acts as a namespace, so two
// different enums can reuse the same member names with zero conflict.

// ---------------------------------------------------------
// PROBLEM 5 — std::vector Basics
// ---------------------------------------------------------
void Problem5_VectorBasics()
{
	std::vector<int> Nums;
	Nums.push_back(10);
	Nums.push_back(20);
	Nums.push_back(30);

	UE_LOG(LogTemp, Warning, TEXT("Size: %d"), (int)Nums.size());

	for (int N : Nums) // range-based for — same syntax already known
	{
		UE_LOG(LogTemp, Warning, TEXT("Element: %d"), N);
	}
}

// ---------------------------------------------------------
// PROBLEM 6 — Pointer Safety After Reallocation
// ---------------------------------------------------------
// NOT safe. A std::vector with only 2 elements has very little spare capacity;
// pushing 50 more almost certainly forces at least one reallocation — the
// vector allocates a new, larger block of memory, copies all existing elements
// into it, and frees the old block. The pointer you took to the OLD memory
// location is now dangling — it points at freed memory. Using it is undefined
// behavior (might crash, might silently read garbage, might "work" by luck).
// This is exactly why you generally don't hold raw pointers/iterators into a
// vector across any operation that might grow it.

// ---------------------------------------------------------
// PROBLEM 7 — Cross-Tie to Hashing
// ---------------------------------------------------------
// A hash map with chaining is, structurally, an array of "buckets," where each
// bucket needs to hold a growable list of entries (since multiple keys can
// collide into the same bucket). That growable per-bucket list is implemented
// as a std::vector — so std::vector<Entry> is literally the data structure
// sitting inside each bucket of the hash table you learned Day 29/30.
