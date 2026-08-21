# Day 18 — Encapsulation & Public/Private (C++)

## Core Mechanism
Encapsulation = bundling data with the functions that operate on it, AND restricting direct outside access to that data so it can only be changed through controlled functions. C++ enforces this at compile time with access specifiers:

- `private:` — accessible only from inside the class's own member functions (and `friend`s — see edge case below).
- `public:` — accessible from anywhere the object is visible.
- `protected:` — accessible from the class and classes that inherit from it (proper coverage Day 19, inheritance — mentioned now so the keyword isn't a surprise when it shows up).

## The struct/class Gotcha (ties to Day 15)
You already learned struct vs class are nearly identical in C++. Here is the ONE real difference:

- `struct` members default to `public`
- `class` members default to `private`

That's the entire difference. Constructors, destructors, member functions, inheritance — all identical on both. This default is *why* convention reaches for `class` when you want private-by-default data hiding, and `struct` for simple public data bags with no rules to protect (a plain 3-float Vector, for instance).

## Worked Example

```cpp
class BankAccount
{
private:
    float Balance;                     // hidden — outside code cannot touch this directly

public:
    BankAccount(float StartingBalance) // constructor
    {
        Balance = StartingBalance;
    }

    float GetBalance()                 // getter — read-only access
    {
        return Balance;
    }

    void Deposit(float Amount)         // controlled write access
    {
        if (Amount > 0)                 // invariant: never deposit a non-positive amount
        {
            Balance += Amount;
        }
    }
};
```

Line by line:
- `private: float Balance;` — no outside code can write `Account.Balance = -9999;`. The compiler rejects it — this is enforced, not a naming convention people are trusting each other to respect.
- `GetBalance()` is `public` — outside code CAN read the balance, just not write it directly.
- `Deposit()` is the ONLY path to changing `Balance` from outside, and it enforces a rule (`Amount > 0`) every single call. Direct field access could never guarantee that rule runs.

Mentally run `Account.Balance = -9999;` from `main()` — that's a **compile error** ("Balance is private within this context"), not a runtime bug caught later. That is the actual point of encapsulation: invalid states become impossible to compile, not just something you hope nobody forgets to check.

## Pitfall: "Private Just Means Hidden"
Common misconception: private is about tidiness. It's actually about protecting **invariants** — rules about your data that must always hold (balance never negative, health never exceeds max, a linked list's `Head` never pointing at freed memory). If outside code can reach in and set a field directly, no member function you write can guarantee that rule holds — someone will eventually bypass it. Encapsulation is what turns "this object is always in a valid state" into a compiler-enforced promise.

## Why It Matters
- Every serious C++/UE5 codebase leans on this. Epic's own convention: private members prefixed (e.g. `Health`), controlled access via public functions or `UPROPERTY`.
- Direct UE5 tie: `UPROPERTY(EditAnywhere)` vs `UPROPERTY(VisibleAnywhere)` vs no `UPROPERTY` at all *is* encapsulation applied to the C++/Blueprint/Editor boundary — deciding exactly what a designer can touch from the Editor vs what only C++ is allowed to control. Real in Phase 2.
- Interview follow-up you will get: "why not just make everything public?" Answer with the invariant argument above, not "it's convention."

## Edge Case: A Getter Can Still Leak Mutability
```cpp
private:
    int* Data;
public:
    int* GetData() { return Data; }    // BROKEN encapsulation
```
Even though `Data` is private, this getter hands the raw pointer straight to outside code, which can now do `Account.GetData()[0] = 9999;` — mutating what `Data` points to and completely bypassing any rule you meant to enforce. This connects directly to the `T*` vs `T*&` pointer-semantics work from Day 12: returning a raw pointer or non-const reference from a getter quietly reopens the exact hole `private` was supposed to close. The actual fix (`const int*`, returning a copy, or a const reference) is a `const`-correctness topic — flagged for Day 25 on your roadmap — but the trap is worth recognizing now, before you write your own getters today.
