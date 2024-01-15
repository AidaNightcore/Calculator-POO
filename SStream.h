#pragma once
#ifndef MYSSTREAM_H
#define MYSSTREAM_H

#include <string>
#include <iostream>
using namespace std;

class MySStream {
public:
    MySStream(const char* str);

    
    MySStream& operator>>(string& str);

    MySStream& operator>>(float& num);

    explicit operator bool() const;

private:
    const char* data;
};

inline MySStream::MySStream(const char* str) : data(str) {}


inline MySStream& MySStream::operator>>(string& str) {
    while (*data != '\0') {
        if (*data == ' ' || *data == '\t' || *data == '\n') {
            ++data;
            break;
        }

        str += *data;
        ++data;
    }

    return *this;
}

inline MySStream& MySStream::operator>>(float& num) {
    string str;
    *this >> str;

    num = stof(str);

    return *this;
}

inline MySStream::operator bool() const {
    return *data != '\0';
}

#endif 