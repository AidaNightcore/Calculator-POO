// RPNConverter.cpp
#include "RPNConverter.h"

RPNConverter::RPNConverter() {}

RPNConverter::~RPNConverter() {}

stack<string> RPNConverter::convertToRPN(const string& infixExpression) {
    stack<string> resultStack;
    stack<char> operatorStack;
    sstream sstream(infixExpression);

    string token;
    while (sstream >> token) {
        if (!token.empty()) {  // Ensure the token is not empty
            if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
                // Operand, push to result stack
                resultStack.push(token);
            }
            else if (isOperator(token[0])) {
                // Operator
                while (!operatorStack.empty() && isHigherPrecedence(operatorStack.top(), token[0])) {
                    resultStack.push(string(1, operatorStack.top()));
                    operatorStack.pop();
                }
                operatorStack.push(token[0]);
            }
            else if (isOpeningBracket(token[0])) {
                // Opening bracket, push to operator stack
                operatorStack.push(token[0]);
            }
            else if (isClosingBracket(token[0])) {
                // Closing bracket, pop operators until matching opening bracket
                while (!operatorStack.empty() && !isOpeningBracket(operatorStack.top())) {
                    resultStack.push(string(1, operatorStack.top()));
                    operatorStack.pop();
                }
                // Pop the opening bracket from the stack
                if (!operatorStack.empty()) {
                    operatorStack.pop();
                }
            }
        }
    }

    // Pop remaining operators from the operator stack to the result stack
    while (!operatorStack.empty()) {
        resultStack.push(string(1, operatorStack.top()));
        operatorStack.pop();
    }

    return resultStack;
}

int RPNConverter::getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else {
        return 0; // Assuming other operators have lower precedence
    }
}

bool RPNConverter::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool RPNConverter::isOpeningBracket(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool RPNConverter::isClosingBracket(char c) {
    return c == ')' || c == ']' || c == '}';
}

bool RPNConverter::isHigherPrecedence(char op1, char op2) {
    int precedence1 = getPrecedence(op1);
    int precedence2 = getPrecedence(op2);

    return precedence1 >= precedence2;
}
