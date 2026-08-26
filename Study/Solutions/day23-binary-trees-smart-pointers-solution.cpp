// Day 23 Solutions — Binary Trees Intro + Pointer/Reference Review + unique_ptr
// Compare AFTER attempting. Every answer explained, not just shown.

#include <iostream>
#include <memory>
using namespace std;

// ---------- SECTION A: Binary Tree Structure (raw pointers) ----------

// A1.
struct TreeNode
{
    int Value;
    TreeNode* Left;
    TreeNode* Right;

    TreeNode(int InValue) : Value(InValue), Left(nullptr), Right(nullptr) {}
};
// Why Left/Right default to nullptr in the constructor: a freshly created
// node is always a leaf until you explicitly attach children. If we didn't
// initialize them, they'd hold garbage addresses (same danger as any
// uninitialized pointer) and CountLeaves below would crash on garbage.

// A2 (shown inside main() below — building the tree is a sequence of
// statements, not a standalone function).

// A3.
int CountLeaves(TreeNode* Node)
{
    if (Node == nullptr)
        return 0;   // empty tree/subtree contributes zero leaves

    if (Node->Left == nullptr && Node->Right == nullptr)
        return 1;   // this node itself is a leaf — count it, don't recurse further

    // Not a leaf: the answer is "however many leaves are in my left subtree,
    // plus however many are in my right subtree." Trust the recursive calls
    // to already have the right answer for their subtree (delegate, don't
    // iterate) — don't try to track a running counter manually.
    return CountLeaves(Node->Left) + CountLeaves(Node->Right);
}

// A4.
int FindMax(TreeNode* Node)
{
    // Design note: returning int for an empty tree has no clean answer —
    // INT_MIN is a common convention (any real value beats it), but it's a
    // sentinel hack, not a real solution. The "correct" production fix is
    // to return an optional<int> or take an out-parameter for "was a value
    // found." For this intro exercise, INT_MIN is acceptable — the point
    // is recognizing the problem, not necessarily solving it perfectly yet.
    if (Node == nullptr)
        return INT_MIN;

    int LeftMax = FindMax(Node->Left);
    int RightMax = FindMax(Node->Right);

    int Result = Node->Value;
    if (LeftMax > Result) Result = LeftMax;
    if (RightMax > Result) Result = RightMax;
    return Result;
}

// ---------- SECTION B: Pointer & Reference Review ----------

// B1.
// Prediction: 20 20 20
// Why: PtrA and RefA both refer to the SAME int (Value). *PtrA = 10 changes
// Value to 10. RefA = 20 then changes the same Value to 20. There's only
// ever one int in memory here — Value, PtrA, and RefA are three different
// ways to reach it, not three separate ints.

// B2.
// int& BadRef;   // ILLEGAL
// A reference MUST bind to something at the moment it's created — it has
// no concept of "not yet pointing at anything," unlike a pointer which can
// legally hold nullptr. There is no such thing as a null or unbound
// reference in valid C++; the language enforces this at compile time.

// B3.
// What's wrong: Local is a stack variable — it's destroyed the instant
// MakeDanglingNode() returns. The returned address points at memory that
// no longer belongs to this object; it's now dangling. Using it afterward
// is undefined behavior (might look fine, might crash, might corrupt
// unrelated data — that unpredictability IS the danger).
TreeNode* MakeNodeFixed()
{
    TreeNode* HeapNode = new TreeNode(99);   // lives until explicitly deleted
    return HeapNode;
    // caller is now responsible for eventually calling delete on this —
    // this exact responsibility is WHY Section C introduces unique_ptr.
}

// ---------- SECTION C: unique_ptr ----------

// C1.
// If TreeNode's Left/Right become std::unique_ptr<TreeNode>, the old raw-
// pointer code from A2 (Root->Left = new TreeNode(30);) breaks: you can't
// assign a raw `new TreeNode(30)` pointer directly into a unique_ptr member
// via `=` — you must use make_unique, e.g.:
//   Root->Left = make_unique<TreeNode>(30);
// This actually works fine going DOWN the tree (each node uniquely owns
// its children — that's a completely natural ownership model: a subtree
// is genuinely owned by its parent, and if the parent is destroyed, the
// whole subtree should auto-destroy too, which unique_ptr gives you for
// free, recursively, with zero manual delete calls anywhere).
struct TreeNodeSmart
{
    int Value;
    unique_ptr<TreeNodeSmart> Left;
    unique_ptr<TreeNodeSmart> Right;
    TreeNodeSmart(int InValue) : Value(InValue), Left(nullptr), Right(nullptr) {}
};

// C2.
// After std::move(A): A is left in a valid-but-empty state — A == nullptr.
// cout << A->Value; dereferences a null unique_ptr, which is the same
// category of crash as dereferencing any null pointer (undefined behavior,
// typically a segfault). B is now the sole owner of the TreeNode that A
// used to own.

// C3.
void TakesOwnership(unique_ptr<TreeNode> Node)
{
    cout << Node->Value << endl;
    // Node goes out of scope at the end of this function -> TreeNode is
    // destroyed here automatically, since this function is now the owner.
}
// After calling TakesOwnership(std::move(MyPtr)) in main, MyPtr is empty
// (nullptr) — ownership was moved INTO the function parameter, and the
// object was destroyed when the function returned. You cannot use MyPtr
// afterward. This is the same "moved-from means empty" rule as C2, just
// happening via a function call instead of a direct std::move assignment.


int main()
{
    // A2: build the tree with raw pointers
    TreeNode* Root = new TreeNode(50);
    Root->Left = new TreeNode(30);
    Root->Right = new TreeNode(70);
    Root->Left->Left = new TreeNode(20);
    Root->Right->Right = new TreeNode(90);

    cout << "Leaves: " << CountLeaves(Root) << endl;   // 20 and 90 are leaves -> 2
    cout << "Max: " << FindMax(Root) << endl;          // 90

    // B1 verification
    int Value = 5;
    int* PtrA = &Value;
    int& RefA = Value;
    *PtrA = 10;
    RefA = 20;
    cout << Value << " " << *PtrA << " " << RefA << endl;   // 20 20 20

    // C2/C3 demo
    unique_ptr<TreeNode> A = make_unique<TreeNode>(5);
    unique_ptr<TreeNode> B = move(A);
    cout << "B owns value: " << B->Value << endl;
    // cout << A->Value;   // would crash — A is null after the move

    unique_ptr<TreeNode> C = make_unique<TreeNode>(42);
    TakesOwnership(move(C));
    // C is now empty here — do not use C->Value below this line

    // NOTE: Root and its children were made with raw `new` and are never
    // deleted here — that's a deliberate leak left in for you to notice.
    // Real code should either delete each node (annoying, easy to miss
    // one) or, better, use the unique_ptr version from C1 instead.

    return 0;
}
