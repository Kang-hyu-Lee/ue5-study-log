// Day 18 — Encapsulation Exercises
// Type every line yourself. Reference concept file: day18-encapsulation-concept.md

#include <iostream>
using namespace std;

// -----------------------------------------------------------------------
// Problem 1: PlayerHealth
// Build a class with:
//   private: int CurrentHealth, int MaxHealth
//   public constructor PlayerHealth(int InMaxHealth) that sets MaxHealth and starts
//     CurrentHealth at full.
//   public TakeDamage(int Amount) — subtracts Amount, but CurrentHealth must never go
//     below 0 (clamp it). "Clamp" = force a value to stay within a min/max range.
//   public Heal(int Amount) — adds Amount, but CurrentHealth must never exceed MaxHealth.
//   public GetHealth() — returns CurrentHealth (read-only).
//   public IsDead() — returns true if CurrentHealth == 0.
// Hint: clamping is just an if-check after the add/subtract, same shape as the
// Deposit() invariant check in the concept file's BankAccount example.
// -----------------------------------------------------------------------
class PlayerHealth
{
    // TODO
    private:
    
    int CurrentHealth;
    int MaxHealth;
   
    public:
    
    PlayerHealth(int InMaxHealth)
    {
        MaxHealth = InMaxHealth;
        CurrentHealth = InMaxHealth;
    }
    
    void TakeDamage(int Amount)
    {
        CurrentHealth -= Amount;
        if(CurrentHealth < 0) CurrentHealth = 0;
    }

    void Heal(int Amount)
    {
        CurrentHealth += Amount;
        if(CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;
    }

    int GetHealth()
    {
        return CurrentHealth;
    }

    bool IsDead()
    {
        return CurrentHealth == 0; //can collapse to a single line since == already gives a bool
    }
};


// -----------------------------------------------------------------------
// Problem 2: Inventory
// Build a class wrapping a FIXED-SIZE array of item IDs:
//   private: int Items[10], int Count (how many slots are filled, starts at 0)
//   public AddItem(int ItemId) — only adds if Count < 10 (invariant: never overflow the
//     array). Returns true if added, false if inventory was full.
//   public GetItemCount() — returns Count (read-only).
// Note: do NOT add a getter that returns the Items array itself or a pointer into it —
// that's the leak pattern from the concept file's edge case. GetItemCount() only.
// -----------------------------------------------------------------------
class Inventory
{
    // TODO
    private:
    
    int Items[10];
    int Count = 0;

    public:
    
    bool AddItem(int ItemId){
        if(Count < 10)
        {
            Items[Count] = ItemId;
            Count ++;

            return true;
        }
        return false;
    }

    int GetItemCount() 
    {
        return Count;
    }
};


// -----------------------------------------------------------------------
// Problem 3: Spot the Bug (analysis only — no code to write)
// The class below compiles fine. In a comment underneath, explain in your own words
// WHY it is still broken encapsulation despite Data being private, and what specifically
// an outside caller could do that Deposit()-style validation could never prevent.
// -----------------------------------------------------------------------
class Wallet
{
private:
    int* Data;
public:
    Wallet(int StartingCents) { Data = new int(StartingCents); }
    int* GetData() { return Data; }
};

// Your explanation here:int* GetData will allow them to get the address to the actual private field and edit it with *Wallet.GetData() = -9999;
// TODO


int main()
{
    PlayerHealth Hp(1000);
    Hp.TakeDamage(100);
    cout << "Took 100 Damage: " << Hp.GetHealth() << "/1000" << endl;
    Hp.Heal(50);
    cout << "Healed 50 Health: " << Hp.GetHealth() <<"/1000" << endl;
    cout << "Is player dead: " << Hp.IsDead() << endl;

    Inventory Inv;
    Inv.AddItem(5);
    Inv.AddItem(10);
    cout << "Item count: " << Inv.GetItemCount() << endl;

    return 0;
}
