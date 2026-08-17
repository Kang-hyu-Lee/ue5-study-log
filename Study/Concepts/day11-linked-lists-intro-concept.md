# Linked Lists — Intro

## 0. Preview: minimal `struct` (full lesson is Day 15)
A linked list node needs to hold two things together: a value, and a pointer
to the next node. C++ bundles fields like this with `struct`:

```cpp
struct Node {
    int Data;
    Node* Next;
};
```

That's the entire preview — a `struct` is just a way to group related
variables under one name, accessed with `.` (e.g. `SomeNode.Data`). Day 15
covers `struct` vs `class` properly (access control, member functions,
constructors). For now you only need enough to build a `Node`.

## 1. What a Linked List Is

### Mechanism
A linked list is a chain of nodes. Each node owns its data *and* a pointer to
the next node. There's no single block of contiguous memory — nodes can live
anywhere; what connects them is purely the `Next` pointers.

Worked example — building a 3-node list by hand:
```cpp
Node A{10, nullptr};
Node B{20, nullptr};
Node C{30, nullptr};

A.Next = &B;   // A now points to B
B.Next = &C;   // B now points to C
// C.Next stays nullptr — C is the last node ("tail")

Node* Head = &A;   // Head is how you find the start of the list
```
Reading the list: start at `Head`, print `Head->Data`, move to `Head->Next`,
repeat until the pointer is `nullptr`. (`Head->Data` is shorthand for
`(*Head).Data` — arrow syntax exists because dereference-then-dot is so
common with pointers-to-structs that C++ gives it a dedicated operator.)

### Contrast with arrays (why this data structure exists)
| | Array | Linked List |
|---|---|---|
| Memory layout | one contiguous block | scattered, connected by pointers |
| Access by index | O(1) — jump straight to `Ptr + i` | O(n) — must walk node by node from head |
| Insert/delete at front | O(n) — must shift every element over | O(1) — just relink a few pointers |
| Fixed size upfront? | yes, for raw arrays (Day 4/8) | no — grows one node at a time |

### Pitfall
Losing your only reference to the rest of the list. If you do
`Head = Head->Next` without first saving the old `Head` somewhere, and the old
first node was the only thing pointing to it, that memory becomes
unreachable — this is a memory leak (relevant once you meet `new`/`delete`
on Day 16, since list nodes are typically heap-allocated in real code, not
stack variables like in the example above).

### Why it matters
This is one of the most common interview data structures precisely because
it forces you to reason about pointers under pressure — reversing a list,
detecting a cycle, finding the middle node are all classic timed questions
(Day 12 is dedicated insert/delete timed practice). In UE5, `TDoubleLinkedList`
exists in the engine, and the *conceptual* pattern — nodes connected by
pointers rather than indexed by position — shows up in scene graphs, event
delegate chains, and any "process one thing, then the next" system.

### Edge case
The empty list: `Head == nullptr`. Every traversal loop must check for
`nullptr` *before* dereferencing — walking off the end of the list without
that check dereferences a null pointer (Section 2 of `pointer-arithmetic.md`)
and crashes. The empty-list case is also the one beginners most often forget
to test, and it's usually the first case an interviewer will probe
("what does your function do if I pass it an empty list?").
