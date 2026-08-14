// Pointers Pt.2 — Exercises
// Type this yourself. Don't paste. Explain each line back before moving on.

#include <iostream>
using namespace std;

int main() {
    // 1. Array walk via pointer arithmetic
    //    Declare: int Health[4] = {100, 80, 60, 40};
    //    Get a pointer to the first element (no & needed — array name decays to pointer).
    //    Using ONLY pointer arithmetic (Ptr + i) and dereference (*), print all 4 values —
    //    do NOT use Health[i] anywhere in this one.

    int Health[4] = {100, 80, 60, 40};
    int* HpPtr = Health;

    cout << "Health array elements: ";
    for (int i=0; i<4; i++){
        //cout << HpPtr[i] << " "; Spec says to use pointer arithmetic (Ptr + i)
        cout << *(HpPtr + i) << " ";
    }
    cout << endl;
    // 2. Prove *(Ptr + i) == Ptr[i]
    //    Using the same Health array, pick any index i, and print both
    //    *(Ptr + i) and Ptr[i] on the same line to confirm they match.
    int i = 3;
    cout << "*(HpPtr + i):  "<< *(HpPtr + i) << "\n" << "(HpPtr[i]): " << (HpPtr[i]) << '\n';

    // 3. One-past-the-end pointer (safe use)
    //    Compute EndPtr = Ptr + 4 (one past Health's last element).
    //    Write a loop that starts at Ptr and increments until it equals EndPtr,
    //    printing each value along the way. Do NOT dereference EndPtr itself.
    //i = 0; this one is just the wrong type to begin with
    //int EndPtr = *(HpPtr + 4); I did the opposite of what had to be done we did not want to dereference EndPtr just get the address of HpPtr+4 to compare
    int* EndPtr = HpPtr + 4;
    int* Walker = HpPtr;
    while(Walker != EndPtr){
        cout <<"Current elment: " << *Walker <<'\n';
        Walker++;
    }

    // 4. Null check before dereference
    //    Declare int* Nothing = nullptr;
    //    Write an if/else that checks Nothing before dereferencing:
    //    print "empty" if null, otherwise print *Nothing.
    //    (This should never crash, however you run it.)
    int* Nothing = nullptr;

    if(Nothing == nullptr) {
        cout << "Empty" << '\n';
    }else {
        cout << "Not nullptr printing content: " << *Nothing << '\n'; //added printing *Nothing
    }
    // 5. Wild vs dangling — identify, don't run
    //    Below are two snippets. As a COMMENT above each, label it
    //    "wild" or "dangling" and explain why in one line. Do not fix them,
    //    just diagnose.
        //This one is a wild pointer because it is never initialized just created with int* PtrA; so holds garbage
    // Snippet A:
    // int* PtrA;
    // std::cout << *PtrA;
        //This one is a dangling pointer because the element at the pointer's address is no longer in scope once we are out (so Temp is out of scope)
    // Snippet B:
    // int* PtrB;
    // {
    //     int Temp = 99;
    //     PtrB = &Temp;
    // }
    // std::cout << *PtrB;


    // 6. Defensive nulling
    //    Declare int Value = 7; int* Ptr6 = &Value;
    //    Print *Ptr6, then set Ptr6 = nullptr, then show a SAFE check
    //    (like exercise 4) that would catch someone trying to use Ptr6 after
    //    it's been nulled — no crash should be possible.
    int Value = 7;
    int* Ptr6 = &Value;

    cout << "Currnet element at *Ptr6: " << *Ptr6 << '\n'; //fixed from cout << "*Ptr" this would only print the string *Ptr6 instead of 7
    Ptr6 = nullptr;

    if(Ptr6 == nullptr){
        cout << "Nulled by nullptr" << '\n';
    } else{
        cout << "No nullptr printing content: " << *Ptr6 << '\n'; //added printing *Ptr*
    }

    return 0;
}
