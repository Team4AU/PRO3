//
// Created by dani on 4/17/20.
//

#include "jsonValidationException.h"

jsonValidationException::jsonValidationException(const std::string &msg,
                                                 int errNum, int errOff):
                                                 std::runtime_error(msg) {
    this->errorNumber = errNum;
    this->errorOffset = errOff;
}

jsonValidationException::~jsonValidationException() noexcept {

}

int jsonValidationException::getErrorOffset() const noexcept {
    return this->errorOffset;
}

int jsonValidationException::getErrorNumber() const noexcept {
    return this->errorNumber;
}
