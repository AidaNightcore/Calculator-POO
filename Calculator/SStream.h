#pragma once

class sstream {
public:
    sstream(const char* str);
    ~sstream();

    template <typename T>
    sstream& operator>>(T& value);
    template <typename T>
    sstream& operator<<(const T& value);
    const char* str() const;

private:
    char* buffer;
    size_t size;
    size_t position; 

    bool isWhitespace(char c) const; 
};

#include "SStream.cpp";

