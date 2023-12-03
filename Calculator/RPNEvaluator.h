#pragma once
#include <string>
#include <stack>

class RPNEvaluator {
public:
    RPNEvaluator();
    ~RPNEvaluator();

    double calculateRPN(const string& rpnExpression);

private:
    bool isOperator(char c);
};
#include "RPNEvaluator.cpp"; 