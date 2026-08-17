// Pointers Pt.2 — Solutions

#include <iostream>
using namespace std;

int main() {
    // 1. Array walk via pointer arithmetic
    int Health[4] = {100, 80, 60, 40};
    int* HpPtr = Health;   // array decays to pointer at Health[0]

    cout << "Health array elements: ";
    for (int i = 0; i < 4; i++) {
        cout << *(HpPtr + i) << " ";   // explicit arithmetic + dereference,
                                        // NOT HpPtr[i] — same result, different
                                        // mechanism, which is the point of the drill
    }
    cout << endl;

    // 2. Prove *(Ptr + i) == Ptr[i]
    int i = 3;
    cout << "*(HpPtr + i): " << *(HpPtr + i) << "\n"
         << "(HpPtr[i]):   " << HpPtr[i] << '\n';
    // Both print 40 — HpPtr[i] IS *(HpPtr + i), just with different syntax.
    // This is literally how the compiler treats array subscripting.

    // 3. One-past-the-end pointer
    int* EndPtr = HpPtr + 4;   // COMPUTE the address only — never dereference this
    int* Walker = HpPtr;
    while (Walker != EndPtr) {
        cout << "Current element: " << *Walker << '\n';
        Walker++;               // moves by sizeof(int), lands on next element
    }
    // Stopping condition compares ADDRESSES (Walker vs EndPtr), never reads
    // memory to decide when to stop. EndPtr itself is never dereferenced —
    // it's a landmark, not a container.

    // 4. Null check before dereference
    int* Nothing = nullptr;
    if (Nothing == nullptr) {
        cout << "Empty" << '\n';
    } else {
        cout << *Nothing << '\n';   // only reachable if Nothing were NOT null —
                                      // guarded, so this line can never run on
                                      // a null pointer. That's the whole pattern.
    }

    // 5. Wild vs dangling
    // Snippet A — WILD: int* PtrA; declares the pointer but never assigns it
    // an address. It holds whatever garbage bits happened to be in that
    // memory slot already. It was never valid — there's no "before" state
    // where it pointed somewhere real.
    //
    // Snippet B — DANGLING: PtrB = &Temp; was valid the moment it was
    // assigned — Temp genuinely existed at that address. But Temp is a
    // block-scoped local; once the { } block ends, Temp's storage is
    // reclaimed. PtrB still holds that old address, but nothing valid is
    // guaranteed to live there anymore. It WAS valid, then stopped being.

    // 6. Defensive nulling
    int Value = 7;
    int* Ptr6 = &Value;

    cout << "*Ptr6: " << *Ptr6 << '\n';   // 7 — dereference, not a string literal
    Ptr6 = nullptr;                        // defensive: null it immediately after
                                            // you're done needing it

    if (Ptr6 == nullptr) {
        cout << "Nulled — safe to check, unsafe to deref" << '\n';
    } else {
        cout << *Ptr6 << '\n';   // guarded — unreachable while Ptr6 is null
    }
    // The whole point: nulling Ptr6 after use turns a potential dangling
    // pointer into a checkable null pointer. A dangling pointer looks just
    // as "valid" as a real one until you dereference it and something goes
    // wrong (sometimes not even every run — that's what makes UB dangerous).
    // A null pointer is safe to interrogate with == nullptr, always.

    return 0;
}
