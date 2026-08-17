// Day 12 — References vs Pointers — SOLUTIONS

// ---------------------------------------------------------------
// Problem 1 — Reference swap
void Swap(int& A, int& B)
{
    int Temp = A;   // A is already the int itself (A is a reference) —
                    // this copies the VALUE, immune to later reassignment
    A = B;
    B = Temp;
}

// ---------------------------------------------------------------
// Problem 2 — Pointer swap
void SwapPtr(int* A, int* B)
{
    int Temp = *A;   // must dereference: *A is "the int A points to."
                      // Temp must hold a VALUE (int), not another address
                      // (int*) — if Temp were int* Temp = A, it would
                      // still point at A's memory, and by the time you
                      // read *Temp later, that memory could already be
                      // overwritten by the line above it.
    *A = *B;          // write B's value into A's address
    *B = Temp;         // write the saved original value into B's address
    // Note: A and B (the pointer variables themselves) are never
    // reassigned — only the values AT the addresses they hold change.
    // That's the whole point: the caller's ints (not the caller's local
    // pointer copies) end up swapped.
}

// ---------------------------------------------------------------
// Problem 3 — Spot the bug
//
// int& GetDoubled(int Value)
// {
//     int Result = Value * 2;
//     return Result;
// }
//
// Bug: Result is a local variable — it lives on the function's stack
// frame. That memory is reclaimed the moment the function returns.
// Returning a REFERENCE to Result hands the caller an alias to memory
// that no longer belongs to anything. This is a dangling reference —
// same category of bug as a dangling pointer, just without * syntax to
// flag it visually. It compiles cleanly and may even "work" on some
// runs (undefined behavior can look correct by luck), which is exactly
// what makes it dangerous: it won't reliably fail during testing.
// Fix (conceptually): return int (by value), not int&, since there's no
// caller-owned variable to alias here.

// ---------------------------------------------------------------
// Problem 4 — const& vs value
struct FakeStruct
{
    int Values[20];
};

void TakesByValue(FakeStruct S)
{
    // Every call copies all 20 ints (80 bytes) onto the stack.
}

void TakesByConstRef(const FakeStruct& S)
{
    // No copy — S is an alias for the caller's actual struct. const
    // blocks this function from modifying it, giving the same safety
    // guarantee as pass-by-value without paying for the copy.
}
// In real UE5-style code: use TakesByConstRef for anything bigger than a
// primitive (FVector, FTransform, this FakeStruct) — you get read access
// without the cost of copying every byte on every call.

// ---------------------------------------------------------------
// Problem 5 — When NOT to use a reference
//
// Nullability: an inventory slot that may or may not currently hold an
// item — Item* CurrentItem, checked against nullptr, models "possibly
// nothing" in a way a reference (which can never be null) cannot.
//
// Reseating: a character's active skill-set pointer that gets reassigned
// after a job/class change — SkillSet* ActiveSkills = &WarriorSkills;
// later reassigned to &MageSkills. A reference is bound permanently at
// declaration and could never be redirected like this.
//
// Arithmetic: walking a fixed-size char buffer (e.g. char Name[20]) one
// character at a time looking for the '\0' terminator — char* Ptr = Name;
// while (*Ptr != '\0') { Ptr = Ptr + 1; } — this requires actual pointer
// arithmetic (stepping the address itself), which references don't
// support at all.
