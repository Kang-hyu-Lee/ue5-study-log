// Day 23 Exercises — Binary Trees Intro + Pointer/Reference Review + unique_ptr
// Type these yourself. Do not paste. Predict output before compiling where relevant.
// See day23-binary-trees-smart-pointers-concept.md for the worked examples these build on.

#include <iostream>
#include <memory>
using namespace std;

// ---------- SECTION A: Binary Tree Structure (raw pointers) ----------

// A1. Define a struct named TreeNode with:
//     - an int member "Value"
//     - a TreeNode* member "Left"
//     - a TreeNode* member "Right"
//     - a constructor that takes an int and initializes Value, and sets
//       Left and Right to nullptr.
// (write your struct here)

struct TreeNode
{

    int Value;
    TreeNode* Left;
    TreeNode* Right;
    TreeNode(int n): Value(n), Left(nullptr), Right(nullptr) {}
};

// A2. In main() (see bottom of file), using `new`, manually build this tree
//     and store the root in a variable called Root:
//
//             50
//            /  \
//           30   70
//          /       \
//         20        90
//
//     Hint: same pattern as the worked example in the concept file —
//     Root->Left->Left etc.


// A3. Write a function CountLeaves(TreeNode* Node) that returns the number
//     of leaf nodes (nodes where Left == nullptr AND Right == nullptr) in
//     the tree rooted at Node.
//     - Must handle the empty-tree case (Node == nullptr) — what should it
//       return in that case? Think before coding.
//     - Hint: this needs recursion (Day 18/19). Delegate, don't iterate:
//       trust CountLeaves on the left subtree and right subtree to give
//       you the right answer, then combine.

int CountLeaves(TreeNode* Node)
{
    if(Node == nullptr){ return 0;}
    if(Node->Left == nullptr && Node->Right == nullptr){
        return 1;
    }
    return CountLeaves(Node->Left) + CountLeaves(Node->Right);
}


// A4. Write a function FindMax(TreeNode* Node) that returns the largest
//     Value found anywhere in the tree (not assuming any ordering — this
//     is a plain binary tree, not a BST, so you must check every node).
//     - Decide what to return for an empty tree and explain your choice
//       in a comment (there's no perfect answer with a plain int return
//       type — that's the point, think about why).

int FindMax(TreeNode* Node)
{
    if(Node == nullptr) { return INT_MIN;}
    int Max = Node->Value;
    int LeftMax = FindMax(Node->Left);
    int RightMax = FindMax(Node->Right);
    if(LeftMax > Max) { Max = LeftMax; }
    if(RightMax > Max) { Max = RightMax; }
    return Max;
}


// ---------- SECTION B: Pointer & Reference Review ----------

// B1. Without running it, predict what this prints, then verify:
/*
    int Value = 5;
    int* PtrA = &Value;
    int& RefA = Value;
    *PtrA = 10;
    RefA = 20;
    cout << Value << " " << *PtrA << " " << RefA << endl;
*/
// Your prediction (write as a comment): Value 20 20 20 because they are pointing and referencing the same object and both a pointer and reference can mutate the content

// B2. Explain in a comment why the following does NOT compile, referencing
//     the pointer/reference table in the concept file:
/*
    int& BadRef; //a reference has to always be initialized which is this case is not because it's a different name for the same thing so the thing has to exist
*/

// B3. Explain in a comment what is wrong with this function, and rewrite
//     it correctly below your explanation:
//TreeNode* MakeDanglingNode()
//{
//    TreeNode Local(99);   // stack-allocated, not heap
//    return &Local;
//}
// Your fix here:
// The variable Local will be out of scope but we are returning its address &Local leading to whatever is using this into undefined behaviour

TreeNode* MakeDanglingNode()
{
    TreeNode* Local = new TreeNode(99);
    return Local;
}


// ---------- SECTION C: unique_ptr ----------

// C1. Rewrite A2's tree-building code using std::unique_ptr<TreeNode>
//     instead of raw TreeNode*. You'll hit a real design question:
//     TreeNode's Left/Right members are raw TreeNode* — can a struct's
//     members be unique_ptr too? Try changing TreeNode itself so Left
//     and Right are std::unique_ptr<TreeNode> and see what breaks when
//     you try your old A2 code. Write what you observe in a comment.
//     (Hint: this is genuinely the point of the exercise — smart pointer
//     ownership inside self-referential structs is a real design decision,
//     not a beginner mistake if you get stuck. Note your findings.)

struct TreeNodeUnique
{
    int Value;
    std::unique_ptr<TreeNodeUnique> Left;
    std::unique_ptr<TreeNodeUnique> Right;
    TreeNodeUnique(int n): Value(n) {}
};

// C2. Given:
/*
    std::unique_ptr<TreeNode> A = std::make_unique<TreeNode>(5);
    std::unique_ptr<TreeNode> B = std::move(A);
*/
//     - What is the state of A after this? What happens if you then do
//       cout << A->Value; ? Predict, then explain why in a comment.
// A null-pointer crash because the whole unique_ptr's point is that there is a single owner so in this case it has been moved from A to B so now A just holds nullptr;

// C3. Write a function TakesOwnership(std::unique_ptr<TreeNode> Node) that
//     just prints Node->Value. In main(), call it by moving a unique_ptr
//     into it. Explain in a comment: after the call, can you still use
//     your original unique_ptr variable? Why or why not?

void TakesOwnership(std::unique_ptr<TreeNodeUnique> Node) //Parameter by value means there is an ownership transfer, different from if the parameter was somthing like unique_ptr<TreeNode>& Node because a reference and pointers only borrow access
{
    cout << Node->Value << endl;
}


int main()
{
    // A2 goes here
    TreeNode* Root =  new TreeNode(50);
    Root->Left = new TreeNode(30);
    Root->Left->Left = new TreeNode(20);
    Root->Right = new TreeNode (70);
    Root->Right->Right = new TreeNode(90);

    std::unique_ptr<TreeNodeUnique> Root2 = std::make_unique<TreeNodeUnique>(50);
    Root2->Left = std::make_unique<TreeNodeUnique>(30);
    Root2->Left->Left = std::make_unique<TreeNodeUnique>(20);
    Root2->Right = std::make_unique<TreeNodeUnique>(70);
    Root2->Right->Right = std::make_unique<TreeNodeUnique>(90);

    // call CountLeaves and FindMax on your tree, print results

    cout << "Number of Leaves: " << CountLeaves(Root) << endl;

    cout << "Max Value: " << FindMax(Root) << endl;

    // B1 verification
    
    int Value = 5;
    int* PtrA = &Value;
    int& RefA = Value;
    *PtrA = 10;
    RefA = 20;
    cout << Value << " " << *PtrA << " " << RefA << endl;

    // C1, C2, C3 here
    std::unique_ptr<TreeNode> A = std::make_unique<TreeNode>(5);
    std::unique_ptr<TreeNode> B = std::move(A);
    TakesOwnership(std::move(Root2));

    return 0;
}
