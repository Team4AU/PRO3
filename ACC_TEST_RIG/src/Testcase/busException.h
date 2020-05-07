/*
 * busException.h
 *
 *  Created on: May 5, 2020
 *      Author: dani
 */

#ifndef TESTCASE_BUSEXCEPTION_H_
#define TESTCASE_BUSEXCEPTION_H_
#include <exception>
#include <stdexcept>
#include <string>

class busException : public std::runtime_error {
protected:
    int errorNumber;
public:
    explicit busException(const std::string& msg, int errNum);
    virtual ~busException() noexcept override;
    virtual int getErrorNumber() const noexcept;
};

#endif /* TESTCASE_BUSEXCEPTION_H_ */
