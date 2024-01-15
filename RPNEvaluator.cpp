#include "RPNEvaluator.h"

RPNEvaluator::RPNEvaluator() {}

RPNEvaluator::RPNEvaluator(const SStack<string>& rpnStack) : rpnStack(rpnStack) {}

RPNEvaluator::~RPNEvaluator() {}

double RPNEvaluator::evaluate() {
    SStack<double> resultStack;

    while (!rpnStack.empty()) {
        string token = rpnStack.top();
        rpnStack.pop();

        if (isDigit(token[0]) || (token.size() > 1 && token[0] == '-' && isDigit(token[1]))) {
           
            resultStack.push(stof(token));
        }
        else if (isOperator(token[0])) {
            if (resultStack.getSize() < 2) {
                
                throw runtime_error("Need more operands");
            }
            double operand2 = resultStack.top();
            resultStack.pop();
            double operand1 = resultStack.top();
            resultStack.pop();

            double result = performOperation(operand1, operand2, token[0]);
            resultStack.push(result);
        }
        else {
            throw runtime_error("Invalid token in RPN expression");
        }
    }

    if (resultStack.getSize() != 1) {
        throw runtime_error("Invalid RPN expression");
    }

    return resultStack.top();
}

bool RPNEvaluator::isDigit(char c) {
    return '0' <= c && c <= '9';
}

void RPNEvaluator::setRPNStack(const SStack<string>& rpnStack) {
    this->rpnStack = rpnStack;
}


double RPNEvaluator::performOperation(double operand1, double operand2, char op) {
    switch (op) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        if (operand2 == 0) {
            throw runtime_error("Division by zero");
        }
        return operand1 / operand2;
    case '^': 
        return pow(operand1, operand2);
    case '#': 
        return pow(operand2, 1.0 / operand1);
    default:
        throw runtime_error("Unknown operator");
    }
}
