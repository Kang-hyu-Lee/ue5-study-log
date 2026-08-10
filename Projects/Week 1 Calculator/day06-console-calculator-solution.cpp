// Day 6 — Portfolio Project: Console Calculator — SOLUTION
// Compare against your own attempt. This mirrors your working structure,
// with the ordering polish noted in review (validate operator before reading numbers).

#include <iostream>

double Add(double a, double b) { return a + b; }
double Subtract(double a, double b) { return a - b; }
double Multiply(double a, double b) { return a * b; }
double Divide(double a, double b) { return a / b; } // caller guarantees b != 0 (precondition)

int main()
{
    char op;
    double a;
    double b;

    while (true)
    {
        std::cout << "Enter operator (+ - * / or q to quit): " << std::endl;
        std::cin >> op;

        if (op == 'q')
        {
            break; // exits the while loop entirely — program ends here, this IS "done"
        }

        // Validate op BEFORE reading numbers — reject garbage in one step, not two.
        // != is "not equal". && is logical AND: the whole condition is true only if
        // EVERY comparison is true (op matches none of the four valid operators).
        // Short-circuit note: C++ stops checking left-to-right the moment one side
        // of && is false, since the overall result is already determined.
        if (op != '+' && op != '-' && op != '*' && op != '/')
        {
            std::cout << "Invalid operator" << std::endl;
            continue; // skip straight back to the prompt — no wasted number reads
        }

        std::cout << "Please enter your two numbers: " << std::endl;
        std::cin >> a >> b;

        if (op == '+')
        {
            std::cout << "a + b = " << Add(a, b) << std::endl;
        }
        else if (op == '-')
        {
            std::cout << "a - b = " << Subtract(a, b) << std::endl;
        }
        else if (op == '*')
        {
            std::cout << "a * b = " << Multiply(a, b) << std::endl;
        }
        else // op == '/' — the only remaining possibility after validation above
        {
            if (b == 0) // exact-zero comparison is safe: 0.0 has no fractional binary
                         // expansion to round, unlike e.g. 0.1 — see Day 6 chat log
            {
                std::cout << "This is a divide-by-zero" << std::endl;
                continue; // skip to next loop iteration — session survives bad input
            }
            std::cout << "a / b = " << Divide(a, b) << std::endl;
        }
    }

    return 0;
}

// NOTE: learner's original submission read a/b BEFORE validating op, wasting two
// cin reads on garbage input — functionally correct, minor UX inefficiency.
// This version validates op with a guard clause (the != && != chain above) before
// touching a/b at all. Both are logically correct; this ordering is tighter.
