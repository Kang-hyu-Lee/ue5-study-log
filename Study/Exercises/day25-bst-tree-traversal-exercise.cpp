// Day 25 Exercises — BST + Tree Traversal
// Type this file yourself. Do not paste. Compile with: g++ day25-bst-tree-traversal-exercise.cpp -o day25bst

#include <iostream>
using namespace std;

struct TreeNode
{
    int Value;
    TreeNode* Left;
    TreeNode* Right;

    TreeNode(int InValue) : Value(InValue), Left(nullptr), Right(nullptr) {}
};

// ---------------------------------------------------------------------
// PROBLEM 1: Implement Insert
// Recursive insert into a BST. Must maintain the BST invariant.
// Duplicate convention: IGNORE duplicates (do nothing if value already exists).
// Reminder: base case returns `new TreeNode(NewValue)`. Non-base case must
// reassign Root->Left / Root->Right to the recursive call's return value.
TreeNode* Insert(TreeNode* Root, int NewValue)
{
    // TODO
    if(Root == nullptr)
    {
        return new TreeNode(NewValue); //base case
    }
    if(NewValue < Root->Value){

        Root->Left = Insert(Root->Left, NewValue);
    }
    else if(NewValue > Root->Value)
    {
        Root->Right = Insert(Root->Right, NewValue);
    }
    return Root;
}

// ---------------------------------------------------------------------
// PROBLEM 2: Implement Contains
// Recursive search. Return true if Target exists anywhere in the tree.
bool Contains(TreeNode* Root, int Target)
{
    // TODO
    if(Root == nullptr)return false;
    if(Root->Value == Target) return true;
    if(Target < Root->Value) return Contains(Root->Left, Target);
    return Contains(Root->Right, Target);

}

// ---------------------------------------------------------------------
// PROBLEM 3: Implement InOrder traversal
// Should print values separated by a space, in ascending order (BST property).
void InOrder(TreeNode* Root)
{
    // TODO
    if(Root == nullptr) return;
    InOrder(Root->Left);
    cout << Root->Value << " ";
    InOrder(Root->Right);
}

// ---------------------------------------------------------------------
// PROBLEM 4: Implement PreOrder traversal
// Self, Left, Right. Print values separated by a space.
void PreOrder(TreeNode* Root)
{
    // TODO
    if(Root == nullptr) return;
    cout << Root->Value << " ";
    PreOrder(Root->Left);
    PreOrder(Root->Right);
}

// ---------------------------------------------------------------------
// PROBLEM 5: Implement PostOrder traversal
// Left, Right, Self. Print values separated by a space.
void PostOrder(TreeNode* Root)
{
    // TODO
    if(Root == nullptr) return;
    PostOrder(Root->Left);
    PostOrder(Root->Right);
    cout << Root->Value << " ";
}

// ---------------------------------------------------------------------
// PROBLEM 6: Implement FindMin
// BST property means the minimum value is always the leftmost node.
// Iterative OR recursive is fine. Return the int value (assume tree is non-empty).
int FindMin(TreeNode* Root)
{
    // TODO
    TreeNode* Current = Root;
    while(Current->Left != nullptr){
       Current = Current->Left; 
    }
    return Current->Value;

    //if(Root == nullptr) return INT_MAX;
    //int Min = Root->Value;
    //int LeftMin = FindMin(Root->Left);
    //if(LeftMin < Min) {Min = LeftMin;}
    //return Min;
}
// ---------------------------------------------------------------------
// PROBLEM 7: Implement CountNodes
// Recursive. Return total number of nodes in the tree (0 for nullptr).
int CountNodes(TreeNode* Root)
{
    // TODO
    if(Root == nullptr) return 0;
    return (1+ CountNodes(Root->Left)) + (CountNodes(Root->Right));
}

// ---------------------------------------------------------------------
// PROBLEM 8: Implement DeleteTree
// Recursive. Free every node with `delete`, no leaks.
// Hint: which traversal order guarantees children are freed before their parent?
void DeleteTree(TreeNode* Root)
{
    // TODO
    if (Root == nullptr) return;
    DeleteTree(Root->Left);
    DeleteTree(Root->Right);
    delete Root;
}

// ---------------------------------------------------------------------
// PROBLEM 9 (trace-through, answer in a comment, no code needed):
// Given this insert sequence: 50, 30, 70, 20, 40, 60, 80
// Draw the resulting tree shape (as a comment, using indentation) and write
// out what InOrder, PreOrder, and PostOrder would each print.
//50
//30 70
//20 40 60 80
//InOrder: 20 30 40 50 60 70 80
//PreOrder: 50 30 20 40 70 60 80
//PostOrder: 20 30 40 60 80 70 50 
//Corrected: 20 40 30 60 80 70 50

// ---------------------------------------------------------------------
// PROBLEM 10 (conceptual, answer in a comment, no code needed):
// Insert sequence: 10, 20, 30, 40, 50 (already sorted ascending).
// What shape does the tree degenerate into? What is Contains()'s Big-O
// on THIS specific tree, and why does it no longer match the "balanced"
// O(log n) claim?
//It will be a linear line so it had O(n) and this is because it doesn't guarantee a balanced tree

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
