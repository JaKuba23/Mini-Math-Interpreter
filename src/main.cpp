#include "parser.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    string expr;
    cout << "Mini Math Interpreter. Enter an expression or 'exit' to quit." << endl;

    while (cout << "> ", getline(cin, expr) && expr != "exit") {
        if (expr.empty()) continue;

        try {
            Parser parser(expr);
            auto ast = parser.parseExpression();
            cout << "Result: " << ast->eval() << endl;
        } catch(const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
