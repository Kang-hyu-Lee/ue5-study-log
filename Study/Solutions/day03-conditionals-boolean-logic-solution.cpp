// Day 3 C++ Solutions — Conditionals & Boolean Logic

#include <iostream>
#include <cmath>   // for std::abs, used in a note below

int main() {

    // 1. Positive / Negative / Zero
    int number = -7;
    if (number > 0) {
        std::cout << "Positive\n";
    } else if (number < 0) {
        std::cout << "Negative\n";
    } else {
        std::cout << "Zero\n";
        // Note: only reachable if neither > 0 nor < 0 matched — i.e. exactly 0.
    }

    // 2. Health classifier
    int health = 50;
    if (health >= 75) {
        std::cout << "Healthy\n";
    } else if (health >= 25) {
        std::cout << "Wounded\n";
    } else {
        std::cout << "Critical\n";
    }
    // Order is high-to-low on purpose: if we tested ">= 25" first, a health of 90
    // would incorrectly match "Wounded" and never reach the "Healthy" check.

    // 3. Score range check with &&
    int score = 85;
    if (score >= 0 && score <= 100) {
        std::cout << "Valid score\n";
    }
    // Short-circuit note: if score were, say, -5, the left side (score >= 0) is false,
    // so && short-circuits — but here that doesn't save any expensive work, it's just
    // the mechanism. The safety-pattern benefit shows up more in exercise 5.

    // 4. Bug fix: = vs ==
    bool isAlive = true;
    if (isAlive == false) {   // FIXED: == compares, doesn't assign
        std::cout << "Player died\n";
    }
    // Bonus idiomatic version — since isAlive is already a bool, you can just negate it:
    // if (!isAlive) { ... }
    // The buggy original (`if (isAlive = false)`) would have SET isAlive to false every
    // time this ran, then evaluated false as the condition (so the branch wouldn't even
    // fire) — silently corrupting isAlive's value on top of getting the wrong branch logic.

    // 5. Trace: does `(x > 0) || (10 / x > 2)` crash when x == 0?
    // NO. Left side: (0 > 0) is false. Since this is ||, C++ does NOT stop on false —
    // || only short-circuits when the LEFT side is TRUE (then it skips the right side).
    // Left side false means || MUST evaluate the right side to determine the final answer.
    // So (10 / x) DOES run with x == 0 -> this is a real divide-by-zero, undefined behavior.
    // (This is the mirror-image trap of the && example in the concept file: with &&, a
    // false left side protects you; with ||, a false left side does NOT protect you —
    // you'd need the false-guard on the || itself, e.g. (x == 0) || (10 / x > 2) doesn't
    // fix it either, since that's also just reordering the same problem. The real fix is
    // an explicit guard: if (x != 0 && 10 / x > 2) using && instead.)

    // 6. Grade classifier
    int examScore = 82;
    char grade;
    if (examScore >= 90) {
        grade = 'A';
    } else if (examScore >= 80) {
        grade = 'B';
    } else if (examScore >= 70) {
        grade = 'C';
    } else if (examScore >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }
    std::cout << "Grade: " << grade << "\n";
    // Same high-to-low ordering principle as exercise 2. If ordered low-to-high
    // (>= 60 first), an examScore of 95 would match "D" territory first and stop there.

    return 0;
}
