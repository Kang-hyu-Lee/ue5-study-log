// Day 16 — Stacks & Queues — EXERCISES
// Type your attempts below each problem. Do not look at the solution file until you've tried.

#include <iostream>
using namespace std;

// ============================================================
// PROBLEM 1 — Array-based stack, fixed capacity
// ============================================================
// Build a stack of ints backed by a fixed-size array (capacity 5).
// Implement: Push, Pop, Peek, IsEmpty, IsFull.
// Pop on empty stack: print "Stack underflow" and return -1 (sentinel).
// Push on full stack: print "Stack overflow" and do nothing.
//
// struct ArrayStack
// {
//     int Data[5];
//     int Top;   // hint: what should Top be when the stack is empty? (see concept file trace)
// };
//
// void InitStack(ArrayStack& s);      // hint: & = pass by reference, see Day 12 concept
// void Push(ArrayStack& s, int value);
// int Pop(ArrayStack& s);
// int Peek(ArrayStack& s);
// bool IsEmpty(ArrayStack& s);
// bool IsFull(ArrayStack& s);

// YOUR CODE HERE:
struct ArrayStack
{
    int Data[5];
    int Top = -1;
};

void InitStack(ArrayStack& s){
    s.Top = -1;
}

void Push(ArrayStack& s, int value){
    if(s.Top == 4){
        cout << "Stack overflow" << endl;
        return;
    }else{
        s.Data[s.Top + 1] = value;
        s.Top += 1;
    }
}

int Pop(ArrayStack& s){
    if(s.Top == -1){
        cout << "Stack underflow" << endl;
        return -1;
    }else{
        int TopStack = s.Data[s.Top];
        s.Top -= 1;
        return TopStack;
    }
}

int Peek(ArrayStack& s){
    if(s.Top == -1){
        cout << "Stack is empty" << endl;
        return -1;
    }else{
        return s.Data[s.Top];
    }
}

bool IsEmpty(ArrayStack& s){
    if(s.Top == -1){
        cout << "Stack is empty" << endl;
        return true;
    }else {
        cout << "Stack is not empty" << endl;
        return false;
    }
}

bool IsFull(ArrayStack& s){
    if(s.Top == 4){
        cout << "Stack is full" << endl;
        return true;
    }else{
        cout << "Stack is not full" << endl;
        return false;
    }
}


// ============================================================
// PROBLEM 2 — Trace by hand, then verify
// ============================================================
// Given this sequence of calls on an empty ArrayStack (capacity 5):
// Push(3), Push(7), Push(1), Pop(), Push(9), Pop(), Pop()
// Write out the returned value of each Pop() call and the final state of Top,
// as a COMMENT, before writing code to verify it. Then write a small main()
// snippet that runs this sequence and prints results to check yourself.

// YOUR TRACE (as comments) HERE:
//3 7 1
//3 7 (1) so 1
//3 7 9
//3 7 (9) so 9
//3 (7) so 7
//Top will be equal to 0 because only 3 is left

// YOUR VERIFICATION CODE HERE:
int main(){
    ArrayStack Stack;
    InitStack(Stack);

    Push(Stack, 3);
    Push(Stack, 7);
    Push(Stack, 1);
    cout << Pop(Stack) << endl;
    Push(Stack, 9);
    cout << Pop(Stack) << endl;
    cout << Pop(Stack) << endl;

    return 0;
}
// ============================================================
// PROBLEM 3 — Linked-list-based queue
// ============================================================
// You already have TodoNode-style struct experience. Build:
//
// struct QueueNode
// {
//     int Value;
//     QueueNode* Next;
// };
//
// struct Queue
// {
//     QueueNode* Head;   // front — dequeue from here
//     QueueNode* Tail;    // back — enqueue here
// };
//
// void InitQueue(Queue& q);
// void Enqueue(Queue& q, int value);
// int Dequeue(Queue& q);        // print "Queue underflow", return -1 if empty
// bool IsEmpty(Queue& q);
//
// Hint: Enqueue must handle the EMPTY-QUEUE case separately (Head and Tail
// both need to point at the new node) vs. the non-empty case (only Tail's
// Next changes, then Tail itself moves). This mirrors the head-insert vs.
// mid-insert distinction you handled in DeleteCompleted design questions.

// YOUR CODE HERE:
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

void InitQueue(Queue& q){
    q.Head = nullptr;
    q.Tail = nullptr;
}

void Enqueue(Queue& q, int value){
    QueueNode* node = new QueueNode{value, nullptr};
    if(q.Head == nullptr){ //I'm thinking that I don't need to check tail because head nullptr inherently means tail nullptr from init function
        q.Head = node;
        q.Tail = node;
    }else{
        q.Tail->Next = node;
        q.Tail = node;
    }
}

int Dequeue(Queue& q){
    if(q.Head != nullptr){
        int Value = q.Head->Value;
        QueueNode* CurrNode = q.Head;
        q.Head = q.Head->Next;
        delete CurrNode;
        if(q.Head == nullptr){
            q.Tail = nullptr;
        }
        return Value;
    }else{
        cout << "Queue underflow" << endl;
        return -1;
    }
}

bool IsEmpty(Queue& q){
    return (q.Head == nullptr);
}


// ============================================================
// PROBLEM 4 — Conceptual (answer as comments, no code)
// ============================================================
// a) Why is a naive array-based queue's Dequeue() O(n) instead of O(1)?
// b) What specifically would go wrong if your Queue struct only had a
//    Head pointer and no Tail pointer? Be specific about which operation
//    breaks and why.
// c) Give ONE real gamedev example where a stack is the right structure,
//    and ONE where a queue is the right structure. Don't reuse the exact
//    examples from the concept file — think of your own.

// YOUR ANSWERS HERE:
//Dequeuing element at index 0 will involve a shift of all elements in the array so O(n) because we need to iterate the whole array for the shift
//This would break Enqueue because we need to attach the new node after the last node which is Tail but if we don't have it then it'll be an iteration through next until nullptr, breaking the entire point of the linked list
//Stack would be the right structure for maybe a system where you can see your match history but it shows the most recent one first, and for queue anything that involves queueing so like slay the spire turn games where the cards play in the order you pressed them.

// ============================================================
// PROBLEM 5 — Bug hunt
// ============================================================
// The Dequeue() below has a bug. Find it and fix it as a comment explaining
// WHY it's wrong (don't just paste corrected code — explain the failure mode).
//
// int Dequeue(Queue& q)
// {
//     int value = q.Head->Value;
//     q.Head = q.Head->Next;
//     if(q.Head == nullptr){
//          q.Tail = nullptr; //this would be the fix
//     }
//     return value;
// }
//
// Hint: think about what happens to Tail when you dequeue the LAST remaining
// element in the queue.

// YOUR ANSWER HERE:
//The tail will become a dangling pointer because the Tail still points at the previous tail node even though head is now pointing to nullptr
