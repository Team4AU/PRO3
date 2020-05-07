/*
 * busException.cpp
 *
 *  Created on: May 5, 2020
 *      Author: dani
 */

#include "busException.h"

/**
 *
 * @param msg
 * @param errNum
 */
busException::busException(const std::string &msg, int errNum) :
		std::runtime_error(msg) {
	this->errorNumber = errNum;
}

busException::~busException() noexcept {
}


/**
 *
 * @return
 */
int busException::getErrorNumber() const noexcept {
    return this->errorNumber;
}
