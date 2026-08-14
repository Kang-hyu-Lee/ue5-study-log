# Linked Lists Intro — Exercises

Work these on paper or in a .cpp scratch file — whichever makes tracing
pointers easier for you. Type any code yourself.

1. **Build a 4-node list by hand.** Using the `Node` struct and pattern from
   `linked-lists-intro.md` Section 1, declare four `Node` variables holding
   `5, 15, 25, 35` and link them in that order with a `Head` pointer. Write
   out (in comments or on paper) the address-chain: what does `Head` point
   to, what does `Head->Next` point to, all the way to the tail.

   struct Node{
      int Data;
      Node* Next;
   };

   Node A{5, nullptr};
   Node B{15, nullptr};
   Node C{25, nullptr};
   Node D{35, nullptr};

   Node* Head = &A;
   A.Next = &B;
   B.Next = &C;
   C.Next = &D;

   //Head points to Node A -> Node B-> Node C-> Node D-> nullptr

2. **Traverse and sum.** Using the list from #1, write a loop starting at
   `Head` that adds up all four `Data` values and prints the total. Your
   loop's stopping condition needs to check for one specific pointer value —
   name it before you write the loop.
   
   //it needs to check for nullptr
   Node* Current = Head;
   int Sum = 0;
   while(Currrent != nullptr){
      Sum += Current->Data;
      Current = Current->Next;
   }
   std::cout << "Sum = " << Sum;

3. **Empty list trace.** Suppose `Head` is `nullptr` (no nodes at all). Trace
   through your traversal loop from #2 by hand, line by line — what happens
   on the very first check? Would your loop crash, loop forever, or exit
   cleanly? If it wouldn't exit cleanly as written, note what condition
   needs to be checked first.

   //It would exit the loop right away with condition Current != nullptr then would print Sum = 0

4. **Array vs linked list, applied.** You have a game inventory that gets
   items added to the *front* constantly (most-recent-first display) and
   almost never accessed by index. Which structure — array or linked list —
   fits better, and why, in terms of Big-O for the front-insert operation
   specifically? (Reference the comparison table in the concept file.)

   //Linked list because Arrays would require a whole shift whereas linked list would only require you to connect the next of the new item to the current head then assign this new item as head
   //Another plus is that linked lists can grow one item at a time whereas arrays have a fixed size

5. **Find the break.** Below is a broken 3-node build attempt. Identify the
   bug (don't fix it yet — just explain in one line what will happen when
   this is traversed from `Head`):
   ```cpp
   Node X{1, nullptr};
   Node Y{2, nullptr};
   Node Z{3, nullptr};
   X.Next = &Y;
   // Y.Next = &Z;   <- this line is missing
   Node* Head = &X;
   ```
   //if there is a nullptr check it would work just that we'll never reach node Z because it hasn't been inserted into the linked list
   //(Better wording) The traversal loop already checks for nullptr, so this won't crash but instead it'll walk X -> Y, find Y->Next is still nullptr from its initializer, and stop there. Z is just never reached; it's a silent logic bug, not a memory-safety one

6. **Cycle spot-check (conceptual only, no timed solving yet).** If a
   node's `Next` accidentally points back to an earlier node in the same
   list instead of `nullptr` at the tail, what happens to a naive traversal
   loop that only checks `CurrentNode != nullptr`? You don't need to solve
   cycle detection today (that's a classic timed-interview problem for
   later) — just describe the failure mode in one sentence.

   //this would lead to an infinite loop because it would just keep cycling from that earlier node forever