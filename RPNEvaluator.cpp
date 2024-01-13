#include "RPNEvaluator.h"

RPNEvaluator::RPNEvaluator() {}

RPNEvaluator::RPNEvaluator(const SStack<string>& rpnStack) : rpnStack(rpnStack) {}

RPNEvaluator::~RPNEvaluator() {}



float RPNEvaluator::evaluate() {
    SStack<float> resultStack;

    while (!rpnStack.empty()) {
        string token = rpnStack.top();
        rpnStack.pop();

        if (isDigit(token[0]) || (token.size() > 1 && token[0] == '-' && isDigit(token[1]))) {
            // Operand, push to result stack
            resultStack.push(stof(token));
        }
        else if (isOperator(token[0])) {
            // Operator, perform operation
            if (resultStack.getSize() < 2) {
                // Invalid RPN expression
                throw runtime_error("Need more operands");
            }
            float operand2 = resultStack.top();
            resultStack.pop();
            float operand1 = resultStack.top();
            resultStack.pop();

            float result = performOperation(operand1, operand2, token[0]);
            resultStack.push(result);
        }
        else {
            // Invalid token in RPN expression
            throw runtime_error("Invalid token in RPN expression");
        }
    }

    if (resultStack.getSize() != 1) {
        // Invalid RPN expression
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

float RPNEvaluator::performOperation(float operand1, float operand2, char op) {
    switch (op) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        if (operand2 == 0) {
            // Division by zero
            throw runtime_error("Division by zero");
        }
        return operand1 / operand2;
    default:
        // Unknown operator
        throw runtime_error("Unknown operator");
    }
}
