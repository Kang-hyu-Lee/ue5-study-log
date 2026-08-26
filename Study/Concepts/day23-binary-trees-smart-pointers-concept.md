# Day 23 — Binary Trees Intro & Pointer/Reference Review + unique_ptr

---

## PART 1 (DSA): Binary Trees — Intro

### Core mechanism
Everything you've built so far (arrays, linked lists, stacks, queues) is **linear** — one element leads to exactly one next element. A **tree** is **nonlinear**: one node can branch to *multiple* children. A **binary tree** specifically caps that at 2 children per node: `Left` and `Right`.

Terminology (memorize these — interviewers use them without defining them):
- **Node** — a single element (same idea as a linked list node, but 2 next-pointers instead of 1)
- **Root** — the top node, the only node with no parent
- **Parent / Child** — direct relationship between connected nodes
- **Leaf** — a node with no children (both pointers null)
- **Edge** — the connection between a parent and child
- **Depth** (of a node) — how many edges from the root to that node
- **Height** (of a tree) — the depth of its deepest leaf

### Worked example
Picture this shape (values arbitrary, no ordering rule yet — that's tomorrow's BST topic):

```
        10
       /  \
      5    15
     / \     \
    2   7    20
```

- `10` is the root, depth 0.
- `5` and `15` are children of `10`, depth 1.
- `2`, `7`, `20` are leaves, depth 2. Height of tree = 2.

In code, a tree node is a **self-referential struct** — same trick as a linked list node, just two pointers instead of one:

```cpp
struct TreeNode
{
    int Value;
    TreeNode* Left;
    TreeNode* Right;

    // constructor: new node always starts as a leaf (both children null)
    TreeNode(int InValue) : Value(InValue), Left(nullptr), Right(nullptr) {}
};
```

Building the tiny tree above by hand, one `new` at a time:

```cpp
TreeNode* Root = new TreeNode(10);
Root->Left = new TreeNode(5);
Root->Right = new TreeNode(15);
Root->Left->Left = new TreeNode(2);
Root->Left->Right = new TreeNode(7);
Root->Right->Right = new TreeNode(20);
```

Walk this line by line: `Root->Left` doesn't dereference-then-arrow twice, it's `(Root->Left)->Left` — each `->` moves you one node deeper. This is identical in spirit to `Head->Next->Next` from linked lists, just now you're choosing a direction (`Left` or `Right`) at each step instead of always going `Next`.

### Common pitfall at this level
Forgetting that **an empty tree is `nullptr`, not an "empty struct."** There's no such thing as a `TreeNode` with no data — a tree with zero nodes is represented purely by a null root pointer. Every tree function you write must handle `if (Node == nullptr)` as the first check, exactly like you did with linked lists.

### Why it matters in production / interviews
- UE5's **Widget hierarchy**, **Behavior Trees** (AI), and **Scene Component hierarchy** (`RootComponent` → attached children) are all trees under the hood.
- "Traverse a tree" (pre-order / in-order / post-order) is one of the most common whiteboard questions — we're not doing traversal yet (that's Day 25, BST + traversal), today is purely structure.

### Edge case where the naive understanding breaks
A binary tree has **no rule enforcing balance or ordering**. Nothing stops you from building this "tree," which is really just a linked list wearing a tree's clothes:

```
10
  \
   15
     \
      20
        \
         25
```

Every node only uses `Right`. Search through this is O(n), not the O(log n) you might assume "because it's a tree." Balance/ordering is what BSTs add tomorrow — a plain binary tree alone guarantees nothing about search speed.

---

## PART 2 (C++): Pointer & Reference Review

Quick recap table before `unique_ptr` — you covered this Day 10–14, this is reinforcement, not new material:

| | Pointer (`T*`) | Reference (`T&`) |
|---|---|---|
| Holds | a memory address | an alias to an existing variable |
| Can be null? | yes (`nullptr`) | no — must bind to something real at creation |
| Can be reseated (point elsewhere later)? | yes | no — bound for life |
| Needs dereferencing (`*p`) to access value? | yes | no — used exactly like the original variable |
| Declared without initializing? | legal (dangerous — dangling) | illegal — must initialize immediately |

Pitfall reminder: a pointer that's declared but never assigned (`TreeNode* P;`) doesn't point at "nothing" — it points at **garbage**, whatever address happened to be in that memory slot. Calling `P->Value` on that is undefined behavior, not a clean crash you can rely on. Always initialize pointers to `nullptr` if you don't have a real address yet.

---

## PART 3 (C++): Smart Pointer Concept — `unique_ptr`

### The problem raw pointers create
Every `new` you've written needs exactly one matching `delete`, and *you* are responsible for remembering it — the compiler won't warn you. Two failure modes:
- **Forget the `delete`** → memory leak (you've hit this already in past days).
- **`delete` twice, or delete + still use the pointer** → double-free / dangling access, undefined behavior (you also hit this in Day 20's `LogQueue`).

### Core mechanism: RAII
**RAII = Resource Acquisition Is Initialization.** The idea: tie a resource's lifetime to an object's scope, so the resource is automatically cleaned up when that object goes out of scope — no manual `delete` call needed, ever. `unique_ptr` is C++'s standard-library implementation of RAII for heap memory.

```cpp
#include <memory>

void MakeNode()
{
    std::unique_ptr<TreeNode> NodePtr = std::make_unique<TreeNode>(10);
    // use NodePtr like a normal pointer: NodePtr->Value, NodePtr->Left, etc.

}   // function ends here — NodePtr goes out of scope
    // its destructor runs automatically, which calls delete on the TreeNode
    // you never wrote "delete" anywhere. That's the entire point.
```

Line by line:
- `std::unique_ptr<TreeNode>` — the type: "a unique_ptr that owns a TreeNode."
- `std::make_unique<TreeNode>(10)` — allocates a `TreeNode` on the heap (like `new TreeNode(10)` internally) and hands ownership to the unique_ptr. **Always prefer `make_unique` over `new` + wrapping manually** — it's exception-safer and is the standard idiom.
- No `delete` anywhere. The destructor of `unique_ptr` (which runs automatically at end of scope, same mechanism as any other local variable) does it for you.

### The defining rule: exactly ONE owner
A `unique_ptr` **cannot be copied.** This won't compile:

```cpp
std::unique_ptr<TreeNode> A = std::make_unique<TreeNode>(5);
std::unique_ptr<TreeNode> B = A;   // COMPILE ERROR — copy is deleted
```

Contrast with a raw pointer, where this compiles fine and silently creates the double-free bug:

```cpp
TreeNode* A = new TreeNode(5);
TreeNode* B = A;   // compiles. Now A and B both "own" the same memory.
delete A;
delete B;   // double-free — undefined behavior, likely crash
```

This is the entire value proposition of `unique_ptr`: it turns a silent runtime bug into a loud compile-time error.

You *can* transfer ownership deliberately, via `std::move`:

```cpp
std::unique_ptr<TreeNode> A = std::make_unique<TreeNode>(5);
std::unique_ptr<TreeNode> B = std::move(A);
// ownership moved to B. A is now empty (equals nullptr). Only B may delete it.
```

### Common pitfall at this level
Using `A` after `std::move(A)` as if it still owns the object. Once moved-from, a `unique_ptr` is guaranteed to be in a valid-but-empty state (`nullptr`) — it's not an error to touch it, but dereferencing it (`A->Value`) is the same null-pointer crash as any other null pointer.

### Why it matters in production
Manual `new`/`delete` bugs (leaks, double-frees, use-after-free) are among the most common sources of crashes and security vulnerabilities in C++ codebases. `unique_ptr` eliminates an entire category of them for free, at zero runtime cost — it compiles down to the same machine code as a raw pointer with manual delete, it's a compile-time-only safety net.

### Edge case / UE5-specific trap (important — don't carry this into Phase 2 wrong)
**`unique_ptr` is NOT how you manage `UObject`-derived classes in UE5** (`AActor`, `APawn`, `UActorComponent`, etc.). Those are managed by Unreal's own garbage collector via `UPROPERTY()` pointers — wrapping a `UObject` in a `unique_ptr` fights the engine's memory system and will cause crashes. `unique_ptr` is for **plain, non-`UObject` C++ helper classes** (data structures like this `TreeNode`, utility objects, non-engine systems) where you're managing memory yourself with no engine involvement. This distinction trips up almost everyone coming from generic C++ into UE5 — flagging it now so it's already load-bearing knowledge before Phase 2.

### Interview follow-up to expect
"What's the difference between `unique_ptr` and `shared_ptr`?" — you haven't covered `shared_ptr` yet (that's a later day: multiple owners, reference-counted), but know that `unique_ptr` = single owner, `shared_ptr` = multiple owners with a shared count. Don't guess further than that yet.
