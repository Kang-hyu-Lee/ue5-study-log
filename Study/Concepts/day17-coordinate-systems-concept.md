# Day 17 — Coordinate Systems: Local vs World Space

## The core mechanism

Every position in a game exists relative to SOME origin. There isn't one universal
"true" coordinate — there are always at least two frames of reference in play:

- **World space**: the level's single global origin (0,0,0). Everything CAN be
  expressed in world space, and it's what physics, collision, and rendering
  ultimately need.
- **Local space** (also "relative space" / "object space"): an object's OWN
  origin, sitting at that object's pivot point, with axes rotated to match
  that object's own orientation.

An object's local space moves and rotates WITH the object. If you're standing
inside a moving, spinning space station, "forward" in your local space always
means "toward the front of the station" — even while the station's world-space
position and rotation are constantly changing underneath you.

## Why two spaces instead of one

Attachment. If a sword is attached to a hand socket, you don't want to
recompute the sword's world position every time the hand moves — you want to
say ONCE: "sword sits 5cm forward, 0 up, 0 right, relative to the hand" (local
space), and let the ENGINE recompute world position automatically every frame
by combining that fixed local offset with the hand's current world transform.

This is exactly the parent-child transform chain from Day 15's matrix lesson:

```
ChildWorldTransform = ChildLocalTransform * ParentWorldTransform
```

(Order matters — Day 15: matrix multiplication is non-commutative. Apply the
child's own rotation/scale first, in its own frame, THEN place the whole
result into the parent's frame.)

## Worked numeric example

Setup:
- Parent (e.g. a turret base) is at world position **(5, 3)**, rotated **90°**
  counter-clockwise.
- Child (e.g. the turret's gun barrel) has LOCAL position **(2, 0)** — i.e.
  "2 units forward along the parent's local X-axis, 0 on Y" — relative to the
  parent, with no additional local rotation of its own.

Question: where is the gun barrel in WORLD space?

Step 1 — apply the parent's rotation to the child's local offset.
Rotating (2, 0) by 90° CCW using the Day 15 rotation matrix:
```
x' = x*cos(90) - y*sin(90) = 2*0 - 0*1 = 0
y' = x*sin(90) + y*cos(90) = 2*1 + 0*0 = 2
```
Rotated offset = **(0, 2)**.

Step 2 — translate by the parent's world position (add).
```
WorldPos = ParentWorldPos + RotatedOffset
         = (5, 3) + (0, 2)
         = (5, 5)
```

Result: the gun barrel is at world (5, 5) — even though its LOCAL coordinate
never changed and never will, as long as it stays attached at that offset.
Rotate the turret again, and the SAME local (2,0) produces a DIFFERENT world
result, because step 1's rotation changes.

## Common pitfall

Assuming "local position (0,0,0)" means "at the world origin." It doesn't —
it means "zero offset from the parent." If the parent is at world (500, 0, 0),
a child with local (0,0,0) is ALSO at world (500, 0, 0), not at the level
origin. This trips people up constantly in UE5: resetting an actor's
`RelativeLocation` to zero snaps it back to its PARENT, not to the level's
(0,0,0).

## Edge case where the naive understanding breaks

If an object has NO parent (nothing attached to), its local space and world
space are numerically identical — the "parent transform" is the identity
transform (no rotation, no translation, no scale). This is why beginners can
get away with treating local == world for a long time: most of your early
objects are unparented root actors. The distinction becomes unavoidable the
moment ANYTHING gets attached to ANYTHING else — weapons to hands, cameras to
heads, wheels to a car body.

## UE5 tie-in

- `GetActorLocation()` — world space.
- `RelativeLocation` on a `USceneComponent` — local space, relative to
  whatever it's attached to (its parent component, or the world if
  unattached — see edge case above).
- Adding a local-space offset directly to a world-space position without
  transforming it first is a real, common bug class — it's the "position +
  position is meaningless" lesson from Day 15, but the SPACE-mismatch
  version: you can't just add two vectors that are expressed in different
  reference frames and expect a meaningful result, even if the addition
  itself is dimensionally valid.

*(flagged Day 17)*
