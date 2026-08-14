# Pointers Pt.2 — Arithmetic, Null & Dangling Deep-Dive

## 1. Pointer Arithmetic

### Mechanism
A pointer holds an address. When you do math on a pointer, C++ doesn't move by
1 byte — it moves by `sizeof(type)` bytes, so the pointer always lands on the
start of the *next* element of that type.

```cpp
int Scores[3] = {10, 20, 30};
int* Ptr = Scores;        // array name decays to a pointer to element 0
std::cout << *Ptr;        // 10
Ptr = Ptr + 1;             // moves 4 bytes (sizeof(int)), NOT 1 byte
std::cout << *Ptr;        // 20
```

Worked example, byte-level:
- `Scores` lives at address `1000` (made up, for illustration).
- `Scores[0]` = address 1000, `Scores[1]` = address 1004, `Scores[2]` = address 1008 (each `int` = 4 bytes on most systems).
- `Ptr + 1` computes `1000 + (1 * sizeof(int))` = `1004` → lands exactly on `Scores[1]`.
- If `Ptr` were a `double*` (8 bytes), `Ptr + 1` would add 8, not 4. The `+1` always means "next element of this type," never "next byte."

`Ptr++` and `Ptr--` work the same way — increment/decrement by one element's width. `*(Ptr + i)` is exactly equivalent to `Ptr[i]` — this is *why* array indexing works at all: `Scores[i]` is syntactic sugar for `*(Scores + i)`.

### Pitfall
Pointer arithmetic is only defined behavior **within a single array, plus one element past the end** (used for end-iterators/loop bounds). Two common mistakes:
- Doing arithmetic on a pointer to a single (non-array) variable: `int X = 5; int* P = &X; P + 1;` — this computes *some* address, but it doesn't point at anything meaningful. Dereferencing it is undefined behavior (UB).
- Walking a pointer past `array + size` and dereferencing it. `array + size` itself (one-past-the-end) is legal to *hold and compare*, but dereferencing it reads memory you don't own.

### Why it matters
This is the actual mechanism behind array indexing, `std::vector` iterators, and — later — linked list traversal (`CurrentNode = CurrentNode->Next` is pointer reassignment, same family of operation). Interviewers ask "what does `arr[i]` really mean" specifically to check you understand `*(arr + i)`, not just that you can use `[]`.

### Edge case
`Ptr + 1` landing one element past the last valid element is legal to *compute and compare* (`if (Ptr == EndPtr)`) but illegal to *dereference*. This exact pattern is how `for` loops with pointers safely detect "done" without ever reading out-of-bounds memory — the comparison is safe, the read is not.

---

## 2. Null Pointer

### Mechanism
`nullptr` is a pointer value guaranteed to point at *no valid address*. It's the explicit "this pointer currently points at nothing" state — you set it deliberately, and you check for it before trusting the pointer.

```cpp
int* Ptr = nullptr;
if (Ptr == nullptr) {
    std::cout << "Nothing to read here.\n";
}
```

### Pitfall
Dereferencing a null pointer (`*Ptr` when `Ptr == nullptr`) is one of the most common crash sources in real code — it's a guaranteed crash (segfault) on virtually every platform, not silently-wrong behavior. The pitfall isn't the crash itself — it's *forgetting the check* before a dereference, especially after a function that might legitimately return "nothing" (e.g. "find this item, return its pointer, or nullptr if not found").

### Why it matters
Every UE5 raw pointer to a `UObject`/`AActor` can legitimately be null (object not yet spawned, already destroyed, optional reference never set). `IsValid(Ptr)` / null checks before use are mandatory production habit, not a beginner-only concern.

### Edge case
`nullptr == 0` is true in comparisons, but they are not the same *type* — `nullptr` is a distinct pointer-literal type (`std::nullptr_t`) precisely so it can't accidentally be confused with the integer `0` in overload resolution. (You don't need to use overloads yet — just know `nullptr` is the correct modern C++ null, not `NULL` or `0`, which are older/weaker conventions.)

---

## 3. Dangling Pointer (deep-dive)

### Mechanism
A dangling pointer is a pointer that **used to be valid** but now points at memory that's no longer yours — the variable it pointed to went out of scope, or the memory was freed. The pointer's bit pattern doesn't change on its own; it still "points" at that old address, but nothing valid is guaranteed to live there anymore.

```cpp
int* MakeDangling() {
    int Local = 42;
    return &Local;   // Local's storage is destroyed when this function returns
}
// caller now holds a pointer to memory that no longer belongs to Local
```

### Pitfall — Wild vs Dangling (interview-common distinction)
These are frequently confused, and interviewers ask this directly:
- **Wild pointer** (covered Day 10): never initialized at all — points at garbage from the start, was never valid.
- **Dangling pointer**: *was* valid, then became invalid because the thing it pointed to was destroyed/freed while the pointer itself kept the old address.

Both are equally dangerous to dereference — the danger isn't "was it ever valid," it's "is it valid *right now*."

### Why it matters
This is the exact bug class smart pointers (`unique_ptr`, and UE5's `TWeakObjectPtr`) exist to prevent — you'll meet the formal fix conceptually on Day 23. In UE5 specifically: holding a raw `AActor*` to an actor that gets destroyed mid-game (player killed an enemy, level streamed out) and then using it next tick without a validity check is a dangling-pointer crash — one of the most common UE5 crash reports in real projects.

### Edge case
Setting a pointer to `nullptr` immediately after the thing it points to is destroyed removes the danger — a null pointer is safe to *check*, a dangling one is not (it looks just as "valid" as a real pointer until you dereference it and it explodes, sometimes not even every time — UB can appear to "work" until it doesn't). This is why some codebases enforce "always null a pointer after delete/scope-exit" as a defensive habit.
