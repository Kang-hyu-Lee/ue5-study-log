// Day 17 — Classes: Constructors, Destructors, Member Functions — SOLUTIONS

#include <iostream>
using namespace std;

// ============================================================
// PROBLEM 1 — SOLUTION
// ============================================================
class Rectangle
{
public:
    float Width, Height;

    float Area()
    {
        return Width * Height;
    }

    float Perimeter()
    {
        return 2 * (Width + Height);
    }
};

// ============================================================
// PROBLEM 2 — SOLUTION
// ============================================================
class Rectangle2
{
public:
    float Width, Height;

    Rectangle2()                          // default constructor
        : Width(1), Height(1) { }

    Rectangle2(float w, float h)          // parameterized constructor
        : Width(w), Height(h) { }

    float Area() { return Width * Height; }
};

// ============================================================
// PROBLEM 3 — SOLUTION
// ============================================================
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

    int Get()
    {
        return *Value;
    }
};
// Expected behavior in main(): "IntBox destroyed" prints exactly at the
// closing `}` of the nested block — NOT at program exit, NOT when Get()
// is called. Stack-allocated objects are destroyed automatically the
// instant they go out of scope, in reverse order of creation. This is the
// mechanism RAII relies on: no manual delete needed at the call site at
// all, because scope exit triggers it for you.

// ============================================================
// PROBLEM 4 — SOLUTION
// ============================================================
// struct Pair { int A; int B; Pair(int b): B(b), A(B+1) {} };
// Declaration order in the struct is A, then B (A declared first).
// So construction initializes A FIRST, regardless of initializer-list
// order. At the moment A is initialized, B has NOT been set yet — B is
// still holding an uninitialized garbage value. A(B+1) reads that garbage
// value, so A ends up garbage/undefined.
// THEN B is initialized: B(b) -> B = 10.
// Result: P.B = 10 (correct, defined). P.A = undefined garbage (reads B
// before B has a real value) — NOT 11, even though the initializer list
// visually suggests B is set before A is computed.
// This is exactly the "edge case that breaks the naive mental model" from
// the concept file — most compilers will warn about this with -Wreorder.

// ============================================================
// PROBLEM 5 — SOLUTION
// ============================================================
// A destructor that does `delete Next;` cascades: deleting ONE node calls
// its destructor, which deletes `Next`, which runs THAT node's destructor,
// which deletes ITS Next, and so on down the entire rest of the chain.
// DeleteCompleted is designed to remove exactly ONE node from the middle
// of the list while the rest of the list stays intact and reachable. If
// TodoNode had that cascading destructor, calling `delete` on the single
// completed node would destroy every node AFTER it in the list too —
// silently corrupting the rest of the to-do list in one call. The fix
// (if TodoNode ever becomes a class) would be a destructor that does NOT
// touch Next at all — ownership of "delete the rest of the chain" belongs
// to a separate explicit function (e.g. a full-list Clear()/destructor on
// the LIST itself, not on each individual node).

int main()
{
    Rectangle r;
    r.Width = 4; r.Height = 3;
    cout << "Rectangle Area: " << r.Area() << endl;

    Rectangle2 defaultRect;
    Rectangle2 customRect(5.0f, 2.0f);
    cout << "Default Rect Area: " << defaultRect.Area() << endl;   // 1
    cout << "Custom Rect Area: " << customRect.Area() << endl;     // 10

    cout << "Before block" << endl;
    {
        IntBox box(42);
        cout << "Box value: " << box.Get() << endl;
    } // "IntBox destroyed" prints HERE, automatically
    cout << "After block" << endl;

    return 0;
}
