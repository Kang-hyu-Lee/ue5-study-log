// DAY 19 — DSA: RECURSION TIMED PRACTICE
// Rules:
// - Set a timer. Budget ~3 min per problem, ~25 min total. Don't check solutions mid-attempt.
// - Every function must be recursive (no for/while loops as the primary mechanism), unless noted.
// - Predict the output/behavior in a comment ABOVE each function call in main() before running.
// - No new syntax below beyond what you've already covered (arrays, pointers, linked lists, recursion).

#include <iostream>
using namespace std;

// -----------------------------------------------------------------
// Q1 — Factorial(int N)
// Base case: N <= 1 returns 1.
// Recursive case: N * Factorial(N - 1).
int Factorial(int N)
{
    // TODO
    if(N <= 1) return 1;
    return N * Factorial(N-1);
}

// -----------------------------------------------------------------
// Q2 — SumToN(int N)
// Sum of all integers from 1 to N, recursively (no loop, no formula).
int SumToN(int N)
{
    // TODO
    if(N == 0)return 0;
    return N + SumToN(N-1);
}

// -----------------------------------------------------------------
// Q3 — Power(int Base, int Exp)
// Computes Base^Exp recursively. Assume Exp >= 0.
// Hint: Base^Exp == Base * Base^(Exp-1). What's the base case for Exp == 0?
int Power(int Base, int Exp)
{
    // TODO
    if(Exp == 0)return 1;
    return Base * Power(Base,Exp-1);
}

// -----------------------------------------------------------------
// Q4 — SumArray(int Arr[], int Size)
// Recursively sum all elements of an array.
// Hint: shrink the problem by summing Arr[0] + SumArray(rest of array, Size - 1).
// You'll need to pass a pointer offset (Arr + 1) — same array, different starting address.
int SumArray(int Arr[], int Size)
{
    // TODO
    if(Size == 0)return 0;
   return Arr[Size-1] + SumArray(Arr, Size - 1);
}

// -----------------------------------------------------------------
// Q5 — CountDigits(int N)
// Count how many digits N has, recursively. Assume N >= 0.
// Hint: N / 10 removes the last digit. Base case: N < 10 has 1 digit.
int CountDigits(int N)
{
    // TODO
    if(N < 10)return 1;
    return 1 + CountDigits(N / 10);
}

// -----------------------------------------------------------------
// Q6 — IsPalindromeStr(const char* Str, int Left, int Right)
// Returns true if the substring from index Left to Right (inclusive) reads the same forwards/backwards.
// Hint: base case is Left >= Right (0 or 1 chars left = trivially a palindrome).
// Recursive case: compare Str[Left] and Str[Right], then recurse inward (Left+1, Right-1).
bool IsPalindromeStr(const char* Str, int Left, int Right)
{
    // TODO
    if(Left >= Right)return true;
    if(Str[Left] != Str[Right]) return false;
    return IsPalindromeStr(Str, Left + 1, Right - 1);
}

// -----------------------------------------------------------------
// Q7 — GCD(int A, int B)   [Euclid's algorithm]
// Base case: if B == 0, return A.
// Recursive case: GCD(B, A % B).
// This is a real interview staple — trace it by hand for GCD(48, 18) before coding.
int GCD(int A, int B)
{
    // TODO
    if(B == 0) return A;
    return GCD(B, A%B);
}

// -----------------------------------------------------------------
// Q8 — SumLinkedList(Node* Head)   [ties back to your LinkedStack/linked list work]
// Recursively sum the Data field of every node in a singly linked list.
// You'll need a minimal Node struct — reuse the shape you already know:
struct Node
{
    int Data;
    Node* Next;
};
// Base case: Head == nullptr → sum of empty list is 0.
// Recursive case: Head->Data + SumLinkedList(Head->Next).
int SumLinkedList(Node* Head)
{
    // TODO
    if(Head == nullptr)return 0;
    return Head->Data + SumLinkedList(Head->Next);
}

// -----------------------------------------------------------------
int main()
{
    // Q1
    cout << "Factorial(5) = " << Factorial(5) << endl; // predict before running:

    // Q2
    cout << "SumToN(10) = " << SumToN(10) << endl; // predict:

    // Q3
    cout << "Power(2, 6) = " << Power(2, 6) << endl; // predict:

    // Q4
    int Arr[] = {4, 8, 15, 16, 23, 42};
    cout << "SumArray = " << SumArray(Arr, 6) << endl; // predict:

    // Q5
    cout << "CountDigits(48291) = " << CountDigits(48291) << endl; // predict:

    // Q6
    const char* Word = "racecar";
    cout << "IsPalindromeStr = " << IsPalindromeStr(Word, 0, 6) << endl; // predict:

    // Q7
    cout << "GCD(48, 18) = " << GCD(48, 18) << endl; // predict:

    // Q8
    Node C{3, nullptr};
    Node B{2, &C};
    Node A{1, &B};
    cout << "SumLinkedList = " << SumLinkedList(&A) << endl; // predict:

    return 0;
}
