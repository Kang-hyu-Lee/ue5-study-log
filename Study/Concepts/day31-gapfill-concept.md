# Day 31 Gap-Fill — TWeakObjectPtr, enum class, std::vector
(Debt from Day 29/30's silent-gap audit — closing before continuing further into Day 31.)

---

## 1. TWeakObjectPtr

**Mechanism:** a "weak" reference to a `UObject` — it does **not** count as a GC root, unlike a `UPROPERTY() UObject*`. Internally it holds the object's pointer plus a serial number, so it can detect whether the object has since been destroyed/garbage-collected. You never dereference it directly — you check `.IsValid()` (or check `.Get() != nullptr`) first, every time.

**Why it matters (ties to today's GC/UPROPERTY discussion):** `UPROPERTY()` on a `UObject*` keeps that object alive as long as the pointer exists — sometimes that's wrong. Example: "last enemy that hit me" — you want to remember which actor it was, but you do NOT want that reference to keep the enemy alive forever after it dies/despawns. That's exactly `TWeakObjectPtr`'s job: remember it, but don't force it to persist.

**Pitfall:** assuming a `TWeakObjectPtr` that was valid a moment ago is still valid now. It can go stale (target destroyed) at ANY point where GC could run — including partway through a function, not just "before this function started." Check validity immediately before each use, not once at the top of a long function.

**Edge case:** even within a single frame/tick, if something else triggers the object's destruction between when you stored the weak pointer and when you use it, `.Get()` returns `nullptr` — this is expected behavior, not a bug, and your code must handle it gracefully every time, not treat one successful check as a guarantee for the rest of the function.

**Syntax:**
```cpp
TWeakObjectPtr<AActor> WeakRef;
WeakRef = SomeActor; // implicit assignment from a raw pointer

if (WeakRef.IsValid())
{
    AActor* Actor = WeakRef.Get(); // safe to use now
    // ...
}
```

---

## 2. enum class

**Mechanism:** `enum class` defines a set of named integer constants, **scoped** to the enum's own name — you must write `EEnumName::Value`, unlike old C-style `enum` where the names leak directly into the surrounding scope.

**Why it matters:** two different `enum class` types can each have a member named `None` with zero naming collision (`EDoorState::None` vs `EWeaponState::None` are unambiguous). Old-style `enum` can't do this — both `None`s would collide in the same scope. `enum class` is also strongly typed: it won't implicitly convert to `int` without an explicit cast, which catches bugs where you accidentally compare or assign across two unrelated enum types.

**Pitfall:** forgetting the scope prefix. Writing `Open` instead of `EDoorState::Open` simply won't compile — this is usually the first "why won't this compile" moment for someone used to old-style `enum`, which would have silently allowed the bare name.

**Edge case (forward reference):** when a `enum class` needs to be visible in Blueprint or the editor, UE5 adds the `UENUM(BlueprintType)` macro above it — the reflection-macro sibling to `UCLASS()`, needed ahead of Day 50's `ECollisionChannel`. The raw `enum class` syntax itself is standard C++ and works standalone with no macro, for pure-C++ logic that never needs Blueprint visibility.

**Syntax:**
```cpp
enum class EDoorState : uint8 { Closed, Open, Locked };
// ": uint8" sets the underlying storage type — optional, but common in UE5
// for memory efficiency and because UENUM requires a fixed-width integer type.

EDoorState State = EDoorState::Closed;
if (State == EDoorState::Open) { /* ... */ }
```

---

## 3. std::vector

**Mechanism:** a dynamic array — contiguous memory like Day 8's C-style arrays, but it resizes itself automatically as you add elements via `.push_back()`, managing its own heap allocation/reallocation internally so you never manually call `new[]`/`delete[]` for it.

**Why it matters (ties to hashing):** Day 29/30's hash map/set chaining buckets are, under the hood, literally implemented as a `std::vector` of entries per bucket — this is the concrete mechanism behind "hashing handles collisions by chaining." It's also just the general-purpose growable-list tool used everywhere in plain C++ before you meet `TArray` (Unreal's equivalent, already flagged Day 29).

**Pitfall:** reallocation invalidates existing pointers/iterators/references into the vector. If you take a pointer to `nums[3]` and a later `push_back()` triggers a resize (the whole array gets copied to new memory), that old pointer is now dangling — pointing at freed memory. This is a **manual C++ memory bug**, distinct from Day 30's GC-dangling-pointer discussion (that was about UE5's garbage collector; this is about `std::vector` managing its own raw heap memory).

**Edge case:** `.size()` (current element count) vs `.capacity()` (allocated room before the next reallocation) are different numbers. `push_back()` only reallocates when `size == capacity`; when that happens, capacity typically doubles. This means push_back is O(1) *on average* (amortized) but any single call CAN be O(n) if it happens to be the one that triggers a resize — a common follow-up interview question.

**Syntax:**
```cpp
#include <vector>

std::vector<int> Nums;
Nums.push_back(5);
Nums.push_back(12);
int Count = Nums.size();  // 2
int First = Nums[0];      // 5, same [] indexing as a raw array

for (int N : Nums) { /* range-based for, already known from Day 30 */ }
```
