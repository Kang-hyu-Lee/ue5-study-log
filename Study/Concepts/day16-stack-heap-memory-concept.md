# Day 16 — Stack vs Heap Memory (C++)

Two different regions of memory your program uses. Confusingly, "the stack" here is a hardware/OS memory region — same *name* as yesterday's data structure, different thing. Context tells you which is meant.

## 1. Stack memory (automatic)

Every time you call a function, C++ carves out a small block for its local variables — a "stack frame." When the function returns, that block is automatically destroyed. No code needed from you.

```cpp
void Foo()
{
    int x = 5;       // x lives on the stack, inside Foo's stack frame
    // ... Foo does stuff ...
}                     // Foo returns -> x is destroyed automatically, memory reclaimed
```

- Fast (just moves a pointer up/down).
- Small total size (~1-8MB depending on OS/thread) — this is the same stack that overflows with runaway recursion (Day 18).
- Lifetime = tied exactly to scope (`{ }` block). You never manually free it.

## 2. Heap memory (manual)

A much larger pool of memory that YOU control explicitly with `new` and `delete`. It does NOT get cleaned up when a function returns.

```cpp
int* ptr = new int(5);   // allocates space for one int on the heap, sets it to 5
                          // ptr (on the stack) holds the ADDRESS of that heap memory
// ... use *ptr ...
delete ptr;               // frees the heap memory. Required — nothing does this for you.
```

- `new Type(args)` — allocates space for one object on the heap, calls its constructor, returns a pointer to it.
- `new Type[n]` — allocates an array of n objects on the heap, returns a pointer to the first one.
- `delete ptr;` — frees a single heap object.
- `delete[] ptr;` — frees a heap array. Using plain `delete` on an array (or vice versa) is undefined behavior — the sizes/bookkeeping don't match.
- Slower than stack (the allocator has to find free space, track it).
- Lifetime = however long YOU want, until you call `delete`. This is exactly why linked list nodes (`TodoNode`) are heap-allocated — a node created inside `AddTask` must outlive `AddTask` returning, which stack memory cannot do.

## 3. Worked example — why linked lists NEED the heap

```cpp
TodoNode* MakeNode(std::string task)
{
    TodoNode temp;              // if this were used instead of `new`...
    temp.Task = task;
    return &temp;                // returning address of a STACK variable
}                                 // temp is destroyed HERE, when MakeNode returns
// The returned pointer now points at destroyed memory -> dangling pointer, undefined behavior
```

vs. the correct version (what you actually wrote in `todo-list.cpp`):

```cpp
TodoNode* MakeNode(std::string task)
{
    TodoNode* NewNode = new TodoNode();   // heap-allocated -> survives past this function
    NewNode->Task = task;
    return NewNode;                        // pointer is valid, memory still exists
}
```

This is the concrete reason `AddTask` uses `new TodoNode()` and not a plain local `TodoNode`.

## 4. Pitfall checklist (all three are classic interview questions)

**Memory leak** — allocate with `new`, never `delete`. Memory stays reserved for the entire program's life even though nothing uses it anymore.
```cpp
void Leak()
{
    Counter* c = new Counter();   // heap allocated
}                                  // c (the pointer variable) is destroyed — but the
                                   // Counter object it pointed to is NOT freed. LEAK.
```
This is exactly the Day 15 `Counter` bug — flagged then, fixed now: add `delete c;` before the function ends, or restructure so ownership/deletion is clear.

**Dangling pointer** — using a pointer AFTER its memory has been freed.
```cpp
int* p = new int(5);
delete p;         // memory freed
*p = 10;           // UNDEFINED BEHAVIOR — p still holds the old address, but that memory
                    // may now be reused for something else entirely
```
Fix convention: set `p = nullptr;` immediately after `delete p;`, so any accidental reuse crashes predictably (dereferencing `nullptr`) instead of silently corrupting unrelated memory.

**Double delete** — calling `delete` twice on the same pointer. Undefined behavior, frequently crashes. Common cause: two different pointers/paths in your code both think they "own" the same heap object and both try to clean it up.

## 5. UE5 relevance — this is NOT how UObjects work

Raw `new`/`delete` is what you use for plain C++ types (structs, your own classes, `TodoNode`-style data) — these are exactly what you've been building. But `UObject`-derived classes in UE5 use a **Garbage Collector (GC)** instead — you don't call `delete` on a `UObject`; Epic's GC tracks references and frees them automatically. Mixing the two mental models is a real, common beginner bug in UE5: calling `delete` on a UObject, or expecting GC to clean up a raw `new` — neither works. Full UObject/GC treatment comes later, once you're inside UE5 (Phase 2+); for now, the rule is simple: everything you're writing right now is plain C++, so `new` always needs a matching `delete`, no exceptions.

## 6. Direct callback to your portfolio code

Check `Study/Portfolio/todo-list.cpp`: every `AddTask` call does `new TodoNode()`. Ask yourself right now, before today's exercises — **does anything in your file ever call `delete` on a `TodoNode`?** If not, your to-do list leaks a node every time a task is deleted or the program ends. We'll fix this concretely when `DeleteCompleted` gets finished.
