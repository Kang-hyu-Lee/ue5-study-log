// Day 6 — Portfolio Project: Console Calculator
// Combines: variables, conditionals (if/else), loops (while), functions
//
// GOAL: interactive console calculator that:
//   1. Repeatedly asks the user for an operator (+, -, *, /) or 'q' to quit
//   2. Reads two numbers
//   3. Computes the result using a SEPARATE FUNCTION for each operation
//   4. Prints the result
//   5. Repeats until 'q'
//
// NEW SYNTAX (explained in chat before you start — ask again if unclear):
//   - std::cin >> variable;   reads keyboard input into variable
//   - break;                  immediately exits the loop it's inside
//
// RULES:
//   - Do NOT paste any code Claude gives you — retype it after understanding it.
//   - One function per operation. No logic for +,-,*,/ should live in main().
//   - Handle divide-by-zero explicitly. Decide your behavior BEFORE coding it.
//
// ---------------------------------------------------------

#include <iostream>
#include <cmath>

// TODO: write your four function definitions here.
// Signatures (fill in the body):
// double Add(double a, double b) { ... }
// double Subtract(double a, double b) { ... }
// double Multiply(double a, double b) { ... }
// double Divide(double a, double b) { ... }   // hint: what do you return/print if b == 0?

double Add(double a, double b){
    return a + b;
}

double Subtract(double a, double b){
    return a - b;
}

double Multiply(double a, double b){
    return a * b;
}

double Divide(double a, double b){
    return a / b;
}

double Magnitude(double a, double b){
    return sqrt(a * a + b * b);
}
int main()
{
    // TODO: declare a char variable to hold the operator
    // TODO: declare two double variables for the operands
    char op;
    double a;
    double b;

    // TODO: while loop — condition should keep looping until you decide to stop
    //   Inside the loop:
    //     - std::cout a prompt: "Enter operator (+ - * / or q to quit): "
    //     - std::cin the operator char
    //     - if operator == 'q' -> break;
    //     - otherwise: std::cout prompts + std::cin the two numbers
    //     - if/else chain: match operator to the right function call
    //     - std::cout the result
    //     - if operator matches none of +,-,*,/,q -> print an error, don't crash

    while (true){
        std::cout << "Enter operator (+ - * / or m for magnitude or q to quit): " << std::endl;
        std::cin >> op;
        if (op == 'q'){
            break;
        }else if (op == '+' || op == '-' || op == '*' || op == '/'){ //added operator check logic before receiving a and b
                                                   //initially had it as an else branch after checking the divide operator
            std::cout << "Please enter your two numbers: " << std::endl;
            std::cin >> a >> b;
        }else if (op == 'm'){
            std::cout << "Please enter your 2D vector as 2 numbers (x and y)" << std::endl;
            std::cin >> a >> b;
            std::cout << "Magnitude of (" << a << ", " << b << ")" << Magnitude(a, b) << std::endl;
        }else {
            std::cout << "Invalid operator" << std::endl;
            continue; //learned to use continue to skip the rest of the loop to not completely exit program
                      //initially used break and return 1 which both resulted to the program getting terminated
        }
        if (op == '+'){
            std::cout << a << " " << op << " " << b << " = " << Add (a, b) << std::endl;
        } else if (op == '-'){
            std::cout << a << " " << op << " " << b << " = " << Subtract(a, b) << std::endl;
        } else if (op == '*'){
            std::cout << a << " " << op << " " << b << " = " << Multiply(a, b) << std::endl;
        } else if (op == '/'){
            if (b == 0){
                std::cout << "This is a divide-by-zero" << std::endl;
                continue;
            } else{
                std::cout << a << " " << op << " " << b << " = " << Divide(a, b) << std::endl;
            }
        }

    }

    return 0;
}
