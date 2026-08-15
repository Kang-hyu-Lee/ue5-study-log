// Day 12 — Linked List Insert/Delete — TIMED PRACTICE
// Type this yourself. Do not paste. Set a timer per problem — the point is
// building speed/fluency on a pattern you already understand conceptually,
// not re-deriving it from scratch each time.
//
// Reuse this struct for all problems below.
#include <iostream>
struct Node
{
    int Data;
    Node* Next;
};

// ---------------------------------------------------------------
// Problem 1 (target: 5 min) — Insert at Front
// Write a function that takes the current Head (by reference, so you can
// reassign it) and a value, creates a new node, and inserts it at the front.
// Signature:
// void InsertAtFront(Node*& Head, int Value);

void InsertAtFront(Node*& Head, int Value){
    Node* NewNode = new Node{Value, nullptr};
    NewNode->Next = Head;
    Head = NewNode;

}

// ---------------------------------------------------------------
// Problem 2 (target: 6 min) — Insert at Back
// Same idea, but the new node becomes the new tail.
// Handle the empty-list case (Head == nullptr).
// Signature:
// void InsertAtBack(Node*& Head, int Value);

void InsertAtBack(Node*& Head, int Value){
    Node* NewNode = new Node{Value, nullptr};
    Node* Current = Head;
    if(Head == nullptr){
        Head = NewNode;
    } else{
        while(Current->Next != nullptr){
            Current = Current->Next;
        }
        Current->Next = NewNode;
    }
}


// ---------------------------------------------------------------
// Problem 3 (target: 7 min) — Delete Head
// Remove the first node and free its memory. Handle the case where the
// list becomes empty after deletion.
// Signature:
// void DeleteHead(Node*& Head);

void DeleteHead(Node*& Head){
    if(Head->Next == nullptr){
        Node* Temp = Head;
        Head = nullptr;
        delete Temp;
        std::cout << "Empty after deletion";
    }else {
        Node* Temp = Head;
        Head = Head->Next;
        delete Temp;
    }
}


// ---------------------------------------------------------------
// Problem 4 (target: 8 min) — Delete by Value
// Find the first node whose Data matches TargetValue and remove it.
// Handle: value is in the head node, value is in the middle, value is not
// found anywhere in the list (do nothing, don't crash).
// Signature:
// void DeleteValue(Node*& Head, int TargetValue);

void Deletevalue(Node*& Head, int TargetValue){
    Node* Prev = Head;
    if(Head == nullptr){
        std::cout << "Head is a nullptr" << std::endl;
        return;
    }else if(Head->Data == TargetValue){
        if(Head->Next == nullptr){
            Node* Temp = Head;
            Head = nullptr;
            delete Temp;
            std::cout << "Value is in head node, linked list empty after deletion\n";
            return;
        }else{
            Node* Temp = Head;
            Head = Head->Next;
            delete Temp;
            std::cout << "Value is in head node\n";
            return;
        }   
    }else {
        while(Prev->Next != nullptr){
            if(Prev->Next->Data == TargetValue){
                Node* Current = Prev->Next;
                Prev->Next = Current->Next;
                delete Current;
                std::cout << "Value is in the middle\n";
                return;
            }else{
                Prev = Prev->Next;
            }
        }
    }
    if(Prev->Data != TargetValue){
    std::cout << "Value is not found anywhere in the list\n";
    }
}

// ---------------------------------------------------------------
// Problem 5 (target: 6 min) — Print + Count
// Two small helpers you'll want for testing everything above.
// Signature:
// void PrintList(Node* Head);      // e.g. "10 -> 20 -> 30 -> nullptr"
// int CountNodes(Node* Head);

void PrintList(Node* Head){
    while(Head != nullptr){
        std::cout << Head->Data << " -> ";
        Head = Head->Next;
    }
    std::cout << "nullptr" << std::endl;
}

int CountNode(Node* Head){
    int Count = 0;
    while(Head != nullptr){
        Count++;
        Head = Head->Next;
    }
    return Count;
}

// ---------------------------------------------------------------
// Problem 6 (target: 10 min) — Put it together
// In main(): build a list of 5 ints using InsertAtBack, print it, delete
// the head, delete a value from the middle, delete a value that doesn't
// exist, print again, and confirm the count matches what you expect at
// each step.
// int main() { ... }

int main() {
    Node* Head = nullptr; 

    InsertAtBack(Head, 10);
    InsertAtBack(Head, 20);
    InsertAtBack(Head, 30);
    InsertAtBack(Head, 40);
    InsertAtBack(Head, 50);
    
    PrintList(Head);

    std::cout << "Expected count 5, Actual count: "<< CountNode(Head) << std::endl;

    DeleteHead(Head);
    Deletevalue(Head, 30);
    Deletevalue(Head, 60);

    PrintList(Head);

    std::cout << "Expected count 3, Actual count: "<< CountNode(Head) << std::endl;

    
    return 0;
}