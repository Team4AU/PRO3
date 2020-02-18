////////////////////////////////////////////////////////////
//
// Source file	: ADXL345.cpp
// Author				: Nikolaj
// Date 				: 4 Dec 2019
// Version 			:
//
// Description : adxl345 driver
//
////////////////////////////////////////////////////////////
#include "ADXL345.h"

/**
* @breif Constructor for the ADXL345 class. It requires the bus nr. and device Id.
* @param bus The bus number. Usually 0 or 1 on the BBB
* @param address The device ID on the bus.
 */

ADXL345::ADXL345(unsigned int bus, unsigned int address) :
	I2C(I2CBus, I2CAddress)
{
	this->I2CAddress = address;
	this->I2CBus = bus;
	this->accelX = 0;
	this->accelY = 0;
	this->accelZ = 0;
	this->registers = NULL;
	this->range = ADXL345::PLUSMINUS_16_G;
	this->resolution = ADXL345::HIGH;
	this->baud = ADXL345::BANDWITH_1600_Hz;
	this->writeRegister(BW_RATE, 0x0f);
	this->updateRegisters();

}

ADXL345::~ADXL345()
{
	// TODO Auto-generated destructor stub
}

/**
 * @breif combining two 8-bit registers.
 * @param msb an unsigned character that contains the most significant byte
 * @param lsb an unsigned character that contains the least significant byte
 */
short ADXL345::combineRegisters(unsigned char msb, unsigned char lsb) {
	//shift the MSB left by 8 bits and OR with LSB
	return ((short)msb << 8) | (short)lsb;
}
/**
 *  @breif used to update the DATA_FORMAT register
 * @return 0 if the register is updated successfully and 1 on failure
 */
int ADXL345::updateRegisters() {
	//update the DATA_FORMAT register
	char data_format = 0x00;  //+/- 2g with normal resolution
	//Full_resolution is the 3rd LSB
	data_format = data_format | ((this->resolution) << 3);
	data_format = data_format | this->range; // 1st and 2nd LSB therefore no shift
	return this->writeRegister(DATA_FORMAT, data_format);
}

/**
 * @breif sets range on ADXL345 register 0x31
 * @return 0 on success and 1 on failure
 */

int ADXL345::setRange(ADXL345::RANGE range)
{
	this->range = range;
	if (updateRegisters() == 1) {
		perror("ADXL345: Failed write Range to register\n");
		return 1;
	}
	return 0;
}

/**
 * @breif sets resolution on ADXL345 register 0x31
 * @return 0 on success and 1 on failure
 */
int ADXL345::setResolution(ADXL345::RESOLUTION resulution)
{
	this->resolution = resulution;
	if (updateRegisters() == 1) {
		perror("ADXL345: Failed write resulotion to register\n");
		return 1;
	}
	return 0;
}

/**
 * @breif sets baud rate on ADXL345 register 0x2C
 * @return 0 on success and 1 on failure
 */
int ADXL345::setBWrate(ADXL345::BAUD baud)
{
	this->baud = baud;
	if (this->writeRegister(BW_RATE, baud) == 1) {
		perror("ADXL345: Failed write Baud rate to register\n");
		return 1;
	}
	return 0;

}
/**
 * @breif Reads sensor state, by reading register 0x32-0x37 and combining 2 registers
 * @return 0 if the registers are successfully read and -1 if the device ID is incorrect.
 */
int ADXL345::ReadSensorState() {
	this->registers = this->readRegisters(BUFFER_SIZE, 0x00);
	if (*this->registers != 0xe5) {
		perror("ADXL345: Failure Condition - Sensor ID not Verified");
		return -1;
	}
	this->accelX = this->combineRegisters(*(registers + DATAX1), *(registers + DATAX0));
	this->accelY = this->combineRegisters(*(registers + DATAY1), *(registers + DATAY0));
	this->accelZ = this->combineRegisters(*(registers + DATAZ1), *(registers + DATAZ0));
	this->resolution = (ADXL345::RESOLUTION) (((*(registers + DATA_FORMAT)) & 0x08) >> 3);
	this->range = (ADXL345::RANGE) ((*(registers + DATA_FORMAT)) & 0x03);
	return 0;
}

/**
 * @breif Opens or creates output file, truncates existing file and writes
 * header
 * @return 0 if the file is opened correctly
 */
int ADXL345::OpenOutFile() {
	//open output file
	this->outFile.open(OUT_FILE, ios::out | ios::trunc);
	if (!this->outFile.is_open()) {
		return 1;
	}

	//write header for file
	this->outFile << "x,y,z" << endl;
	return 0;
}

/**
 * @breif Close output file
 * @return 0 if file is closed
 */
int ADXL345::CloseOutFile() {
	//close output file
	//flush buffer before file is closed
	//check for bad bit before closing.
	this->outFile.flush();
	if (this->outFile.bad()) {
		this->outFile.close();
		return 1;
	}
	this->outFile.close();
	return 0;
}

/**
 * @breif Writes X, Y and Z data to output file
 * @return 0 if write is successful
 */
int ADXL345::WriteDataToFile(short x, short y, short z) {
	//write line to output file
	//check is bad bit is set. this bit is only set when there is
	//an actual write error, not guaranteed to happen before an actual
	// write is performed.
	if (this->outFile) {
		this->outFile << x << "," << y << "," << z << endl;
	}
	if (this->outFile.bad()) {
		return 1;
	}
	return 0;
}

int ADXL345::WriteDataToFile(ostream os, short x, short y, short z) {
	//function for testing write funcktion - boost variant
	if (os) {
		os << x << "," << y << "," << z << endl;
	}
	if (os.bad()) {
		return 1;
	}
	return 0;
}
