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
}

// ---------------------------------------------------------
// PROBLEM 2 — Conceptual (answer in a comment)
// ---------------------------------------------------------
// Explain why using a raw UPROPERTY() AActor* instead of TWeakObjectPtr
// for "LastAttacker" would be the wrong choice here.
// TODO: write your answer as a comment.

// ---------------------------------------------------------
// PROBLEM 3 — enum class Declaration + Switch
// ---------------------------------------------------------
// Declare an enum class EDoorState : uint8 with values Closed, Open, Locked.
// Write a function that takes an EDoorState and logs a different message
// for each state using a switch statement.
// Hint: switch (State) { case EDoorState::Closed: ... break; ... }
// TODO

// ---------------------------------------------------------
// PROBLEM 4 — Conceptual (answer in a comment)
// ---------------------------------------------------------
// You have two enums: EDoorState { Closed, Open, Locked } and
// EWeaponState { Closed, Open, Reloading }  <- imagine this compiled with
// old-style `enum` instead of `enum class`. What specifically breaks, and why
// does `enum class` avoid it?
// TODO: write your answer as a comment.

// ---------------------------------------------------------
// PROBLEM 5 — std::vector Basics
// ---------------------------------------------------------
// Declare a std::vector<int>, push_back the values 10, 20, 30.
// Log its .size(), then log each element using a range-based for loop.
// TODO
void Problem5_VectorBasics()
{
	// TODO
}

// ---------------------------------------------------------
// PROBLEM 6 — Conceptual (answer in a comment)
// ---------------------------------------------------------
// Take a pointer to element [0] of a std::vector<int> right after creating it
// with 2 elements. Then push_back 50 more elements. Is that old pointer still
// safe to use? Why or why not?
// TODO: write your answer as a comment.

// ---------------------------------------------------------
// PROBLEM 7 — Conceptual, Cross-Tie to Hashing (answer in a comment)
// ---------------------------------------------------------
// Day 29/30 covered hash map chaining for collisions. In one or two sentences,
// explain where std::vector actually shows up inside that mechanism.
// TODO: write your answer as a comment.
