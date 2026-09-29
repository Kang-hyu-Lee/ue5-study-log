// Day 36 — Merge Sort exercises
// Rules: type everything yourself. No looking at the solution file until you've attempted on paper + in code.
// Uncomment each test call in main() as you finish that problem.
// Compile: g++ -std=c++17 -Wall -Wextra day36-merge-sort-exercise.cpp -o day36 && ./day36

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

// =====================================================================
// P1 — Merge two already-sorted vectors into one sorted vector.
// Hint: two indices i, j. Compare fronts, push the smaller, advance.
// Hint: after the main loop, ONE side still has leftovers — copy them.
// Hint: use <= so ties take from `a` (stability — matters in P4).
// =====================================================================
std::vector<int> mergeTwo(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<int> merged;

    std::size_t i = 0;
    std::size_t j = 0;

    merged.reserve(a.size() + b.size());

    while(i < a.size() && j < b.size()){
        if(a[i] <= b[j]){
            merged.push_back(a[i++]);
        }else{
            merged.push_back(b[j]);
            j++;
        }
    }

    while(i < a.size()){
        merged.push_back(a[i]);
        i++;
    }

    while(j < b.size()){
        merged.push_back(b[j]);
        j++;
    }

    return merged;
}

// =====================================================================
// P2 — PAPER ONLY (write the answer in this comment block).
// Trace merge sort on [5, 1, 4, 2, 8, 0, 3].
// Show every split, then every merge, like the concept file's trace.
// Then answer: how many merge LEVELS did you get? Compare to log2(7).
//
// Your trace:
// SPLIT (mid = lo + (hi-lo)/2, half-open ranges [lo,hi))
// [5, 1, 4, 2, 8, 0, 3]
// [5, 1, 4]    [2, 8, 0, 3]
// [5]    [1, 4]    [2, 8]    [0, 3]
//        [1] [4]    [2] [8]    [0] [3]
//
// MERGE (bottom-up as recursion returns)
//        [1, 4]    [2, 8]    [0, 3]
// [1, 4, 5]    [0, 2, 3, 8]
// [0, 1, 2, 3, 4, 5, 8]
// 3 Levels
// =====================================================================

// =====================================================================
// P3 — In-place-style merge sort on a vector using ONE shared buffer.
// Range convention: half-open [lo, hi).
// Hint: base case is "size 0 or 1" -> hi - lo <= 1.
// Hint: mid = lo + (hi - lo) / 2   (why not (lo+hi)/2 ? answer in a comment)
// Hint: mergeRange writes into buf[lo..hi) then copies back into v[lo..hi).
// =====================================================================
void mergeRange(std::vector<int>& v, std::vector<int>& buf,
                std::size_t lo, std::size_t mid, std::size_t hi)
{
    std::size_t i = lo;
    std::size_t j = mid;
    std::size_t k = lo;

    while(i < mid && j < hi){
        if(v[i] <= v[j]){
            buf[k++] = v[i++];
        }else{
            buf[k++] = v[j++];
        }
    }

    while(i < mid){
        buf[k++] = v[i++];
    }

    while(j < hi){
        buf[k++] = v[j++];
    }

    assert(k == hi);

    for(std::size_t t=lo; t<hi; ++t){
        v[t] = buf[t];
    }
}

void mergeSortRec(std::vector<int>& v, std::vector<int>& buf, std::size_t lo, std::size_t hi)
{
    if(hi-lo <= 1){
        return;
    }

    std::size_t mid = lo + (hi - lo)/2;
    
    mergeSortRec(v, buf, lo, mid);
    
    mergeSortRec(v, buf, mid, hi);

    mergeRange(v, buf, lo, mid, hi);

}

void mergeSort(std::vector<int>& v)
{
    std::vector<int> buf(v.size());

    mergeSortRec(v, buf, 0, v.size());
}

// =====================================================================
// P4 — Stability. Sort players by score ASCENDING with merge sort,
// keeping original order for equal scores.
// Input:  {Ana,90} {Ben,80} {Cy,90} {Dee,80}
// Expect: {Ben,80} {Dee,80} {Ana,90} {Cy,90}
// Hint: same structure as P3, but compare .score.
// Bonus: change <= to < in your merge, re-run, and write down what breaks.
// =====================================================================
struct Player
{
    std::string name;
    int score;
};

void mergePlayersRange(std::vector<Player>& v, std::vector<Player>& buf, std::size_t lo, std::size_t mid, std::size_t hi){
    std::size_t i = lo;
    std::size_t j = mid;
    std::size_t k = lo;

    while(i < mid && j < hi){
        if(v[i].score <= v[j].score){
            buf[k++] = v[i++];
        }else{
            buf[k++] = v[j++];
        }
    }

    while(i < mid){
        buf[k++] = v[i++];
    }

    while(j < hi){
        buf[k++] = v[j++];
    }

    for(std::size_t t = lo; t < hi; ++t){
        v[t] = buf[t];
    }
}

void mergePlayersRec(std::vector<Player>& v, std::vector<Player>& buf, std::size_t lo, std::size_t hi){
    if(hi - lo <= 1){
        return;
    }

    std::size_t mid = lo + (hi-lo)/2;
    mergePlayersRec(v, buf, lo, mid);
    mergePlayersRec(v, buf, mid, hi);

    mergePlayersRange(v, buf, lo, mid, hi);
}

void mergeSortPlayers(std::vector<Player>& v)
{
    std::vector<Player> buf(v.size());
    mergePlayersRec(v, buf, 0, v.size());
}

// =====================================================================
// P5 — Count inversions: pairs (i < j) where v[i] > v[j].
// Brute force is O(n^2). Do it in O(n log n) by modifying the merge.
// Hint: when you take an element from the RIGHT half, how many elements
//       still waiting in the LEFT half are bigger than it? (all of them — why?)
// Hint: use long long for the count (n=100k can exceed int range).
// Checks: [2,4,1,3,5] -> 3    [5,4,3,2,1] -> 10    [1,2,3] -> 0
// =====================================================================
long long mergeCount(std::vector<int>& v, std::vector<int>& buf, std::size_t lo, std::size_t mid, std::size_t hi)
{
    std::size_t i = lo;
    std::size_t j = mid;
    std::size_t k = lo;
    long long count = 0;

    while(i < mid && j < hi){
        if(v[i] <= v[j]){
            buf[k++] = v[i++];
        }else{
            buf[k++] = v[j++];
            count += static_cast<long long> (mid-i);
        }
    }

    while(i < mid){
        buf[k++] = v[i++];
    }

    while(j < hi){
        buf[k++] = v[j++];
    }

    assert(k == hi);

    for(std::size_t t=lo; t<hi; ++t){
        v[t] = buf[t];
    }

    return count;
}

long long countRec(std::vector<int>& v, std::vector<int>& buf, std::size_t lo, std::size_t hi)
{
    if(hi - lo <= 1) return 0;

    std::size_t mid = lo + (hi-lo)/2;

    long long left = countRec(v, buf, lo, mid);

    long long right = countRec(v, buf, mid, hi);

    long long cross = mergeCount(v, buf, lo, mid, hi);

    return left + right + cross;

}

long long countInversions(std::vector<int> v) // by value on purpose: we sort a copy
{
    std::vector<int> buf(v.size());
    return countRec(v, buf, 0, v.size());
}

// =====================================================================
// P6 — Merge sort a singly linked list (ties to Day 11-12).
// Hint 1: find the middle with slow/fast pointers; CUT the list (slow->next = nullptr).
//         Start fast at head->next so a 2-node list splits 1|1, not 2|0 (infinite recursion!).
// Hint 2: merge by RELINKING nodes, not creating new ones. Use a dummy head node.
// Hint 3: base case: empty list or single node.
// =====================================================================
struct Node
{
    int val;
    Node* next;
};

Node* splitHalf(Node* head)          // returns head of second half, cuts the first
{
    Node* slow = head;
    Node* fast = head->next;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* secHead = slow->next;
    slow->next = nullptr;
    return secHead;
}

Node* mergeLists(Node* a, Node* b)
{
    Node dummy{0, nullptr};
    Node* tail = &dummy;
    while(a!=nullptr && b!=nullptr){
        if(a->val <= b->val){
            tail->next = a;
            a = a->next;
        }else{
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a ? a:b;
    return dummy.next;
}

Node* sortList(Node* head)
{
    if(!head || !head->next) return head;
    Node* rightHead = splitHalf(head);
    Node* left = sortList(head);
    Node* right = sortList(rightHead);

    return mergeLists(left, right);
    
}

// helpers — already written for you (not the point of today)
Node* buildList(const std::vector<int>& vals)
{
    Node* head = nullptr;
    for (auto it = vals.rbegin(); it != vals.rend(); ++it) head = new Node{*it, head};
    return head;
}
std::vector<int> listToVector(Node* head)
{
    std::vector<int> out;
    for (Node* n = head; n; n = n->next) out.push_back(n->val);
    return out;
}
void freeList(Node* head)
{
    while (head) { Node* next = head->next; delete head; head = next; }
}

// =====================================================================
// P7 — Short answers (write in this comment block).
// a) n = 1024. How many split levels? Upper bound on total element copies?
// b) Merge sort on an ALREADY sorted array of 1M ints: faster than on random input? Big-O?
// c) Auxiliary space for P3 vs P6. Why the difference?
// d) Why is (lo + hi) / 2 dangerous with int indices?
//
// Answers:
// a) 10 levels, upperbound is 1024*10 so 10 240
// b) No merge sort is O(n log n) no matter what because there is no premature exit it runs the entire sort everytime (every element is still copied even if there are fewer comparisons)
// c) P3 had a buffer that we first built the sorted array on then copied the entire array back (O(n) because O(n) for buf + O(log n) for recursion stack), whereas P6 was a relinking existing nodes so no copying (O(log n) for recursion stack)
// d) because lo+hi is done first and this could go out of int bounds which is undefined behaviour
//  
// =====================================================================

// =====================================================================
// P8 — Edge-case test harness. Write testMergeSortEdgeCases() that runs
// mergeSort on: empty, one element, all duplicates, already sorted,
// reverse sorted, negatives mixed with positives.
// Hint: copy input, std::sort the copy as the "expected", assert equality.
// =====================================================================
void checkSorts(std::vector<int> v){
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    mergeSort(v);
    assert(expected == v);

}
void testMergeSortEdgeCases()
{
    checkSorts({});
    checkSorts({42});
    checkSorts({7, 7, 7, 7});
    checkSorts({1, 2, 3, 4, 5});
    checkSorts({5, 4, 3, 2, 1});
    checkSorts({-3, 10, 0, -3, 7, -100});
    checkSorts({2, 1});
}

int main()
{
    assert(mergeTwo({1,4,9}, {2,3,10,11}) == std::vector<int>({1,2,3,4,9,10,11}));      // P1
    assert(mergeTwo({},{}) == std::vector<int>{});
    assert(mergeTwo({},{1,2}) == std::vector<int>({1,2}));

    { std::vector<int> v{38,27,43,3,9,82,10}; mergeSort(v);                              // P3
        assert(v == std::vector<int>({3,9,10,27,38,43,82})); }

    { std::vector<Player> p{{"Ana",90},{"Ben",80},{"Cy",90},{"Dee",80}};                 // P4
        mergeSortPlayers(p);
        assert(p[0].name=="Ben" && p[1].name=="Dee" && p[2].name=="Ana" && p[3].name=="Cy");}
     assert(countInversions({2,4,1,3,5}) == 3);                                           // P5
     assert(countInversions({5,4,3,2,1}) == 10);
     assert(countInversions({1,2,3}) == 0);

     { Node* h = buildList({4,1,3,9,2}); h = sortList(h);                                 // P6
       assert(listToVector(h) == std::vector<int>({1,2,3,4,9})); freeList(h); }

     testMergeSortEdgeCases();                                                             // P8

    std::cout << "Day 36 checks done.\n";
    return 0;
}
