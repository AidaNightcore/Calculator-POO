//#include "SStream.h"
//
//MySStream::MySStream(const char* str) : internalstring(str) {
//    refillStack();
//}
//
//
//MySStream::operator bool() const {
//    return !charStack.empty();
//}
//
//bool MySStream::empty() const {
//    return !static_cast<bool>(*this);
//}
//
//void MySStream::refillStack() {
//    while (*internalstring != '\0') {
//        charStack.push(*internalstring);
//        ++internalstring;
//    }
//}
//
//bool MySStream::isDigitChar(char c) const {
//    return '0' <= c && c <= '9';
//}