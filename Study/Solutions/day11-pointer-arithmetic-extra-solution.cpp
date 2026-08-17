// Pointers Pt.2 — Extra Drills — Solutions

#include <iostream>
using namespace std;

int* FindFirstNegative(int* Arr, int Size) {
    int* Walker = Arr;
    int* EndPtr = Arr + Size;   // one-past-end, computed only, never dereferenced

    while (Walker != EndPtr) {
        if (*Walker < 0) {
            return Walker;      // found it — hand back the address
        }
        Walker++;
    }
    return nullptr;             // scanned everything, nothing negative found
}

int main() {
    // 7. Backwards walk
    int Nums[5] = {1, 2, 3, 4, 5};
    int* NumPtr = Nums;

    cout << "Printing Nums in reverse order: ";
    for (NumPtr += 4; NumPtr >= Nums; NumPtr--) {
        cout << *NumPtr << " ";
    }
    cout << endl;
    // Key fix vs. the buggy first attempt: >= instead of != includes the
    // Nums (index 0) case. != stops the loop the instant NumPtr reaches Nums,
    // before the body runs on that iteration — >= lets that final iteration
    // execute, then correctly fails the check on the NEXT decrement.
    // Legal because relational comparison (<, >, <=, >=) between pointers
    // IS well-defined within a single array — the standard guarantees
    // addresses increase monotonically across an array's elements.

    // 8. Pointer subtraction
    int* FirstPtr = Nums;
    int* LastPtr = Nums + 4;

    cout << "Value diff (*LastPtr - *FirstPtr): " << (*LastPtr - *FirstPtr) << '\n';
    cout << "Pointer diff (LastPtr - FirstPtr): " << (LastPtr - FirstPtr) << '\n';
    // LastPtr - FirstPtr == 4. This is NOT a raw byte count — the compiler
    // automatically divides the byte gap by sizeof(int) before returning
    // the result. Raw byte gap here would be 16 (4 elements * 4 bytes),
    // but pointer subtraction hands you 4: the ELEMENT COUNT between the
    // two addresses. This is why it's only legal within one array — the
    // "divide by element size" step only means something if both pointers
    // are measured in that same array's units.
    // Separately: *LastPtr - *FirstPtr (5 - 1 = 4) is a VALUE subtraction,
    // unrelated to pointer subtraction — they matched here by coincidence
    // of this specific data, not because they're the same operation.

    // 9. Two arrays, no crossing
    int A[3] = {1, 2, 3};
    int B[3] = {4, 5, 6};
    int* PtrA = A;
    int* PtrB = B;
    // PtrA - PtrB or PtrA < PtrB would compile, but the result is UNDEFINED
    // per the C++ standard — not "garbage," but literally not guaranteed to
    // mean anything. The standard only promises a meaningful relationship
    // between pointers within the SAME array (monotonic addresses, valid
    // subtraction as element count). A and B are two independent objects —
    // the compiler/OS decides their relative placement in memory, and nothing
    // in the language guarantees which one is "before" the other, or that
    // the gap between them is any particular multiple of sizeof(int).
    // It might look plausible when you run it once — that's what makes UB
    // dangerous, not that it visibly breaks.

    // 10. Function returning a dangling pointer
    // int* GetLocalAddress() {
    //     int LocalValue = 10;
    //     return &LocalValue;
    // }
    // LocalValue is a local variable — its storage lives on the stack frame
    // of GetLocalAddress(). The moment the function returns, that stack
    // frame is torn down/reused for whatever's called next. The returned
    // address still points at that now-invalid location — dereferencing it
    // reads memory that's no longer guaranteed to hold LocalValue, or
    // anything meaningful at all. Classic dangling pointer, produced at the
    // moment of return rather than at an explicit scope-exit like exercise
    // 10's { } block version.

    // 11. Null-safe function contract
    int Data[5] = {3, 7, -2, 9, -4};
    int* FNPtr = FindFirstNegative(Data, 5);
    if (FNPtr == nullptr) {
        cout << "None found\n";
    } else {
        cout << "Found first negative number: " << *FNPtr << endl;
    }
    // FindFirstNegative returns -2's address (index 2). Dereference only
    // happens inside the else branch, which only runs when FNPtr is
    // guaranteed non-null — no path to an unguarded dereference exists.

    // 12. Fix the dangling bug
    // int* Ptr = nullptr;
    // {
    //     int Temp = 5;
    //     Ptr = &Temp;
    // }
    // if (Ptr != nullptr) {
    //     std::cout << *Ptr;   // still broken
    // }
    // The null check is not the bug — it correctly evaluates Ptr's actual
    // state. The bug is that Ptr's state was never updated when Temp went
    // out of scope. Pointers don't know when the memory they point to
    // becomes invalid; nothing in the language automatically nulls a
    // pointer when its target's scope ends. So Ptr still holds Temp's old
    // (now-stale) address — a well-defined bit pattern, just no longer
    // pointing at anything guaranteed valid. Ptr != nullptr evaluates true
    // (it genuinely isn't null), the branch runs, and *Ptr reads memory
    // that's already been reclaimed. A null check can only catch a pointer
    // that IS nullptr — it does nothing for a dangling pointer, since
    // dangling pointers are indistinguishable from valid ones by inspection
    // alone. Real fix: whoever ends Temp's scope would need to manually
    // write Ptr = nullptr; right there, so the check downstream has
    // something real to catch.

    return 0;
}
