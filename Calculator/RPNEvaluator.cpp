#include "RPNEvaluator.h"
#include <cmath>
#include <cctype>
#include "sstream.h"

using namespace std; 
RPNEvaluator::RPNEvaluator() {}

RPNEvaluator::~RPNEvaluator() {}

double RPNEvaluator::calculateRPN(const string& rpnExpression) {
    stack<double> values;
    istringstream iss(rpnExpression);
    string token;

    while (iss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
            values.push(stod(token));
        }
        else if (isOperator(token[0])) {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();

            switch (token[0]) {
            case '+': values.push(a + b); break;
            case '-': values.push(a - b); break;
            case '*': values.push(a * b); break;
            case '/': values.push(a / b); break;
            case '^': values.push(pow(a, b)); break;
            case 's': values.push(sqrt(b)); break;
            }
        }
    }

    return values.top();
}

bool RPNEvaluator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 's';
}
