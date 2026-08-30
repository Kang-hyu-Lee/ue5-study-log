// Day 25 Solutions — Const Correctness + Epic Naming Convention
// Compare against your own attempt AFTER you've tried every problem.

#include <iostream>
#include <string>
#include <cmath>

int SourceValue = 42;
int OtherValue = 99;

// PROBLEM 1 -------------------------------------------------------------
const int* PtrToConst = &SourceValue;        // (a) pointer to const int
int* const ConstPtr = &SourceValue;          // (b) const pointer to int
const int* const FullyConst = &SourceValue;  // (c) const pointer to const int

// PROBLEM 2 -------------------------------------------------------------
// (a) PtrToConst:
//     WOULD compile:  PtrToConst = &OtherValue;      (repointing is fine)
//     WOULD NOT:      *PtrToConst = 5;                (can't modify pointed-to data)
//
// (b) ConstPtr:
//     WOULD compile:  *ConstPtr = 5;                  (modifying data is fine)
//     WOULD NOT:      ConstPtr = &OtherValue;          (can't repoint a const pointer)
//
// (c) FullyConst:
//     Nothing compiles that changes anything — both are locked.
//     WOULD NOT:      *FullyConst = 5;   AND   FullyConst = &OtherValue;

// PROBLEM 3 -------------------------------------------------------------
void PrintGreeting(const std::string& Name)   // const& : no copy, no mutation allowed
{
    std::cout << "Hello, " << Name << "\n";
}

// PROBLEM 4 -------------------------------------------------------------
struct FPoint2D
{
    float X;
    float Y;

    float GetDistanceFromOrigin() const   // const: only reads X, Y, this becomes const FPoint2D*
    {
        return std::sqrt(X * X + Y * Y);
    }

    void Scale(float Factor)              // NOT const: intentionally mutates X and Y
    {
        X *= Factor;
        Y *= Factor;
    }
};

// PROBLEM 5 -------------------------------------------------------------
// const FPoint2D FixedPoint = { 3.0f, 4.0f };
// (a) FixedPoint.GetDistanceFromOrigin();  -> COMPILES. It's a const method,
//     legal to call on a const object (this is const FPoint2D*, matches).
// (b) FixedPoint.Scale(2.0f);              -> FAILS. Scale() is NOT const,
//     but FixedPoint IS const — calling a mutating method on a const object
//     is a compile error (you'd need a non-const this pointer, don't have one).

// PROBLEM 6 -------------------------------------------------------------
// APlayerController    -> A: Actor-derived (spawnable/possessable world object)
// UInventoryComponent  -> U: UObject-derived, not an actor itself (a component)
// FTransform           -> F: plain struct, no UObject machinery (position/rot/scale bundle)
// TArray<int>          -> T: template class (generic container, works for any type)
// EDamageType           -> E: enum (a fixed set of named categories)
// IInteractable        -> I: interface (a contract other classes implement)
// bIsSprinting         -> b: boolean variable prefix (not a type prefix — applies to the variable name)

// PROBLEM 7 -------------------------------------------------------------
// Bug: `CurrentHealth = CurrentHealth;` inside a const method. Even though
// it assigns a value to itself and LOOKS harmless, it's still a WRITE to a
// member variable, and `this` is `const FHealthPool*` inside a const method
// — the compiler blocks ANY assignment to a member, regardless of whether
// the value actually changes. The compiler doesn't evaluate "is this a
// no-op" — it just sees an assignment to a const-qualified object and rejects it.
//
// Fix: delete that line entirely, it did nothing useful anyway:
class FHealthPool
{
public:
    float CurrentHealth;

    float GetHealthPercent(float MaxHealth) const
    {
        return CurrentHealth / MaxHealth;
    }
};

int main()
{
    FPoint2D P = { 3.0f, 4.0f };
    std::cout << "Distance: " << P.GetDistanceFromOrigin() << "\n";
    P.Scale(2.0f);
    std::cout << "After scale: (" << P.X << ", " << P.Y << ")\n";

    PrintGreeting("Kang");

    return 0;
}
