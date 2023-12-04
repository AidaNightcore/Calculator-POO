#include "SStream.h"

MySStream::MySStream(const char* str) : internalString(str) {
    refillStack();
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