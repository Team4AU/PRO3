//
// Created by dani on 4/17/20.
//

#ifndef JSON_JSONVALIDATIONEXCEPTION_H
#define JSON_JSONVALIDATIONEXCEPTION_H
#include <exception>
#include <stdexcept>
#include <string>

class jsonValidationException : public std::runtime_error {
protected:
    int errorNumber;
    int errorOffset;
public:
    explicit jsonValidationException(const std::string& msg, int errNum, int errOff);
    ~jsonValidationException() noexcept override;
    virtual int getErrorNumber() const noexcept;
    virtual int getErrorOffset() const noexcept;
};


#endif //JSON_JSONVALIDATIONEXCEPTION_H
