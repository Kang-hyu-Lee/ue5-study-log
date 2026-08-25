// Day 22 Solutions — Polymorphism & Virtual Functions
// Compare against your own attempt AFTER you've tried each problem yourself.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// =====================================================================
// PROBLEM 1
// =====================================================================
class EditorSession
{
protected:
    string Content;

public:
    EditorSession(string Ini) : Content(Ini) {}

    virtual void PrintContent() const   // virtual = enables dynamic dispatch
    {
        cout << Content << endl;
    }

    virtual ~EditorSession()   // Problem 3 — see note below
    {
        cout << "EditorSession destroyed" << endl;
    }
};

class TextEditor : public EditorSession
{
public:
    TextEditor(string Ini) : EditorSession(Ini) {}

    void PrintContent() const override
    {
        cout << "[TextEditor] " << Content << endl;
    }

    ~TextEditor()
    {
        cout << "TextEditor destroyed" << endl;
    }
};

// =====================================================================
// PROBLEM 2
// =====================================================================
class CodeEditor : public EditorSession
{
public:
    CodeEditor(string Ini) : EditorSession(Ini) {}

    void PrintContent() const override
    {
        cout << "[CodeEditor] " << Content << endl;
    }
};

// =====================================================================
// PROBLEM 4
// =====================================================================
void ShowIt(EditorSession Session)   // BY VALUE — slices the object
{
    Session.PrintContent();
    // Always prints the EditorSession version. Passing by value copies
    // only the EditorSession portion of the object — the TextEditor
    // part (and its vtable pointer identifying it as a TextEditor) is
    // discarded. Polymorphism requires a pointer or reference; slicing
    // happens because a plain value copy can't preserve "what derived
    // type is this really."
}

int main()
{
    // ---- Problem 1 ----
    // Predict: "[TextEditor] Hello World" — Ptr's declared type is
    // EditorSession*, but virtual dispatch resolves to the actual
    // object's type (TextEditor) at runtime.
    EditorSession* Ptr = new TextEditor("Hello World");
    Ptr->PrintContent();

    // ---- Problem 2 ----
    // Predict: each prints its own override, in order — polymorphism
    // through a container of base pointers is the whole point of the
    // pattern (this is effectively how UE5 iterates actors generically).
    vector<EditorSession*> Sessions;
    Sessions.push_back(new TextEditor("doc.txt content"));
    Sessions.push_back(new CodeEditor("int main() {}"));
    for (EditorSession* S : Sessions)
    {
        S->PrintContent();
    }
    for (EditorSession* S : Sessions)
    {
        delete S;   // safe because destructor is virtual (Problem 3)
    }

    // ---- Problem 3 ----
    // WITHOUT virtual destructor: delete through EditorSession* would
    // print ONLY "EditorSession destroyed" — TextEditor's destructor
    // never runs (undefined behavior technically, but commonly this is
    // the observed symptom). Any resources TextEditor owns leak.
    // WITH virtual destructor (as written above): delete prints BOTH
    // "TextEditor destroyed" then "EditorSession destroyed" — derived
    // destructor runs first, then the base's, matching construction
    // order in reverse (same rule you verified empirically on Day 19).
    EditorSession* Ptr2 = new TextEditor("test");
    delete Ptr2;

    // ---- Problem 4 ----
    // Predict: "Hello World" (EditorSession's plain version), NOT
    // "[TextEditor] Hello World" — confirmed by ShowIt's implementation
    // above. Slicing happened at the moment of the by-value function
    // call.
    TextEditor MyTextEditor("Hello World");
    ShowIt(MyTextEditor);

    return 0;
}

// ---- Problem 5 note (no separate class needed to demonstrate) ----
// If EditorSession's constructor called PrintContent() in its body:
// it would call EditorSession::PrintContent(), NOT TextEditor's
// override — even while constructing a TextEditor. At that point in
// construction, the TextEditor portion of the object doesn't exist
// yet (base constructors run first), so the vtable is still set up
// as "plain EditorSession." Same logic applies in reverse for
// destructors: by the time ~EditorSession() runs, TextEditor's part
// is already destroyed, so any virtual call there also resolves to
// EditorSession's own version.
