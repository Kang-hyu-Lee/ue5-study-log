// Day 15 — C++ Exercises: Structs vs Classes
// Write actual code for each problem. Compile-check where noted.

#include <string>
#include <iostream>

// ---------- Problem 1 ----------
// Convert this struct into a class with IDENTICAL behavior (same fields
// accessible the same way from outside). You'll need an access specifier
// keyword you may not have used explicitly before — look up "public"
// on cppreference if the syntax isn't obvious.
struct Vec2
{
    float X;
    float Y;
};
// class Vec2 { ... your version here ... };
//class Vec2
//{
//public:
//    float X;
//    float Y;    
//};

// ---------- Problem 2 ----------
// This class won't compile as-is if you try to touch its fields from
// outside. Fix it by adding the correct access specifier so the fields
// below are reachable from main(). Do NOT change struct/class keyword —
// keep it a class, just fix the access.
class Player
{
public:
    std::string Name;
    int Health;
};
// (in your test code) Player p; p.Name = "Hero";  <-- currently won't compile, fix it


// ---------- Problem 3 — conceptual, answer as a comment ----------
// You're designing a type called InventorySlot that holds an item name
// and a quantity, with NO methods planned — other code will just read
// and set the fields directly. Should this be a struct or a class?
// Justify your answer in 1-2 sentences using the convention from the
// concept file (not just "because it's simpler").

//a struct because it has to be light and is not something that has almost no behaviour and is safe to copy freely


// ---------- Problem 4 — conceptual, answer as a comment ----------
// You're designing a type called BankAccount that holds a balance, and
// must guarantee the balance never goes negative (all changes go through
// a Deposit/Withdraw function that validates the amount). Should this be
// a struct or a class? Justify your answer.

//because a bank balance should stay hidden unless accessed through proper functions it should be a class and only accessed using those functions


// ---------- Problem 5 ----------
// Write a small class called Counter with:
//   - a private int field CurrentCount, starting at 0
//   - a public member function Increment() that adds 1 to CurrentCount
//   - a public member function GetCount() that returns CurrentCount
// (You've seen member functions before on Day 5 — same declaration
// pattern, just now living inside a class body.)
// Then in a short main(), create a Counter, call Increment() 3 times,
// and print GetCount().

class Counter{
    int CurrentCount = 0;
public:
    void Increment(){
        CurrentCount ++;
    }
    int GetCount(){
        return CurrentCount;
    }
};


// ---------- Problem 6 — pitfall check, answer as a comment ----------
// A teammate writes this and says "structs and classes are basically
// interchangeable so it doesn't matter which I pick." They then add a
// virtual function to a struct they're using for UDP network packet data
// that gets raw-copied byte-for-byte over the wire. What's about to break,
// and why (tie your answer to the Edge Case section in the concept file)?

//a struct is not longer POD once you add a virtual function and UE5's USTRUCT() relies on structs staying simple, which can lead to corrupt data

int main(){
    Counter* Count = new Counter();
    Count->Increment();
    Count->Increment();
    Count->Increment();
    std::cout << Count->GetCount() << std::endl;
    
    return 0;
}
