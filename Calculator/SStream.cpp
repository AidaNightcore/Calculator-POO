#include "SStream.h"

MySStream::MySStream(const char* str) : internalString(str) {
    refillStack();
}

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

MySStream::operator bool() const {
    return !charStack.empty();
}

bool MySStream::empty() const {
    return !static_cast<bool>(*this);
}

void MySStream::refillStack() {
    while (*internalString != '\0') {
        charStack.push(*internalString);
        ++internalString;
    }
}

bool MySStream::isDigitChar(char c) const {
    return '0' <= c && c <= '9';
}