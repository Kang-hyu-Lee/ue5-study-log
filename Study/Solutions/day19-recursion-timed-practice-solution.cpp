// DAY 19 — DSA: RECURSION TIMED PRACTICE — SOLUTIONS
// Compare AFTER attempting. Every solution includes: the base case, the reduction step,
// and a call-stack trace for at least one problem so you can see recursion "unwind."

#include <iostream>
using namespace std;

// -----------------------------------------------------------------
// Q1 — Factorial
int Factorial(int N)
{
    if (N <= 1) return 1;              // base case: stop shrinking
    return N * Factorial(N - 1);       // reduction: smaller problem + combine
}
/* Call stack trace for Factorial(4):
   Factorial(4) = 4 * Factorial(3)
                = 4 * (3 * Factorial(2))
                = 4 * (3 * (2 * Factorial(1)))
                = 4 * (3 * (2 * 1))          <- base case hit, stack starts unwinding
                = 4 * (3 * 2) = 4 * 6 = 24
   Each call waits (its stack frame stays alive) until the one below it returns.
   This is WHY deep recursion costs memory — every waiting frame sits on the call stack. */

// -----------------------------------------------------------------
// Q2 — SumToN
int SumToN(int N)
{
    if (N <= 0) return 0;
    return N + SumToN(N - 1);
}

// -----------------------------------------------------------------
// Q3 — Power
int Power(int Base, int Exp)
{
    if (Exp == 0) return 1;            // anything^0 == 1
    return Base * Power(Base, Exp - 1);
}

// -----------------------------------------------------------------
// Q4 — SumArray
int SumArray(int Arr[], int Size)
{
    if (Size <= 0) return 0;
    // Arr[0] is the "current" element. Arr + 1 is a pointer to the array
    // starting one element later — same memory, new starting address.
    // Size - 1 tells the next call it now has one fewer element to consider.
    return Arr[0] + SumArray(Arr + 1, Size - 1);
}

// -----------------------------------------------------------------
// Q5 — CountDigits
int CountDigits(int N)
{
    if (N < 10) return 1;              // single digit left
    return 1 + CountDigits(N / 10);    // integer division drops the last digit
}

// -----------------------------------------------------------------
// Q6 — IsPalindromeStr
bool IsPalindromeStr(const char* Str, int Left, int Right)
{
    if (Left >= Right) return true;                 // crossed or met in the middle
    if (Str[Left] != Str[Right]) return false;       // mismatch found, short-circuit
    return IsPalindromeStr(Str, Left + 1, Right - 1); // shrink the window inward
}

// -----------------------------------------------------------------
// Q7 — GCD (Euclid's algorithm)
int GCD(int A, int B)
{
    if (B == 0) return A;
    return GCD(B, A % B);
}
/* Trace GCD(48, 18):
   GCD(48, 18) -> B != 0 -> GCD(18, 48 % 18 = 12)
   GCD(18, 12) -> GCD(12, 18 % 12 = 6)
   GCD(12, 6)  -> GCD(6, 12 % 6 = 0)
   GCD(6, 0)   -> B == 0 -> return 6
   Answer: 6. Notice the pair always shrinks — that's the proof this terminates. */

// -----------------------------------------------------------------
// Q8 — SumLinkedList
struct Node
{
    int Data;
    Node* Next;
};

int SumLinkedList(Node* Head)
{
    if (Head == nullptr) return 0;                    // empty list/end of list
    return Head->Data + SumLinkedList(Head->Next);
}
// PITFALL TO NOTICE: this is structurally identical to SumArray — recursion over
// "current element + recurse on the rest" is a pattern that applies to any
// self-referential/sequential structure, not just arrays. Trees (Day 23+) use
// the exact same shape: CurrentNodeValue + Recurse(Left) + Recurse(Right).

// -----------------------------------------------------------------
int main()
{
    cout << "Factorial(5) = " << Factorial(5) << endl;             // 120
    cout << "SumToN(10) = " << SumToN(10) << endl;                 // 55
    cout << "Power(2, 6) = " << Power(2, 6) << endl;                // 64
    int Arr[] = {4, 8, 15, 16, 23, 42};
    cout << "SumArray = " << SumArray(Arr, 6) << endl;              // 108
    cout << "CountDigits(48291) = " << CountDigits(48291) << endl;  // 5
    const char* Word = "racecar";
    cout << "IsPalindromeStr = " << IsPalindromeStr(Word, 0, 6) << endl; // 1 (true)
    cout << "GCD(48, 18) = " << GCD(48, 18) << endl;                // 6
    Node C{3, nullptr};
    Node B{2, &C};
    Node A{1, &B};
    cout << "SumLinkedList = " << SumLinkedList(&A) << endl;        // 6

    return 0;
}
