// Day 24 — Templates Exercises
// Type this yourself — do not paste. Predict compiler behavior before running.

#include <iostream>
using namespace std;

// ---------------------------------------------------------------
// Problem 1: Write a template Max function
// ---------------------------------------------------------------
// Return whichever of A or B is larger, generic over type T.
// hint: template<typename T> goes on the line ABOVE the function signature.
// hint: use > to compare, same as you would for int.

template<typename T>
T Max(T a, T b){
    if(a>=b) return a;
    return b;
}


// ---------------------------------------------------------------
// Problem 2: Write a template Min function
// ---------------------------------------------------------------
// Same idea as Problem 1 but returns the smaller value.
template<typename T>
T Min(T a, T b){
    if(a>=b) return b;
    return a;
}


// ---------------------------------------------------------------
// Problem 3: Write a template Swap function
// ---------------------------------------------------------------
// Swap the values of A and B IN PLACE — meaning the caller's original variables
// change. Think back to Day 12 (references vs pointers): what do you need in the
// parameter list to mutate the CALLER's variables, not local copies?
// hint: this needs references (&), not plain T parameters.

template<typename T>
void Swap(T &a, T&b){
    T temp = a;
    a = b;
    b = temp;
}

// ---------------------------------------------------------------
// Problem 4: Predict-then-test — a template that will fail for some types
// ---------------------------------------------------------------
// Below is a template Clamp function. Read it, predict what type(s) it will
// FAIL to compile for, then test your prediction in main() by calling it with
// a type you think will break it.
struct Dummy
{
    float A;
};

template<typename T>
T Clamp(T Value, T MinVal, T MaxVal)
{
    if (Value < MinVal) return MinVal;
    if (Value > MaxVal) return MaxVal;
    return Value;
}
// Your prediction (write as a comment): Clamp will fail to compile for a type that...
// A type that doesn't have a defined > operators such as strings (without using .length())


// ---------------------------------------------------------------
// Problem 5: Simple class template
// ---------------------------------------------------------------
// Write a class template `Pair` holding two values of the SAME type T:
// members FirstValue and SecondValue, both type T.
// Add a member function PrintPair() that prints both values.
// hint: template<typename T> goes above `class Pair`, same pattern as functions.

template <typename T>
class Pair{
    T Fval;
    T Sval;
    public:
    Pair(T FirstValue, T SecondValue) : Fval(FirstValue), Sval(SecondValue) {}
    void PrintPair(){
        cout<< "First Value: " << Fval << '\n' <<"Second Value: " << Sval << endl;
    }
};


int main()
{
    // Call Max/Min with at least two different types (e.g. int and float) to
    // prove one function body handles both.
    cout << "Float Max: " << Max(2.0,3.0) << endl;
    cout << "Int Max: " << Max(2,3) << endl;
    cout << "Float Min: " << Min(2.0,3.0) << endl;
    cout << "Int Min: " << Min(2,3) << endl;
    // Call Swap with two ints, print before/after to confirm it actually mutated
    // the caller's variables.
    int a = 2;
    int b = 3;
    cout << "Before swap: "<< a << " " << b << endl;

    Swap(a,b);
    cout << "After swap: "<< a << " " << b << endl;

    // Instantiate Pair<int> and Pair<FString-equivalent, i.e. std::string> and
    // call PrintPair() on both.
    Pair<int> IntPair(1,2);
    Pair<string> StringPair("Hello", "World");
    IntPair.PrintPair();
    StringPair.PrintPair();
    
    return 0;
}
