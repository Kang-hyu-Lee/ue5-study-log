// Day 26 - C++ Weak Spot Review - SOLUTIONS

#include <memory>
#include <string>
#include <iostream>

// ============================================================
// SECTION 1: CONST CORRECTNESS
// ============================================================

class InventoryItem
{
public:
    InventoryItem(std::string InName, int InQuantity) : Name(InName), Quantity(InQuantity) {}

    // Problem 1 FIX:
    std::string GetName() const { return Name; } // MISSING const before fix.
    // Why it matters: GetName() doesn't mutate anything, so it should be callable on a
    // const InventoryItem&. Without const here, ANY function that receives the item as
    // `const InventoryItem&` (read-only access) cannot call GetName() at all - the
    // compiler refuses, because a non-const method could theoretically mutate the object,
    // which would violate the const promise.

    void SetQuantity(int NewQuantity) { Quantity = NewQuantity; } // WRONGLY const before fix.
    // Why it matters: SetQuantity DOES mutate Quantity. Marking it const is a straight-up
    // lie to the compiler about intent - it would only compile at all because Quantity is
    // a plain int and not, say, itself const-qualified in a way that blocks it; the deeper
    // problem is semantic, not a compile error: you've told every caller "this function
    // won't change the object," which is false, and it opens the door to real const-away
    // bugs if this class ever gets used through a const reference expecting that guarantee.

private:
    std::string Name;
    int Quantity;
};

// Problem 2:
// `const InventoryItem&` is a promise to the caller AND the compiler: "this function will
// not modify the object it was handed." The compiler enforces that promise by restricting
// what you're allowed to call ON that reference to const-qualified member functions only.
// If GetName() is non-const, calling Item.GetName() through a const reference asks the
// compiler to allow a call that COULD mutate the object (the compiler can't see inside
// GetName() to prove it's actually read-only - it only trusts the const keyword on the
// signature) - so it refuses to compile, full stop, not a warning.

// ============================================================
// SECTION 2: TEMPLATES
// ============================================================

template<typename T>
T Max(T A, T B)
{
    return (A > B) ? A : B;
}
// Max(3, "hello") fails at INSTANTIATION time, not declaration time. The template itself
// compiles fine with no type specified - it's just a blueprint. Only when you actually call
// Max(3, "hello") does the compiler try to instantiate T=int for one argument and T=const
// char* for the other, can't unify them into one T, and (even if it could) `int > const
// char*` isn't a valid operator> comparison - THAT's where it fails, at the call site, not
// where Max is defined.

// ============================================================
// SECTION 3: POLYMORPHISM / VIRTUAL FUNCTIONS
// ============================================================

class Shape
{
public:
    virtual float GetArea() { return 0.0f; } // Problem 4 FIX: added virtual
    // WITHOUT virtual: Shape* pointing at a Circle calls Shape::GetArea() (returns 0.0f) -
    // the compiler picks the function based on the STATIC (pointer's declared) type at
    // compile time. This is called "hiding," not overriding - Circle::GetArea() exists but
    // is never reached through a base pointer.
    // WITH virtual: the call is resolved at RUNTIME via a vtable lookup based on the
    // ACTUAL object type the pointer points to - so Shape* pointing at a Circle correctly
    // calls Circle::GetArea(). This is the entire mechanism that makes "process an array
    // of different derived types through one base pointer type" work at all.
};

class Circle : public Shape
{
public:
    Circle(float InRadius) : Radius(InRadius) {}
    float GetArea() override { return 3.14159f * Radius * Radius; } // `override` optional but
    // recommended: makes the compiler verify this actually overrides a virtual base method
    // (catches typos in signature that would otherwise silently create a NEW unrelated
    // function instead of overriding).
private:
    float Radius;
};

// Problem 5
float TotalArea(Shape* Shapes[], int Count)
{
    float Total = 0.0f;
    for (int i = 0; i < Count; i++)
    {
        Total += Shapes[i]->GetArea(); // virtual dispatch picks the right derived GetArea()
    }
    return Total;
}

// ============================================================
// SECTION 4: SMART POINTERS
// ============================================================

std::unique_ptr<int> CreateAndMaybeReturn(bool ShouldSucceed)
{
    std::unique_ptr<int> Data = std::make_unique<int>(42);
    if (!ShouldSucceed)
    {
        return nullptr; // Data (the unique_ptr) goes out of scope here -> its destructor
        // runs automatically -> the int it owned is deleted. No leak, no explicit delete
        // needed, and it's not a matter of remembering to do it right - there is no delete
        // call anywhere for a leak to be missing FROM.
    }
    return Data; // ownership moves to the caller; Data itself is left empty/null after this
    // (unique_ptr can't be copied, only moved - this is what "unique" ownership means).
}

// ============================================================
// SECTION 5: EPIC NAMING CONVENTION
// ============================================================

// bool bIsAlive;
//   -> `b` prefix: Epic's rule is booleans specifically get `b`, regardless of what they
//      represent, so the type is identifiable at a glance without reading the declaration.
//
// int HealthPoints;
//   -> No prefix, just PascalCase: plain value types (int, float, etc.) other than bool
//      don't get a letter prefix in Epic's convention - PascalCase alone is enough.
//
// float* DamageMultiplier;
//   -> No special prefix: this is a raw pointer to a NON-UObject type. Epic's pointer
//      prefixes (like the historic p-prefix seen in some older codebases) are NOT part of
//      the current standard - modern Epic style just uses PascalCase here too, same as any
//      other variable, and relies on the declared type (visible right next to the name) to
//      convey "this is a pointer."
//
// class AActor* Owner; (using AActor as a stand-in Actor-derived type here, since
// APlayerCharacter itself isn't declared in this file)
//   -> `A` prefix: comes from the TYPE, not from being a pointer. UE5 class-category
//      prefixes: `A` = Actor-derived, `U` = UObject-derived (non-Actor), `S` = Slate
//      widget, `F` = plain struct, `T` = template class, `I` = interface. The prefix on
//      the VARIABLE mirrors the prefix already on the CLASS it points to - it's not an
//      independent "this variable is a pointer" signal the way Hungarian notation would be.
