# Matrices Intro — Solutions (Day 10)

## 1. Scale matrix
```
| 2 0 |   | 3 |   | 2*3 + 0*4 |   | 6 |
| 0 2 | x | 4 | = | 0*3 + 2*4 | = | 8 |
```
Result: (6, 8). This matrix is 2 x the identity matrix — it scales both x
and y by 2, uniformly. Any diagonal matrix with equal diagonal values is a
uniform scale.

## 2. 90 degree rotation
```
| 0 -1 |   | 0 |   | 0*0 + -1*1 |   | -1 |
| 1  0 | x | 1 | = | 1*0 +  0*1 | = |  0 |
```
Result: (-1, 0). Check against the unit circle: (0,1) sits at 90 degrees;
rotating another 90 degrees CCW lands at 180 degrees, which is (-1, 0).
Matches.

## 3. Flip across the x-axis (correction from attempt)
```
| 1  0 |   | 5 |   | 1*5 +  0*2 |   |  5 |
| 0 -1 | x | 2 | = | 0*5 + -1*2 | = | -2 |
```
Result: (5, -2). This negates the y-component only, which reflects the
point ACROSS the x-axis (not the y-axis) — the axis you flip across is the
one that stays fixed while the OTHER coordinate flips sign. To flip across
the y-axis instead, you'd negate x and keep y: `| -1 0 | / | 0 1 |`.
Common mix-up — worth re-deriving from scratch once more.

## 4. Order matters — A then B vs B then A
A = scale x by 2: `| 2 0 | / | 0 1 |`
B = 90 degree rotation: `| 0 -1 | / | 1 0 |`

**A then B**, starting from (1, 0):
- A x (1,0) = (2*1+0*0, 0*1+1*0) = (2, 0)
- B x (2,0) = (0*2 + -1*0, 1*2 + 0*0) = (0, 2)
- Result: (0, 2)

**B then A**, starting from (1, 0):
- B x (1,0) = (0*1 + -1*0, 1*1 + 0*0) = (0, 1)
- A x (0,1) = (2*0+0*1, 0*0+1*1) = (0, 1)
- Result: (0, 1)

(0, 2) != (0, 1) — confirmed different. In UE5 terms: if an Actor has both a
Scale and a Rotation set, the ENGINE'S fixed order for combining them
matters — you don't get to casually reorder scale/rotate/translate and
expect the same final transform. This is why FTransform composition order
is a real, documented concern, not a theoretical nitpick.

## 5. Identity matrix
```
| 1 0 |   | 7 |   | 1*7 + 0*-3 |   | 7 |
| 0 1 | x | -3| = | 0*7 + 1*-3 | = | -3 |
```
Result: (7, -3) — unchanged. Makes sense because each output component
picks up 1x its own input and 0x the other — mathematically it's doing
nothing, the same role 1 plays in scalar multiplication. Useful as a
"no transform applied yet" starting point when building up a transform
chain in code.
