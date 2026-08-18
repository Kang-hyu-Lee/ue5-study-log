// Day 15 — C++ Solutions: Structs vs Classes

#include <string>
#include <iostream>

// ---------- Problem 1 ----------
struct Vec2
{
    float X;
    float Y;
};

class Vec2Class            // renamed to avoid redefinition clash with struct above
{
public:                    // MUST be explicit — class defaults to private,
    float X;               // without this line X/Y would be unreachable
    float Y;               // from outside the class entirely
};
// Both types behave identically from the outside: Vec2Class v; v.X = 1.0f;
// works exactly like the struct version, ONLY because of the public: line.


// ---------- Problem 2 ----------
class Player
{
public:                    // <-- the fix: without this, Name/Health are
    std::string Name;      //     private by default (class rule) and
    int Health;             //     p.Name = "Hero" fails to compile outside
};
// Note: this makes Player fully public, which somewhat defeats the point
// of using `class` (see the concept file's pitfall on this) — flagged
// here as the mechanical fix; Problem 4 covers when private is the right
// call instead.


// ---------- Problem 3 ----------
// InventorySlot should be a STRUCT. It's plain data with no invariant to
// protect (any name/quantity combination is "valid" from the type's own
// perspective) and no behavior — matches the struct convention exactly:
// "safe to copy freely, no hidden rules to enforce."


// ---------- Problem 4 ----------
// BankAccount should be a CLASS. It has an invariant it must protect
// (balance never negative) that depends on funneling ALL changes through
// validated member functions. Making balance public on a struct would let
// any outside code set it directly (account.Balance = -500;), bypassing
// the validation entirely. Private fields + public Deposit/Withdraw is
// the textbook use case for encapsulation.


// ---------- Problem 5 ----------
class Counter
{
private:                        // explicit for clarity, though class defaults here
    int CurrentCount;

public:
    // Constructor — initializes CurrentCount to 0 when a Counter is created.
    // (New syntax: this is a member function with the SAME NAME as the
    // class, no return type. It runs automatically on creation.)
    Counter()
    {
        CurrentCount = 0;
    }

    void Increment()
    {
        CurrentCount = CurrentCount + 1;
    }

    int GetCount()
    {
        return CurrentCount;
    }
};

int main()
{
    Counter MyCounter;          // constructor runs here, CurrentCount = 0
    MyCounter.Increment();
    MyCounter.Increment();
    MyCounter.Increment();
    std::cout << MyCounter.GetCount() << "\n";   // prints 3
    return 0;
}


// ---------- Problem 6 ----------
// Adding a virtual function to the struct gives it a hidden vtable
// pointer, which means the struct is no longer POD (plain old data) —
// its actual in-memory layout now includes extra bytes the programmer
// didn't put there and the network protocol doesn't know about. Raw
// byte-for-byte copying (memcpy / sending it directly over UDP) will
// now copy garbage/misaligned data instead of the intended fields, and
// the receiving end (which expects the original plain layout) will
// misinterpret the bytes. This is exactly the Edge Case flagged in the
// concept file: "struct" being legal to add behavior to doesn't mean
// it's safe to, once something downstream (replication, serialization,
// raw memory copies) depends on the type staying simple.
