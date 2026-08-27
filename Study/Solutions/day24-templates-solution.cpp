// Day 24 — Templates SOLUTIONS
// Read only after attempting on paper + in your own exercise file first.

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// Problem 1
// ---------------------------------------------------------------
template<typename T>
T Max(T A, T B)
{
    return (A > B) ? A : B;
    // Compiler generates a separate Max<int>, Max<float>, etc. for each type
    // actually used below — one function body, many concrete instantiations.
}

// ---------------------------------------------------------------
// Problem 2
// ---------------------------------------------------------------
template<typename T>
T Min(T A, T B)
{
    return (A < B) ? A : B;
}

// ---------------------------------------------------------------
// Problem 3
// ---------------------------------------------------------------
template<typename T>
void Swap(T& A, T& B)
{
    T Temp = A;
    A = B;
    B = Temp;
    // T& (reference), not T — matches the Day 12 lesson: to mutate the CALLER's
    // actual variables rather than local copies, the parameters must bind to the
    // originals. Without &, this would swap two copies and have zero effect
    // outside the function — a silent no-op bug, not a compile error.
}

// ---------------------------------------------------------------
// Problem 4
// ---------------------------------------------------------------
template<typename T>
T Clamp(T Value, T MinVal, T MaxVal)
{
    if (Value < MinVal) return MinVal;
    if (Value > MaxVal) return MaxVal;
    return Value;
}
// Prediction: Clamp fails to compile for any type T that hasn't defined
// operator< (and operator>, implicitly needed via < comparisons here — actually
// only < is used directly, but note real clamp logic often needs both).
// A raw struct with no operators defined, e.g.:
//   struct NoCompare { int Value; };
// calling Clamp(NoCompare{1}, NoCompare{0}, NoCompare{5}) fails to compile,
// with an error pointing at THIS call site (Problem 4's instantiation), not at
// the Clamp function body itself — exactly the pitfall from the concept file.

// ---------------------------------------------------------------
// Problem 5
// ---------------------------------------------------------------
template<typename T>
class Pair
{
public:
    T FirstValue;
    T SecondValue;

    void PrintPair()
    {
        cout << "(" << FirstValue << ", " << SecondValue << ")\n";
    }
};

int main()
{
    cout << "Max(3, 7): " << Max(3, 7) << "\n";           // 7
    cout << "Max(2.5f, 1.1f): " << Max(2.5f, 1.1f) << "\n"; // 2.5
    cout << "Min(3, 7): " << Min(3, 7) << "\n";             // 3

    int X = 5, Y = 10;
    cout << "Before swap: X=" << X << " Y=" << Y << "\n";
    Swap(X, Y);
    cout << "After swap: X=" << X << " Y=" << Y << "\n"; // X=10 Y=5

    cout << "Clamp(15, 0, 10): " << Clamp(15, 0, 10) << "\n"; // 10, works fine for int

    // Uncommenting the block below proves the Problem 4 prediction:
    // struct NoCompare { int Value; };
    // NoCompare A{1}, B{0}, C{5};
    // Clamp(A, B, C); // COMPILE ERROR: no operator< for NoCompare

    Pair<int> IntPair;
    IntPair.FirstValue = 1;
    IntPair.SecondValue = 2;
    IntPair.PrintPair(); // (1, 2)

    Pair<string> StringPair;
    StringPair.FirstValue = "hello";
    StringPair.SecondValue = "world";
    StringPair.PrintPair(); // (hello, world)
    // Same Pair<T> template, two totally different concrete types instantiated —
    // this is exactly what TArray<int32> vs TArray<AActor*> does in UE5.

    return 0;
}
