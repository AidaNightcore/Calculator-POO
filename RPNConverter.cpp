#include "RPNConverter.h"

RPNConverter::RPNConverter() {}

RPNConverter::~RPNConverter() {}
SStack<string> RPNConverter::convertToRPN(const string& infixExpression) {
    SStack<string> resultStack;
    SStack<char> operatorStack;

    MySStream mySStream(infixExpression.c_str());

    string token, currentNumber;
    while (mySStream >> token || token!="") {
        if (isNumber(token)) {
            resultStack.push(token);
        }
        else if (token.length() == 1 && isOperator(token[0])) {
            char currentOperator = token[0];
            while (!operatorStack.empty() && isHigherPrecedence(operatorStack.top(), currentOperator) && !isOpeningBracket(operatorStack.top())) {
                resultStack.push(string(1, operatorStack.top()));
                operatorStack.pop();
            }
            operatorStack.push(currentOperator);
        }
        else {
            for (char c : token) {
                if (isDigit(c) || c == '.') {
                    currentNumber += c;
                }
                else if (isOperator(c)) {
                    char currentOperator = c;
                    if (!currentNumber.empty()) {
                        resultStack.push(currentNumber);
                        currentNumber.clear();
                    }
                    while (!operatorStack.empty() && isHigherPrecedence(operatorStack.top(), currentOperator) && !isOpeningBracket(operatorStack.top())) {
                        resultStack.push(string(1, operatorStack.top()));
                        operatorStack.pop();
                    }
                    operatorStack.push(currentOperator);
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
                        resultStack.push(string(1, operatorStack.top()));
                        operatorStack.pop();
                    }
                    if (operatorStack.empty() || !isOpeningBracket(operatorStack.top())) {
                        throw runtime_error("Mismatched brackets");
                    }
                    operatorStack.pop(); 
                }
                else {
                    throw runtime_error("Invalid character in the infix expression");
                }
            }
            if (!currentNumber.empty()) {
                resultStack.push(currentNumber);
                currentNumber.clear();
            }
        }
        token.clear();
    }

    while (!operatorStack.empty()) {
        if (isOpeningBracket(operatorStack.top())) {
            throw runtime_error("Mismatched brackets");
        }
        resultStack.push(string(1, operatorStack.top()));
        operatorStack.pop();
    }

    if (resultStack.getSize() > 2 ) {
        SStack<string> resultStackCopy;
        
        while (!resultStack.empty()) {
            resultStackCopy.push(resultStack.top());
            resultStack.pop(); 
        }
        resultStack = resultStackCopy; 
        return resultStack;
    }
    else {
        throw runtime_error("Invalid expression");
    }
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
        return 0; 
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
        
        if (op1 == '^' || op1 == '#') {
            return false; 
        }
        else {
            return true; 
        }
    }
}

bool RPNConverter::isNumber(const string& token) {
    size_t dotCount = 0;
    bool hasDot = false;

    for (size_t i = 0; i < token.length(); ++i) {
        if (token[i] == '-') {
            
            if (i != 0) {
                return false; 
            }
        }
        else if (token[i] == '.') {
            ++dotCount;
            hasDot = true;
            if (dotCount > 1) {
                throw runtime_error("Invalid expression");
            }
        }
        else if (!isDigit(token[i])) {
            return false;
        }
    }

    if (hasDot && token.back() == '.' || hasDot && token[0] == '.') {
        throw runtime_error("Invalid expression");
    }
    else return true;
}

bool RPNConverter::isDigit(char c) {
    return ('0' <= c && c <= '9') || c == '.';
}