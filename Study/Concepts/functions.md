# C++ Functions — Declaration, Parameters, Return Values

## Core Mechanism
A function is a named, reusable block of code. Anatomy:
```cpp
returnType FunctionName(paramType paramName, ...) {
    // body
    return value; // only required if returnType isn't void
}
```
- **Declaration/definition**: The compiler reads top-to-bottom and must know a function exists before it's called. If you call a function from `main()` before its full definition appears later in the file, you need a **forward declaration** above `main()` (the signature only, ending in `;`) — or just define the whole function above `main()`.
- **Parameters**: the inputs, listed in the parentheses. By default, C++ passes parameters **by value** — the function receives a *copy*, not the original.
- **Return value**: `return` sends a value back to the caller and immediately exits the function. `void` return type means the function returns nothing.

### Worked Example — reusing today's math block
```cpp
#include <cmath>   // gives us std::sqrt

double VectorMagnitude(double x, double y) {
    double result = std::sqrt(x * x + y * y);
    return result;
}

int main() {
    double mag = VectorMagnitude(3.0, 4.0);
    // mag is now 5.0
    return 0;
}
```
Line by line:
- `#include <cmath>` — pulls in the math library so `std::sqrt` exists. Without it, the compiler doesn't recognize `sqrt`.
- `double VectorMagnitude(double x, double y)` — declares a function named `VectorMagnitude`, returning a `double`, taking two `double` parameters `x` and `y`. These parameter names are local to the function — the caller's variable names don't need to match.
- `double result = std::sqrt(x * x + y * y);` — computes the magnitude formula from the math block, stores it locally.
- `return result;` — sends the value back to whoever called the function, then exits.
- `double mag = VectorMagnitude(3.0, 4.0);` — the call. `3.0` is *copied* into `x`, `4.0` is *copied* into `y`. `mag` receives whatever the function returns.

## Pitfall
Pass-by-value means a function cannot modify the caller's original variable — it's only working on a copy.
```cpp
void TryToDouble(int n) {
    n = n * 2; // only changes the local copy of n
}

int main() {
    int x = 5;
    TryToDouble(x);
    // x is STILL 5 here — TryToDouble never touched the real x
}
```
This trips up almost everyone the first time. Actually fixing this requires **references or pointers** (Day 11-12 on your roadmap) — flagging now so it isn't a shock later.

## Production Relevance
Every UE5 function you'll write — `TakeDamage()`, `CalculateMovement()`, `Fire()` — follows this exact pattern: inputs in, logic, value or effect out. Decomposing gameplay logic into small, named, testable functions is the difference between readable UE5 code and unmaintainable spaghetti.

## Edge Case
A non-`void` function that doesn't `return` on every possible code path:
```cpp
int Classify(int n) {
    if (n > 0) {
        return 1;
    }
    // what if n <= 0? No return here!
}
```
This often compiles with only a warning, not an error — but it's **undefined behavior** if the missing branch executes; the function returns garbage. Always make sure every path returns something, or add a final catch-all `return`.
