# C++ Strings & Basic Input/Output

## What `std::string` Is
A built-in type (from the `<string>` library) for text that **resizes itself automatically** — unlike the fixed-size arrays you just learned (Day 8), where you had to know the size upfront and couldn't grow it. `std::string` handles that memory management for you.

Declaration:
```cpp
std::string name = "Aria";
```
or declare empty and assign later:
```cpp
std::string name;
name = "Aria";
```

## Core Operations
- **Concatenation** — `+` joins strings: `std::string greeting = "Hello, " + name;`
- **Length** — `.length()` or `.size()` (identical, both return character count): `name.length()`
- **Indexing** — same square-bracket syntax as arrays, same zero-indexing: `name[0]` is the first character. Same off-by-one risk as Day 8 arrays applies here too.
- **Comparison** — `==`, `!=`, `<`, `>` compare **lexicographically** (dictionary order, character by character). `"apple" < "banana"` is `true` because `'a'` comes before `'b'` alphabetically/in ASCII value.
- **Substrings** — `.substr(start, length)` extracts a piece: `name.substr(0, 3)` gives the first 3 characters.
- **Searching** — `.find("sub")` returns the index where `"sub"` starts, or a special value `std::string::npos` if not found.

## Basic I/O
- `std::cin >> variable;` reads input **only up to the first whitespace**. Typing `Aria Lin` into a `std::string` read with `cin >>` captures only `"Aria"` — `"Lin"` stays sitting in the input buffer, unread.
- `std::getline(std::cin, variable);` reads the **entire line**, including spaces, up to the newline.
- **The classic gotcha:** if you use `cin >>` and then immediately call `getline()`, the leftover `'\n'` character from the *first* input is still in the buffer. `getline()` sees that `'\n'` immediately, thinks "end of line reached," and returns an **empty string** — even though you typed something. Fix: call `std::cin.ignore();` right after a `cin >>` and before a `getline()`, to discard that leftover newline.

## Worked Example — Line by Line
```cpp
#include <iostream>
#include <string>

int main() {
    std::string playerName;
    std::cout << "Enter your character's first name: ";
    std::cin >> playerName;              // reads up to the first space only

    std::cin.ignore();                   // discards the leftover '\n' still sitting in the buffer

    std::string playerTitle;
    std::cout << "Enter a title (can include spaces): ";
    std::getline(std::cin, playerTitle); // now reads the whole line correctly, spaces included

    std::string fullIntro = playerName + " the " + playerTitle;
    std::cout << fullIntro << '\n';

    return 0;
}
```
- `std::string playerName;` — declares an empty, resizable text variable.
- `std::cin >> playerName;` — reads one whitespace-delimited token into it (e.g. just `"Aria"` even if more was typed).
- `std::cin.ignore();` — without this, the next line would silently fail (see gotcha above).
- `std::getline(std::cin, playerTitle);` — reads everything typed until Enter, spaces and all, into `playerTitle`.
- `playerName + " the " + playerTitle` — concatenation builds one combined string.
- `'\n'` used over `std::endl` per your established convention (no forced flush needed here).

## Pitfall
`.find()` returns an **unsigned** type, so comparing its result to `-1` to check "not found" silently breaks — `-1` gets converted to a huge positive number when compared against an unsigned return type, so the comparison never behaves as expected. Always compare against `std::string::npos` explicitly:
```cpp
if (name.find("Ari") == std::string::npos) { /* not found */ }
```

## Why It Matters
UE5 uses its own text type, `FString`, not `std::string` — but the mental model transfers directly: dynamic resizing, concatenation, searching, substrings all work the same way conceptually, just with `FString`'s own method names. Basic I/O is also the backbone of any console-driven tool, including the string-parsing your Day 13 to-do-list portfolio piece will need (reading a task description as free text).

## Edge Case
`==` on strings is an **exact** match, including case: `"Yes" == "yes"` is `false`. This trips people up constantly in input validation — if you're checking user input like a yes/no answer, you either need to explicitly handle both cases or normalize the casing first (case-normalization itself isn't covered yet, flag with `?` if you want it now).
