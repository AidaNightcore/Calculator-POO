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
    RPNEvaluator(const stack<string>& rpnStack);
    ~RPNEvaluator();

    float evaluate();

    // Method to set the RPN stack
    void setRPNStack(const stack<string>& rpnStack);

private:
    stack<string> rpnStack;
    bool isDigit(char c);
    // Helper method to perform binary operations
    float performOperation(float operand1, float operand2, char op);
};
#endif // RPNEVALUATOR_H