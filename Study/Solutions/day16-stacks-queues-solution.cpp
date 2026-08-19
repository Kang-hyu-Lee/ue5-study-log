// Day 16 — Stacks & Queues — SOLUTIONS
// Compare against your own attempt AFTER you've tried. Read the "why" for each.

#include <iostream>
using namespace std;

// ============================================================
// PROBLEM 1 — Array-based stack, fixed capacity
// ============================================================
struct ArrayStack
{
    int Data[5];
    int Top;   // -1 means empty. Top is the INDEX of the current top element.
};

void InitStack(ArrayStack& s)
{
    s.Top = -1;   // empty state, matches the concept-file trace
}

bool IsEmpty(ArrayStack& s)
{
    return s.Top == -1;
}

bool IsFull(ArrayStack& s)
{
    return s.Top == 4;   // capacity 5, valid indices 0-4
}

void Push(ArrayStack& s, int value)
{
    if (IsFull(s))
    {
        cout << "Stack overflow" << endl;
        return;   // guard clause — same pattern as your DeleteCompleted head-case guards
    }
    s.Top = s.Top + 1;
    s.Data[s.Top] = value;
}

int Pop(ArrayStack& s)
{
    if (IsEmpty(s))
    {
        cout << "Stack underflow" << endl;
        return -1;
    }
    int value = s.Data[s.Top];
    s.Top = s.Top - 1;   // just move Top back — the old value is left in the array
                          // but it's "dead" data, next Push will overwrite it.
    return value;
}

int Peek(ArrayStack& s)
{
    if (IsEmpty(s))
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
    return s.Data[s.Top];
}

// ============================================================
// PROBLEM 2 — Trace
// ============================================================
// Push(3):  Data=[3]           Top=0
// Push(7):  Data=[3,7]         Top=1
// Push(1):  Data=[3,7,1]       Top=2
// Pop():    returns 1          Top=1   Data still [3,7,1] but index 2 is "dead"
// Push(9):  Data=[3,7,9]       Top=2   (overwrote the dead 1)
// Pop():    returns 9          Top=1
// Pop():    returns 7          Top=0
// Final: Top=0, top element is 3

void RunProblem2()
{
    ArrayStack s;
    InitStack(s);
    Push(s, 3);
    Push(s, 7);
    Push(s, 1);
    cout << Pop(s) << endl;   // 1
    Push(s, 9);
    cout << Pop(s) << endl;   // 9
    cout << Pop(s) << endl;   // 7
    cout << "Top index: " << s.Top << endl;   // 0
}

// ============================================================
// PROBLEM 3 — Linked-list-based queue
// ============================================================
struct QueueNode
{
    int Value;
    QueueNode* Next;
};

struct Queue
{
    QueueNode* Head;
    QueueNode* Tail;
};

void InitQueue(Queue& q)
{
    q.Head = nullptr;
    q.Tail = nullptr;
}

bool IsEmpty(Queue& q)
{
    return q.Head == nullptr;
}

void Enqueue(Queue& q, int value)
{
    QueueNode* NewNode = new QueueNode();   // heap-allocated — must outlive this function
    NewNode->Value = value;
    NewNode->Next = nullptr;

    if (IsEmpty(q))
    {
        // Empty-queue case: both Head and Tail must point at the new (only) node.
        q.Head = NewNode;
        q.Tail = NewNode;
        return;   // guard clause — closes off the non-empty branch below
    }

    // Non-empty case: link old tail to new node, then move Tail forward.
    q.Tail->Next = NewNode;
    q.Tail = NewNode;
}

int Dequeue(Queue& q)
{
    if (IsEmpty(q))
    {
        cout << "Queue underflow" << endl;
        return -1;
    }

    QueueNode* OldHead = q.Head;
    int value = OldHead->Value;
    q.Head = q.Head->Next;

    // Critical case the naive version misses: if we just removed the LAST node,
    // q.Head is now nullptr, but q.Tail still points at the freed node -> dangling.
    if (q.Head == nullptr)
    {
        q.Tail = nullptr;
    }

    delete OldHead;   // free the heap node — see stack-vs-heap concept file
    return value;
}

// ============================================================
// PROBLEM 4 — Conceptual answers
// ============================================================
// a) A naive array queue removes from index 0, so every remaining element
//    must shift left by one to close the gap -> O(n) work per Dequeue.
//    A linked-list queue just moves Head to Head->Next -> O(1), no shifting.
//
// b) Without a Tail pointer, Enqueue would have to walk the ENTIRE list from
//    Head every time just to find the last node and attach the new one ->
//    Enqueue degrades from O(1) to O(n). The structure still "works," it's
//    just slow at scale — the kind of bug that only shows up under load,
//    which is exactly why it matters in production/interviews.
//
// c) Stack: an ability-combo/undo system — most recent action is what gets
//    undone first (LIFO matches "undo the last thing I did").
//    Queue: a matchmaking lobby — first player to queue gets matched first
//    (FIFO matches "fairness / arrival order").

// ============================================================
// PROBLEM 5 — Bug hunt
// ============================================================
// Buggy version:
// int Dequeue(Queue& q)
// {
//     int value = q.Head->Value;
//     q.Head = q.Head->Next;
//     return value;
// }
//
// BUG: when the queue has exactly one node and you dequeue it, q.Head->Next
// is nullptr, so q.Head correctly becomes nullptr — but q.Tail is NEVER
// updated. q.Tail still points at the node that Head just moved past.
// The next Enqueue() checks IsEmpty() (true, since Head is null), takes the
// "empty" branch, and sets Head = Tail = NewNode — but the OLD Tail node
// was never deleted, so its memory leaks AND was never properly cleared as
// a "dangling" reference in the meantime. Worse: if any other code path
// used q.Tail directly for a non-empty check instead of q.Head, it would
// wrongly think the queue still has an item.
// FIX (see Problem 3's real Dequeue): explicitly check `if (q.Head ==
// nullptr) q.Tail = nullptr;` after moving Head, AND delete the old node.
// This is the exact same class of bug as your DeleteCompleted "what happens
// on the last/only element" question from Day 12-13.

int main()
{
    RunProblem2();

    Queue q;
    InitQueue(q);
    Enqueue(q, 10);
    Enqueue(q, 20);
    Enqueue(q, 30);
    cout << Dequeue(q) << endl;   // 10
    cout << Dequeue(q) << endl;   // 20
    cout << Dequeue(q) << endl;   // 30
    cout << Dequeue(q) << endl;   // underflow, -1

    return 0;
}
