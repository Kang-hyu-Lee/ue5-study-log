# Big-O Exercises — Day 9

For each code snippet, state the Big-O and briefly justify which rule(s) you applied. For the non-code questions, answer in your own words.

---

**1.**
```cpp
void PrintAll(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << '\n';
    }
}
```
Big-O? Which rule tells you why the loop body itself doesn't add to the order?
O(n) Rule 2: Drop the O(1) WRONG ANSWER: Rule 1: O(1) is a constant so we drop it

---

**2.**
```cpp
void PrintTwice(int arr[], int n) {
    for (int i = 0; i < n; i++) std::cout << arr[i] << '\n';
    for (int i = 0; i < n; i++) std::cout << arr[i] << '\n';
}
```
Big-O? Name the rule that lets you simplify this.
O(n) Rule 1: Drop the constant in O(2n)

---

**3.**
```cpp
void PrintPairs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << arr[i] << "," << arr[j] << '\n';
        }
    }
}
```
Big-O? How does this differ structurally from #2, even though both have "two loops"?
O(n^2) Rule 5: this is a nested loop, and for every element in index arr[i] we iterate arr with j, so for each outer loop we run the inner loop n times
---

**4.**
```cpp
void MixedWork(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << arr[i] + arr[j];
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
    }
}
```
Big-O? Show the intermediate step (before simplifying) and the rule that simplifies it.
O(n^2) So this is first Rule 5 to find O(n^2) then by Rule 4 we add O(n) so O(n^2) + O(n), but by Rule 2 we drop O(n) so O(n^2)
---

**5.**
```cpp
void CompareArrays(int arrA[], int sizeA, int arrB[], int sizeB) {
    for (int i = 0; i < sizeA; i++) std::cout << arrA[i];
    for (int j = 0; j < sizeB; j++) std::cout << arrB[j];
}
```
Big-O? Why can't you simplify this to a single `n` term?
O(sizeA + sizeB) Rule 3: We don't know the actual values for sizeA and sizeB and those two arrays are unrelated groups 
WRONG ANSWER: Even if we knew the values it wouldn't change the answer because there is no guarantee in the code that says they'll stay related as inputs change
---

**6.**
Rank these from cheapest to most expensive growth: `O(n²)`, `O(log n)`, `O(1)`, `O(n log n)`, `O(n)`.
O(1), O(log n), O(n), O(n log n), O(n^2)
---

**7.**
Short answer: a teammate writes `O(2n)` in a code review comment. Explain, in your own words, why this gets simplified to `O(n)` — what does Big-O notation actually care about that makes the `2` irrelevant?
Because BigO O notation cares about the growth shape, so when n is a very large number, the constant does not affect the shape of the growth meaning we can drop it