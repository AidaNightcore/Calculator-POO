#pragma once
#ifndef MYSSTREAM_H
#define MYSSTREAM_H

#include <string>
#include <iostream>
using namespace std;

class MySStream {
public:
    MySStream(const char* str);

    // Read string from MySStream
    MySStream& operator>>(string& str);

    // Read integer from MySStream
    MySStream& operator>>(int& num);

    // Read float from MySStream
    MySStream& operator>>(float& num);

    explicit operator bool() const;

private:
    const char* data;
};

inline MySStream::MySStream(const char* str) : data(str) {}

inline MySStream& MySStream::operator>>(string& str) {
    // Read characters until a space is encountered
    while (*data != '\0' && *data != ' ' && *data != '\t' && *data != '\n') {
        str += *data;
        ++data;
    }

    // Skip whitespace characters
    while (*data == ' ' || *data == '\t' || *data == '\n') {
        ++data;
    }

    return *this;
}

inline MySStream& MySStream::operator>>(int& num) {
    // Read integer using the stoi function
    string str;
    *this >> str;

    // Convert string to integer
    num = stoi(str);

    return *this;
}

inline MySStream& MySStream::operator>>(float& num) {
    // Read float using the stof function
    string str;
    *this >> str;

    // Convert string to float
    num = stof(str);

    return *this;
}

inline MySStream::operator bool() const {
    // Return true if the stream is not at the end
    return *data != '\0';
}

#endif // MYSSTREAM_H