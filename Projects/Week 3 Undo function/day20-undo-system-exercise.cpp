// Day 20 Portfolio Exercise — Undo System
// Type every line yourself. Do not paste. Read day20-undo-system-concept.md first.
//
// Build order (do it in this order, test each piece before moving to the next):
//   1. Command struct
//   2. CommandStack   (adapt your Day 16 ArrayStack pattern, element type = Command)
//   3. LogQueue       (adapt your Day 16 linked-list Queue pattern, element type = std::string)
//   4. EditorSession  (base class)
//   5. TextEditor     (derived class — the explicit base constructor call lives here)
//   6. main()         (test scenario given at the bottom — predict output before running)

#include <iostream>
#include <string>
using namespace std;

// =====================================================================
// 1. Command — plain data struct (public by default, no encapsulation
//    needed for a pure data holder). See concept file Section 3.
// =====================================================================

// TODO: define enum class ActionType with two values: Insert, Delete
enum class ActionType {Insert, Delete};

// TODO: define struct Command with three members:
//   ActionType Type
//   int Position
//   string Text
struct Command
{
    ActionType Type;
    int Position;
    string Text;
};


// =====================================================================
// 2. CommandStack — array-based stack of Command.
//    Adapt this directly from your Day 16 ArrayStack. Same operations,
//    different element type. Fixed capacity is fine (e.g. 100).
// =====================================================================

class CommandStack
{
private:
    // TODO: fixed-size array of Command
    // TODO: int TopIndex (or similar — match whatever you called it in ArrayStack)
    // TODO: capacity constant

    Command Comms[100];
    int Top = -1;
    static const int Capacity = 100;

public:
    // TODO: constructor — initialize empty state

    CommandStack() {};

    // TODO: bool IsEmpty() const
    // TODO: bool IsFull() const
    // TODO: void Push(Command NewCommand)
    // TODO: Command Pop()   // what should happen if the stack is empty? decide and comment why

    bool IsEmpty() const{ return Top < 0; }
    bool IsFull() const{ return Top >= Capacity -1; }
    void Push(Command NewCommand){
        if(!IsFull()){
            Top ++;
            Comms[Top] = NewCommand;
            return;
        }
        cout << "CommandStack is Full" << endl;
    }

    Command Pop() {
        if(IsEmpty()){
            cout << "CommandStack is empty" << endl;
            return Command{ActionType::Delete, -1, ""}; //Position -1 to flag invalid Pop(), empty CommandStack
        }else{
            Command Current = Comms[Top];
            Top --;
            return Current;
        }   
    }

};


// =====================================================================
// 3. LogQueue — linked-list queue of string.
//    Adapt from your Day 16 linked-list Queue. Node holds a string
//    instead of whatever type you used before.
// =====================================================================

struct LogNode
{
    string Data;
    // TODO: pointer to next node — what type, and why must it be a pointer
    // and not a LogNode by value? (you answered this exact question for
    // TodoNode on Day 13 — same reasoning applies)
    LogNode* Next = nullptr; //Because we want to save the address of the next LogNode

};

class LogQueue
{
private:
    // TODO: Front and Rear pointers
    LogNode* Front = nullptr;
    LogNode* Rear = nullptr;

public:
    // TODO: constructor — initialize empty state
    // TODO: destructor — free every node (memory discipline, Day 17)
    LogQueue() {};
    ~LogQueue() {
        while(Front != nullptr){
            LogNode* Temp = Front;
            Front = Front->Next;
            delete Temp;
        }
    }

    // TODO: bool IsEmpty() const
    // TODO: void Enqueue(string Entry)
    // TODO: string Dequeue()   // removes and returns the front entry
    // TODO: void PrintAll() const   // prints every entry front-to-back WITHOUT removing them

    bool IsEmpty() const{
        return Front == nullptr;
    }

    void Enqueue(string Entry){
        LogNode* Log = new LogNode();
        Log->Data = Entry;
        Log->Next = nullptr;
        if(IsEmpty()){
            Front = Log;
            Rear = Log;
        }else{
            Rear->Next = Log;
            Rear = Log;
        }
    }

    string Dequeue(){
        if(IsEmpty()){
            cout << "LogQueue is empty" << endl;
            return "invalid queue is empty";
        }else{
            LogNode* Temp = Front;
            Front = Front->Next;
            string Value = Temp->Data;
            delete Temp;
            return Value;
        }
    }

    void PrintAll() const{
        LogNode* Current = Front;
        while(Current != nullptr){
            cout << Current->Data << endl;
            Current = Current->Next;
        }
    }
};


// =====================================================================
// 4. EditorSession — base class. See concept file Section 4.
// =====================================================================

class EditorSession
{
protected:
    // TODO: string Content
    string Content;

public:
    // TODO: constructor taking initial content, initialize Content via
    // member initializer list (not assignment in the body — you covered
    // why initializer-list is preferred back on Day 17)
    EditorSession(string ini):Content(ini) {};

    // TODO: string GetContent() const
    string GetContent() const{
        return Content;
    }
};


// =====================================================================
// 5. TextEditor — derived class. THIS is where the explicit base
//    constructor call gets stress-tested. See concept file Section 4
//    for the exact syntax and the two pitfalls (compile error vs.
//    silent wrong-content bug).
// =====================================================================

class TextEditor : public EditorSession
{
private:
    CommandStack UndoStack;
    LogQueue ActionLog;

public:
    // TODO: constructor taking initial content — must explicitly call
    // EditorSession's constructor in the initializer list. Try omitting
    // it first on purpose and read the compiler error, then add it back.

    TextEditor(string ini) : EditorSession(ini) {}

    // TODO: void InsertText(int Position, string TextToInsert)
    //   - modify Content using string::insert (hint: cppreference.com,
    //     search "std::string::insert" — look at the (pos, str) overload)
    //   - build the REVERSE command (concept file Section 3 — what
    //     reverses an insert?) and Push it onto UndoStack
    //   - Enqueue a human-readable description onto ActionLog, e.g.
    //     "Inserted \"" + TextToInsert + "\" at position " + to_string(Position)
    //     (note: to_string() converts int -> string, needed to concatenate)

    void InsertText(int Position, string TextToInsert){
        Content.insert(Position, TextToInsert);
        Command Reverse = Command{ActionType::Delete, Position, TextToInsert};
        UndoStack.Push(Reverse);
        ActionLog.Enqueue("Inserted \" " + TextToInsert + " \" at position " + to_string(Position));
    }


    // TODO: void DeleteText(int Position, int Length)
    //   - before modifying Content, capture the substring being removed
    //     (hint: cppreference.com, search "std::string::substr")
    //   - modify Content using string::erase (hint: cppreference.com,
    //     search "std::string::erase")
    //   - build the REVERSE command and Push it onto UndoStack
    //   - Enqueue a log entry

    void DeleteText(int Position, int Length){
        string Save = Content.substr(Position, Length);
        Content.erase(Position, Length);
        Command Reverse = Command{ActionType::Insert, Position, Save};
        UndoStack.Push(Reverse);
        ActionLog.Enqueue("Deleted text at position: " + to_string(Position) + " of length: " + to_string(Length));
    }


    // TODO: void Undo()
    //   - if UndoStack IsEmpty(), print a message and return
    //   - Pop the top Command
    //   - switch on Command.Type:
    //       case ActionType::Insert -> apply as an insert (string::insert)
    //       case ActionType::Delete -> apply as a delete (string::erase)
    //   - Enqueue a log entry describing the undo

    void Undo(){
        if(UndoStack.IsEmpty()){
            cout << "UndoStack is Empty" << endl;
            return;
        }
        Command CurrentUndo = UndoStack.Pop();
        if(CurrentUndo.Type == ActionType::Insert){
            Content.insert(CurrentUndo.Position, CurrentUndo.Text);
            ActionLog.Enqueue("Undo text delete");
        }else{
            Content.erase(CurrentUndo.Position, CurrentUndo.Text.length());
            ActionLog.Enqueue("Undo text insert");
        }
    }

    // TODO: void PrintContent() const
    // TODO: void PrintLog() const   // delegate to ActionLog.PrintAll()
    
    void PrintContent() const{
        cout << GetContent() << endl;
    }

    void PrintLog() const{
        ActionLog.PrintAll();
    }
};


// =====================================================================
// 6. Test scenario — PREDICT the content after each step before you
//    run it. Write your predictions in a comment above each line.
// =====================================================================

int main()
{
    TextEditor Editor("Hello World");

    // Predict Content here:
    Editor.InsertText(5, " Beautiful");

    // Predict Content here:
    Editor.DeleteText(0, 6); // removes "Hello "

    Editor.PrintContent();   // what do you expect?

    // Predict Content here:
    Editor.Undo();
    Editor.PrintContent();

    // Predict Content here:
    Editor.Undo();
    Editor.PrintContent();   // should match the very first line's content

    Editor.PrintLog();       // should print in the ORDER things happened —
                              // this is the queue's job, not the stack's

    return 0;
}
