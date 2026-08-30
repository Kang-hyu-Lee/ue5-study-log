# Day 25 — Binary Search Trees (BST) + Tree Traversal

## 1. What makes a tree a BST (vs the plain binary tree from Day 23)

Day 23's `TreeNode` had NO rule about where values go — left/right child could hold anything.

A **BST adds one invariant**, applied at EVERY node in the tree, not just the root:

> For any node N: every value in N's LEFT subtree is LESS than N's value.
> Every value in N's RIGHT subtree is GREATER than N's value.

**Pitfall (this is the #1 BST bug):** beginners check this only against the *immediate* children, not the whole subtree.

Concrete failure case:
```
        50
       /  \
     30    70
    /  \
  10    60      <-- BROKEN. 60 is less than 30's parent 50? No wait —
```
Let's make the actual broken example explicit: `60` is greater than `30` (its direct parent, fine) but `60` is also in `50`'s LEFT subtree, and `60 > 50`. That violates the invariant even though `60 > 30` looks locally fine. The rule is transitive across the WHOLE subtree, not just parent-child.

Same struct as Day 23:
```cpp
struct TreeNode
{
    int Value;
    TreeNode* Left;
    TreeNode* Right;

    TreeNode(int InValue) : Value(InValue), Left(nullptr), Right(nullptr) {}
};
```
Nothing changes structurally. What changes is the DISCIPLINE you enforce when inserting.

## 2. Insert (recursive)

Mechanism: walk left if the new value is smaller, right if larger, until you fall off the tree (hit `nullptr`) — that's where the new node attaches.

```cpp
TreeNode* Insert(TreeNode* Root, int NewValue)
{
    if (Root == nullptr)              // base case: found the empty slot
    {
        return new TreeNode(NewValue);
    }

    if (NewValue < Root->Value)
        Root->Left = Insert(Root->Left, NewValue);   // recurse left, reattach
    else if (NewValue > Root->Value)
        Root->Right = Insert(Root->Right, NewValue);  // recurse right, reattach
    // if equal — see duplicates note below

    return Root;   // hand back the (possibly unchanged) subtree root
}
```

**Why `Root->Left = Insert(Root->Left, ...)` and not just `Insert(Root->Left, ...)`?**
This is "delegate, don't iterate" from Day 19/20 recursion again: the recursive call returns the correct subtree root (new node if it just got created, unchanged pointer otherwise), and you MUST reassign it — otherwise the new node is built on the heap but nothing points to it. Classic leak + "why didn't my insert work" bug.

**Duplicates — pick a convention and be consistent:** most common: ignore (do nothing), OR route duplicates right (`>=` goes right). Either is fine; what's NOT fine is leaving it undefined, because then traversal order becomes unpredictable.

## 3. Search

Same walk logic, no reattachment needed since you're not modifying:
```cpp
bool Contains(TreeNode* Root, int Target)
{
    if (Root == nullptr) return false;
    if (Root->Value == Target) return true;
    if (Target < Root->Value) return Contains(Root->Left, Target);
    return Contains(Root->Right, Target);
}
```

## 4. Big-O — and the trap carried over from Day 23

Each comparison eliminates one subtree, so a BALANCED tree gives you `O(log n)` search/insert — same shape as binary search on a sorted array.

**Edge case where the naive understanding breaks:** insert values already in sorted order — `10, 20, 30, 40, 50` — and the "tree" degenerates into a straight line (every node only has a right child). That's `O(n)`, identical to a linked list. **A BST does not self-balance.** Balanced variants (AVL, Red-Black trees) exist specifically to fix this — out of scope for Phase 1, flagged here so you know the `O(log n)` claim has a condition attached, not a guarantee.

## 5. Traversals — three orders, one recursive shape

All three visit left subtree, visit self, visit right subtree — they only differ in WHEN "visit self" happens relative to the two recursive calls.

```cpp
void InOrder(TreeNode* Root)     // Left, Self, Right
{
    if (Root == nullptr) return;
    InOrder(Root->Left);
    std::cout << Root->Value << " ";
    InOrder(Root->Right);
}

void PreOrder(TreeNode* Root)    // Self, Left, Right
{
    if (Root == nullptr) return;
    std::cout << Root->Value << " ";
    PreOrder(Root->Left);
    PreOrder(Root->Right);
}

void PostOrder(TreeNode* Root)   // Left, Right, Self
{
    if (Root == nullptr) return;
    PostOrder(Root->Left);
    PostOrder(Root->Right);
    std::cout << Root->Value << " ";
}
```

**The one fact worth memorizing cold (common interview question):** **in-order traversal of a BST visits values in sorted ascending order.** This falls directly out of the BST invariant — left subtree (all smaller) gets fully visited before self, self before right subtree (all larger). This is WHY the invariant is useful, not just a rule to obey.

**Pre-order use case:** copying/serializing a tree (root first means you can rebuild the same shape on deserialize).
**Post-order use case:** deleting a tree bottom-up (delete children before the parent that points to them — deleting parent first would leak the children, no way to reach them anymore).

## 6. Why this matters beyond the interview question

- Traversal is the same recursive skeleton you'll see in scene graph walks, UI widget trees, and behavior trees in UE5 — "process children, then/before self" is a repeating pattern, not a tree-specific trick.
- Unbalanced BST degrading to O(n) is the same root cause class as any data structure whose performance guarantee depends on an invariant you have to maintain yourself — worth remembering for when balanced trees (or just using `std::map`, which IS balanced internally) come up later.

## 7. Common pitfall recap
- Checking BST property against immediate parent only, not full subtree ancestry.
- Forgetting to reassign `Root->Left = Insert(...)` — orphaned heap node, memory leak.
- Assuming O(log n) unconditionally — depends on insertion order / balance.
- Confusing traversal order names — anchor on WHEN "visit self" happens: before both (pre), between (in), after both (post).
