# Linked List Insert & Delete — Concept Notes (Day 12)

## Recap: Node structure (Day 11)
```cpp
struct Node
{
    int Data;
    Node* Next;
};
```
`Next` holds the address of the following node, or `nullptr` if this is the last node.

## Insert Operations

### Insert at Front (Day 11 recap)
```
NewNode->Next = Head;
Head = NewNode;
```
Order matters: you must point `NewNode` at the old `Head` *before* you overwrite `Head`, or you lose the rest of the list forever.

### Insert at Back
You don't have a "tail" pointer stored (yet — that's a design choice, not a requirement), so you must **traverse** to find it:
```
Node* Current = Head;
while (Current->Next != nullptr)
{
    Current = Current->Next;
}
Current->Next = NewNode;
NewNode->Next = nullptr;
```
Edge case: if `Head == nullptr` (empty list), "insert at back" and "insert at front" are the same operation — `Head = NewNode`.

### Insert at Position (middle)
Given `Prev` (the node *before* where you want to insert):
```
NewNode->Next = Prev->Next;
Prev->Next = NewNode;
```
Same ordering rule as front-insert: set the new node's `Next` before you overwrite `Prev->Next`, or you cut the list.

## Delete Operations

### Delete Head
```
Node* Temp = Head;
Head = Head->Next;
delete Temp;
```
`Temp` exists because once you move `Head`, you have no way to find the old head node again to free it. Save the pointer first.

### Delete a Middle Node (given `Prev`, the node before the target)
```
Node* Temp = Prev->Next;
Prev->Next = Temp->Next;
delete Temp;
```

### Delete Tail
Traverse to the *second-to-last* node (you need `Prev`, not `Current`, because you have to rewrite its `Next`):
```
Node* Current = Head;
while (Current->Next->Next != nullptr)
{
    Current = Current->Next;
}
delete Current->Next;
Current->Next = nullptr;
```

## Worked Example (concrete addresses)
List: `10 -> 20 -> 30`, sitting at fake addresses `0x100 -> 0x200 -> 0x300 -> nullptr`.

**Delete the middle node (20, at 0x200):**
1. `Prev` = node at `0x100` (holds 10). `Prev->Next` currently = `0x200`.
2. `Temp = Prev->Next` → `Temp` = `0x200`.
3. `Prev->Next = Temp->Next` → `Prev->Next` now = `0x300`. The list, as far as traversal is concerned, is now `10 -> 30`. Node 20 is **unreachable** by traversal but the memory at `0x200` still physically holds `{20, 0x300}` — it hasn't been freed yet.
4. `delete Temp` → the memory at `0x200` is returned to the heap allocator. It may get reused by the next `new` call at any time.
5. **The trap:** if any *other* variable in your program still stored `0x200` (e.g. you'd saved a second pointer to that node earlier), that variable is now dangling — it holds an address that used to be valid and looks like a real address, but the data there is no longer yours and could be overwritten by anything.

## Common Pitfalls
- Overwriting a `Next` pointer *before* saving/using the value it held — you permanently lose the rest of the list. Always save what you need into a `Temp` first.
- `delete`-ing a node but not updating the pointer that referenced it — the deleted memory is freed, but your list still traverses into the dangling pointer above.
- Forgetting to update `Head` specifically when the node being inserted/deleted is the first one — it's the one case where there's no `Prev` to update.
- Off-by-one when inserting/deleting "at position N" — is position 0 the head, or the node after it? Decide and stay consistent.

## Edge Cases
- **Empty list** (`Head == nullptr`): insert-anywhere collapses to insert-at-front; delete is either a no-op or should be treated as an error (deleting from nothing).
- **Single-node list**: deleting it must set `Head = nullptr` — there is no `Prev`, no `Next`, just an empty list afterward.
- **Deleting a value that isn't in the list**: your traversal loop hits `nullptr` without finding a match — you must handle "not found" explicitly rather than assuming the target always exists.

## Why It Matters
- Stacks, queues, and trees (coming up this Phase) all reuse this exact "save-before-you-overwrite" pointer discipline. Master it once here.
- UE5 relevance: raw linked lists show up less often than `TArray`, but the *pointer-chasing discipline* is identical to traversing UE5's delegate broadcast lists, scene component hierarchies, and any intrusive linked structure in engine source. Interviewers use linked list insert/delete specifically because it's the cleanest way to test whether you understand pointers, not because you'll hand-roll one at your job.
