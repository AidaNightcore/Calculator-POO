#include "Calculator.h"

Calculator::Calculator() {}

Calculator::~Calculator() {}

void Calculator::run() {
    while (true) {
        try {
            // Get input from the user
            string infixExpression = getUserInput();

            if (infixExpression == "exit") {
                cout << "Exiting the calculator program." << endl;
                break;
            }

             //Convert to RPN using RPNConverter
            stack<string> rpnStack = rpnConverter.convertToRPN(infixExpression);

            //Set RPN stack in RPNEvaluator
            rpnEvaluator.setRPNStack(rpnStack);

            //// Evaluate and display the result
            double result = rpnEvaluator.evaluate();
            cout << "Result: " << result << endl;
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}


string Calculator::getUserInput() {
    string input;
    cout << "Enter an infix expression (e.g., 3 + 4 * ( 2 - 1 ) / 5): ";
    getline(cin >> ws, input); // Read the entire line, including whitespaces

    return input;
}

// Overload << operator for output
ostream& operator<<(ostream& os, const Calculator& calculator) {
    os << "Custom output for Calculator class"; // Add custom output as needed
    return os;
}

// Overload >> operator for input
istream& operator>>(istream& is, Calculator& calculator) {
    // Implement custom logic to read data for Calculator from the input stream if needed
    return is;
}