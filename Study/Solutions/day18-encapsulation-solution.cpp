// Day 18 — Encapsulation Solutions
// Compare against your own attempt AFTER you've tried every problem.

#include <iostream>
using namespace std;

// -----------------------------------------------------------------------
// Problem 1: PlayerHealth
// -----------------------------------------------------------------------
class PlayerHealth
{
private:
    int CurrentHealth;
    int MaxHealth;

public:
    PlayerHealth(int InMaxHealth)          // constructor: start at full health
    {
        MaxHealth = InMaxHealth;
        CurrentHealth = InMaxHealth;
    }

    void TakeDamage(int Amount)
    {
        CurrentHealth -= Amount;
        if (CurrentHealth < 0)             // clamp: never below 0
        {
            CurrentHealth = 0;
        }
    }

    void Heal(int Amount)
    {
        CurrentHealth += Amount;
        if (CurrentHealth > MaxHealth)     // clamp: never above MaxHealth
        {
            CurrentHealth = MaxHealth;
        }
    }

    int GetHealth()
    {
        return CurrentHealth;
    }

    bool IsDead()
    {
        return CurrentHealth == 0;
    }
};
// Why this is real encapsulation: there is no path from outside code to an invalid
// CurrentHealth (negative, or above MaxHealth) — every mutation goes through a function
// that enforces the clamp. Direct field access would let a caller set CurrentHealth = -50
// with no error, silently breaking IsDead() and anything downstream that assumes health
// is never negative.


// -----------------------------------------------------------------------
// Problem 2: Inventory
// -----------------------------------------------------------------------
class Inventory
{
private:
    int Items[10];
    int Count;

public:
    Inventory()
    {
        Count = 0;                          // starts empty; Items[] contents don't matter yet
    }

    bool AddItem(int ItemId)
    {
        if (Count >= 10)                    // invariant: never write past index 9
        {
            return false;
        }
        Items[Count] = ItemId;
        Count = Count + 1;
        return true;
    }

    int GetItemCount()
    {
        return Count;
    }
};
// Why no GetItems() returning the array: an int[10] "decays" to an int* when returned,
// handing out a raw pointer into your private array — outside code could then write
// Inventory.GetItems()[0] = 9999 directly, bypassing AddItem()'s Count<10 check entirely.
// Same leak shape as the Wallet bug in Problem 3.


// -----------------------------------------------------------------------
// Problem 3: Spot the Bug — explanation
// -----------------------------------------------------------------------
// Data is private, so `Wallet.Data = something;` correctly fails to compile. But GetData()
// hands back the raw int* itself. Once a caller has that pointer, they can write
// *(Wallet.GetData()) = -9999; and mutate the exact memory Data points to — no constructor
// logic, no validation, nothing in Wallet's own code runs to check the new value. Any
// invariant Wallet was meant to protect (e.g. "cents can never go negative") is fully
// bypassable. The class LOOKS encapsulated because the compiler blocks direct field access,
// but the getter quietly reopens the same hole by leaking a mutable pointer to the private
// data. This is the exact "Edge Case" from the concept file — private the field, but still
// leak write access through what a getter returns.

class Wallet
{
private:
    int* Data;
public:
    Wallet(int StartingCents) { Data = new int(StartingCents); }
    int* GetData() { return Data; }
};


int main()
{
    PlayerHealth Hero(100);
    Hero.TakeDamage(150);
    cout << "Health after overkill damage: " << Hero.GetHealth() << endl;   // 0, not -50
    cout << "IsDead: " << Hero.IsDead() << endl;                             // 1 (true)

    Inventory Bag;
    for (int i = 0; i < 12; i++)
    {
        bool Added = Bag.AddItem(i);
        if (!Added)
        {
            cout << "Slot " << i << " rejected, inventory full" << endl;
        }
    }
    cout << "Final item count: " << Bag.GetItemCount() << endl;              // 10, not 12

    return 0;
}
