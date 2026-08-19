// Day 16 — Stack vs Heap Memory — SOLUTIONS
// Compare against your own attempt AFTER you've tried. Read the "why" for each.

#include <iostream>
using namespace std;

// ============================================================
// PROBLEM 1 — Identify stack vs heap
// ============================================================
// int a = 5;                       // STACK — plain local int, no `new`
// int* b = new int(5);             // HEAP — `new` always allocates on the heap
// int* c = &a;                     // STACK — c just holds the address of `a`,
//                                     which itself lives on the stack
// int arr[10];                     // STACK — fixed-size local array, no `new`
// int* d = new int[10];            // HEAP — `new[]` allocates the array on the heap;
//                                     `d` (the pointer) lives on the stack, but the
//                                     10 ints it points to live on the heap

// ============================================================
// PROBLEM 2 — Fix the leak
// ============================================================
// Original leaks because `counter` (heap memory from `new int(0)`) is never
// freed before the function returns. The pointer VARIABLE `counter` is
// destroyed when MakeCounter() returns (it's a stack variable), but that
// only destroys the pointer, not the heap memory it pointed to. That heap
// int is now unreachable — nothing holds its address anymore — permanently
// leaked for the rest of the program's run.

void MakeCounterFixed()
{
    int* counter = new int(0);
    *counter = *counter + 1;
    cout << *counter << endl;
    delete counter;      // free it before the function ends
    counter = nullptr;   // convention: null it out so any accidental reuse
                          // crashes predictably instead of corrupting memory
}

// Even better in real code: since this doesn't need to outlive the function
// at all, just use a plain stack int instead of `new` — only reach for the
// heap when the data genuinely needs to survive past the current scope
// (like your TodoNode, which must survive past AddTask returning).

// ============================================================
// PROBLEM 3 — Dangling pointer
// ============================================================
// VersionA has the bug.
//
// int* VersionA()
// {
//     int local = 42;     // stack variable, scoped to VersionA
//     return &local;       // returns the ADDRESS of a stack variable
// }                          // <- local is destroyed HERE, the instant VersionA returns
//
// The bug occurs immediately upon return — the returned pointer is already
// dangling before the caller even gets to use it. The caller might get
// lucky and see 42 still sitting in that memory (undefined behavior can
// "look fine" by coincidence), or might see garbage, or might crash —
// that unpredictability is exactly why it's dangerous: it can pass testing
// and fail later.
//
// VersionB is correct — `heapVal` points to heap memory that survives the
// function returning. BUT it introduces a design risk: the CALLER is now
// responsible for calling delete on the returned pointer, and nothing in
// the function signature enforces that. If the caller forgets -> leak. If
// two different callers each think they own it and both delete it ->
// double delete. This ambiguous-ownership problem is exactly why modern
// C++ prefers smart pointers (unique_ptr) — flagged for Day 23, not needed
// yet, just good to know the raw-pointer version has this real weakness.

// ============================================================
// PROBLEM 4 — Double delete
// ============================================================
// int* a = new int(5);
// int* b = a;          // b now holds the SAME address as a — not a copy of
//                        // the int, a copy of the POINTER (the address)
// delete a;             // frees the heap memory
// delete b;             // UNDEFINED BEHAVIOR — b still holds that now-freed
//                        // address, and delete is called on it a second time
//
// General pattern: this happens whenever heap memory has no single clear
// "owner." If two pointer variables (or two different parts of a codebase)
// both believe they're responsible for freeing the same memory, both will
// eventually call delete on it. The fix is always a design fix, not a
// syntax fix: decide, explicitly, WHICH piece of code owns a given heap
// allocation and is the only one allowed to delete it. This is exactly the
// kind of ownership question your DeleteCompleted function has to answer
// for TodoNode — who deletes a node once it's unlinked from the list?

// ============================================================
// PROBLEM 5 — Portfolio audit
// ============================================================
// This one is genuinely yours to answer by reading your own file — that's
// the point of the exercise. But the shape of the answer, based on how
// AddTask/MarkComplete were built so far:
//
// a) `new` calls: inside AddTask, once per task added (`new TodoNode()`).
// b) `delete` calls: almost certainly none yet — DeleteCompleted isn't
//    finished, and nothing else in the file has a reason to delete.
// c) Yes, it leaks — every task ever added stays allocated on the heap for
//    the entire program run, even after being "removed" from the visible
//    list (once DeleteCompleted unlinks it without deleting it). Also
//    leaks everything still in the list at normal program exit, though
//    that specific case is harmless in practice since the OS reclaims all
//    process memory on exit — the IN-PROGRAM leak from repeated add/delete
//    cycles is the one that actually matters.
// d) DeleteCompleted needs to call `delete` on each node AFTER unlinking it
//    from the list (i.e. after updating the previous node's Next pointer
//    or the Head pointer to skip over it) — deleting before unlinking
//    would lose the pointer needed to fix the links. This directly informs
//    finishing DeleteCompleted next session.

int main()
{
    MakeCounterFixed();
    return 0;
}
