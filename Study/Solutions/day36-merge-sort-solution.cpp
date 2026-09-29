// Day 36 — Merge Sort SOLUTIONS
// Check only after attempting. If your version differs but passes, compare reasoning, not style.
// Compile: g++ -std=c++17 -Wall -Wextra day36-merge-sort-solution.cpp -o day36s && ./day36s

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

// ---------------------------------------------------------------------
// P1 — merge two sorted vectors
// ---------------------------------------------------------------------
std::vector<int> mergeTwo(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<int> out;
    out.reserve(a.size() + b.size());      // one allocation: we know the final size upfront

    std::size_t i = 0, j = 0;
    while (i < a.size() && j < b.size())   // stop as soon as EITHER side is exhausted
    {
        if (a[i] <= b[j]) out.push_back(a[i++]);   // <= : ties favour left -> stable
        else              out.push_back(b[j++]);
    }
    while (i < a.size()) out.push_back(a[i++]);    // leftovers (only one of these loops runs)
    while (j < b.size()) out.push_back(b[j++]);
    return out;
}

// ---------------------------------------------------------------------
// P2 — trace of [5, 1, 4, 2, 8, 0, 3]
//
// SPLIT:  [5 1 4 2 8 0 3]
//         [5 1 4]          [2 8 0 3]
//         [5] [1 4]        [2 8]    [0 3]
//             [1] [4]      [2] [8]  [0] [3]
// MERGE:      [1 4]        [2 8]    [0 3]
//         [1 4 5]          [0 2 3 8]
//         [0 1 2 3 4 5 8]
//
// Merge levels: 3. log2(7) ≈ 2.81 -> ceil = 3. Levels = ceil(log2 n).
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// P3 — merge sort with one shared buffer, half-open [lo, hi)
// ---------------------------------------------------------------------
void mergeRange(std::vector<int>& v, std::vector<int>& buf,
                std::size_t lo, std::size_t mid, std::size_t hi)
{
    std::size_t i = lo;    // front of left half  [lo, mid)
    std::size_t j = mid;   // front of right half [mid, hi)
    std::size_t k = lo;    // write position in buf

    while (i < mid && j < hi)
    {
        if (v[i] <= v[j]) buf[k++] = v[i++];
        else              buf[k++] = v[j++];
    }
    while (i < mid) buf[k++] = v[i++];
    while (j < hi)  buf[k++] = v[j++];

    for (std::size_t t = lo; t < hi; ++t) v[t] = buf[t];   // copy merged range back
}

void mergeSortRec(std::vector<int>& v, std::vector<int>& buf, std::size_t lo, std::size_t hi)
{
    if (hi - lo <= 1) return;                     // size 0 or 1: already sorted (safe: hi >= lo always)
    std::size_t mid = lo + (hi - lo) / 2;         // (lo+hi)/2 can overflow for large indices
    mergeSortRec(v, buf, lo, mid);
    mergeSortRec(v, buf, mid, hi);
    mergeRange(v, buf, lo, mid, hi);
}

void mergeSort(std::vector<int>& v)
{
    std::vector<int> buf(v.size());               // ONE allocation for the whole sort
    mergeSortRec(v, buf, 0, v.size());
}

// ---------------------------------------------------------------------
// P4 — stable sort of players by score
// ---------------------------------------------------------------------
struct Player
{
    std::string name;
    int score;
};

void mergePlayers(std::vector<Player>& v, std::vector<Player>& buf,
                  std::size_t lo, std::size_t mid, std::size_t hi)
{
    std::size_t i = lo, j = mid, k = lo;
    while (i < mid && j < hi)
    {
        // <= is the ENTIRE stability guarantee. With <, an equal-score right element
        // (e.g. Dee) would jump ahead of an equal-score left element (Ben).
        if (v[i].score <= v[j].score) buf[k++] = v[i++];
        else                          buf[k++] = v[j++];
    }
    while (i < mid) buf[k++] = v[i++];
    while (j < hi)  buf[k++] = v[j++];
    for (std::size_t t = lo; t < hi; ++t) v[t] = buf[t];
    // Note: this COPIES std::strings. Day 37 (std::move) shows how to avoid that cost.
}

void mergeSortPlayersRec(std::vector<Player>& v, std::vector<Player>& buf, std::size_t lo, std::size_t hi)
{
    if (hi - lo <= 1) return;
    std::size_t mid = lo + (hi - lo) / 2;
    mergeSortPlayersRec(v, buf, lo, mid);
    mergeSortPlayersRec(v, buf, mid, hi);
    mergePlayers(v, buf, lo, mid, hi);
}

void mergeSortPlayers(std::vector<Player>& v)
{
    std::vector<Player> buf(v.size());
    mergeSortPlayersRec(v, buf, 0, v.size());
}
// Bonus result with <: order becomes Dee, Ben, Cy, Ana. Still "sorted by score", but ties are reversed.
// A test that only checks scores would PASS. That's why the P4 assert checks names.

// ---------------------------------------------------------------------
// P5 — count inversions in O(n log n)
// Key insight: when right[j] is taken before left[i], right[j] is smaller than
// left[i] AND everything after left[i] in the left half (left half is sorted).
// That's (mid - i) inversions counted in O(1) instead of one by one.
// ---------------------------------------------------------------------
long long mergeCount(std::vector<int>& v, std::vector<int>& buf,
                     std::size_t lo, std::size_t mid, std::size_t hi)
{
    long long inv = 0;
    std::size_t i = lo, j = mid, k = lo;
    while (i < mid && j < hi)
    {
        if (v[i] <= v[j]) buf[k++] = v[i++];          // <= : equal values are NOT inversions
        else
        {
            inv += static_cast<long long>(mid - i);   // all remaining left elements > v[j]
            buf[k++] = v[j++];
        }
    }
    while (i < mid) buf[k++] = v[i++];
    while (j < hi)  buf[k++] = v[j++];
    for (std::size_t t = lo; t < hi; ++t) v[t] = buf[t];
    return inv;
}

long long countRec(std::vector<int>& v, std::vector<int>& buf, std::size_t lo, std::size_t hi)
{
    if (hi - lo <= 1) return 0;
    std::size_t mid = lo + (hi - lo) / 2;
    long long left  = countRec(v, buf, lo, mid);     // inversions entirely inside left
    long long right = countRec(v, buf, mid, hi);     // inversions entirely inside right
    long long cross = mergeCount(v, buf, lo, mid, hi); // pairs spanning both halves
    return left + right + cross;
}

long long countInversions(std::vector<int> v)
{
    std::vector<int> buf(v.size());
    return countRec(v, buf, 0, v.size());
}

// ---------------------------------------------------------------------
// P6 — merge sort on a singly linked list
// ---------------------------------------------------------------------
struct Node
{
    int val;
    Node* next;
};

Node* splitHalf(Node* head)
{
    // fast starts one ahead so that for 2 nodes: slow stays at node 1 -> split 1|1.
    // If fast started at head, a 2-node list splits 2|0 -> sortList recurses on the same list forever.
    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* second = slow->next;
    slow->next = nullptr;      // CUT: without this, the "first half" still runs to the end
    return second;
}

Node* mergeLists(Node* a, Node* b)
{
    Node dummy{0, nullptr};    // stack-allocated dummy: no new/delete needed
    Node* tail = &dummy;       // tail always points at the last node of the result
    while (a && b)
    {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else                  { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;    // attach the leftover chain in ONE step (no loop needed — it's already linked)
    return dummy.next;         // dummy removed the "is result empty yet?" special case
}

Node* sortList(Node* head)
{
    if (!head || !head->next) return head;   // 0 or 1 node
    Node* second = splitHalf(head);
    return mergeLists(sortList(head), sortList(second));
}

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

// ---------------------------------------------------------------------
// P7 — short answers
// a) log2(1024) = 10 split levels. Each level copies n elements -> ~10 * 1024 = 10,240 copies.
// b) Same Big-O: O(n log n). It still splits and merges every level. Comparisons drop somewhat
//    (each merge exhausts the left side early), but copies don't, and Big-O doesn't change.
//    Contrast: insertion sort is O(n) on sorted input. Merge sort gets no benefit from pre-sorted data.
// c) P3: O(n) buffer + O(log n) stack. P6: O(log n) stack only. Lists merge by relinking
//    existing nodes, so no copy destination is needed.
// d) If lo and hi are both near INT_MAX, lo + hi overflows (undefined behaviour for signed int),
//    and mid becomes garbage or negative. lo + (hi - lo) / 2 never exceeds hi.
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// P8 — edge-case harness
// ---------------------------------------------------------------------
void checkSorts(std::vector<int> input)
{
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());   // trusted reference implementation
    mergeSort(input);
    assert(input == expected);
}

void testMergeSortEdgeCases()
{
    checkSorts({});                          // empty: must not crash
    checkSorts({42});                        // single element
    checkSorts({7, 7, 7, 7});                // all duplicates
    checkSorts({1, 2, 3, 4, 5});             // already sorted
    checkSorts({5, 4, 3, 2, 1});             // reverse sorted
    checkSorts({-3, 10, 0, -3, 7, -100});    // negatives + duplicates
    checkSorts({2, 1});                      // smallest non-trivial split
}

int main()
{
    assert(mergeTwo({1,4,9}, {2,3,10,11}) == std::vector<int>({1,2,3,4,9,10,11}));
    assert(mergeTwo({}, {1,2}) == std::vector<int>({1,2}));

    { std::vector<int> v{38,27,43,3,9,82,10}; mergeSort(v);
      assert(v == std::vector<int>({3,9,10,27,38,43,82})); }

    { std::vector<Player> p{{"Ana",90},{"Ben",80},{"Cy",90},{"Dee",80}};
      mergeSortPlayers(p);
      assert(p[0].name=="Ben" && p[1].name=="Dee" && p[2].name=="Ana" && p[3].name=="Cy"); }

    assert(countInversions({2,4,1,3,5}) == 3);
    assert(countInversions({5,4,3,2,1}) == 10);   // n(n-1)/2 = 10: max possible for n=5
    assert(countInversions({1,2,3}) == 0);
    assert(countInversions({}) == 0);

    { Node* h = buildList({4,1,3,9,2}); h = sortList(h);
      assert(listToVector(h) == std::vector<int>({1,2,3,4,9})); freeList(h); }
    { Node* h = buildList({2,1}); h = sortList(h);
      assert(listToVector(h) == std::vector<int>({1,2})); freeList(h); }

    testMergeSortEdgeCases();

    std::cout << "All Day 36 checks passed.\n";
    return 0;
}
