// Day 26 - C++ Weak Spot Review
// Covers this week's newer topics that haven't had timed practice yet:
// const correctness, templates, polymorphism/virtual, unique_ptr, Epic naming.

#include <memory>
#include <string>

// ============================================================
// SECTION 1: CONST CORRECTNESS
// ============================================================

class InventoryItem
{
public:
    InventoryItem(std::string InName, int InQuantity) : Name(InName), Quantity(InQuantity) {}

    // Problem 1: One of these two member function declarations below is missing a `const`
    // it should have, and one of them HAS a `const` it should NOT have. Find both, and
    // explain why for each (what would break, or what capability would be wrongly lost).
    std::string GetName() const { return Name; } //we add const so this is received as a const pointer, guaranteeing to the user that the member variable wont be modified
    void SetQuantity(int NewQuantity) { Quantity = NewQuantity; } //we need to remove const from the function because then nothing can be modified in the functions body, including the quantity assignment

private:
    std::string Name;
    int Quantity;
};

// Problem 2: Given this function signature:
//   void PrintItem(const InventoryItem& Item)
// PrintItem's body tries to call Item.GetName() and it fails to compile (assuming you've
// fixed Problem 1's GetName() to be const-correct... it should still compile fine then).
// But if GetName() were left NON-const, explain exactly why PrintItem would fail to compile,
// referencing what `const InventoryItem&` promises the caller.
// The const reference gives a const this to the getter but the getter can only receive non-const this, and that leads to the compilation error

// ============================================================
// SECTION 2: TEMPLATES
// ============================================================

// Problem 3: Write a template function:
//   template<typename T> T Max(T A, T B)
// that returns whichever of A or B is larger, using operator>.
// Then answer (comment, no code needed): if you call Max(3, "hello"), what happens, and at
// what stage does it fail - is it a declaration-time error or an instantiation-time error?
template<typename T>
T Max(T A, T B)
{
    if(A>=B) return A;
    return B;
}
//it fails when the compiler tried to build the type specific function of this template because there are two types so instantiation-time error I believe

// ============================================================
// SECTION 3: POLYMORPHISM / VIRTUAL FUNCTIONS
// ============================================================

class Shape
{
public:
    // Problem 4: This is currently NOT virtual. Add the `virtual` keyword, then explain
    // in a comment: with a Shape* pointing at a Circle object, what does GetArea() return
    // WITH virtual vs WITHOUT it, and why.
    virtual float GetArea() { return 0.0f; } 
    //Without virtual it would give the GetArea of shape for 0.0f and with virtual, the compiler will check at runtime by looking at the vtable so will run Circle's GetArea 
    //(follow hidden pointer vptr generated when a class has at least one virtual function)
};

class Circle : public Shape
{
public:
    Circle(float InRadius) : Radius(InRadius) {}
    float GetArea() { return 3.14159f * Radius * Radius; }
private:
    float Radius;
};

// Problem 5: Write TotalArea(Shape* Shapes[], int Count) that sums GetArea() across an
// array of Shape* (which may actually point at Circle or other derived objects).
// float TotalArea(Shape* Shapes[], int Count)
float TotalArea(Shape* Shapes[], int Count)
{
    float AreaSum = 0;
    for(int i=0; i<Count; i++)
    {
        AreaSum += Shapes[i]->GetArea();
    }
    return AreaSum;
}

// ============================================================
// SECTION 4: SMART POINTERS
// ============================================================

// Problem 6: This function leaks memory on the early-return path. Rewrite it using
// std::unique_ptr so the leak becomes structurally impossible, not just "remembered."
// int* CreateAndMaybeReturn(bool ShouldSucceed)
// {
//     int* Data = new int(42);
//     if (!ShouldSucceed)
//     {
//         return nullptr; // <- Data leaks here, nothing ever deletes it
//     }
//     return Data;
// }
std::unique_ptr<int> CreateAndMaybeReturn(bool ShouldSucceed)
{
    std::unique_ptr<int>Data = std::make_unique<int>(42); //this makes it delete once out of scope so even on nullptr return
    if(!ShouldSucceed)
    {
        return nullptr;
    }
    return Data;
}

// ============================================================
// SECTION 5: EPIC NAMING CONVENTION
// ============================================================

// Problem 7: Rename each variable below to Epic/UE5 convention, and in a comment next to
// each, state WHICH category rule you applied (not just "add the prefix" - state the
// reasoning, e.g. "bool -> b prefix because...").
//   bool isAlive; bIsAlive type-category prefix meaning the variable is a bool
//   int healthPoints; HealthPoints Pascal Case just lets us know its a plain value type
//   float* damageMultiplier; DamageMultiplier same as above UE doesn't consider pointers when flagging  // this one is a plain (non-UObject) pointer
//   class APlayerCharacter* owner; APlayerCharacter Owner where A is for Actor, so can be created // this one IS a UObject-derived pointer Correction:no prefix on the variable — the A already lives on the type name (APlayerCharacter) it points to
