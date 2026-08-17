# Pointers Pt.1 — Concept Notes (Day 10)

## What a pointer is
Every variable lives somewhere in memory — it has an **address**. A pointer is
a variable whose value IS an address (not ordinary data like a number or
character) — it "points to" where another variable lives.

## The two operators

- `&` (address-of): given a variable, gives you its memory address.
- `*` (dereference): given a pointer, gives you the value stored AT that
  address. Also used when *declaring* a pointer type.

These are the same symbols as multiplication (`*`) and bitwise AND (`&`) —
context (are you declaring/using a pointer, or doing arithmetic?) tells C++
which meaning applies. This dual-use is a common early confusion point.

## Worked example — line by line

```cpp
int x = 5;        // 1. normal int variable, holds value 5
int* ptr = &x;     // 2. ptr is declared as "pointer to int", initialized
                    //    to hold the ADDRESS of x (not the value 5)

std::cout << x;     // 3. prints 5 — the value of x
std::cout << &x;     // 4. prints x's address (some hex number, e.g. 0x7ffee...)
std::cout << ptr;     // 5. prints the SAME address as line 4 — ptr holds x's address
std::cout << *ptr;     // 6. prints 5 — dereferencing ptr means "go to that
                        //    address and give me the value stored there"

*ptr = 10;              // 7. dereference ptr, then ASSIGN through it —
                        //    this changes x itself (not ptr) to 10,
                        //    because *ptr means "the thing ptr points to"
std::cout << x;         // 8. prints 10 — x actually changed, even though
                        //    we never wrote "x = 10" directly
```

Line-by-line breakdown of the concept:
- Line 1: ordinary variable, ordinary memory slot.
- Line 2: `int*` is the TYPE ("pointer to int"). `ptr` doesn't hold 5 — it
  holds x's address. Two separate pieces of data exist now: x (value 5) and
  ptr (an address that happens to point at x).
- Lines 3–6: `x` and `*ptr` are two different ways of asking for the SAME
  value — one direct, one indirect through the pointer.
- Line 7: this is the whole point of pointers — you can change a variable's
  value indirectly, through something that merely holds its address. This is
  how UE5 functions can modify an Actor without needing the Actor to be a
  parameter passed by value.

## Pitfall: uninitialized (wild) pointers
```cpp
int* wild;          // NOT initialized — holds garbage, some random address
std::cout << *wild;  // undefined behavior — could crash, could silently
                      // corrupt memory, could "work" and hide the bug
```
This is worse than the array-out-of-bounds UB from Day 8, because a wild
pointer can point ANYWHERE in memory, not just adjacent to a known array.
Always initialize a pointer — to a real address, or to `nullptr` if it
doesn't point anywhere yet.

## Why this matters in UE5
Raw pointers are everywhere: `AActor* MyActor`, `UStaticMeshComponent* Mesh`.
Every time you write `MyActor->SomeFunction()`, you're dereferencing a
pointer under the hood (`->` is dereference + member access combined).
Understanding `&`/`*` here is the prerequisite for pointer arithmetic
(tomorrow), references, and eventually `TObjectPtr`/smart pointers — all of
which exist specifically to make raw-pointer mistakes harder to make, but
you need to understand the raw version first to understand what they're
protecting you from.

## Edge case: dangling pointers
```cpp
int* MakeDangling() {
    int local = 42;
    return &local;   // returning address of a LOCAL variable
}   // local goes out of scope HERE — its memory is no longer valid
// the returned pointer now points at memory that's no longer "yours" —
// dereferencing it is undefined behavior, even though the pointer itself
// still looks like a valid address
```
This is a classic beginner UE5 crash pattern: returning a pointer/reference
to a stack-local `FVector` or similar from a function.

## Recap
- Pointer = variable holding an address.
- `&x` = "give me x's address." `*ptr` = "give me the value at that address"
  (or, on the left of `=`, "assign to the value at that address").
- Uninitialized pointers and dangling pointers are both undefined behavior —
  the compiler will not stop you.
