//
// Created by dani on 3/3/20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE KX224Test

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "KX224.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

using boost::test_tools::output_test_stream;

/**
* Testcase KX224TestRange
* Unit test for setting and getting range of KX224
* Sets Range in KX224 register
* Gets Range from local varible in class
*/
BOOST_AUTO_TEST_CASE(KX224TestRange)
{
	const unsigned int BUS = 1;
	const unsigned int ADDR = 0x1E;
	KX224 sensor(BUS, ADDR);

	BOOST_REQUIRE(sensor.setRange(KX224::PLUSMINUS_32_G)==0);
	BOOST_CHECK(sensor.getRange() == KX224::PLUSMINUS_32_G);
}

/**
* Testcase KX224TestXYZ
* Unit test for reading sensor data X,Y and Z
* Gets X, Y and Z from sensor registers
*/
BOOST_AUTO_TEST_CASE(KX224TestXYZ)
{

    const unsigned int BUS = 1;
    const unsigned int ADDR = 0x1E;
    KX224 sensor(BUS, ADDR);

	BOOST_REQUIRE(sensor.readSensorData() == 0);

	BOOST_CHECK(sensor.getaccelX() != 0);
	BOOST_CHECK(sensor.getaccelY() != 0);
	BOOST_CHECK(sensor.getaccelZ() != 0);
}

/**
* Testcase KX224TestWriteXYZ
* Unittest for writing 3 16 bit integers to ostream
* Appends data to file
* Closes file
*/

BOOST_AUTO_TEST_CASE(KX224TestWriteXYZ) {
        const short X = 16;
        const short Y = 11;
        const short Z = 0;
        const unsigned int BUS = 1;
        const unsigned int ADDR = 0x1E;
        KX224 sensor(BUS, ADDR);
        output_test_stream output;
        int writeStatus = sensor.WriteDataToFile(output, X, Y, Z);
        BOOST_CHECK(writeStatus == 0);
        //output << X << "," << Y << "," << Z << "\n";;
        BOOST_CHECK(output.is_equal("16,11,0\n"));
}

/**
* Testcase KX224TestOpenCloseFile
* Unittest for opening or creating file
* closes file
*/

BOOST_AUTO_TEST_CASE(KX224TestOpenCloseFile) {
        const unsigned int BUS = 1;
        const unsigned int ADDR = 0x1E;
        KX224 sensor(BUS, ADDR);

        BOOST_REQUIRE(sensor.OpenOutFile()==0); //Open file
        BOOST_CHECK(sensor.CloseOutFile() == 0);
        struct stat buffer;
        BOOST_CHECK(stat(OUT_FILE,&buffer) == 0);
}

/**
* Testcase KX224TestBaud
* Unit test for setting and getting baud rate of KX224
* Set Baud rate in KX224 register
* Gets Baud rate from local varible in class
*/
BOOST_AUTO_TEST_CASE(KX224TestBaud)
{
    const unsigned int BUS = 1;
    const unsigned int ADDR = 0x1E;
    KX224 sensor(BUS, ADDR);

	BOOST_REQUIRE(sensor.setBWrate(KX224::BANDWIDTH_12800_Hz) == 0);
	BOOST_CHECK(sensor.getBaud() == KX224::BANDWIDTH_12800_Hz);

}

/**
* Testcase KX224TestResolution
* Unit test for setting and getting range of KX224
* Set Resolution in KX224 register
* Gets Resolution from local varible in class
*/
BOOST_AUTO_TEST_CASE(KX224TestResolution)
{

    const unsigned int BUS = 1;
    const unsigned int ADDR = 0x1E;
    KX224 sensor(BUS, ADDR);

	BOOST_REQUIRE(sensor.setResolution(KX224::HIGH) == 0);
	BOOST_CHECK(sensor.getResolution() == KX224::HIGH);

}