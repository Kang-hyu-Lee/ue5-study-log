// Day 18 — Recursion Exercises
// Type every line yourself. Do not paste. Predict each function's output on paper
// before you compile. No loops (for/while) allowed in any solution below — recursion only,
// that's the point of the exercise.
// Reference concept file: day18-recursion-concept.md
// New syntax not yet covered gets an inline hint pointing to cppreference.com.

#include <iostream>
#include <cstring>
using namespace std;

// -----------------------------------------------------------------------
// Problem 1: SumArray
// Recursively sum all elements of an int array. No loops.
// Hint: pass the array pointer, the size, and (implicitly via a helper) the current index.
//       Base case: index == size -> return 0.
// -----------------------------------------------------------------------
int SumArray(int Arr[], int Size)
{
    // TODO
    if( Size == 0){
        return 0;
    }else{
        return Arr[Size-1] + SumArray(Arr, Size-1);
    }
}


// -----------------------------------------------------------------------
// Problem 2: Power
// Compute Base^Exp for a non-negative integer Exp, recursively. No loops, no pow().
// Hint: Base^Exp = Base * Base^(Exp-1). Base case: Exp == 0 -> return 1.
// -----------------------------------------------------------------------
int Power(int Base, int Exp)
{
    // TODO
    if(Exp == 0){
        return 1;
    }else{
        return Base * Power(Base, Exp - 1);
    }
}


// -----------------------------------------------------------------------
// Problem 3: IsPalindrome
// Check whether a C-string (char array) reads the same forwards and backwards, recursively.
// Hint: strlen() from <cstring> gets you the length (see cppreference.com/w/cpp/string/byte/strlen
// if unfamiliar). Compare Str[Left] to Str[Right], then recurse inward (Left+1, Right-1).
// Base case: Left >= Right -> true.
// -----------------------------------------------------------------------
bool IsPalindrome(char Str[], int Left, int Right)
{
    // TODO
    if(Left >= Right){
        return true;
    }else{
        if(Str[Left] != Str[Right]) return false;   //flat syntax
        return IsPalindrome(Str, Left + 1, Right - 1); //no need for else the if returns anyways if flagged
    }
}


// -----------------------------------------------------------------------
// Problem 4: CountNodes
// Recursively count the number of nodes in a singly linked list, given the Head pointer.
// Use the same Node struct pattern from your portfolio to-do list (a struct with an int
// Value and a Node* Next).
// Hint: base case is Head == nullptr -> return 0.
// -----------------------------------------------------------------------
struct Node
{
    int Value;
    Node* Next;
};

int CountNodes(Node* Head)
{
    // TODO
    if(Head == nullptr)return 0;
    return 1 + CountNodes(Head->Next);
}


// -----------------------------------------------------------------------
// Problem 5: PrintReverse
// Print a linked list's values in reverse order WITHOUT modifying/reversing the list itself.
// Do not build a second data structure (no array/stack) — pure recursion only.
// Hint: this is the "unwind" pattern from the concept file's Factorial trace — the print
// has to happen AFTER the recursive call, not before. Think about why.
// -----------------------------------------------------------------------
void PrintReverse(Node* Head)
{
    // TODO
    if(Head == nullptr)return;
    PrintReverse(Head->Next);
    cout << Head->Value << endl;
}


int main()
{
    // Build a small test list and array yourself here once the functions above are written,
    // then predict each function's output BEFORE running.
    int Arr[5] = {10,20,30,40,50};
    char Word[] = "racecar";
    Node A{10, nullptr};
    Node B{20, nullptr};
    Node C{30, nullptr};
    Node D{40, nullptr};
    A.Next = &B;
    B.Next = &C;
    C.Next = &D;
    Node* Head = &A;

    cout << "SUMARRAY: " << SumArray(Arr, 5) << endl;
    cout << "POWER 2^5: " << Power(2,5) << endl;
    cout << "ISPALINDROME: " << IsPalindrome(Word, 0, strlen(Word - 1)) << endl;
    cout << "COUNTNODES: " << CountNodes(Head) << endl;
    cout << "PRINTREVERSE: " << endl;
    PrintReverse(Head);

    return 0;
}
