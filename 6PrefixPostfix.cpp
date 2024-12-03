#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

int evaluatePostfix(const string& expression) {
    stack<int> s;
    for (char c : expression) {
        if (isdigit(c)) {
            s.push(c - '0');
        } else {
            int operand2 = s.top(); s.pop();
            int operand1 = s.top(); s.pop();
            switch (c) {
                case '+': s.push(operand1 + operand2); break;
                case '-': s.push(operand1 - operand2); break;
                case '*': s.push(operand1 * operand2); break;
                case '/': s.push(operand1 / operand2); break;
                case '^': s.push(pow(operand1, operand2)); break;
            }
        }
    }
    return s.top();
}

int evaluatePrefix(const string& expression) {
    stack<int> s;
    for (int i = expression.size() - 1; i >= 0; --i) {
        if (isdigit(expression[i])) {
            s.push(expression[i] - '0');
        } else {
            int operand1 = s.top(); s.pop();
            int operand2 = s.top(); s.pop();
            switch (expression[i]) {
                case '+': s.push(operand1 + operand2); break;
                case '-': s.push(operand1 - operand2); break;
                case '*': s.push(operand1 * operand2); break;
                case '/': s.push(operand1 / operand2); break;
                case '^': s.push(pow(operand1, operand2)); break;
            }
        }
    }
    return s.top();
}

int main() {
    string postfix = "23*54*+9-";
    string prefix = "-+*23*549";

    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;
    cout << "Prefix Evaluation: " << evaluatePrefix(prefix) << endl;

    return 0;
}
