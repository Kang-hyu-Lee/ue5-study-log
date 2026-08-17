// Day 12 — Linked List Insert/Delete — SOLUTIONS
// Matches the final, debugged versions worked through in session.
// Explanations focus on WHY each line is needed, not just what it does —
// most of these lines correspond to a bug that existed at some point
// during today's session.

#include <iostream>

struct Node
{
    int Data;
    Node* Next;
};

// ---------------------------------------------------------------
// Problem 1 — Insert at Front
void InsertAtFront(Node*& Head, int Value)
{
    Node* NewNode = new Node{ Value, nullptr };
    NewNode->Next = Head;   // MUST happen before Head is overwritten, or the
                            // rest of the list becomes unreachable
    Head = NewNode;
    // Head is Node*& — a reference to the CALLER's pointer variable, not a
    // copy. Without the &, this reassignment would only change a local
    // copy inside this function, and the caller's list would never update.
}

// ---------------------------------------------------------------
// Problem 2 — Insert at Back
void InsertAtBack(Node*& Head, int Value)
{
    Node* NewNode = new Node{ Value, nullptr };
    if (Head == nullptr)
    {
        // Empty list: inserting at back IS inserting at front here —
        // there's no existing tail to walk to.
        Head = NewNode;
    }
    else
    {
        Node* Current = Head;
        while (Current->Next != nullptr)   // walk until Current IS the last node
        {
            Current = Current->Next;
        }
        Current->Next = NewNode;
    }
}

// ---------------------------------------------------------------
// Problem 3 — Delete Head
void DeleteHead(Node*& Head)
{
    if (Head->Next == nullptr)
    {
        // Single-node list: save the address before freeing it (you can't
        // delete something and then still reference it afterward), then
        // null out Head since the list is now empty.
        Node* Temp = Head;
        Head = nullptr;
        delete Temp;
        std::cout << "Empty after deletion";
    }
    else
    {
        Node* Temp = Head;      // save old head before it's lost
        Head = Head->Next;      // advance caller's Head to the new first node
        delete Temp;            // free the old node's memory
    }
}

// ---------------------------------------------------------------
// Problem 4 — Delete by Value
void DeleteValue(Node*& Head, int TargetValue)
{
    // Guard added after the session found a real crash risk: dereferencing
    // Head below with no check would be undefined behavior if the list is
    // already empty when this function is called.
    if (Head == nullptr)
    {
        std::cout << "Head is a nullptr" << std::endl;
        return;
    }

    Node* Prev = Head;

    if (Head->Data == TargetValue)
    {
        if (Head->Next == nullptr)
        {
            Node* Temp = Head;
            Head = nullptr;
            delete Temp;
            std::cout << "Value is in head node, linked list empty after deletion\n";
            return;   // early exit — nothing left to check below
        }
        else
        {
            Node* Temp = Head;
            Head = Head->Next;
            delete Temp;
            std::cout << "Value is in head node\n";
            return;   // early exit
        }
    }
    else
    {
        while (Prev->Next != nullptr)
        {
            if (Prev->Next->Data == TargetValue)
            {
                Node* Current = Prev->Next;
                Prev->Next = Current->Next;   // splice around Current BEFORE deleting it
                delete Current;
                std::cout << "Value is in the middle\n";
                return;
                // return (not break) matters here: break would only exit the
                // while loop, letting execution fall through into the
                // "not found" check below — which would misfire, because
                // Prev now legitimately holds a DIFFERENT value than
                // TargetValue even on a successful delete.
            }
            else
            {
                Prev = Prev->Next;
            }
        }
    }

    // Only reached if the loop ran to completion without a match — i.e.
    // genuinely not found. Safe to dereference Prev here because the loop
    // condition (Prev->Next != nullptr) guarantees Prev never becomes null.
    if (Prev->Data != TargetValue)
    {
        std::cout << "Value is not found anywhere in the list\n";
    }
}

// ---------------------------------------------------------------
// Problem 5 — Print + Count
void PrintList(Node* Head)
{
    while (Head != nullptr)
    {
        std::cout << Head->Data << " -> ";
        Head = Head->Next;
    }
    std::cout << "nullptr" << std::endl;
}

int CountNode(Node* Head)
{
    int Count = 0;
    while (Head != nullptr)
    {
        Count++;
        Head = Head->Next;
    }
    return Count;
}

// ---------------------------------------------------------------
// Problem 6 — Put it together
int main()
{
    Node* Head = nullptr;

    InsertAtBack(Head, 10);
    InsertAtBack(Head, 20);
    InsertAtBack(Head, 30);
    InsertAtBack(Head, 40);
    InsertAtBack(Head, 50);

    PrintList(Head);
    std::cout << "Expected count 5, Actual count: " << CountNode(Head) << std::endl;

    DeleteHead(Head);
    DeleteValue(Head, 30);
    DeleteValue(Head, 60);   // not found — should print the "not found" message only

    PrintList(Head);
    std::cout << "Expected count 3, Actual count: " << CountNode(Head) << std::endl;

    return 0;
}
