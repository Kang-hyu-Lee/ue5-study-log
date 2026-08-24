# Day 20 — Portfolio: Undo System (Stacks + Queues + Inheritance)

## 1. Why This Project

Every editor with Ctrl+Z — including the Unreal Editor itself — is built on this exact pattern:
record just enough info to *reverse* an action, keep those records in a stack, replay them
on undo. Unreal's internal name for it is `FScopedTransaction`. You are building a simplified
version of a real engine subsystem, not a toy exercise.

## 2. Data Structure Choice — Why Stack, Why Queue

| Structure | Access pattern | What it stores today | Why this shape fits |
|---|---|---|---|
| Stack (LIFO) | last in, first out | Undo history | The *most recent* edit is always the one you undo first. You never want to undo edit #2 before edit #5. |
| Queue (FIFO) | first in, first out | Action log (for display) | A log is read top-to-bottom in the order things happened. If it were a stack, your log would print backwards. |

Same event stream, two structures, because they answer two different questions:
"what do I reverse next?" (stack) vs. "what happened, in order?" (queue).

## 3. The Command Idea (lite version — no polymorphism yet)

Naive approach: store a full copy of the text before every edit. Works, but wastes memory —
a 10,000-character document edited 500 times = 500 copies of ~10,000 characters.

Better: store only the **diff**, and only enough info to reverse it. This is a `Command`:

```cpp
enum class ActionType { Insert, Delete };

struct Command
{
    ActionType Type;
    int Position;
    std::string Text;
};
```

**New syntax: `enum class`.** An enum is a type that can only hold one of a fixed set of
named values. `enum class` (vs. plain `enum`) forces you to write the full name
(`ActionType::Insert`, not just `Insert`) — prevents accidental mixing with unrelated enums
or plain integers. Always prefer `enum class` in new code; plain `enum` is a legacy C-ism.

**Worked example — the reversal logic (do this on paper before touching code):**

Starting content: `"Hello World"`

Action: `InsertText(5, " Beautiful")` → content becomes `"Hello Beautiful World"`
- To reverse an **insert**, you **delete** the same text at the same position.
- Command pushed to undo stack: `{ Delete, 5, " Beautiful" }`

Action: `DeleteText(0, 6)` (deletes `"Hello "`) → content becomes `"Beautiful World"`
- To reverse a **delete**, you **insert** the text you removed, at the same position.
- Command pushed to undo stack: `{ Insert, 0, "Hello " }`

Undo stack right now (top → bottom): `{ Insert, 0, "Hello " }`, `{ Delete, 5, " Beautiful" }`

Call `Undo()`:
- Pop `{ Insert, 0, "Hello " }` → apply it → content becomes `"Hello Beautiful World"` again.

Call `Undo()` again:
- Pop `{ Delete, 5, " Beautiful" }` → apply it → content becomes `"Hello World"`. Back to start.

**Pitfall:** the command you *store* is the OPPOSITE action of what the user just did. This
trips almost everyone up on first attempt — write the reversal rule down before coding.

## 4. Architecture: Why Split Into Two Classes

```
EditorSession          (base — "a thing that holds content")
      ^
      |  is-a
      |
  TextEditor            (derived — adds undo/redo + logging behavior)
```

`EditorSession` models the generic idea of "something with a content buffer" — deliberately
minimal, so it *could* later be reused for something that isn't a text editor (a config
editor, a scene-name editor, whatever). `TextEditor` adds the parts specific to text editing:
the undo stack and the action log. This is a real architectural boundary, not busywork —
separating "what data exists" from "what behavior operates on it" is a pattern you'll use
constantly in UE5 (base Actor vs. derived gameplay classes).

```cpp
class EditorSession
{
protected:
    std::string Content;

public:
    EditorSession(std::string InitialContent) : Content(InitialContent) {}
    std::string GetContent() const { return Content; }
};

class TextEditor : public EditorSession
{
private:
    CommandStack UndoStack;
    LogQueue ActionLog;

public:
    TextEditor(std::string InitialContent) : EditorSession(InitialContent) {}
    // ... methods below
};
```

**Mechanism — explicit base constructor call:** `TextEditor(std::string InitialContent) :
EditorSession(InitialContent) {}` — the part after the colon runs BEFORE the derived
constructor's own body. A derived object physically contains its base part as a subobject;
that subobject must be fully constructed first. `EditorSession` only has a *parameterized*
constructor (no default `EditorSession()`), so `TextEditor` MUST call it explicitly — there's
no implicit fallback the compiler can reach for.

**Pitfall (compile-time):** delete the `: EditorSession(InitialContent)` part entirely, and
this won't compile — "no default constructor exists for EditorSession." Try this yourself
once during typing to see the exact error.

**Edge case (silent bug, not a compile error):** if `EditorSession` DID also have a
default constructor (`EditorSession() : Content("") {}`), then forgetting the explicit call
would NOT fail to compile — it would silently call the default instead, and `Content` would
start as `""` instead of your `InitialContent`. No error, just wrong behavior. This is the
dangerous version of the mistake — always check what you intended to initialize actually got
initialized.

## 5. Why No Virtual Functions Here (and why that's correct for today)

You might expect `Command` itself to be a class hierarchy (`InsertCommand`, `DeleteCommand`
each deriving from a `Command` base) since you just learned inheritance. Deliberately NOT
doing that today: calling behavior correctly through a base class pointer/reference requires
the `virtual` keyword, which isn't taught until Day 22. Without `virtual`, calling a function
through a base pointer runs the BASE version regardless of the actual derived type — a
function-call flavor of the object slicing you already saw. `Command` stays a plain data
struct with a `switch` on `ActionType` instead — correct, taught-material-only design for
where you are right now. Day 22 will show you why the polymorphic version is better once you
have the tool for it.

## 6. Adapting Your Existing Stack/Queue (no templates yet — Day 24)

You already hand-built an array-based stack and a linked-list queue (Day 16). Templates
(writing one generic version reusable for any type) aren't taught until Day 24, so today you
adapt those same structures to new, specific types by copying the pattern and swapping the
element type:

- `ArrayStack<int>`-style → `CommandStack` holding `Command` instead of `int`.
- Linked-list `Queue<int>`-style → `LogQueue` holding `std::string` instead of `int`.

This means writing the structure twice with different types is expected and correct at this
stage — it's not wasted effort, it's exactly the pain that motivates templates when you get
there.

## 7. New stdlib syntax needed today (not taught yet — hint comments mark these in the
exercise file)

- `std::string::insert(pos, str)` — inserts `str` starting at index `pos`.
- `std::string::erase(pos, count)` — removes `count` characters starting at index `pos`.
- `std::string::substr(pos, count)` — returns a NEW string copy of `count` characters
  starting at `pos` (does not modify the original).

Look these up on cppreference.com when you hit the hint comment in the exercise file —
practice using the reference the way you will on the job.

## 8. Portfolio / Interview Framing

This is a legitimate talking point: "I built a text-editing undo system using a hand-rolled
stack for undo history and a queue for a chronological action log, with a base/derived class
split separating generic session state from editor-specific behavior." That's a real answer
to "tell me about a project," and it previews the Command design pattern used in production
editor tooling — including Unreal's own transaction system.
