// Day 18 — Recursion Solutions
// Compare against your own attempt AFTER you've tried every problem. Don't read ahead.

#include <iostream>
#include <cstring>
using namespace std;

// -----------------------------------------------------------------------
// Problem 1: SumArray
// -----------------------------------------------------------------------
int SumArray(int Arr[], int Size)
{
    if (Size == 0)                       // base case: nothing left to add
    {
        return 0;
    }
    // Take the LAST element (Arr[Size-1]) and recurse on everything before it.
    // Could equally recurse on the front (Arr[0] + SumArray(Arr+1, Size-1)) —
    // both are valid; this version avoids pointer arithmetic on Arr.
    return Arr[Size - 1] + SumArray(Arr, Size - 1);
}
// Trace SumArray({1,2,3}, 3):
//   3 + SumArray({1,2,3}, 2)
//       2 + SumArray({1,2,3}, 1)
//           1 + SumArray({1,2,3}, 0)
//               0                      <- base case
//           = 1
//       = 3
//   = 6


// -----------------------------------------------------------------------
// Problem 2: Power
// -----------------------------------------------------------------------
int Power(int Base, int Exp)
{
    if (Exp == 0)                        // base case: anything^0 == 1
    {
        return 1;
    }
    return Base * Power(Base, Exp - 1);
}
// Power(2, 4) = 2 * Power(2,3) = 2 * (2 * Power(2,2)) = ... = 16
// Same unwind-and-multiply shape as Factorial in the concept file.


// -----------------------------------------------------------------------
// Problem 3: IsPalindrome
// -----------------------------------------------------------------------
bool IsPalindrome(char Str[], int Left, int Right)
{
    if (Left >= Right)                   // base case: pointers met or crossed -> checked everything
    {
        return true;
    }
    if (Str[Left] != Str[Right])         // mismatch found -> not a palindrome, stop early
    {
        return false;
    }
    return IsPalindrome(Str, Left + 1, Right - 1);  // shrink the window inward
}
// Call as: IsPalindrome(MyStr, 0, strlen(MyStr) - 1);
// Trace "racecar" (indices 0-6): (r,r) match -> (a,a) match -> (c,c) match -> Left(3) >= Right(3) -> true


// -----------------------------------------------------------------------
// Problem 4: CountNodes
// -----------------------------------------------------------------------
struct Node
{
    int Value;
    Node* Next;
};

int CountNodes(Node* Head)
{
    if (Head == nullptr)                 // base case: ran off the end of the list
    {
        return 0;
    }
    return 1 + CountNodes(Head->Next);   // this node counts as 1, plus however many follow
}


// -----------------------------------------------------------------------
// Problem 5: PrintReverse
// -----------------------------------------------------------------------
void PrintReverse(Node* Head)
{
    if (Head == nullptr)                 // base case: nothing to print
    {
        return;
    }
    PrintReverse(Head->Next);            // go all the way to the end FIRST (no printing yet)
    cout << Head->Value << " ";          // THEN print, on the way back up the call stack
}
// Why this works: recursion walks forward to the tail before any cout runs (the recursive
// call is the FIRST line). The prints only start happening as each frame returns, starting
// from the tail — so the tail prints first, the head prints last. Same "unwind" mechanism
// as Factorial's multiply-on-the-way-back. If you swap the two lines (print, then recurse)
// you get forward order instead — that's the pre-order vs post-order distinction from the
// concept file.


int main()
{
    int Arr[] = { 1, 2, 3, 4 };
    cout << "SumArray: " << SumArray(Arr, 4) << endl;          // 10
    cout << "Power(2,5): " << Power(2, 5) << endl;              // 32

    char Word[] = "racecar";
    cout << "IsPalindrome: " << IsPalindrome(Word, 0, (int)strlen(Word) - 1) << endl; // 1 (true)

    Node C{ 3, nullptr };
    Node B{ 2, &C };
    Node A{ 1, &B };
    cout << "CountNodes: " << CountNodes(&A) << endl;           // 3
    cout << "PrintReverse: ";
    PrintReverse(&A);                                            // 3 2 1
    cout << endl;

    return 0;
}
