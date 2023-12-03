#pragma once
#include "SStream.h"
#include "Stack.h"
#include <string>

class RPNConverter {
public:
    RPNConverter();
    ~RPNConverter();

    stack<string> convertToRPN(const std::string& infixExpression);

private:
    int getPrecedence(char op);
    bool isOperator(char c);
    bool isOpeningBracket(char c);
    bool isClosingBracket(char c);
    bool isHigherPrecedence(char op1, char op2);
};



#include "RPNConverter.cpp";