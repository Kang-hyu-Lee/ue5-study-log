#include <iostream>
using namespace std;

struct Node{
    int Data;
    Node* Next;
};

int main() {

    Node A{5, nullptr};
    Node B{15, nullptr};
    Node C{25, nullptr};
    Node D{35, nullptr};

    Node* Head = &A;
    A.Next = &B;
    B.Next = &C;
    C.Next = &D;

    Node* Current = Head;
    int Sum = 0;

    while(Current != nullptr){
        Sum += Current->Data;
        Current = Current->Next;
    }
    cout << "Sum = " << Sum << endl;

    return 0;
}