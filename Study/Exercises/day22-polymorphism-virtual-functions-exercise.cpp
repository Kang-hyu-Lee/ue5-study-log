// Day 22 Exercise — Polymorphism & Virtual Functions
// Type every line yourself. Read day22-polymorphism-virtual-functions-concept.md first.
// Build and test each problem before moving to the next.

#include <iostream>
#include <string>
using namespace std;

// =====================================================================
// PROBLEM 1 — Make PrintContent virtual and override it
//
// Copy your EditorSession + TextEditor classes from Day 20 (simplified
// here — just Content + PrintContent, you don't need the undo system
// for this exercise).
//
// TODO:
//   - Add `virtual` to EditorSession::PrintContent()
//   - In TextEditor, override it with `override` keyword, printing
//     "[TextEditor] " before the content
//   - In main(), create an EditorSession* pointing to a TextEditor,
//     call PrintContent() through the base pointer, confirm you get
//     the TextEditor version (predict the output BEFORE running)
// =====================================================================
class EditorSession
{
protected:
    string Content;

public:
    EditorSession(string ini):Content(ini) { PrintContent(); };

    virtual ~EditorSession(){
        cout << "EditorSession destroyed" << endl;
    }

    virtual void PrintContent() const {
        cout << Content << endl;
    }
};

class TextEditor : public EditorSession
{
public:
    TextEditor(string ini) : EditorSession(ini) {}

    ~TextEditor(){
        cout << "TextEditor destroyed" << endl;
    }
    
    void PrintContent() const override{
        cout << "[TextEditor]" << Content << endl;
    }
};

// =====================================================================
// PROBLEM 2 — Add a second derived class
//
// TODO:
//   - Create class CodeEditor : public EditorSession
//   - Override PrintContent() to print "[CodeEditor] " before content
//   - In main(), create an array/vector of EditorSession* containing
//     one TextEditor and one CodeEditor, loop through it, call
//     PrintContent() on each through the base pointer — confirm each
//     one prints its OWN version, not the base version
// =====================================================================
class CodeEditor : public EditorSession
{
public:
    CodeEditor(string ini) : EditorSession(ini) {}
    
    void PrintContent() const override{
        cout << "[CodeEditor]" << Content << endl;
    }
};

// =====================================================================
// PROBLEM 3 — Virtual destructor
//
// TODO:
//   - Give EditorSession a destructor that prints "EditorSession destroyed"
//   - Give TextEditor a destructor that prints "TextEditor destroyed"
//   - First, WITHOUT marking EditorSession's destructor virtual: create
//     an EditorSession* pointing to a TextEditor, delete it, observe
//     which destructor(s) print
//   - Then add `virtual` to EditorSession's destructor, repeat the same
//     delete, observe the difference
//   - Write a one-line comment explaining what changed and why
// =====================================================================
// the virtual keyword made it check the actual type at runtime to reach for the TextEditor destructor

// =====================================================================
// PROBLEM 4 — Object slicing, reproduced on purpose
//
// TODO:
//   - Write a free function `void ShowIt(EditorSession Session)` that
//     takes an EditorSession BY VALUE (not pointer/reference) and calls
//     Session.PrintContent()
//   - Call ShowIt(MyTextEditor) where MyTextEditor is an actual TextEditor
//     object (not a pointer)
//   - Predict which version prints BEFORE running, then run it and
//     confirm. Write a one-line comment explaining why, referencing
//     the concept file's Section 3
// =====================================================================

void ShowIt(EditorSession Session){
    Session.PrintContent();
}
//it will create a copy of input as a EditorSession type even if I input a TextEditor so will follow that PrintContent() from EditorSession

// =====================================================================
// PROBLEM 5 — Constructor virtual-call edge case
//
// TODO:
//   - In EditorSession's constructor, call PrintContent() (the virtual
//     function) from inside the constructor body
//   - Predict: when constructing a TextEditor, does this call
//     TextEditor's override or EditorSession's own version? Write your
//     prediction as a comment BEFORE running, then run and confirm
//     against the concept file's Section 6
// =====================================================================
// In this case TextEditor hasn't been constructed yet because we are still in the EditorSession's constructor so it will print as a EditorSession

int main()
{
    // Build your test scenarios for Problems 1–5 here, one at a time.
    // Predict output in a comment above each call before running it.
    EditorSession* Ptr = new TextEditor("Hello World");
    Ptr->PrintContent();

    EditorSession* Arr[2];
    EditorSession* Ptr2 = new CodeEditor("Hello World");

    Arr[0] = Ptr;
    Arr[1] = Ptr2;

    for(int i=0; i<2; i++){
        Arr[i]->PrintContent();
    }

    delete Ptr;
    delete Ptr2;
    
    TextEditor Editor("Hello World");
    ShowIt(Editor);
    return 0;
}
