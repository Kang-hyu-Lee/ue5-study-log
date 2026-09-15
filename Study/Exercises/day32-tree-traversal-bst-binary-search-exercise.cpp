// Day 32 — Spaced-Rep Timed Drill + Binary Search + Self-Balancing Trees (conceptual)
// Type this file yourself. Do not paste. Attempt every problem before opening the solution file.
//
// TIMING: this is a DRILL, not a leisurely review. Set an actual timer per section.
// If you blow through the time limit, that's diagnostic information (write it in your
// log's "confused" line), not a failure — it tells us where the debt item hasn't
// actually closed yet.

#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// SECTION 1 — Tree Traversal (REVIEW — timer: 10 minutes total)
// ============================================================

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

// The tree used for Section 1 problems (build this exact tree by hand first):
//
//              50
//            /    \
//          30      70
//         /  \    /  \
//       20   40  60   80
//
// Problem 1.1 (2 min): Without writing code, write on paper the IN-ORDER traversal
// order of the tree above (left, root, right). Just the sequence of numbers.
//20 30 40 50 60 70 80

// Problem 1.2 (2 min): Write the PRE-ORDER traversal order (root, left, right) by hand.
//50 30 20 40 70 60 80

// Problem 1.3 (2 min): Write the POST-ORDER traversal order (left, right, root) by hand.
//20 40 30 60 80 70 50

// Problem 1.4 (4 min): Now implement IN-ORDER traversal as actual C++ code.
// Build the tree above using `new TreeNode(...)` and wire up left/right pointers,
// then call your function and confirm the printed output matches your Problem 1.1 answer.
void inOrderTraversal(TreeNode* root) {
    // TODO: recursive traversal. Base case: what happens when root is nullptr?
    if(root == nullptr) return;
    inOrderTraversal(root->left);
    std::cout << root->value << " ";
    inOrderTraversal(root->right);
}

// ============================================================
// SECTION 2 — BST Insert & Bounds Validation (REVIEW — timer: 12 minutes total)
// ============================================================

// Problem 2.1 (5 min): Implement BST insert (iterative or recursive, your choice).
// Reminder of the rule you're implementing: at every node, if new value < node's value,
// go left; if greater, go right; insert when you hit a nullptr.
TreeNode* bstInsert(TreeNode* root, int value) {
    // TODO
    if(root == nullptr) 
    {
        return new TreeNode(value);
    }
    if(root->value > value)
    {
        root->left = bstInsert(root->left, value);
    }
    else if(root->value < value)
    {
        root->right = bstInsert(root->right, value);
    }
    return root;
}

// Problem 2.2 (7 min): Implement isValidBST — given a tree, return true only if it
// satisfies the BST property EVERYWHERE, not just locally between a node and its
// immediate children.
//
// HINT (the actual bug this problem is designed to catch): checking only
// `node->left->value < node->value && node->right->value > node->value` at each node
// is NOT sufficient. Example of a tree that passes that shallow check but is NOT a
// valid BST:
//
//          10
//         /  \
//        5    15
//            /  \
//           6    20
//
// Node 15's left child (6) is less than 15 (locally fine) but 6 is NOT less than 10 —
// it violates the BST property relative to an ANCESTOR two levels up, not just its
// direct parent. Your function needs to track a valid (min, max) RANGE that narrows
// as you recurse down, not just compare to the immediate parent.

bool isValidBSTHelper(TreeNode* root, TreeNode*& prev){
    if(root == nullptr) return true;
    if(!isValidBSTHelper(root->left, prev)) return false;
    if(prev != nullptr && root->value <= prev->value) return false;
    prev = root;
    return isValidBSTHelper(root->right, prev);
}

bool isValidBST(TreeNode* root) {
    // TODO
    TreeNode* prev = nullptr;
    return isValidBSTHelper(root, prev);
}

// ============================================================
// SECTION 3 — Binary Search (NEW — timer: 10 minutes total)
// ============================================================

// Problem 3.1 (6 min): Implement binary search on a sorted vector<int>. Return the
// index of target if found, -1 if not found. Watch the three off-by-one pitfalls
// covered in today's concept file: loop condition, bound updates, mid calculation.
int binarySearch(const vector<int>& arr, int target) {
    // TODO
    int lo = 0;
    int hi = static_cast<int>(arr.size()) - 1;
    while(lo <= hi)
    {
        int mid = lo+(hi-lo)/2;
        if(arr[mid] == target)
        {
            return mid;
        }
        else if(arr[mid] < target)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1;
        }
    } 

    return -1;
}

// Problem 3.2 (4 min, conceptual — no code): The array [2, 5, 5, 5, 5, 9] contains
// four copies of 5. Trace your Problem 3.1 implementation by hand searching for 5.
// Which index does it return? Is that guaranteed to be the FIRST occurrence? Write
// one sentence explaining why or why not.
// it will return 2 but that is not the first occurence because we check mid and return if found. To find first occurence, we would need to save that index and keep going to the left until we find the first occurence.
// ============================================================
// SECTION 4 — Self-Balancing Trees (NEW — conceptual, no code, timer: 5 minutes)
// ============================================================

// Problem 4.1: Insert 1, 2, 3, 4, 5 (in that order) into an empty plain BST by hand
// (paper). Draw the resulting shape. What is its height? What is the height of a
// BALANCED tree containing the same 5 values?

//1
//2
//3
//4
//5
//so height 4 if it was balanced it would be height 2

// Problem 4.2: In one or two sentences — what specific rule does a red-black tree
// enforce that a plain BST does not, and what operation does it trigger when that
// rule is violated?
// A red node cannot have a red child and every path from a node to any of it's descendants null pointers passes through the same number of black nodes
// triggers a rotation when violated to balance the tree

// Problem 4.3 (interview-framing): A teammate says "std::map is a BST so it's
// O(log n)." What's incomplete about that statement, and what's the more precise
// version?
// A BST is O(log n) if balanced, where std::map is a red-black tree under the hood which guarantees the O(log n) worst case
