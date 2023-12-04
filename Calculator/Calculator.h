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
    friend std::ostream& operator<<(std::ostream& os, const Calculator& calculator);

    // Overload >> operator for input
    friend std::istream& operator>>(std::istream& is, Calculator& calculator);

private:
    RPNConverter rpnConverter;
    RPNEvaluator rpnEvaluator;

    string getUserInput();
};