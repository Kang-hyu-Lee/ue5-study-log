// Day 29 -- Hashing Pt. 1 -- Exercises
// No C++ hash map syntax needed yet (std::unordered_map is Day 30's syntax lesson).
// These are conceptual/tracing problems -- work on paper first, then type your reasoning
// as comments under each problem. Don't peek at the solution file until you've attempted all 5.

/*
Problem 1 -- Hash & Bucket Trace
Hash function: hash(key) = (sum of ASCII codes of characters) % 7
Keys to insert IN ORDER: "bat", "cab", "no"

a) Compute the hash and bucket index for each key.
   (ASCII: a=97, b=98, c=99, o=111, n=110, t=116)
b) Identify any collisions.
c) Using CHAINING, describe in words what buckets 0 through 6 contain after all three inserts.
*/
/*
a) bat = 98 + 97 + 116 = 311 % 7 = 3
   cab = 99 + 98 + 97 = 294 % 7 = 0
   no = 110 + 111 = 221 % 7 = 4

b) There are no collisions

c) 0 - cab
   1 -
   2 -
   3 - bat
   4 - no
   5 -
   6 - 
*/


/*
Problem 1b -- CORRECTED: Actual Collision Trace
(Problem 1's key set produces ZERO collisions -- bat/cab/no hash to 3/0/4, all different
buckets. That's a gap in the original exercise, not an error in your math if you got those
same numbers. Use THIS key set instead -- verified to actually collide -- for 1c/2 below.)

Same hash function: hash(key) = (sum of ASCII codes) % 7
Keys to insert IN ORDER: "cab", "bag", "fed", "ace", "add"
(ASCII: a=97, b=98, c=99, d=100, e=101, f=102, g=103)

a) Compute the hash and bucket index for EACH of the 5 keys.
b) Identify which two keys collide (same bucket).
c) Using CHAINING, describe what buckets 0-6 contain after all five inserts.
*/
/*
a) cab = 99 + 97 + 98 = 294 % 7 = 0
   bag = 98 + 97 + 103 = 298 % 7 = 4
   fed = 102 + 101 + 100 = 303 % 7 = 2
   ace = 97 + 99 + 101 = 297 % 7 = 3
   add = 97 + 100 + 100 = 297 % 7 = 3

b) ace and add collide

c) 0 - cab
   1 -
   2 - fed
   3 - ace -> add
   4 - bag
   5 -
   6 - 
*/

/*
Problem 2 -- Collision Resolution Comparison
Using the KEYS FROM PROBLEM 1b (cab, bat, act) -- these actually collide:

a) If using OPEN ADDRESSING with linear probing (step = +1, wrap around at 7), where does the
   colliding key actually land instead of its natural bucket?
b) In one sentence: why can't open addressing just leave a colliding key in its "natural" bucket
   the way chaining does?
*/
/*
a) 3 - ace
   5 - add
   So because ace is already in bucket 3 add has to be placed in the next empty bucket which is 5 because bag is currently in 4 meaning it can't be placed there

b) Because open addressing is limited to a single value per bucket unlike chaining which is just a linked list so can be added indefinitely
*/


/*
Problem 3 -- Worst Case By Design
Describe (in words, no need to compute real ASCII values) a hash function that is technically
VALID -- it always returns some bucket index in range -- but performs terribly for a table
storing English words. What property of the function makes it bad?
*/
// A function that hashes using the length(word) % table_size because a lot of the words in English are clusteres around a certain number of letters, meaning that there is a high chance of collision


/*
Problem 4 -- Real-World Mapping (Hash Map vs Tree)
Give ONE gamedev example (not from the concept file) where a hash map's O(1) average lookup
would matter for performance, AND one example where you'd reach for a tree (BST) instead.
Justify each in 1 sentence -- tie the tree example back to something hashing structurally
CANNOT give you (hint: think about ordering).
*/
//This would be better than the linked list for the inventory that we made, because it'll help fetch and place items at O(1) time making it very efficient
//A tree can be used for a MVP system where we find the largest DPS done during the raid like in Lost Ark because hash maps can find the DPS of every single player by key but the tree will tell us right away who is the MVP as the most right node is the largest


/*
Problem 5 -- Load Factor / Resize Intuition (reasoning only, no formula required)
A hash map starts with table size 8. You insert 20 items, no removals, table never resizes.

a) What happens to the average bucket chain length as inserts continue?
b) What operation would you expect a real implementation to trigger automatically to keep
   lookups fast? You don't need the exact algorithm -- just name the problem it solves.
*/
/*
a) Length keeps growing as more and more collision happen

b) A way to dynamically resize the hashmap so increase the number of buckets to keep up with the number of items
*/

// Reference for Day 30's actual C++ syntax: https://en.cppreference.com/w/cpp/container/unordered_map
