#include <iostream>
#include <string>
#include <stdexcept>
#include "arithmetic.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    string expression;
    char cont = 'y';

    while (cont == 'y' || cont == 'Y') {
        if (cin.peek() == '\n') cin.ignore();

        cout << "Enter expression: ";
        getline(cin, expression);

        Arithmetic A(expression);
        double values[256];
        bool isSet[256];

        for (int i = 0; i < 256; i++) {
            isSet[i] = false;
        }

        try {
            string p = A.ToPostfix();
            cout << "Postfix: " << p << endl;

            double res = A.Calculate(values, isSet);
            cout << "Result: " << res << endl;
        }
        catch (const std::exception& e) {
            cout << "Error: " << e.what() << endl;
        }

        cout << "\nAgain? (y/n): ";
        cin >> cont;
    }

    return 0;
}