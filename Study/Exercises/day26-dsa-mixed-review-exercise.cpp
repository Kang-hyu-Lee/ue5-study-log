// Day 26 - DSA Mixed Timed Review
// Target: ~30 min, closed notes. Arrays / Linked Lists / Stacks & Queues / BST + Traversals.
// Section 4 (BST/Traversals) is weighted heavier - today's recall check surfaced a
// name<->order mix-up on in/pre/post-order, so this drills that specifically.

// ============================================================
// SECTION 1: ARRAYS
// ============================================================
#include <iostream>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

// Problem 1: Reverse an array in place (no second array allocated).
// void ReverseArray(int Arr[], int Size)
// Hint: two-pointer swap, one index from the front, one from the back, walk toward the middle.

void ReverseArray(int Arr[], int Size)
{
    int* back = &Arr[Size - 1];
    int* front = &Arr[0];

    while(front < back)
    {
        int Temp = *back;
        *back = *front;
        *front = Temp;
        front ++;
        back --;
    }
}

// Problem 2: Check whether an array is sorted ascending.
// bool IsSortedAscending(int Arr[], int Size)
// Edge case to think about before you code: what should Size == 0 or Size == 1 return, and why?

bool IsSortedAscending(int Arr[], int Size)
{
    if(Size == 0) 
    {
        cout << "Array is empty" << endl;
        return true;
    }
    else if(Size == 1)
    {
        cout << "Array has a single element" << endl;
        return true;
    }
    int Prev = Arr[0];
    for(int i=1; i<Size; i++)
    {
        if (Arr[i] > Prev)
        {
            Prev = Arr[i];
        }
        else
        {
            return false;
        }
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

// Problem 3: Count nodes in a singly linked list WITHOUT recursion.
// int CountNodes(Node* Head)

int CountNodes(Node* Head)
{
    int Count = 0;
    while(Head != nullptr){
        Head = Head->Next;
        Count ++;
    }
    
    return Count;
}

// Problem 4: Find the middle node of a singly linked list in ONE pass over the list.
// Node* FindMiddle(Node* Head)
// Hint: run two pointers from Head - one steps 1 node per loop iteration, the other steps
// 2 nodes per iteration. When the fast one reaches the end, think about where the slow one
// must be relative to the total length. (This pattern has a name - "fast/slow pointers" -
// you haven't been taught the name yet, but you already have every mechanic needed to
// derive it yourself from pointer basics.)

Node* FindMiddle(Node* Head)
{
    Node* Fast = Head;
    Node* Slow = Head;

    while(Fast != nullptr && Fast->Next != nullptr){
        Fast = Fast->Next->Next;
        Slow = Slow->Next;
    }

    return Slow;
}

// ============================================================
// SECTION 3: STACKS & QUEUES
// Using std::stack / std::queue this time instead of your hand-rolled versions.
// Reference: cppreference.com/w/cpp/container/stack and .../w/cpp/container/queue
// Relevant member functions: push, pop, top (stack) / front (queue), empty
// ============================================================

// Problem 5: Given a std::string made only of '(' and ')' characters, determine whether
// the parentheses are balanced, using std::stack<char>.
// bool IsBalanced(std::string Input)
bool IsBalanced(std::string Input)
{
    std::stack<char> Current;
    for(char c:Input)
    {
        if(c == '(')
        {
            Current.push(c);
        }
        else if (c == ')')
        {
            if(Current.empty()) { return false; }
            Current.pop();
        }
    }
    return Current.empty();
}



// Problem 6: Simulate a FIFO print queue using std::queue<std::string>. Enqueue three job
// names of your choice, then dequeue + print all three in the order they'll actually print.

void FifoPrintQueue(){
    std::queue<std::string> StringQueue;
    StringQueue.push("Study");
    StringQueue.push("Cook");
    StringQueue.push("Clean");

    while(!StringQueue.empty())
    {
        cout << StringQueue.front() << endl;
        StringQueue.pop();
    }
}

// ============================================================
// SECTION 4: BST + TRAVERSALS (heavier weight - this week's flagged gap)
// ============================================================

struct TreeNode
{
    int Value;
    TreeNode* Left;
    TreeNode* Right;
};

// Problem 7 (PAPER - no code): Insert this sequence into an empty BST, one value at a time,
// in this exact order: 5, 3, 8, 1, 4, 7, 9
// Draw the resulting tree. Then write out, by hand, the three traversal sequences:
//5
//3 8
//1 4 7 9
//   - In-order 1 3 4 5 7 8 9
//   - Pre-order 5 3 1 4 8 7 9
//   - Post-order 1 4 3 7 9 8 5

// Problem 8: Write IsValidBST(TreeNode* Root) - returns true only if the tree rooted at
// Root actually satisfies the BST invariant everywhere, not just at the top level.
// bool IsValidBST(TreeNode* Root)
// Hint: checking just "Left->Value < Root->Value < Right->Value" at each node is NOT
// sufficient - it misses violations deeper in a subtree. Think about what valid RANGE of
// values each node is allowed to hold, and how that range narrows as you recurse down.

bool IsValidBSTHelper(TreeNode* Root, long Min, long Max)
{
    bool LeftValid;
    bool RightValid;
    
    if(Root == nullptr) return true;
    
    if(Min < Root->Value && Root->Value < Max)
    {
        LeftValid = IsValidBSTHelper(Root->Left, Min, Root->Value);
        RightValid = IsValidBSTHelper(Root->Right, Root->Value, Max);
    }
    else
    {
        return false;
    }

    return LeftValid && RightValid;
}

bool IsValidBST(TreeNode* Root)
{
    long Min = LONG_MIN;
    long Max = LONG_MAX;
    return IsValidBSTHelper(Root, Min, Max);
}

// Problem 9: Write CountLeaves(TreeNode* Root) - returns the number of leaf nodes
// (nodes with no children at all) in the tree.
// int CountLeaves(TreeNode* Root)

int CountLeaves(TreeNode* Root)
{
    if(Root == nullptr) return 0;
    if(Root->Left == nullptr && Root->Right == nullptr) return 1;
    return CountLeaves(Root->Left) + CountLeaves(Root->Right);
}

// Problem 10 (PAPER - traversal ID drill, do this WITHOUT re-deriving from Problem 7,
// use only the L/Root/R position rule to identify each): For the tree from Problem 7,
// three traversal outputs are given below, deliberately unlabeled. Identify which is
// In-order, which is Pre-order, and which is Post-order.
//   Output A: 1, 3, 4, 5, 7, 8, 9 In-Order
//   Output B: 5, 3, 1, 4, 8, 7, 9 Pre-Order
//   Output C: 1, 4, 3, 7, 9, 8, 5 Post-Order
