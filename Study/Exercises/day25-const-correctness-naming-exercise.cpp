// Day 25 Exercises — Const Correctness + Epic Naming Convention
// Type this file yourself. Do not paste. Compile with: g++ day25-const-correctness-naming-exercise.cpp -o day25const

#include <iostream>
#include <string>
#include <cmath>

// ---------------------------------------------------------------------
// PROBLEM 1: Declare three variables for the SAME int, demonstrating the
// three const-pointer forms. Given:
int SourceValue = 42;
int OtherValue = 99;
//
// (a) Declare a pointer-to-const-int pointing at SourceValue.
// (b) Declare a const-pointer-to-int pointing at SourceValue.
// (c) Declare a const-pointer-to-const-int pointing at SourceValue.
// TODO: write the three declarations here.

const int* PointerToConstInt = &SourceValue;
int* const ConstPointerToInt = &SourceValue;
const int* const ConstPointerToConstInt = &SourceValue;

// ---------------------------------------------------------------------
// PROBLEM 2: For each variable from Problem 1, write ONE line that WOULD
// compile (repoint OR modify, whichever is legal for that variable) and
// as a comment, one line that would NOT compile.
// TODO

void CompileTester()
{
    PointerToConstInt = &OtherValue; //*PointerToConstInt = OtherValue;
    *ConstPointerToInt = OtherValue; //ConstPointerToInst = &OtherValue;
    //Cannot reassign ConstPointerToConstInt because both are const
}
// ---------------------------------------------------------------------
// PROBLEM 3: Fix the function signature.
// This function should NOT copy Name (it's expensive) and should NOT be
// able to modify the caller's string. Rewrite the signature only.
void PrintGreeting(const std::string& Name)   // <-- fix this line
{
    std::cout << "Hello, " << Name << "\n";
}


// ---------------------------------------------------------------------
// PROBLEM 4: Complete the struct below. GetDistanceFromOrigin() should be
// a const member function (it only reads X, Y, never writes them).
// Scale() intentionally mutates X and Y, so it must NOT be const.
struct FPoint2D
{
    float X;
    float Y;

    // TODO: implement GetDistanceFromOrigin() — const, returns sqrt(X*X + Y*Y)
    float GetDistanceFromOrigin() const
    {
        return sqrt(X*X + Y*Y);
    }

    // TODO: implement Scale(float Factor) — not const, multiplies X and Y by Factor
    void Scale(float Factor)
    {
        X *= Factor;
        Y *= Factor;
    }
};


// ---------------------------------------------------------------------
// PROBLEM 5 (trace-through, answer in a comment, no code needed):
// Given:
//   const FPoint2D FixedPoint = { 3.0f, 4.0f };
// Which of these two calls compiles, and which fails? Explain why in one line.
//   (a) FixedPoint.GetDistanceFromOrigin(); //This one compiles because it is const on a const variable
//   (b) FixedPoint.Scale(2.0f); //This one fails because FixedPoint is a const FPoint2D so we can't mutate it


// ---------------------------------------------------------------------
// PROBLEM 6: Naming convention identification.
// For each declared name below, write in a comment which Epic prefix
// category it belongs to (A / U / F / T / E / I / S / b) and why:
//   APlayerController Actor-derived so spawnable in the world
//   UInventoryComponent UObject-derived so not necessarily spawnable, such as component and subsystems amongst others
//   FTransform Plain struct, non-UObject class
//   TArray<int> Template class as we saw can be used with different types where the compiler builds the custom function according to the type that was given
//   EDamageType Enum is a way to add naming to certain variables so like we can make a enum Days = {mon, tue, etc..} Corrected: A fixed set of named categories
//   IInteractable Interface is a prebuilt function structure to apply to make sure it has the functions it needs
//   bIsSprinting Boolean so true or false


// ---------------------------------------------------------------------
// PROBLEM 7: This class has a const-correctness bug. Find it, explain in
// a comment WHY it fails to compile, then fix it.
class FHealthPool
{
public:
    float CurrentHealth;

    float GetHealthPercent(float MaxHealth) const
    {
        //CurrentHealth = CurrentHealth; // bug is here somewhere in this method
                                         // First why are we assigning CurrentHealth to CurrentHealth unless another function updates CurrentHealth, and if it did we need const
                                         // We cannot reassign CurrentHealth because the function is const so we need to remove the line or make the function non const but const makes sense here to get health%
        return CurrentHealth / MaxHealth;
    }
};


int main()
{
    // Use this space to test your Problem 3 and Problem 4 answers once written.
    PrintGreeting("ChaeYeon");
    FPoint2D Point;
    Point.X = 10;
    Point.Y = 20;
    std::cout << "Distance from origin: " << Point.GetDistanceFromOrigin() << std::endl;
    Point.Scale(2);
    std::cout << "Scaled by 2: " << "(" << Point.X << ", " << Point.Y << ")" << std::endl;

    return 0;
}
