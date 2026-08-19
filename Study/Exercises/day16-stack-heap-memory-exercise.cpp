// Day 16 — Stack vs Heap Memory — EXERCISES
// Type your attempts below each problem. Do not look at the solution file until you've tried.

#include <iostream>
using namespace std;

// ============================================================
// PROBLEM 1 — Identify stack vs heap
// ============================================================
// For each line below, write "STACK" or "HEAP" as a comment saying where
// the actual data lives (not the pointer variable itself, the DATA it
// refers to).
//
// int a = 5;                       //stack
// int* b = new int(5);             //heap
// int* c = &a;                     //stack
// int arr[10];                     //stack
// int* d = new int[10];            //heap

// YOUR ANSWERS HERE:



// ============================================================
// PROBLEM 2 — Fix the leak
// ============================================================
// This function leaks. Rewrite it so it doesn't. Explain in a comment WHY
// the original leaks.
//
// void MakeCounter()
// {
//     int* counter = new int(0);
//     *counter = *counter + 1;
//     cout << *counter << endl;
// }

// YOUR FIXED VERSION HERE:
void MakeCounter(){
    int* counter = new int(0);
    *counter = *counter + 1;
    cout << *counter << endl;
    delete counter;
}

//The function never calls delete for the new counter on the heap but what I'm confused about is why are we creating the counter without a parameter then it's not useful either way no?



// ============================================================
// PROBLEM 3 — Dangling pointer, spot it
// ============================================================
// One of these two functions has a dangling pointer bug. Identify which one
// and explain exactly when the bug occurs.
//
// int* VersionA()
// {
//     int local = 42;
//     return &local;
// }
//
// int* VersionB()
// {
//     int* heapVal = new int(42);
//     return heapVal;
// }
//
// (Note: VersionB requires the CALLER to eventually delete the returned
// pointer — whose responsibility is that, and why is it risky design?)

// YOUR ANSWER HERE: Version A local is a local variable so when we return &local, the variable disappears with the end of the function from the stack
//For the note, it's risky to make the caller delete the heap value because this should be managed internally. Either have a cleanup in another function like a separate delete function but this too once again has no parameters so it's counterintuitive



// ============================================================
// PROBLEM 4 — Double delete
// ============================================================
// Write a short main()-style snippet (as a comment, no need to compile)
// that demonstrates a double-delete bug: two different pointer variables
// both end up trying to delete the same heap memory. Then explain, in your
// own words, the general PATTERN of code structure that causes this
// (hint: think about ownership — who "owns" a piece of heap memory and is
// responsible for deleting it?).

// YOUR ANSWER HERE:
//int main(){
//  int* b = new int(10);
//  DeleteValue(b); where function takes parameter (int*& b)
//  delete b;
//}
//RIGHT ANSWER:
//int main(){
//  int* a = new int(10)
//  int* b = a;
//  delete a;
//  delete b; //One path deletes and nulls its own reference
              //but a second separate pointer variable still holds the stale address and doesn't know it's dangling
//}



// ============================================================
// PROBLEM 5 — Portfolio audit (no new code — inspect your own file)
// ============================================================
// Open Study/Portfolio/todo-list.cpp. Answer as comments:
// a) List every place `new` is called.
// b) List every place `delete` is called (if any).
// c) Based on a) and b), does your current file leak? Under what
//    conditions (e.g. only when a task is deleted? only at program exit?)?
// d) What line(s) will you need to add to DeleteCompleted to fix this,
//    given what you now know about heap memory?

// YOUR AUDIT HERE: 
//a) AddTask();
//b) DeleteCompleted();
//c) No we designed it so that it wouldn't by making AddTask create the TodoNode on the heap, and DeleteCompleted iterates through from head all the way to the end to delete the completed TodoNodes
//d)void DeleteCompleted(TodoNode*& Head){
//    while(Head != nullptr){
//        if(Head->Data.IsComplete){
//            TodoNode* Temp = Head;
//            Head = Head->Next;
//            delete Temp;
//        }else{
//            break;
//        }
//    }
//    if(Head == nullptr){
//        return;
//    }else{
//       TodoNode* Prev = Head;
//        while(Prev->Next != nullptr){
//            if(Prev->Next->Data.IsComplete){
//                TodoNode* Current = Prev->Next;
//                Prev->Next = Current->Next;
//                delete Current;
//            }else{
//                Prev = Prev->Next;
//            } 
//        }
//    }
//}
// We already completed the function with the deletes, where we use Temp or Current to assign the current TodoNode and free it once we're done