// Pointers Pt.2 — Extra Drills
// Separate from the first 6 — do these whenever, no rush.
// Type this yourself. Don't paste.

#include <iostream>
using namespace std;

int* FindFirstNegative(int* Arr, int Size){
    int* Walker = Arr;
    int* EndPtr = Arr + Size;

    while(Walker != EndPtr){
        if(*Walker < 0){
            return Walker;
        }
        Walker++; 
    }
    return nullptr;
}

int main() {
    // 7. Backwards walk
    //    int Nums[5] = {1, 2, 3, 4, 5};
    //    Get a pointer to the LAST element without using indexing to find it
    //    directly (i.e. build the pointer via arithmetic: Ptr + 4, not &Nums[4]).
    //    Then walk backwards (Ptr--) printing each value until you've printed
    //    all 5, ending at the first element.
    int Nums[5] = {1, 2, 3, 4, 5};
    int* NumPtr = Nums;

    cout << "Printing Nums in reverse order: ";

    for(NumPtr += 4; NumPtr >= Nums; NumPtr--) {
        cout << *NumPtr << " ";
    }
    
    cout << endl;
    // 8. Pointer subtraction
    //    Using Nums from #7, take a pointer to element 0 and a pointer to
    //    element 4. Subtract them (LastPtr - FirstPtr). Print the result and,
    //    in a comment, explain what the number you get actually represents
    //    (hint: it's not a byte count).
    int* FirstPtr = Nums;
    int* LastPtr = Nums + 4;

    cout << *LastPtr - *FirstPtr << '\n' << LastPtr - FirstPtr << '\n'; //so both printed 4 one is 5-1 and the other I would think is the substraction of the addresses on whatever base they are in (wrong answer)
                                                                        //the 4 in 'LastPtr - FirstPtr' comes from the raw byte gap(16) divided by sizeof(int) because it's an int array so 16/4=4

    // 9. Two arrays, no crossing
    //    Declare two separate arrays: int A[3] = {1,2,3}; int B[3] = {4,5,6};
    //    Get PtrA pointing at A[0] and PtrB pointing at B[0].
    //    In a comment (do not write code that does this): explain why
    //    computing PtrA - PtrB or comparing PtrA < PtrB would be meaningless,
    //    even though it would compile.
    int A[3] = {1, 2, 3};
    int B[3] = {4, 5, 6};

    int* PtrA = A;
    int* PtrB = B;

    //they are two separate arrays meaning that we cannot use comparisons that involve the addresses themselves because those would just be garbage results (attempt)
    //garabe result is too vague it's that the result is not defined by the C++ standard because the pointers belong to two different objects, so undefined

    // 10. Function returning a dangling pointer
    //    Below is a function. As a comment underneath, explain exactly why
    //    calling it and dereferencing the result is unsafe, referencing what
    //    you learned about scope and stack memory.
    //
    //    int* GetLocalAddress() {
    //        int LocalValue = 10;
    //        return &LocalValue;
    //    }
    //
    //    (Do not call this function in your file — diagnosis only.)
        //this function returns a variable that is only in the scope of this function so once outside the pointer will become a dangling pointer


    // 11. Null-safe function contract
    //    Write a function `int* FindFirstNegative(int* Arr, int Size)` that
    //    scans Arr and returns a pointer to the first negative value it finds,
    //    or nullptr if none exist. Then call it on
    //    int Data[5] = {3, 7, -2, 9, -4};
    //    and safely print either the found value or "none found" — no
    //    dereference should be possible without a null check first.

    int Data[5] = {3, 7, -2, 9, -4};
    
    int* FNPtr = FindFirstNegative(Data, 5);
    if(FNPtr == nullptr){
        cout << "None found\n";
    }else{
        cout << "Found first negative number: " << *FNPtr << endl;
    }

    // 12. Fix the dangling bug
    //    Here's a version of exercise 10 someone "fixed" by adding a null
    //    check. As a comment, explain why this fix does NOT actually work:
    //
    //    int* Ptr = nullptr;
    //    {
    //        int Temp = 5;
    //        Ptr = &Temp;
    //    }
    //    if (Ptr != nullptr) {
    //        std::cout << *Ptr;   // still broken — why? 
    //    }                        //the int* Ptr = nullptr; happens before the Ptr = &Temp assignment, so Ptr by this point still holds the address but what's stored in that address is no longer guaranteed to be something meaningful(memory has been reclaimed and can be used for something else) because &Temp is out of scope
                                   //(added solution depth) so when Ptr != nullptr is checked it will check to true because there is a undefined value to this address(dangling pointer) then will attempt to std::cout << *Ptr; which is a dangling pointer problem              
                                   // the solution here would be to assign nullptr once it is out from the function with the variable that went out of scope

    return 0;
}
