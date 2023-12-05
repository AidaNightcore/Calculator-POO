#pragma once
#ifndef RPNCONVERTER_H
#define RPNCONVERTER_H 
#include "SStream.h"
#include "Stack.h"
#include <string>
#include <iostream>

class RPNConverter {
public:
    RPNConverter();
    ~RPNConverter();

    stack<string> convertToRPN(const string& infixExpression);

private:
    int getPrecedence(char op);
    bool isDigit(char c);
    bool isOperator(char c);
    bool isOpeningBracket(char c);
    bool isClosingBracket(char c);
    bool isHigherPrecedence(char op1, char op2);
};
#endif // RPNCONVERTER_H