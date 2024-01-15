#pragma once
#include <iostream>
#include <string>
#include <iomanip> 
#include "RPNConverter.h"
#include "RPNEvaluator.h"


class Calculator {
public:
    Calculator();
    ~Calculator();

    void run();

    
    friend ostream& operator<<(ostream& os, const Calculator& calculator);
    
    friend istream& operator>>(istream& is, Calculator& calculator);

private:
    RPNConverter rpnConverter;
    RPNEvaluator rpnEvaluator;

    string getUserInput();
};