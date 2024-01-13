#pragma once
#ifndef RPNEVALUATOR_H
#define RPNEVALUATOR_H
#include "SStream.h"
#include "Stack.h"
#include <cmath>
#include <string>

class RPNEvaluator {
public:
    RPNEvaluator();
    RPNEvaluator(const SStack<string>& rpnStack);
    ~RPNEvaluator();

    float evaluate();

    // Method to set the RPN SStack
    void setRPNStack(const SStack<string>& rpnStack);

    bool isOperator(char c) const {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '#';
    }

private:
    SStack<string> rpnStack;
    bool isDigit(char c);
    // Helper method to perform binary operations
    float performOperation(float operand1, float operand2, char op);
};
#endif // RPNEVALUATOR_H