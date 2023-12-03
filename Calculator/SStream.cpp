#include "SStream.h"
#include <cctype>  // for isdigit
#include <cstring> // for strlen
using namespace std; 
sstream::sstream(const char* str) : buffer(nullptr), size(strlen(str)), position(0) {
    buffer = new char[size + 1];  // +1 for null terminator
    strcpy(buffer, str);
}

sstream::~sstream() {
    delete[] buffer;
}

template <typename T>
sstream& sstream::operator>>(T& value) {
    value = 0;

    while (position < size && isWhitespace(buffer[position])) {
        position++;
    }

    int sign = 1;
    if (position < size && buffer[position] == '-') {
        sign = -1;
        position++;
    }

    while (position < size && isdigit(buffer[position])) {
        value = value * 10 + (buffer[position] - '0');
        position++;
    }

    value *= sign;

    return *this;
}

const char* sstream::str() const {
    return buffer;
}

bool sstream::isWhitespace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}
template <typename T>
sstream& sstream::operator>>(T& value) {
    
    float result = 0;
    while (buffer[position] >= '0' && buffer[position] <= '9') {
        result = result * 10 + (buffer[position] - '0');
        ++position;
    }
    value = static_cast<T>(result);
    return *this;
}

template <typename T>
sstream& sstream::operator<<(const T& value) {
    
    float temp = static_cast<float>(value);
    int digits = 0;
    while (temp > 0) {
        temp /= 10;
        ++digits;
    }

    temp = static_cast<int>(value);
    for (int i = digits - 1; i >= 0; --i) {
        buffer[position + i] = '0' + temp % 10;
        temp /= 10;
    }

    position += digits;
    return *this;
}

const char* sstream::str() const {
    return &buffer[position];
}

// Explicit instantiation of the template functions for int
