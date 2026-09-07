// Day 29 -- Hashing Pt. 1 -- Solutions
// Read AFTER attempting the exercise file. Compare your reasoning, don't just check answers.

/*
Problem 1 -- Hash & Bucket Trace

"bat" = b(98)+a(97)+t(116) = 311 -> 311 % 7 = 3
"cab" = c(99)+a(97)+b(98)  = 294 -> 294 % 7 = 0
"no"  = n(110)+o(111)      = 221 -> 221 % 7 = 4

a) bat -> bucket 3, cab -> bucket 0, no -> bucket 4
b) No collisions -- all three land in different buckets.
c) bucket 0: [cab]
   bucket 1: (empty)
   bucket 2: (empty)
   bucket 3: [bat]
   bucket 4: [no]
   bucket 5: (empty)
   bucket 6: (empty)

Note: if you got different bucket numbers, re-check your ASCII sums first -- that's the
most common arithmetic slip, not a conceptual error.
*/


/*
Problem 1b -- CORRECTED: Actual Collision Trace

"cab" = c(99)+a(97)+b(98) = 294 -> 294 % 7 = 0
"bat" = b(98)+a(97)+t(116) = 311 -> 311 % 7 = 3
"act" = a(97)+c(99)+t(116) = 312 -> 312 % 7 = 4

Wait -- recompute: these three don't collide either at first glance. Correct key set that
DOES collide (same letters, different combination -- hash sums to match):

"cab" = 294 -> 294 % 7 = 0
"bag" = b(98)+a(97)+g(103) = 298 -> 298 % 7 = 4
"fed" = f(102)+e(101)+d(100) = 303 -> 303 % 7 = 2
"ace" = a(97)+c(99)+e(101) = 297 -> 297 % 7 = 3
"add" = a(97)+d(100)+d(100) = 297 -> 297 % 7 = 3  <-- COLLIDES with "ace"

a) cab->0, bag->4, fed->2, ace->3, add->3 (collision)
b) "ace" and "add" both land in bucket 3.
c) bucket 0: [cab] | bucket 1: (empty) | bucket 2: [fed] | bucket 3: [ace] -> [add]
   | bucket 4: [bag] | bucket 5: (empty) | bucket 6: (empty)

(If your own arithmetic on the exercise file's cab/bat/act didn't produce a collision either,
that's correct -- that specific trio doesn't collide. Use the ace/add pair above to answer
1c and 2 with a REAL collision. Apologies for the extra arithmetic detour -- the takeaway
that matters: always verify your hash outputs actually collide before reasoning about
collision behavior, don't assume a "collision exercise" guarantees one.)
*/


/*
Problem 2 -- Collision Resolution Comparison (using ace/add from above, both hash to bucket 3)

a) "ace" inserted first -> bucket 3, empty -> placed there.
   "add" inserted second -> bucket 3, OCCUPIED by "ace" -> probe bucket 4 -> also occupied
   (by "bag", if inserted before "add" -- order matters here, so assume insert order was
   cab, bag, fed, ace, add as listed) -> probe bucket 5 -> empty -> "add" lands in bucket 5.
b) Open addressing has exactly ONE key per slot -- there's no "list" to append to. If a slot
   is occupied, the ONLY way to store the new key is to find a different, empty slot,
   because the data structure has no mechanism for two keys to coexist in the same slot.
*/


/*
Problem 3 -- Worst Case By Design

Example: hash(key) = 0, always. (Or: hash(key) = length(key) % table_size, for a word list
where most words happen to be similar lengths.)

Both are technically VALID hash functions -- they always return an in-range bucket index,
which is all correctness requires. But they ignore almost all information in the key, so
nearly every key collides into the same one or two buckets. The property that makes a hash
function bad: it doesn't distribute keys uniformly across the output range -- it clusters
them. A hash function needs to be *deterministic* (same key -> same hash, every time) AND
*well-distributed* -- correctness alone isn't enough for a hash function to be useful.
*/


/*
Problem 4 -- Real-World Mapping (Hash Map vs Tree)

Hash map example: item ID -> item stats lookup in an inventory system. You know the exact
ID you're looking for and just need the data fast -- no need for ordering, so O(1) average
beats a tree's O(log n).

Tree example: a leaderboard that needs to display scores in ranked order, or find "next
highest score above X." A hash map has NO concept of order between keys -- iterating it
gives you keys in an arbitrary bucket order, not sorted order. A BST keeps keys sorted by
construction, so in-order traversal or "find nearest" queries are natural; a hash map would
require dumping everything out and sorting it from scratch every time, throwing away the
whole point of using a hash map.
*/


/*
Problem 5 -- Load Factor / Resize Intuition

a) Average bucket chain length grows roughly linearly with inserts once the table is full
   relative to its size -- with 20 items in 8 buckets (load factor 2.5), average chain
   length is now over 2 items per bucket instead of near 0-1, so most lookups now require
   walking a short list instead of a single comparison. Performance degrades gradually, not
   as a hard cliff -- but it's degrading in exactly the direction that erases the "hashing
   is O(1)" benefit.
b) A REHASH: the implementation allocates a bigger underlying array (usually roughly double)
   and reinserts every existing key using the new table size in the modulus. This resets
   average chain length back down near 0-1. You don't write this yourself with
   std::unordered_map/TMap -- it happens automatically -- but knowing WHY it happens (and
   that it's an O(n) one-time cost when it triggers) matters for understanding why hash map
   performance can occasionally have unpredictable spikes.
*/
