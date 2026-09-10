// Day 31 Gap-Fill Exercises — TWeakObjectPtr, enum class, std::vector
// Type these yourself. Do not paste. Explain each non-trivial line back before moving on.

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"
#include <vector>

// ---------------------------------------------------------
// PROBLEM 1 — TWeakObjectPtr Storage + Safe Use
// ---------------------------------------------------------
// Write a function that:
// - Takes an AActor* parameter called LastAttacker
// - Stores it in a TWeakObjectPtr<AActor> member-style local variable
// - "Later" (simulate with a second block in the same function) checks
//   IsValid() before using it, and logs the actor's name if valid,
//   or a "no longer valid" message if not.
// Hint: GetName() returns FString; use *SomeActor->GetName() for %s in UE_LOG.
void Problem1_WeakPtrUsage(AActor* LastAttacker)
{
	// TODO
	TWeakObjectPtr<AActor> WeakRef;
	WeakRef = LastAttacker;

	if(WeakRef.IsValid())
	{
		AActor* Actor = WeakRef.Get();
		UE_LOG(LogTemp, Log, TEXT("Attacker: %s"), *Actor->GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("no longer valid"));
}

// ---------------------------------------------------------
// PROBLEM 2 — Conceptual (answer in a comment)
// ---------------------------------------------------------
// Explain why using a raw UPROPERTY() AActor* instead of TWeakObjectPtr
// for "LastAttacker" would be the wrong choice here.
// TODO: write your answer as a comment.
// Becuase we don't want the reference to keep the last attacker alive forever because a UPROPERTY() pointer makes the attacker reachable from the root set,
// so the actor would be uncollected even after death, thus using a TWeakObjectPtr for memory 

// ---------------------------------------------------------
// PROBLEM 3 — enum class Declaration + Switch
// ---------------------------------------------------------
// Declare an enum class EDoorState : uint8 with values Closed, Open, Locked.
// Write a function that takes an EDoorState and logs a different message
// for each state using a switch statement.
// Hint: switch (State) { case EDoorState::Closed: ... break; ... }
// TODO
enum class EDoorState : uint8 {Closed, Open, Locked};

void DoorStateSwtich(EDoorState State)
{
	switch(State)
	{
		case EDoorState::Closed:
			UE_LOG(LogTemp, Warning, TEXT("Closed"));
			break;
		
		case EDoorState::Open:
			UE_LOG(LogTemp, Warning, TEXT("Open"));
			break;
		
		case EDoorState::Locked:
			UE_LOG(LogTemp, Warning, TEXT("Locked"));
			break;
		
		default:
			UE_LOG(LogTemp, Warning, TEXT("Door state invalid"));
			break;
	}
}

// ---------------------------------------------------------
// PROBLEM 4 — Conceptual (answer in a comment)
// ---------------------------------------------------------
// You have two enums: EDoorState { Closed, Open, Locked } and
// EWeaponState { Closed, Open, Reloading }  <- imagine this compiled with
// old-style `enum` instead of `enum class`. What specifically breaks, and why
// does `enum class` avoid it?
// TODO: write your answer as a comment.
// enums would conflict on the Close and Open naming because the compiler can't tell which one I'm calling, whereas enumclass is EDoorState::Open, letting the compiler know we want the Open from EDoorState

// ---------------------------------------------------------
// PROBLEM 5 — std::vector Basics
// ---------------------------------------------------------
// Declare a std::vector<int>, push_back the values 10, 20, 30.
// Log its .size(), then log each element using a range-based for loop.
// TODO
void Problem5_VectorBasics()
{
	// TODO
	std::vector<int> Nums;
	Nums.push_back(10);
	Nums.push_back(20);
	Nums.push_back(30);

	UE_LOG(LogTemp, Log, TEXT("Size: %d"), Nums.size());
	for(int N : Nums){
		UE_LOG(LogTemp, Log, TEXT("%d"), N);
	}
}

// ---------------------------------------------------------
// PROBLEM 6 — Conceptual (answer in a comment)
// ---------------------------------------------------------
// Take a pointer to element [0] of a std::vector<int> right after creating it
// with 2 elements. Then push_back 50 more elements. Is that old pointer still
// safe to use? Why or why not?
// TODO: write your answer as a comment.
// No the vector had to go through resizing meaning the old pointer to element [0] is no longer safe to use if you need to use it take a fresh pointer/reference at that point

// ---------------------------------------------------------
// PROBLEM 7 — Conceptual, Cross-Tie to Hashing (answer in a comment)
// ---------------------------------------------------------
// Day 29/30 covered hash map chaining for collisions. In one or two sentences,
// explain where std::vector actually shows up inside that mechanism.
// TODO: write your answer as a comment.
// so we store collisions in different ways and one of them is chaining which means the keys are put in the same bucket in this case
// as the vector could resize it allows it to continue chaining in the bucket making it a good option to select
