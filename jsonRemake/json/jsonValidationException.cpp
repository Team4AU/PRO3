//
// Created by dani on 4/17/20.
//

#include "jsonValidationException.h"

jsonValidationException::jsonValidationException(const std::string &msg,
                                                 int errNum):
                                                 std::runtime_error(msg) {
    this->errorNumber = errNum;
}

jsonValidationException::~jsonValidationException() noexcept {

}

int jsonValidationException::getErrorNumber() const noexcept {
    return this->errorNumber;
}
