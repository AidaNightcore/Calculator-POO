#include "Calculator.h"

Calculator::Calculator() {}

Calculator::~Calculator() {}

void Calculator::run() {
    while (true) {
        try {
            
            string infixExpression = getUserInput();

            if (infixExpression == "exit" || infixExpression == "exit ") {
                cout << "Exiting the calculator program." << endl;
                break;
            }

            SStack<string> rpnStack = rpnConverter.convertToRPN(infixExpression);
            SStack<string> rpnStackCopy = rpnStack; 
           
            
            /*cout << "RPN Expression: ";
            while (!rpnStackCopy.empty()) {
                cout << rpnStackCopy.top() << " ";
                rpnStackCopy.pop();
            }
            cout << endl;*/
            
            rpnEvaluator.setRPNStack(rpnStack);
            
            
            double result = rpnEvaluator.evaluate();
            cout << "Result: "<< setprecision(5) << result << endl;
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            
        }
    }
}


string Calculator::getUserInput() {
    string input;
    cout << "Enter an infix expression (e.g., 3 + 4 * ( 2 - 1 ) / 5): ";
    getline(cin >> ws, input); 
    return input;
}

ostream& operator<<(ostream& os, const Calculator& calculator) {
    
    return os;
}

istream& operator>>(istream& is, Calculator& calculator) {
    return is;
}