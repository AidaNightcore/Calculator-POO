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

#endif // MYSSTREAM_H