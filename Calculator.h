#pragma once
#include <iostream>
#include <string>
#include "RPNConverter.h"
#include "RPNEvaluator.h"


class Calculator {
public:
    Calculator();
    ~Calculator();

    void run();

    // Overload << operator for output
    friend ostream& operator<<(ostream& os, const Calculator& calculator);

    // Overload >> operator for input
    friend istream& operator>>(istream& is, Calculator& calculator);

private:
    RPNConverter rpnConverter;
    RPNEvaluator rpnEvaluator;

    string getUserInput();
};