// Day 30 — Hashing Pt.2 Solutions
// Compare against your own attempt AFTER trying each problem. Don't read ahead.

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>

// ---------------------------------------------------------------------------
// PROBLEM 1
void Problem1()
{
    std::unordered_map<std::string, int> PlayerScores;

    PlayerScores["Kang"] = 25;              // operator[]: creates + assigns since key is new
    PlayerScores.insert({"Ally", 40});      // insert(): only inserts if key is new
    PlayerScores.insert({"Sam", 15});

    for (auto& Pair : PlayerScores)         // auto& = deduced type, reference (no copy)
    {
        std::cout << Pair.first << ": " << Pair.second << "\n";
        // Pair.first = key, Pair.second = value
        // ORDER NOT GUARANTEED — don't rely on print order matching insert order.
    }
}

// ---------------------------------------------------------------------------
// PROBLEM 2
void Problem2()
{
    std::unordered_map<std::string, int> PlayerScores = { {"Kang", 25}, {"Ally", 40} };

    // count() never inserts — safe existence check.
    if (PlayerScores.count("Boss") > 0)
    {
        std::cout << "found\n";
    }
    else
    {
        std::cout << "not found\n";
    }

    // Equivalent alternative using find():
    // if (PlayerScores.find("Boss") != PlayerScores.end()) { ... }
    // Both are correct. count() reads slightly cleaner for a pure yes/no check;
    // find() is better when you also need the VALUE once you know it exists,
    // since it hands you an iterator (avoids a second lookup).
}

// ---------------------------------------------------------------------------
// PROBLEM 3
void Problem3()
{
    std::unordered_map<std::string, int> M;
    M["A"] = 1;                 // insert A=1        -> size 1
    M["B"] = 2;                 // insert B=2         -> size 2
    M["A"] = 3;                 // A already exists, OVERWRITE, no size change -> size 2
    if (M["C"] > 100) { }       // "C" doesn't exist -> operator[] SILENTLY INSERTS C=0 -> size 3
    M.erase("B");                // remove B                                     -> size 2

    std::cout << "final size: " << M.size() << "\n";  // prints 2

    // The trap is the `if (M["C"] > 100)` line — it LOOKS like a read-only check,
    // but operator[] on a non-existent key inserts it with a default value first,
    // THEN compares. M gained a "C"->0 entry as a side effect of a comparison
    // that evaluated to false and was otherwise ignored.
}

// ---------------------------------------------------------------------------
// PROBLEM 4
bool HasSpawned(const std::unordered_set<int>& SpawnedIDs, int ID)
{
    return SpawnedIDs.count(ID) > 0;
    // count() on a set: 0 or 1, never inserts, never modifies — safe for a
    // const reference parameter (notice the function signature takes the set
    // by const& — count() being a read-only/const-safe operation is exactly
    // why this compiles; find() would also work the same way here).
}

// ---------------------------------------------------------------------------
// PROBLEM 5 — SHORT ANSWER
// std::map is a balanced binary search tree (red-black tree). Its structure
// is rebalanced on every insert/delete so the tree height is ALWAYS bounded
// by O(log n) relative to the number of elements — this is a structural
// guarantee, not a probabilistic one. There is no "bad case" for a balanced
// tree's height; the balancing operations enforce it directly.
//
// std::unordered_map's speed depends entirely on the hash function spreading
// keys evenly across buckets. If many keys hash to the same bucket (bad hash
// function, or an attacker deliberately choosing colliding keys), that one
// bucket degrades into a linked list of length up to n, and searching it
// becomes O(n) — a structural WORST case that hashing cannot rule out the
// way tree rebalancing can. Average case assumes "reasonably even
// distribution," which is usually true but not guaranteed.

// ---------------------------------------------------------------------------
// PROBLEM 6 — SHORT ANSWER
// Example: a leaderboard system that needs to display "top N scores in
// order" every frame or every UI refresh. std::map keeps keys sorted at all
// times as a structural property, so iterating it top-to-bottom (or using
// bounds like lower_bound for "top 10") is already sorted and O(log n) per
// operation. With unordered_map you'd have to copy all entries out and sort
// them yourself every time you need the ordering, which is strictly more
// work for a case where you need order EVERY time, not just occasionally.
// If you only occasionally needed a sorted view, unordered_map + sort-on-
// demand would be fine — the deciding factor is how OFTEN the order matters.

int main()
{
    Problem1();
    Problem2();
    Problem3();
    std::cout << HasSpawned({1,2,3}, 2) << "\n";
    return 0;
}
