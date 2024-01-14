#include "RPNConverter.h"

RPNConverter::RPNConverter() {}

RPNConverter::~RPNConverter() {}
SStack<std::string> RPNConverter::convertToRPN(const std::string& infixExpression) {
    SStack<std::string> resultStack;
    SStack<char> operatorStack;

    MySStream mySStream(infixExpression.c_str());

    std::string token, currentNumber;
    while (mySStream >> token) {
        if (isNumber(token) || (token.length() == 1 && isOperator(token[0]))) {
            if (isNumber(token)) {
                resultStack.push(token);
            }
            else {
                // It's a single character operator
                while (!operatorStack.empty() && isHigherPrecedence(operatorStack.top(), token[0]) && !isOpeningBracket(operatorStack.top())) {
                    resultStack.push(std::string(1, operatorStack.top()));
                    operatorStack.pop();
                }
                operatorStack.push(token[0]);
            }
        }
        else {
            // Token is not a single character operator, handle each character
            for (char c : token) {
                if (isDigit(c) || c == '.') {
                    currentNumber += c;
                }
                else if (isOperator(c)) {
                    if (!currentNumber.empty()) {
                        resultStack.push(currentNumber);
                        currentNumber.clear();
                    }
                    while (!operatorStack.empty() && isHigherPrecedence(operatorStack.top(), c) && !isOpeningBracket(operatorStack.top())) {
                        resultStack.push(std::string(1, operatorStack.top()));
                        operatorStack.pop();
                    }
                    operatorStack.push(c);
                }
                else if (isOpeningBracket(c)) {
                    if (!currentNumber.empty()) {
                        resultStack.push(currentNumber);
                        currentNumber.clear();
                    }
                    operatorStack.push(c);
                }
                else if (isClosingBracket(c)) {
                    if (!currentNumber.empty()) {
                        resultStack.push(currentNumber);
                        currentNumber.clear();
                    }
                    while (!operatorStack.empty() && !isOpeningBracket(operatorStack.top())) {
                        resultStack.push(std::string(1, operatorStack.top()));
                        operatorStack.pop();
                    }
                    if (operatorStack.empty() || !isOpeningBracket(operatorStack.top())) {
                        throw std::runtime_error("Mismatched brackets");
                    }
                    operatorStack.pop(); // Pop the opening bracket
                }
                else {
                    throw std::runtime_error("Invalid character in the infix expression");
                }
            }
            if (!currentNumber.empty()) {
                resultStack.push(currentNumber);
                currentNumber.clear();
            }
        }
    }

    // Process the remaining operators in the stack
    while (!operatorStack.empty()) {
        if (isOpeningBracket(operatorStack.top())) {
            throw std::runtime_error("Mismatched brackets");
        }
        resultStack.push(std::string(1, operatorStack.top()));
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
    else if (op == '#' || op == '^') {
        return 3;
    }
    else {
        return 0; // Assuming other operators have lower precedence
    }
}

bool RPNConverter::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '#';
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

    if (precedence1 > precedence2) {
        return true;
    }
    else if (precedence1 < precedence2) {
        return false;
    }
    else {
        // Equal precedence
        if (op1 == '^' || op1 == '#') {
            return false; // Right-associative operators
        }
        else {
            return true; // Left-associative operators
        }
    }
}

bool RPNConverter::isNumber(const std::string& token) {
    size_t dotCount = 0;

    for (size_t i = 0; i < token.length(); ++i) {
        if (token[i] == '-') {
            // Skip the negative sign at any position
            if (i != 0) {
                return false; // Invalid position for negative sign
            }
        }
        else if (token[i] == '.') {
            // Count the number of dots
            ++dotCount;
            if (dotCount > 1) {
                // More than one dot is not allowed
                return false;
            }
        }
        else if (!isDigit(token[i])) {
            // Non-digit character found
            return false;
        }
    }

    return true;
}

bool RPNConverter::isDigit(char c) {
    return ('0' <= c && c <= '9') || c == '.';
}