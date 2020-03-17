#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SPITest

#include <boost/test/unit_test.hpp>
#include "SPI.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/**
* Testcase SPITestSetup
* Unit test Setting up SPI
* Sets /gets Speed
* Sets /gets polarity and Phase
* Sets /gets Bits per word
*/
BOOST_AUTO_TEST_CASE(SPITestSetup)
{
	const unsigned int BUS = 1;
	const unsigned int ADDR = 0x1E;
	const uint32_t SPEED = 1000000;
	const SPI::CPOL POLARITY = LOGIC_HIGH;
	const SPI::CPHA PHASE = FALLING_EDGE;
	const uint8_t BITS = 8;
	SPI spi(1, 0); //figure lige ud af hvilke der er
		
	BOOST_CHECK(spi.setSpeed(SPEED) == 0);
	BOOST_CHECK(spi.setMode(POLARITY, PHASE) == 0);
	BOOST_CHECK(spi.setBitsPerWord(BITS) == 0);
}

/**
* Testcase SPITestReadWriteRegister
* Unit test for Reading and writing to registers
* Writes to register 0x18
* Reads from register 0x18
* Compares
*/
BOOST_AUTO_TEST_CASE(SPITestReadWriteRegister){
	const unsigned int BUS = 1;
	const unsigned int ADDR = 0x18;
	const unsigned int LENGTH = 1;
	SPI spi(1, 0); //figure lige ud af hvilke der er

	unsigned char data_format = 0x00;
	//Full_resolution is the 7th LSB
	data_format = data_format | ((1) << 7);
	data_format = data_format | (3 << 5); // 5th and 6th LSB
	data_format = data_format | (0 << 8); //0
	
	BOOST_REQUIRE(spi.writeRegister(ADDR, data_format) == 0);
	unsigned char* return_data = spi.readRegisters(LENGTH, ADDR);
	BOOST_CHECK(strncmp(data_format, return_data, sizeof(unsigned char)) == 0);
}
