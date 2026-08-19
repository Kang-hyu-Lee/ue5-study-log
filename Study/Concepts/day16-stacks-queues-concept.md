# Day 16 — Stacks & Queues (DSA)

## 1. Stack — LIFO (Last In, First Out)

A stack only lets you touch ONE end — the "top."

Operations:
- `Push(x)` — add x to the top
- `Pop()` — remove and return the top item
- `Peek()` / `Top()` — look at top item without removing it
- `IsEmpty()` — check if there's anything to pop

Mental model: a stack of plates. You can only add/remove from the top. You cannot pull a plate from the middle without moving everything above it first.

### Worked trace (array-based stack, capacity 5)

State shown as `[values...]`, `top` = index of the top element (`-1` = empty).

```
Start:            []          top = -1
Push(10):         [10]        top = 0
Push(20):         [10,20]     top = 1
Push(30):         [10,20,30]  top = 2
Pop() -> returns 30, [10,20]  top = 1
Push(40):         [10,20,40]  top = 2
Pop() -> returns 40, [10,20]  top = 1
Pop() -> returns 20, [10]     top = 0
```

Every Push/Pop is O(1) — you only ever touch index `top`, never shift anything.

### Array-based pitfall: stack overflow (the real, literal one)

If `top` reaches `capacity - 1` and you `Push` again, you've overflowed the array — this is where the term "stack overflow" comes from *literally*. The function call stack (every function call you make) is a real stack in memory, with a fixed size (~1-8MB depending on OS/thread). Recursion without a base case exhausts it — you'll see this directly on Day 18 (recursion).

---

## 2. Queue — FIFO (First In, First Out)

A queue lets you add at the BACK and remove from the FRONT.

Operations:
- `Enqueue(x)` — add x to the back
- `Dequeue()` — remove and return the item at the front
- `Front()` — look at the front item without removing it
- `IsEmpty()`

Mental model: a checkout line. New people join the back. The person at the front leaves first.

### Worked trace (linked-list-based queue)

Uses two pointers: `Head` (front, where you dequeue) and `Tail` (back, where you enqueue). This is the SAME `Next`-pointer struct pattern you already used in `todo-list.cpp` — a queue is just a linked list where you insert at one end and remove from the other.

```
Start:                    Head = nullptr, Tail = nullptr

Enqueue(10):
  new Node{10, nullptr}
  Head = Tail = [10|null]

Enqueue(20):
  new Node{20, nullptr}
  Tail->Next = [20|null]   // old tail's Next now points to new node
  Tail = [20|null]         // Tail pointer moves to the new node
  List: [10|*]->[20|null]  Head=[10], Tail=[20]

Enqueue(30):
  List: [10|*]->[20|*]->[30|null]  Head=[10], Tail=[30]

Dequeue() -> returns 10
  Head = Head->Next = [20|*]   // move Head forward
  delete old [10] node          // MUST delete — see stack/heap concept file
  List: [20|*]->[30|null]  Head=[20], Tail=[30]
```

### Why the queue needs a `Tail` pointer

Without a `Tail` pointer, `Enqueue` would have to walk the entire list from `Head` every time to find the last node — that's O(n) per enqueue. Keeping a `Tail` pointer that always points at the last node makes `Enqueue` O(1): you just do `Tail->Next = newNode; Tail = newNode;`.

### Array-based queue pitfall (why naive array queues are bad)

If you implement a queue with a plain array and dequeue by removing index 0, every remaining element has to shift left by one to close the gap — O(n) per dequeue. Real array-based queues use a "circular buffer" (wrap the front/back indices around the array) to stay O(1) — not required for you to implement this week, just know the naive version is a trap in an interview.

---

## 3. Gamedev / production relevance

- **Stack**: Undo/redo systems (push each action, pop to undo — sound familiar? Day 20's portfolio project *is* this). Also: the call stack itself, and parsing nested structures (e.g. matching brackets).
- **Queue**: Input buffering (player mashes 3 abilities, they execute in the order pressed), BFS pathfinding/AI (visit nodes in the order discovered), event/task queues, animation queues, network message processing in order received.

## 4. Big-O summary

| Operation | Array-based | Linked-list-based |
|---|---|---|
| Stack Push/Pop | O(1) | O(1) (push/pop at head) |
| Queue Enqueue/Dequeue (naive array) | O(n) dequeue | — |
| Queue Enqueue/Dequeue (with Tail ptr) | — | O(1) |

## 5. Pitfall checklist

- **Underflow**: calling `Pop()`/`Dequeue()` on an empty structure — always check `IsEmpty()` first, or return a clear error/sentinel.
- **Forgetting `Tail`** in a linked-list queue — silently degrades Enqueue to O(n).
- **Forgetting to `delete`** the node you just removed in `Dequeue`/`Pop` if it was heap-allocated — leak. Full explanation in the stack-vs-heap concept file.
