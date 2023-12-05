
#include "RPNConverter.h"

RPNConverter::RPNConverter() {}

RPNConverter::~RPNConverter() {}

stack<string> RPNConverter::convertToRPN(const string& infixExpression) {
    stack<string> resultStack;
    stack<char> operatorStack;

    MySStream mySStream(infixExpression.c_str());

    string token;
    cout << "Before token loop" << endl;
    while (mySStream >> token) {
        cout << "Token: " << token << endl;

        // Process each token separately
        for (size_t i = 0; i < token.size(); ++i) {
            char c = token[i];

            if (isDigit(c) || c == '.') {
                // Operand character, append to the current operand
                resultStack.push(string(1, c));
            }
            else if (isOperator(c)) {
                // Operator character, push to the result stack
                while (!operatorStack.empty() && isHigherPrecedence(operatorStack.top(), c)) {
                    resultStack.push(string(1, operatorStack.top()));
                    operatorStack.pop();
                }
                operatorStack.push(c);

                // Print the content of the operator stack for debugging
                cout << "Operator Stack: ";
                stack<char> tempStack = operatorStack;
                while (!tempStack.empty()) {
                    cout << tempStack.top() << " ";
                    tempStack.pop();
                }
                cout << endl;
            }
            else if (isOpeningBracket(c)) {
                // Opening bracket, push to operator stack
                operatorStack.push(c);
            }
            else if (isClosingBracket(c)) {
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
    cout << "After token loop" << endl;
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
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'|| c=='#';
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
bool RPNConverter::isDigit(char c) {
    return '0' <= c && c <= '9';
}