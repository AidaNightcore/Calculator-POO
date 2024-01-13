#include "RPNConverter.h"

RPNConverter::RPNConverter() {}

RPNConverter::~RPNConverter() {}

SStack<string> RPNConverter::convertToRPN(const string& infixExpression) {
    SStack<string> resultStack;
    SStack<char> operatorStack;

    MySStream mySStream(infixExpression.c_str());

    string token;
    cout << "Before token loop" << endl;
    while (mySStream >> token) {
        cout << "Token: " << token << endl;

        if (isDigit(token[0]) || (token.size() > 1 && token[0] == '-' && isDigit(token[1]))) {
            // Operand, push to result stack
            resultStack.push(token);
        }
        else if (isOperator(token[0])) {
            // Operator character
            while (!operatorStack.empty() && isHigherPrecedence(operatorStack.top(), token[0])) {
                resultStack.push(string(1, operatorStack.top())); // Convert char to string
                operatorStack.pop();
            }
            operatorStack.push(token[0]);

            // Print the content of the operator stack for debugging
            cout << "Operator Stack: ";
            SStack<char> tempStack = operatorStack;
            while (!tempStack.empty()) {
                cout << tempStack.top() << " ";
                tempStack.pop();
            }
            cout << endl;
        }
        else {
            // Invalid token
            throw runtime_error("Invalid token in the infix expression");
        }
    }

    // Pop remaining operators from the operator stack to the result stack
    while (!operatorStack.empty()) {
        resultStack.push(string(1, operatorStack.top())); // Convert char to string
        operatorStack.pop();
    }

    cout << "After token loop" << endl;

    // Reverse the order of the RPN expression
    SStack<string> reversedStack;
    while (!resultStack.empty()) {
        reversedStack.push(resultStack.top());
        resultStack.pop();
    }

    // Return the reversed stack for better visibility
    return reversedStack;
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

    // If op1 has higher precedence, or if they have equal precedence and op1 is left-associative
    return precedence1 > precedence2 || (precedence1 == precedence2 && op1 != '^');
}


bool RPNConverter::isDigit(char c) {
    return ('0' <= c && c <= '9') || c == '.';
}
