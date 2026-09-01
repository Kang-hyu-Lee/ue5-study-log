// Day 26 - DSA Mixed Timed Review - SOLUTIONS

#include <iostream>
#include <string>
#include <stack>
#include <queue>

// ============================================================
// SECTION 1: ARRAYS
// ============================================================

// Problem 1
void ReverseArray(int Arr[], int Size)
{
    int Left = 0;
    int Right = Size - 1;
    while (Left < Right)
    {
        int Temp = Arr[Left];
        Arr[Left] = Arr[Right];
        Arr[Right] = Temp;
        Left++;
        Right--;
    }
}
// Loop condition is Left < Right, not <=, because when they meet or cross the swap is done
// (or would swap an element with itself, harmless but wasted work).

// Problem 2
bool IsSortedAscending(int Arr[], int Size)
{
    // Size 0 or 1: no adjacent pair can violate order, so vacuously true.
    for (int i = 0; i < Size - 1; i++)
    {
        if (Arr[i] > Arr[i + 1]) return false;
    }
    return true;
}

// ============================================================
// SECTION 2: LINKED LISTS
// ============================================================

struct Node
{
    int Value;
    Node* Next;
};

// Problem 3
int CountNodes(Node* Head)
{
    int Count = 0;
    Node* Current = Head;
    while (Current != nullptr)
    {
        Count++;
        Current = Current->Next;
    }
    return Count;
}

// Problem 4
Node* FindMiddle(Node* Head)
{
    Node* Slow = Head;
    Node* Fast = Head;
    // Fast moves 2 steps per loop, Slow moves 1. When Fast falls off the end,
    // Slow has covered exactly half the distance -> sitting on the middle node.
    // Fast != nullptr AND Fast->Next != nullptr guards against dereferencing nullptr->Next
    // on odd-vs-even length lists.
    while (Fast != nullptr && Fast->Next != nullptr)
    {
        Slow = Slow->Next;
        Fast = Fast->Next->Next;
    }
    return Slow;
}
// This is the "fast/slow pointer" (a.k.a. tortoise-and-hare) pattern - shows up again for
// cycle detection later. Same core idea: two pointers moving at different speeds through
// the same structure.

// ============================================================
// SECTION 3: STACKS & QUEUES
// ============================================================

// Problem 5
bool IsBalanced(std::string Input)
{
    std::stack<char> Stack;
    for (char c : Input)
    {
        if (c == '(') Stack.push(c);
        else if (c == ')')
        {
            if (Stack.empty()) return false; // closing paren with nothing open
            Stack.pop();
        }
    }
    return Stack.empty(); // false if any '(' never got closed
}

// Problem 6
void SimulatePrintQueue()
{
    std::queue<std::string> PrintQueue;
    PrintQueue.push("JobA");
    PrintQueue.push("JobB");
    PrintQueue.push("JobC");

    while (!PrintQueue.empty())
    {
        std::cout << PrintQueue.front() << " printed\n"; // FIFO: front() is oldest, JobA first
        PrintQueue.pop();
    }
}

// ============================================================
// SECTION 4: BST + TRAVERSALS
// ============================================================

struct TreeNode
{
    int Value;
    TreeNode* Left;
    TreeNode* Right;
};

// Problem 7 (paper answer)
// Insert order 5, 3, 8, 1, 4, 7, 9 produces:
//
//              5
//            /   \
//           3     8
//          / \   / \
//         1   4 7   9
//
// In-order   (L, Root, R): 1, 3, 4, 5, 7, 8, 9   <- sorted output, this is the BST guarantee
// Pre-order  (Root, L, R): 5, 3, 1, 4, 8, 7, 9
// Post-order (L, R, Root): 1, 4, 3, 7, 9, 8, 5

// Problem 8
bool IsValidBSTHelper(TreeNode* Node, long MinAllowed, long MaxAllowed)
{
    if (Node == nullptr) return true; // empty subtree trivially satisfies the invariant
    if (Node->Value <= MinAllowed || Node->Value >= MaxAllowed) return false;
    // Recurse with a NARROWED range: going left, this node becomes the new upper bound;
    // going right, this node becomes the new lower bound. This is what catches violations
    // buried deeper than one level - a naive "check immediate children only" check misses
    // e.g. a node 3 levels down on the left side that's larger than the top root.
    return IsValidBSTHelper(Node->Left, MinAllowed, Node->Value)
        && IsValidBSTHelper(Node->Right, Node->Value, MaxAllowed);
}
bool IsValidBST(TreeNode* Root)
{
    return IsValidBSTHelper(Root, LONG_MIN, LONG_MAX);
}

// Problem 9
int CountLeaves(TreeNode* Root)
{
    if (Root == nullptr) return 0;
    if (Root->Left == nullptr && Root->Right == nullptr) return 1; // leaf: count it
    return CountLeaves(Root->Left) + CountLeaves(Root->Right); // delegate, don't accumulate manually
}

// Problem 10 (paper answer)
// Output A: 1, 3, 4, 5, 7, 8, 9   -> smallest to largest -> only In-order produces sorted
//                                     output from a BST -> In-order.
// Output B: 5, 3, 1, 4, 8, 7, 9   -> starts with 5 (the root) -> only Pre-order visits Root
//                                     first -> Pre-order.
// Output C: 1, 4, 3, 7, 9, 8, 5   -> ends with 5 (the root) -> only Post-order visits Root
//                                     last -> Post-order.
// Note the identification method: don't try to re-run the recursion in your head under
// time pressure. Root-first = Pre, Root-last = Post, sorted = In. Fastest possible check.
