#pragma once
#ifndef MYSSTREAM_H
#define MYSSTREAM_H
#include <iostream>
#include "Stack.h"
using namespace std; 
class MySStream {
public:
    MySStream(const char* str);

    template <typename T>
    MySStream& operator>>(T& value);

    explicit operator bool() const;
    bool empty() const;

private:
    const char* internalString;
    stack<char> charStack;

    void refillStack();
    bool isDigitChar(char c) const;
};

template <typename T>
MySStream& MySStream::operator>>(T& value) {
    if (charStack.empty()) {
        return *this;
    }

    // Extract a numeric value
    bool isNegative = false;
    if (charStack.top() == '-') {
        isNegative = true;
        charStack.pop();
    }

    // Extract integer part
    value = 0;
    while (!charStack.empty() && isDigitChar(charStack.top())) {
        value = value * 10 + (charStack.top() - '0');
        charStack.pop();
    }

    // Handle fractional part for float
    if (!charStack.empty() && charStack.top() == '.') {
        charStack.pop();
        double fractionalPart = 0.1;  // Starting with 0.1 for the first decimal place
        while (!charStack.empty() && isDigitChar(charStack.top())) {
            value += fractionalPart * (charStack.top() - '0');
            fractionalPart /= 10.0;
            charStack.pop();
        }
    }

    if (isNegative) {
        value = -value;
    }

    return *this;
}
#endif // MYSSTREAM_H