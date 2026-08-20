// Day 17 — Classes: Constructors, Destructors, Member Functions — EXERCISES
// Type your attempts below each problem. Do not look at the solution file until you've tried.

#include <iostream>
using namespace std;

// ============================================================
// PROBLEM 1 — Basic class with member function
// ============================================================
// Write a class `Rectangle` with:
//   float Width, Height;
//   a member function Area() that returns Width * Height
//   a member function Perimeter() that returns 2 * (Width + Height)
// No constructor yet — you'll set Width/Height directly after creating
// the object (this only works because the members are public here — write
// `class Rectangle { public: ... };` for now, since default class access
// is private and you haven't been taught access control yet — Day 18).

// YOUR CODE HERE:
//class Rectangle
//{
//    public:
//
//    float Width, Height;
//    
//    float Area() 
//    {
//        return (Width * Height);
//    }
//
//    float Perimeter()
//    {
//        return 2 * (Width + Height);
//    }
//}



// ============================================================
// PROBLEM 2 — Add constructors
// ============================================================
// Add to Rectangle (or rewrite it):
//   a default constructor that sets Width=1, Height=1
//   a parameterized constructor Rectangle(float w, float h) using an
//     initializer list (not body assignment)
// In main(), create one Rectangle with each constructor and print both
// Area() results.

// YOUR CODE HERE:
class Rectangle
{
    public:
    float Width, Height;
    
    Rectangle(): Width(1), Height(1) {};

    Rectangle(float w, float h): Width(w), Height(h) {};

    float Area() 
    {
        return (Width * Height);
    }

    float Perimeter()
    {
        return 2 * (Width + Height);
    }

};


// ============================================================
// PROBLEM 3 — RAII: constructor/destructor pair
// ============================================================
// Write a class `IntBox` that:
//   holds a single heap-allocated int (int* Value)
//   constructor IntBox(int v): allocates with `new`, stores v
//   destructor ~IntBox(): deletes the pointer, prints "IntBox destroyed"
//   member function Get(): returns *Value
// In main(), create an IntBox on the STACK (not with new) inside a
// nested { } block, call Get() and print it, then let the block end.
// hint: watch the console output — WHEN does "IntBox destroyed" print,
// relative to the closing brace `}`?

// YOUR CODE HERE:
class IntBox
{
    public:
    int* Value;

    IntBox(int v)
    { 
        Value = new int(v);
    }

    ~IntBox() 
    { 
        delete Value;
        cout << "IntBox destroyed" << endl;
    }

    int Get() { return *Value;}
};



// ============================================================
// PROBLEM 4 — Trace by hand (no code)
// ============================================================
// Given:
//   struct Pair
//   {
//       int A;
//       int B;
//       Pair(int b) : B(b), A(B + 1) { }   // note: initializer list order
//                                            // does NOT match declaration order
//   };
//   Pair P(10);
// What are P.A and P.B after construction? Explain WHY using the
// declaration-order rule from the concept file, not the initializer-list
// order as written.

// YOUR ANSWER (as comment):
//Because members are initialized in the order they're declared in the class, A will be initialized first, leading it to access B which hasn't been initialized yet, leading to undefined behaviour
//So we cannot know what A will be because at initialization we are unaware of what is stored in B

// ============================================================
// PROBLEM 5 — Portfolio-relevant conceptual question
// ============================================================
// If TodoNode (from your portfolio to-do list) were converted from a
// plain struct to a class with a destructor that does `delete Next;`,
// what would go wrong the next time DeleteCompleted tries to remove a
// single completed task from the middle of the list? Answer using the
// "destructor + linked list" edge case from the concept file.

// YOUR ANSWER (as comment):
//Triggering a single delete Next would trigger the delete Next of the next node, deleting all the rest of the list

int main()
{
    // Call your Problem 1-3 code here.
    Rectangle NoParam;
    Rectangle Param(2, 2);
    cout << "Area of NoParam: " << NoParam.Area() << " Area of Param: " << Param.Area() << endl;
    
    {
    IntBox Box(30);
    cout<< "IntBox: " << Box.Get() << endl;
    }

    return 0;
}
