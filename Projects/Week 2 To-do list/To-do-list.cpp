#include <iostream>

using namespace std;

struct TodoItem {
    string Description;
    bool IsComplete = false;
    int Priority = 0;
};

struct TodoNode {
    TodoItem Data;
    TodoNode* Next = nullptr;
};

void AddTask(TodoNode*& Head, string Description, int Priority){
    TodoNode* Todo = new TodoNode();
    Todo->Data.Description = Description;
    Todo->Data.Priority = Priority;
    TodoNode* Current = Head;
    if(Head == nullptr){
        Head = Todo;
    }else {
        while(Current->Next != nullptr){
            Current = Current->Next;
        }
        Current->Next = Todo;
    }
}

void PrintAll(const TodoNode* Head){
    while(Head != nullptr){
        if(Head->Data.IsComplete){
            cout << "Task: " << Head->Data.Description << " Priority: " << Head->Data.Priority << " Completion Status: " << "Complete!" << endl;
        }else{
            cout << "Task: " << Head->Data.Description << " Priority: " << Head->Data.Priority << " Completion Status: " << "Incomplete" << endl;
        }
        Head = Head->Next;
    }
}

void MarkComplete(TodoNode* Head, string Description){
    while(Head != nullptr){
        if(Head->Data.Description == Description){
            Head->Data.IsComplete = true;
            return;
        }else {
            Head = Head->Next;
        }
    }
    cout << "Matching task not found in list" << endl;
}

void DeleteCompleted(TodoNode*& Head){
    while(Head != nullptr){
        if(Head->Data.IsComplete){
            TodoNode* Temp = Head;
            Head = Head->Next;
            delete Temp;
        }else{
            break;
        }
    }
    if(Head == nullptr){
        return;
    }else{
        TodoNode* Prev = Head;
        while(Prev->Next != nullptr){
            if(Prev->Next->Data.IsComplete){
                TodoNode* Current = Prev->Next;
                Prev->Next = Current->Next;
                delete Current;
            }else{
                Prev = Prev->Next;
            } 
        }
    }
}

string FindHighestPriority(const TodoNode* Head){
    if(Head == nullptr){
        return "This list is currently empty";
    }else{
        int HighestPrio = Head->Data.Priority;
        string PrioDesc = Head->Data.Description;
        const TodoNode* Walker = Head->Next;
        while(Walker != nullptr){
            if(HighestPrio < Walker->Data.Priority){
                HighestPrio = Walker->Data.Priority;
                PrioDesc = Walker->Data.Description;
            }
            Walker = Walker->Next;
        }
        return PrioDesc;
    }
}

int main(){
    TodoNode* Head = nullptr;

    AddTask(Head, "Buy milk", 2);
    AddTask(Head, "Finish assignment", 5);
    AddTask(Head, "Walk the dog", 1);

    cout << "All tasks:" << endl;
    PrintAll(Head);

    MarkComplete(Head, "Buy milk");
    cout << "Buying milk complete" << endl;
    PrintAll(Head);

    cout << "Find highest priority task: " << endl;
    cout << FindHighestPriority(Head) << endl;

    DeleteCompleted(Head);

    cout << "Updated list:" << endl;
    PrintAll(Head);
    
    return 0;
}