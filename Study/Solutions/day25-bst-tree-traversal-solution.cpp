// Day 25 Solutions — BST + Tree Traversal
// Compare against your own attempt AFTER you've tried every problem.

#include <iostream>

struct TreeNode
{
    int Value;
    TreeNode* Left;
    TreeNode* Right;

    TreeNode(int InValue) : Value(InValue), Left(nullptr), Right(nullptr) {}
};

// PROBLEM 1 -------------------------------------------------------------
TreeNode* Insert(TreeNode* Root, int NewValue)
{
    if (Root == nullptr)
    {
        return new TreeNode(NewValue);   // base case: empty slot found, attach here
    }

    if (NewValue < Root->Value)
    {
        Root->Left = Insert(Root->Left, NewValue);   // MUST reassign — this is
                                                        // what actually attaches the
                                                        // new node into the tree.
                                                        // Without this line the new
                                                        // node is allocated but orphaned.
    }
    else if (NewValue > Root->Value)
    {
        Root->Right = Insert(Root->Right, NewValue);
    }
    // else: NewValue == Root->Value -> duplicate, ignore per convention

    return Root;   // hand this subtree's (possibly unchanged) root back up
}

// PROBLEM 2 -------------------------------------------------------------
bool Contains(TreeNode* Root, int Target)
{
    if (Root == nullptr) return false;          // fell off the tree, not found
    if (Root->Value == Target) return true;     // found it
    if (Target < Root->Value) return Contains(Root->Left, Target);
    return Contains(Root->Right, Target);
    // Only ONE recursive call ever fires per level — BST property lets us
    // discard the other half of the tree without visiting it. This is the
    // O(log n) source: each call halves (on a balanced tree) the search space.
}

// PROBLEM 3 -------------------------------------------------------------
void InOrder(TreeNode* Root)
{
    if (Root == nullptr) return;
    InOrder(Root->Left);
    std::cout << Root->Value << " ";
    InOrder(Root->Right);
}

// PROBLEM 4 -------------------------------------------------------------
void PreOrder(TreeNode* Root)
{
    if (Root == nullptr) return;
    std::cout << Root->Value << " ";
    PreOrder(Root->Left);
    PreOrder(Root->Right);
}

// PROBLEM 5 -------------------------------------------------------------
void PostOrder(TreeNode* Root)
{
    if (Root == nullptr) return;
    PostOrder(Root->Left);
    PostOrder(Root->Right);
    std::cout << Root->Value << " ";
}

// PROBLEM 6 -------------------------------------------------------------
int FindMin(TreeNode* Root)
{
    // Recursive version. Could also be an iterative while(Root->Left) loop —
    // both are O(height). Recursive shown here for consistency with the rest.
    if (Root->Left == nullptr) return Root->Value;   // leftmost node = smallest
    return FindMin(Root->Left);
}

// PROBLEM 7 -------------------------------------------------------------
int CountNodes(TreeNode* Root)
{
    if (Root == nullptr) return 0;
    return 1 + CountNodes(Root->Left) + CountNodes(Root->Right);
    // "Delegate, don't iterate": trust the recursive calls to correctly
    // count their own subtrees, just add 1 for the current node.
}

// PROBLEM 8 -------------------------------------------------------------
void DeleteTree(TreeNode* Root)
{
    if (Root == nullptr) return;
    DeleteTree(Root->Left);
    DeleteTree(Root->Right);
    delete Root;
    // POST-ORDER is required here: children must be freed BEFORE the parent.
    // If you deleted Root first, Root->Left and Root->Right would be
    // unreadable (dangling access) — you'd leak both subtrees, no way to
    // reach them anymore to free them.
}

// PROBLEM 9 -------------------------------------------------------------
// Insert sequence: 50, 30, 70, 20, 40, 60, 80
//
//              50
//            /    \
//          30      70
//         /  \     /  \
//       20   40   60   80
//
// InOrder   (L,Self,R): 20 30 40 50 60 70 80   <- sorted ascending, as guaranteed
// PreOrder  (Self,L,R): 50 30 20 40 70 60 80
// PostOrder (L,R,Self): 20 40 30 60 80 70 50

// PROBLEM 10 -------------------------------------------------------------
// Insert sequence: 10, 20, 30, 40, 50 (already sorted)
// Every new value is greater than the current node, so every insert goes
// RIGHT. The tree degenerates into a straight line (a linked list wearing
// a TreeNode costume):
//   10 -> 20 -> 30 -> 40 -> 50   (each only has a Right child)
//
// Contains() on THIS tree is O(n): every comparison only eliminates the
// (empty) left subtree, so in the worst case you walk all n nodes one at a
// time — identical cost profile to searching an unsorted linked list.
// The O(log n) claim assumes a roughly balanced tree; insertion ORDER is
// what determines whether that assumption holds. Nothing about a plain BST
// enforces balance automatically.

int main()
{
    TreeNode* Root = nullptr;
    int Values[] = { 50, 30, 70, 20, 40, 60, 80 };
    for (int V : Values)
    {
        Root = Insert(Root, V);
    }

    std::cout << "InOrder: ";
    InOrder(Root);
    std::cout << "\n";

    std::cout << "PreOrder: ";
    PreOrder(Root);
    std::cout << "\n";

    std::cout << "PostOrder: ";
    PostOrder(Root);
    std::cout << "\n";

    std::cout << "Contains(40): " << Contains(Root, 40) << "\n";
    std::cout << "Contains(99): " << Contains(Root, 99) << "\n";
    std::cout << "Min: " << FindMin(Root) << "\n";
    std::cout << "Count: " << CountNodes(Root) << "\n";

    DeleteTree(Root);
    Root = nullptr;

    return 0;
}
