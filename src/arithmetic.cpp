#include "arithmetic.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

string Arithmetic::ToPostfix() {
    postfix = "";
    TStack<char> stack(infix.length() * 2);
    bool canBeUnary = true;

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (c == ' ') continue;

        if (isdigit(c) || c == '.') {
            postfix += c;
            while (i + 1 < infix.length() && (isdigit(infix[i + 1]) || infix[i + 1] == '.')) {
                i++;
                postfix += infix[i];
            }
            postfix += " ";
            canBeUnary = false;
        }
        else if (isalpha(c)) {
            postfix += c;
            postfix += " ";
            canBeUnary = false;
        }
        else if (c == '(') {
            stack.Push(c);
            canBeUnary = true;
        }
        else if (c == ')') {
            while (!stack.IsEmpty() && stack.Top() != '(') {
                postfix += stack.Top();
                postfix += " ";
                stack.Pop();
            }

            if (!stack.IsEmpty()) {
                stack.Pop();
            }
            else {
                throw std::invalid_argument("Error: Unmatched closing parenthesis");
            }

            canBeUnary = false;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            char op = c;
            if (op == '-' && canBeUnary) {
                op = '~';
            }

            while (!stack.IsEmpty() && GetPriority(stack.Top()) >= GetPriority(op)) {
                postfix += stack.Top();
                postfix += " ";
                stack.Pop();
            }
            stack.Push(op);
            canBeUnary = true;
        }
    }

    while (!stack.IsEmpty()) {
        if (stack.Top() == '(') {
            throw std::invalid_argument("Error: Unmatched opening parenthesis");
        }
        postfix += stack.Top();
        postfix += " ";
        stack.Pop();
    }

    return postfix;
}

double Arithmetic::Calculate(double* values, bool* isSet) {
    if (postfix.length() == 0) {
        ToPostfix();
    }

    TStack<double> stack;

    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];

        if (c == ' ') continue;

        if (isdigit(c) || c == '.') {
            string numStr = "";
            while (i < postfix.length() && (isdigit(postfix[i]) || postfix[i] == '.')) {
                numStr += postfix[i];
                i++;
            }
            i--;
            stack.Push(stod(numStr));
        }
        else if (isalpha(c)) {
            int index = (int)((unsigned char)c);
            if (isSet[index] == false) {
                cout << "Enter value for " << c << ": ";
                double val;
                cin >> val;
                values[index] = val;
                isSet[index] = true;
            }
            stack.Push(values[index]);
        }
        else if (c == '~') {
            if (stack.IsEmpty()) throw std::invalid_argument("Error: Invalid expression");
            double val = stack.Pop();
            stack.Push(-val);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (stack.IsEmpty()) throw std::invalid_argument("Error: Invalid expression");
            double v2 = stack.Pop();

            if (stack.IsEmpty()) throw std::invalid_argument("Error: Invalid expression");
            double v1 = stack.Pop();

            if (c == '+') stack.Push(v1 + v2);
            if (c == '-') stack.Push(v1 - v2);
            if (c == '*') stack.Push(v1 * v2);
            if (c == '/') {
                if (v2 == 0) throw std::runtime_error("Error: Division by zero");
                stack.Push(v1 / v2);
            }
            if (c == '^') stack.Push(pow(v1, v2));
        }
    }

    if (stack.IsEmpty()) throw std::invalid_argument("Error: Empty result");
    double res = stack.Pop();
    if (!stack.IsEmpty()) throw std::invalid_argument("Error: Extra operands");

    return res;
}