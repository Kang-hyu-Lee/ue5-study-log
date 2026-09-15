// Day 32 — Solutions & Explanations
// Compare against your own attempt AFTER trying, not before.

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

// ============================================================
// SECTION 1 — Tree Traversal
// ============================================================
//
//              50
//            /    \
//          30      70
//         /  \    /  \
//       20   40  60   80
//
// 1.1 IN-ORDER (left, root, right):   20, 30, 40, 50, 60, 70, 80
//     -> for a valid BST, in-order ALWAYS produces sorted output. That's the
//        single most useful fact about in-order traversal — it's a free sorted-
//        list generator and a free "is this a BST" sanity check.
//
// 1.2 PRE-ORDER (root, left, right):  50, 30, 20, 40, 70, 60, 80
//     -> visits root before its subtrees. Useful for COPYING a tree (you need
//        the root's value before you can even create the children).
//
// 1.3 POST-ORDER (left, right, root): 20, 40, 30, 60, 80, 70, 50
//     -> visits root LAST. Useful for DELETING a tree (delete children before
//        the parent, so you never lose the pointer to a subtree you still need).

// 1.4 Implementation:
void inOrderTraversal(TreeNode* root) {
    if (root == nullptr) return;      // base case: empty subtree, nothing to visit
    inOrderTraversal(root->left);     // visit everything smaller, first
    cout << root->value << " ";       // then this node
    inOrderTraversal(root->right);    // then everything bigger
}
// Why this base case matters: EVERY leaf node's left/right are nullptr — the
// recursion naturally bottoms out there. If you forget this check, you dereference
// a nullptr and crash. This is the same "trust the recursive leap of faith" pattern
// from your earlier recursion work — you don't need to trace the whole tree by
// hand, you need to trust that the recursive calls on left/right subtrees already
// correctly traverse THEIR subtrees.

void buildSampleTree(TreeNode*& root) {
    root = new TreeNode(50);
    root->left = new TreeNode(30);
    root->right = new TreeNode(70);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(40);
    root->right->left = new TreeNode(60);
    root->right->right = new TreeNode(80);
}

// ============================================================
// SECTION 2 — BST Insert & Bounds Validation
// ============================================================

TreeNode* bstInsert(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);   // found the insertion point
    }
    if (value < root->value) {
        root->left = bstInsert(root->left, value);   // recurse left, reattach result
    } else {
        root->right = bstInsert(root->right, value);  // recurse right, reattach result
    }
    return root;  // return the (possibly unchanged) subtree root up the call chain
}
// Pitfall this guards against: if you don't REATTACH the result of the recursive
// call (`root->left = bstInsert(...)`), the new node gets created and immediately
// lost — nothing points to it. This is a common first-attempt bug.

// Correct isValidBST — tracks a (min, max) range that narrows as you recurse:
bool isValidBSTHelper(TreeNode* node, long long minVal, long long maxVal) {
    if (node == nullptr) return true;  // empty subtree is trivially valid
    if (node->value <= minVal || node->value >= maxVal) return false;
    // Recurse: going left, this node becomes the new UPPER bound.
    // Going right, this node becomes the new LOWER bound.
    return isValidBSTHelper(node->left, minVal, node->value) &&
           isValidBSTHelper(node->right, node->value, maxVal);
}

bool isValidBST(TreeNode* root) {
    return isValidBSTHelper(root, LLONG_MIN, LLONG_MAX);
}
// Why long long for bounds: if a node's actual value is INT_MIN or INT_MAX, using
// int-range sentinels for "no bound yet" would collide with a real value. Using a
// wider type sidesteps that edge case entirely.
//
// Trace against the trap example from the exercise file:
//          10
//         /  \
//        5    15
//            /  \
//           6    20
// isValidBSTHelper(15, minVal=10, maxVal=+inf) is fine (15 > 10).
// Recursing to node 6: isValidBSTHelper(6, minVal=10, maxVal=15)
//   -> 6 <= minVal(10) is TRUE -> returns false. Caught correctly, because the
//      min/max bound CARRIES DOWN from ancestors, not just the immediate parent.

// ============================================================
// SECTION 3 — Binary Search
// ============================================================

int binarySearch(const vector<int>& arr, int target) {
    int lo = 0, hi = static_cast<int>(arr.size()) - 1;
    while (lo <= hi) {                       // <= not < : must still check when lo==hi
        int mid = lo + (hi - lo) / 2;        // overflow-safe midpoint
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            lo = mid + 1;                    // NOT `lo = mid` -- avoids infinite loop
        } else {
            hi = mid - 1;                    // NOT `hi = mid` -- avoids infinite loop
        }
    }
    return -1;  // lo > hi: range exhausted, target not present
}

// 3.2 Trace on [2, 5, 5, 5, 5, 9] searching for 5 (indices 0..5):
// lo=0 hi=5 mid=2 arr[2]=5 -> match, returns index 2 immediately.
// This is NOT guaranteed to be the first occurrence (index 1) — it's whichever
// matching index the halving happens to land on first. Vanilla binary search
// answers "does 5 exist and where's A valid index" — not "where does it FIRST
// occur." A "find leftmost occurrence" variant needs to keep narrowing left
// (`hi = mid - 1` even on a match, recording mid as a candidate answer) instead
// of returning immediately.

// ============================================================
// SECTION 4 — Self-Balancing Trees (conceptual)
// ============================================================

// 4.1 Inserting 1,2,3,4,5 in order into a plain BST:
//     1
//      \
//       2
//        \
//         3
//          \
//           4
//            \
//             5
// Height = 5 (every node has only a right child). A balanced tree holding the
// same 5 values (e.g. built from mixed insertion order 3,1,4,2,5 as in the
// concept file) has height 3. Same data, same insert algorithm — the ONLY
// difference is insertion order, and it's a 5 vs 3 height difference that only
// gets worse as n grows (sorted insert of n values -> height n; balanced -> log2(n)).

// 4.2 A red-black tree enforces (among other invariants) that a red node can
// never have a red child, and that every root-to-null path passes through the
// same number of black nodes. When an insert/delete violates one of these
// (e.g. creates two reds in a row), the tree triggers a ROTATION (and/or a
// recolor) to restore the invariant — a constant-time, local pointer restructuring,
// not a full rebuild.

// 4.3 "std::map is a BST so it's O(log n)" is incomplete because a PLAIN BST is
// only O(log n) on average, for random insertion order — its WORST case (sorted
// or reverse-sorted input) degrades to O(n), same as a linked list. The precise
// version: "std::map is a RED-BLACK tree (a self-balancing BST), which enforces
// invariants via rotations on every insert/delete to GUARANTEE O(log n) even in
// the worst case, regardless of insertion order."
