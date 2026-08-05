# Day 1 — What a C++ Program Is, Compiling, Variables & Data Types

## 1. What is a program?
A program is a list of instructions a computer executes in order, top to bottom (mostly). You write those instructions as **source code** — plain text, in a `.cpp` file — using a programming language's rules (its *syntax*).

The computer's processor doesn't understand English-like code such as `int age = 20;`. It only understands **machine code**: raw binary instructions specific to the CPU. So your source code has to be translated.

## 2. What is compiling?
**Compiling** = translating your `.cpp` source code into machine code, producing an **executable** file (on Windows, a `.exe`) that the OS can run directly.

The tool that does this is called a **compiler**. Pipeline:
```
your_file.cpp  →  [compiler]  →  your_program.exe
 (source code)                    (machine code, runnable)
```
If your code breaks the language's grammar rules, the compiler refuses and gives you a **compiler error**, with a line number, instead of producing an exe. This is normal and constant — reading compiler errors is a core skill, not a sign of failure.

VS Code itself does NOT compile — it's a text editor. It's usually paired with a compiler (like MinGW on Windows, or Visual Studio's compiler once you're in UE5-land) that runs in the background or via terminal command.

## 3. Anatomy of the smallest real C++ program
```cpp
#include <iostream>
using namespace std;

int main() {
    return 0;
}
```
Line by line, in plain language:

- `#include <iostream>` — a **preprocessor directive** (note: no semicolon at the end — directives are not statements). It tells the compiler "pull in the code for input/output tools (like printing to the screen) before compiling." `iostream` = "input/output stream." Without this line, you can't use `cout` (see below).
- `using namespace std;` — `std` is short for "standard" — it's the name of a big bucket of built-in tools the C++ Standard Library provides (including `cout`). Normally you'd have to write `std::cout` every time (`::` means "look inside this bucket for the following name"). This line says "let me just write `cout` instead of `std::cout` for the rest of this file" — a convenience. Ends with `;` because it IS a statement.
- `int main() { ... }` — every C++ program must have exactly one function called `main`. This is the **entry point** — the first code that runs when your program starts. `int` before `main` means this function will hand back a whole number when it finishes (see `return 0;` below). The `()` after `main` is where a function's inputs would go — empty here, meaning main takes no inputs. The `{ }` curly braces mark the **start and end of the function's body** — everything the function does lives between them.
- `return 0;` — ends the `main` function and hands back the value `0` to the operating system. By convention, `0` means "program finished successfully"; any other number signals an error occurred. Ends with `;` because every statement in C++ ends with a semicolon — it's how the compiler knows where one instruction stops and the next begins.

## 4. Variables & Data Types (in code)
A **variable** in code is a named, labeled spot in the computer's memory that holds a value — same idea as math's "x", but now it physically exists in RAM while your program runs, with a type attached.

**Declaring a variable** (creating it) follows this pattern:
```
type name = value;
```
- `type` — what KIND of data this variable can hold (see table below). C++ requires you to state this up front and it can't change later — this is called being **statically typed**.
- `name` — the label you choose (must start with a letter or underscore, no spaces, case-sensitive).
- `= value` — optional at declaration time, but almost always given: the starting value.
- `;` — every statement ends with a semicolon.

### Core built-in types (Day 1 set)
| Type | Holds | Example |
|---|---|---|
| `int` | whole numbers (no decimal) | `int age = 20;` |
| `double` | decimal numbers (higher precision — default choice for decimals) | `double price = 9.99;` |
| `float` | decimal numbers (less precision, less memory — you'll see why it matters in UE5 later) | `float speed = 5.5f;` (the `f` suffix tells the compiler "this literal is a float, not a double") |
| `char` | a single character | `char grade = 'A';` (single quotes for one char) |
| `bool` | true or false only | `bool isAlive = true;` |

Note: plain text ("strings") like `"Hello"` needs `#include <string>` and the `string` type — not covered today, only mentioned so you recognize it later.

**Common pitfall — uninitialized variables.** `int score;` (no `= value`) is legal C++ — it declares the variable but does NOT set it to 0 or anything predictable. It holds whatever garbage bits happened to be sitting in that memory address before. Reading it before assigning gives an unpredictable value, and the compiler often won't warn you. Rule: always initialize a variable at declaration unless you have a specific reason not to.

**Pitfall — silent narrowing.** `float gravity = 9.8;` (no `f` suffix) still compiles: `9.8` is a `double` literal by default, and C++ silently narrows it down to `float` precision to fit the variable. It works, but relying on this is bad practice — always write float literals with the `f` suffix so your intent is explicit rather than accidental.

**Edge case — integer overflow.** Every type has a fixed size in memory, so a fixed maximum value it can hold (`int` typically maxes around 2.1 billion). What happens past that limit depends on whether the type is signed or unsigned — this distinction is a common interview follow-up, so don't collapse it into one simplified answer:

- **`unsigned int`** — overflow is well-defined by the language: it **wraps around** predictably via modular arithmetic. `UINT_MAX + 1` reliably becomes `0`.
- **`int` (signed, what you'll use almost always)** — overflow is **undefined behavior (UB)**. The C++ standard does not guarantee what happens. In practice, on virtually all real hardware, it *does* wrap to a large negative number (a side effect of two's complement representation) — but the standard doesn't promise this, and compilers are legally allowed to optimize code on the assumption that signed overflow never happens. That can produce results more surprising than a simple wraparound.

No crash, no warning either way — just a wrong number that looks plausible. Real production bug source (e.g. a score/currency counter that "goes negative" with no visible cause). Interview-safe answer: state the unsigned/signed distinction, not just "it goes negative."

## 5. Worked example — full program, explained line by line

```cpp
#include <iostream>          // gives us cout (printing) tools
using namespace std;         // lets us write cout instead of std::cout

int main() {                 // program execution starts here
    int age = 20;            // declare an int variable named age, store 20
    double price = 9.99;     // declare a double variable named price, store 9.99
    bool isStudent = true;   // declare a bool variable, store true

    cout << "Age: " << age << endl;
    cout << "Price: " << price << endl;
    cout << "Is student: " << isStudent << endl;

    return 0;                // exit main, tell OS "success"
}
```

New syntax in the print lines, explained:
- `cout` — "character output" — the tool (from `iostream`) that prints to the console/screen.
- `<<` — the **insertion operator** here. Think of it as "send this into the output stream." You can chain multiple `<<` on one line — each one sends the next piece to be printed, in order, with nothing added between them automatically.
- `"Age: "` — a **string literal** (fixed piece of text), always in double quotes.
- `endl` — "end line" — moves the cursor to a new line after printing (similar to pressing Enter).

Expected output when run:
```
Age: 20
Price: 9.99
Is student: 1
```
Note `isStudent` prints as `1`, not `true` — by default `cout` prints `bool` values as `1`/`0`. This is a known quirk, not a bug.

## 6. Terms introduced here (reference)
- **Source code**: the human-written `.cpp` text file.
- **Compiler**: translates source code → machine code.
- **Executable**: the runnable output of compiling.
- **Entry point**: `main()` — where execution starts.
- **Statement**: one instruction, ends with `;`.
- **Declaration**: creating a variable (`type name = value;`).
- **Statically typed**: a variable's type is fixed at declaration and can't change.
- **String literal**: fixed text in double quotes.
