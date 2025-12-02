#pragma once
#include <string>
#include "stack.h"

using namespace std;

class Arithmetic {
    string infix;
    string postfix;

    int GetPriority(char op) {
        if (op == '(') return 0;
        if (op == '+') return 1;
        if (op == '-') return 1;
        if (op == '*') return 2;
        if (op == '/') return 2;
        if (op == '^') return 3;
        if (op == '~') return 4;
        return -1;
    }

public:
    Arithmetic(string s = "") {
        infix = s;
        postfix = "";
    }

    string GetInfix() const { return infix; }
    string GetPostfix() const { return postfix; }

    string ToPostfix();
    double Calculate(double* values, bool* isSet);
};