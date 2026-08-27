# Day 24 — Templates (Conceptual Intro)

## The problem templates solve

Without templates, if you want an `Add` function that works for `int`, `float`, and
`double`, you write it three times:

```cpp
int Add(int A, int B) { return A + B; }
float Add(float A, float B) { return A + B; }
double Add(double A, double B) { return A + B; }
```

Identical logic, only the type changes. That's a maintenance trap — fix a bug in one,
forget the other two. Templates let you write the logic **once**, generic over type.

## Core mechanism

```cpp
template<typename T>
T Add(T A, T B)
{
    return A + B;
}
```

- `template<typename T>` — declares `T` as a placeholder for "some type, decided later."
  `typename` and `class` are interchangeable here (`template<class T>` works identically)
  — `typename` is more common style, use it.
- `T` then stands in for the real type everywhere in the function signature and body.
- Call it like a normal function: `Add(3, 4)` or `Add(2.5f, 1.5f)`. You don't have to
  specify `T` explicitly — the compiler infers it from your arguments (this is called
  **template argument deduction**).

**Critical distinction — this is compile-time, not runtime:**

This is NOT the same mechanism as virtual functions (Day 22). Virtual functions pick
which override to run at **runtime**, via the vtable, based on the actual object type.
Templates are resolved entirely at **compile time** — the compiler looks at every place
you actually *call* `Add<T>()` with a concrete type, and generates a separate, fully
concrete function for each distinct type used (`Add<int>`, `Add<float>`, etc. all exist
as real separate functions in the compiled binary). This is called **template
instantiation**. If you never call `Add<double>` anywhere in your program, no
`Add<double>` function is ever generated — templates that are never instantiated cost
nothing.

This compile-time-resolution property is why templates are sometimes called
"static polymorphism" vs. virtual functions' "dynamic polymorphism."

## Common pitfall

Template code only gets **type-checked against a real type when it's instantiated**,
not when it's declared. This means an error inside a template can sit silently until
someone calls it with a type that breaks — and the error message points at the
*instantiation site* (where you called it), not necessarily the line inside the
template that's actually wrong, which can be genuinely confusing to read the first
few times. Example: `template<typename T> T Add(T A, T B) { return A + B; }` compiles
fine as a declaration. Calling `Add(MyStructWithNoPlusOperator{}, MyStructWithNoPlusOperator{})`
only then fails — because `operator+` doesn't exist for that struct.

## Class templates (brief — full depth not needed yet)

The same idea extends to classes:

```cpp
template<typename T>
class Container
{
public:
    T Value;
};

Container<int> IntBox;
Container<FString> StringBox;
```

You'll recognize this immediately once you open UE5: `TArray<T>`, `TMap<KeyType,
ValueType>`, `TSharedPtr<T>` are all class templates. `TArray<int32>` and
`TArray<AActor*>` are the same underlying template code, instantiated for two
different `T`s.

## Edge case

A template function that *looks* generic can still silently fail to compile for
certain types — e.g. a template using `<` to compare two `T`s will fail for any `T`
that hasn't defined `operator<`. The template's "genericity" is really "generic over
any type that happens to support the operations the template body uses" — not
truly unlimited. (C++20 `concepts` exist to make these requirements explicit and
give cleaner errors — out of scope for now, mentioned only so the term isn't a
total surprise later.)

## Why it matters — production & interview

- Nearly every UE5 container you'll touch daily is a template: `TArray`, `TMap`,
  `TSet`, `TSharedPtr`, `TWeakObjectPtr`. Understanding template instantiation
  errors (long, ugly compiler messages naming the whole call chain) is a real
  practical skill, not academic.
- Interview follow-up: "difference between templates and function overloading?"
  → Overloading = you manually write each version, compiler picks by matching
  argument types among what you wrote. Templates = you write one version, compiler
  *generates* a version for whatever type you actually use, at compile time.
