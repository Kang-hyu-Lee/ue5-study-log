// Day 12 — References vs Pointers — Exercises
// Type this yourself. Do not paste.

// ---------------------------------------------------------------
// Problem 1 — Reference swap
// Write a function that swaps the values of two ints using references
// (not pointers). Caller should be able to call it like: Swap(A, B);
// with no & or * at the call site.
// Signature:
// void Swap(int& A, int& B);

void Swap(int& A, int& B){
    int Temp = A;
    A = B;
    B = Temp;
}


// ---------------------------------------------------------------
// Problem 2 — Pointer swap
// Write the same swap function using pointers instead. Caller must pass
// addresses explicitly: SwapPtr(&A, &B);
// Signature:
// void SwapPtr(int* A, int* B);
void SwapPtr(int* A, int* B){
    int Temp = *A;
    *A = *B;
    *B = Temp;
}


// ---------------------------------------------------------------
// Problem 3 — Spot the bug
// The function below is broken. Don't fix it yet — write, as a comment,
// WHY it's broken and what category of bug this is (you covered the
// category by name in the concept notes today).
//
// int& GetDoubled(int Value)
// {
//     int Result = Value * 2;
//     return Result;
// }
//
// Your answer (as a comment): This is broken because Result is a local value of GetDoubled, so once it returns, 
// Result becomes a dangling Reference causing undefined behaviour (Dangerous because it will still compile, May even show the right answer)


// ---------------------------------------------------------------
// Problem 4 — const&  vs value
// Write a function TakesByValue(FakeStruct S) and a function
// TakesByConstRef(const FakeStruct& S) for the struct below (a stand-in
// for something like FVector — don't worry about it being fake).
// In a comment, state which one you'd use in real UE5-style code passing
// a large struct, and why, in one sentence.
//
// struct FakeStruct
// {
//     int Values[20]; // pretend this is expensive to copy
// }; //I'd use TakesByConstRef(const FakeStruct& S) because if int Values[20] is expensive to copy, then inputting it with const FakeStruct& will allow
      //the function to access it directly without needing to make a copy, which in this case is expensive (such as a large struct) because a large struct will get every bytes copied


// ---------------------------------------------------------------
// Problem 5 — When NOT to use a reference
// In a comment (no code needed), describe one concrete situation where a
// pointer is the correct choice instead of a reference, and say which
// property of pointers (nullability / reseating / arithmetic) makes it
// the right tool. Use an example that isn't already in the concept notes.

//An example for nullability would be when let's say a variable could be non-existent such as checking if an item is in an inventory
//For reseating let's say a class has a job advancement so has to point to a new set of skills 
//For arithmetic if the variable needs to traverse so maybe finding a name in a player search because the name is a string with a fixed max characters per name so we traverse using sizeof(name max length)
//(Improved answer) So we have a char buffer as a char array to input individual names, and another player list array that keeps all those names, so have a nested loop where
//inner loop parses the name and the outer loop compares it with the search until a player is found
//But the important part of the example is taking steps at sizeof(char) until '\O' is found to parse a name
 