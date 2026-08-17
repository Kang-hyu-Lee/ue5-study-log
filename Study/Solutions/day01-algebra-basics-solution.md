# Day 1 Solutions — Algebra Basics & Order of Operations

Only check these after you've attempted every problem yourself.

## 1. `6 + 2 × (5 − 3)³`
```
= 6 + 2 × (2)³      # parentheses: 5-3=2
= 6 + 2 × 8         # exponent: 2³=8
= 6 + 16            # multiplication: 2×8=16
= 22                # addition
```
**Answer: 22**

## 2. `(8 − 2) × 3 + 4²`
```
= (6) × 3 + 4²      # parentheses: 8-2=6
= 6 × 3 + 16        # exponent: 4²=16
= 18 + 16           # multiplication: 6×3=18
= 34                # addition
```
**Answer: 34**

## 3. `20 ÷ 4 + 3 × (1 + 1)²`
```
= 20 ÷ 4 + 3 × (2)²     # parentheses: 1+1=2
= 20 ÷ 4 + 3 × 4        # exponent: 2²=4
= 5 + 12                # division (20÷4=5) and multiplication (3×4=12), same tier, left to right — both resolved before addition
= 17                    # addition
```
**Answer: 17**

## 4. `5² − (3 + 1) × 2 + 6 ÷ 3`
```
= 5² − (4) × 2 + 6 ÷ 3      # parentheses: 3+1=4
= 25 − 4 × 2 + 6 ÷ 3        # exponent: 5²=25
= 25 − 8 + 2                # multiplication (4×2=8) and division (6÷3=2), left to right
= 17 + 2                    # subtraction/addition left to right: 25-8=17 first
= 19
```
**Answer: 19**

## 5. `x = 4`: `2x² + 3(x − 1)`
```
= 2(4)² + 3(4 − 1)      # substitute x=4 everywhere
= 2(4)² + 3(3)          # parentheses: 4-1=3
= 2(16) + 3(3)          # exponent: 4²=16
= 32 + 9                # multiplication: 2×16=32, 3×3=9
= 41
```
**Answer: 41**

## 6. The mistake
`2 + 3 × 4` was evaluated left-to-right as if all operators had equal priority, giving `(2+3)×4 = 20`. That's wrong because multiplication outranks addition — you must do `3 × 4 = 12` first, then `2 + 12 = 14`.

**Correct answer: 14**
