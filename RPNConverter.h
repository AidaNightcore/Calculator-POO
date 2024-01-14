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

    SStack<string> convertToRPN(const string& infixExpression);

private:
    int getPrecedence(char op);
    bool isDigit(char c);
    bool isOperator(char c);
    bool isOpeningBracket(char c);
    bool isClosingBracket(char c);
    bool isHigherPrecedence(char op1, char op2);
    bool isNumber(const string& token); 
    void handleClosingBracket(string& currentNumber, SStack<string>& resultStack, SStack<char>& operatorStack); 
    void handleOperator(string& currentNumber, SStack<string>& resultStack, SStack<char>& operatorStack, char op); 
};
#endif // RPNCONVERTER_H