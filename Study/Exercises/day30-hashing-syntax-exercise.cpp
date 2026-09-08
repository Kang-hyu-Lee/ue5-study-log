// Day 30 — Hashing Pt.2 Exercises
// Type this file yourself. Do not paste. Attempt each problem before checking the solution file.
// Compile mentally / on paper first if you don't have a scratch .cpp project set up yet.

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>

// ---------------------------------------------------------------------------
// PROBLEM 1
// Declare an unordered_map<std::string, int> called PlayerScores.
// Insert THREE players using operator[] for the first one and insert() for
// the other two. Then print all entries using a range-based for loop in the
// form: "Name: Score".
// Hint: range-based for on a map gives you a std::pair per entry — see
// concept file section "Iterating" for Pair.first / Pair.second.
void Problem1()
{
    // your code here
    std::unordered_map<std::string, int> PlayerScores;
    PlayerScores["Player1"] = 20;
    PlayerScores.insert({"Player2", 30});
    PlayerScores.insert({"Player3", 40});

    for(auto& Name : PlayerScores){
        std::cout << Name.first << " " << Name.second << std::endl;
    }
}

// ---------------------------------------------------------------------------
// PROBLEM 2
// Given the populated map below, write code that checks whether "Boss"
// exists WITHOUT risking an accidental insert.
// Hint: do NOT use PlayerScores["Boss"] for this check — see the Pitfall
// section in the concept file for why.
void Problem2()
{
    std::unordered_map<std::string, int> PlayerScores = { {"Kang", 25}, {"Ally", 40} };

    // your check here — print "found" or "not found"
    if(PlayerScores.count("Boss") > 0){
        std::cout << "found" << std::endl;
        return;
    }
    std::cout << "not found" << std::endl;
}

// ---------------------------------------------------------------------------
// PROBLEM 3 — TRACE (no running code needed, just predict on paper first)
// std::unordered_map<std::string, int> M;
// M["A"] = 1;
// M["B"] = 2;
// M["A"] = 3;
// if (M["C"] > 100) { }
// M.erase("B");
//
// Q: What is M.size() after this sequence? Write your predicted answer as a
// comment, then verify by actually running it
void Problem3()
{
    // predicted size: 2
    // your verification code here
    std::unordered_map<std::string, int> M;
    M["A"] = 1;
    M["B"] = 2;
    M["A"] = 3;
    if(M["C"] > 100) {}
    M.erase("B");
    std::cout << M.size() << std::endl;
}

// ---------------------------------------------------------------------------
// PROBLEM 4
// Write a function HasSpawned(const std::unordered_set<int>& SpawnedIDs, int ID)
// that returns true if ID is already in the set, false otherwise, WITHOUT
// modifying the set.
// Hint: use find() or count() — see the unordered_set section.
bool HasSpawned(const std::unordered_set<int>& SpawnedIDs, int ID)
{
    // your code here
    if(SpawnedIDs.count(ID) > 0){
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// PROBLEM 5 — SHORT ANSWER (write as a comment, in your own words)
// Why does std::map guarantee O(log n) worst case, but std::unordered_map
// does NOT guarantee O(1) worst case? Reference what's actually happening
// under the hood for each.
//
// your answer: because std::map is a self balancing tree, so the invariants, organized by smaller to largest and balanced, guarantees a O(log n) worst case traversal, 
//              but a std::unordered_map is a hashmap and this means there can be a linked list with all keys in a single bucket, which would mean a bad hash function and has O(n) worst case
//

// ---------------------------------------------------------------------------
// PROBLEM 6 — SHORT ANSWER (write as a comment)
// Name one gameplay scenario where you'd pick std::map over
// std::unordered_map, and explain why the ordering/guarantee actually
// matters for that scenario specifically (not just "map is safer").
//
// your answer: Anything that requires finding things in range X to Y or needs larger than so like a leaderboard
//

int main()
{
    Problem1();
    Problem2();
    Problem3();
    std::cout << HasSpawned({1,2,3}, 2) << "\n";
    return 0;
}
