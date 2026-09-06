# Day 29 — Hashing Pt. 1 (Concept)

## What is a Hash Map / Hash Set?
- **Mechanism:** a hash map stores key→value pairs. A hash **function** takes a key, produces a number (the hash), then maps that number to a slot ("bucket") in a fixed-size array via `hash % table_size`. To look up a key: hash it, jump straight to the bucket — no scanning the whole structure.
- A hash **set** is the same idea minus the value — just "is this key present," no associated data.
- Contrast with a plain array: array access by index is O(1) because the index *is* the address offset. A hash map's access is O(1) **average** because the hash function converts an arbitrary key (string, struct, whatever) into something that behaves like an index.

## Why O(1) Average, Not O(1) Guaranteed
- If the hash function spreads keys evenly across buckets, each bucket holds ~0–1 items → lookup is one hash calc + one comparison = O(1).
- **Pitfall:** if the hash function is bad (or the table is too small relative to the number of keys), many keys land in the *same* bucket. A bucket with a collision doesn't return instantly — it has to resolve the collision first.

## Collision Resolution — Two Approaches (conceptual only, no code yet)
1. **Chaining:** each bucket holds a linked list. Collision → append to that bucket's list. Lookup on collision walks the list.
2. **Open addressing:** table has exactly one slot per bucket. Collision → probe (using a step rule) for the next empty slot. Lookup on collision follows the same probe sequence.
- Neither is "better" in general — chaining tolerates a worse hash function more gracefully (worst case degrades to a linked-list scan), open addressing is more cache-friendly but degrades harder as the table fills up (clustering — colliding keys pile into adjacent slots, making the next collision even more likely).

## Worked Example (Chaining, table size 5)
Hash function: `hash(key) = (sum of ASCII codes of characters) % 5`

Insert "cat", "dog", "ax", in that order:

- "cat" = 99+97+116 = 312 → 312 % 5 = **2** → bucket 2: [cat]
- "dog" = 100+111+103 = 314 → 314 % 5 = **4** → bucket 4: [dog]
- "ax" = 97+120 = 217 → 217 % 5 = **2** → **collision** with "cat" → bucket 2 becomes a chain: [cat] → [ax]

Final table:
```
bucket 0: (empty)
bucket 1: (empty)
bucket 2: [cat] -> [ax]
bucket 3: (empty)
bucket 4: [dog]
```

Lookup "ax": hash → 2 → go to bucket 2 → walk the chain: compare "cat" (mismatch) → compare "ax" (match) → return. That walk IS the gap between "O(1) average" and "O(1) worst case" — with a bad hash function funneling everything into bucket 2, this lookup degrades toward an O(n) linked-list scan.

## Why It Matters
- Most common interview topic, full stop. "Two Sum" (classic first hashing problem), duplicate detection, frequency counting — nearly all hashing-shaped.
- Gamedev: `TMap` (UE5's hash map) is used constantly — item ID → item data, actor tag → actor pointer, save-game key → value. You use it directly starting Day 38.

## Edge Case Where the Naive Understanding Breaks
- "Hash maps are always O(1)" is false in the worst case: pathological input (all keys hashing to the same bucket) degrades every operation to O(n) — no better than a linked list. This is why production hash maps (`std::unordered_map`, `TMap`) automatically resize/rehash as the load factor (items ÷ buckets) grows, and why hash function quality matters for security-sensitive code — predictable hash functions enable "hash-flooding" denial-of-service attacks by forcing worst-case collisions on purpose.
- Mutating a key *after* inserting it (when the key's hash depends on data that then changes) silently breaks future lookups — the item is now sitting in the wrong bucket for its *current* hash, but the map doesn't know to move it. Rule of thumb: treat keys as immutable once inserted.
