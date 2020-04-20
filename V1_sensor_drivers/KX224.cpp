
////////////////////////////////////////////////////////////
//
// Source file	: KX224.cpp
// Author				: Dani
// Date 				: 28 Feb 2020
// Version 			:
//
// Description : KX224 driver
//
////////////////////////////////////////////////////////////
#include "KX224.h"
#include <iostream>

KX224::KX224(unsigned int bus, unsigned int address) :
	I2C(bus, address)
{
	this->I2CAddress = address;
	this->I2CBus = bus;
	this->accelX = 0;
	this->accelY = 0;
	this->accelZ = 0;
    this->operatingMode = 0;
	this->registers = NULL;
	this->range = KX224::PLUSMINUS_16_G;
	this->resolution = KX224::HIGH;
	this->baud = KX224::BANDWIDTH_12800_Hz;

	this->setPC1(STANDBY);

	this->writeRegister(ODCNTL, 0x0f);//no filter, 12800 bandwidth

    this->setPC1(OPERATING);

	//this->updateRegisters();

}


KX224::~KX224()
{
	// TODO Auto-generated destructor stub
}

/**
 * @brief set PC1 to 0, this is required to allow writing to registers
 * @return 0 if the register is updated successfully and 1 on failure
 */
int KX224::setPC1(KX224::KX224_OPERATION operation){
    char data_format = 0x00;
    //Full_resolution is the 7th LSB
    data_format = data_format | ((this->resolution) << 7);
    data_format = data_format | (this->range << 5); // 5th and 6th LSB
    data_format = data_format | (operation << 8); //0
    return this->writeRegister(CNTL1, data_format);
}

/**
 * @brief combining two 8-bit registers.
 * @param msb an unsigned character that contains the most significant byte
 * @param lsb an unsigned character that contains the least significant byte
 */
short KX224::combineRegisters(unsigned char msb, unsigned char lsb) {
	//shift the MSB left by 8 bits and OR with LSB
	return ((short)msb << 8) | (short)lsb;
}
/**
 *  @brief used to update the DATA_FORMAT register
 *  @deprecated SHOULD NOT BE USED
 * @return 0 if the register is updated successfully and 1 on failure
 */
int KX224::updateRegisters() {
	//update the DATA_FORMAT register
	char data_format = 0x00;  //+/- 8g with lowcurrent resolution no triggers
	//Full_resolution is the 7th LSB
	data_format = data_format | ((this->resolution) << 7);
	data_format = data_format | (this->range << 5); // 5th and 6th LSB

	//dette må være CNTL1 register
	return this->writeRegister(CNTL1, data_format);
}

/**
 * @brief sets range on KX224 register 0x18
 * @return 0 on success and 1 on failure
 */

int KX224::setRange(KX224::KX224_RANGE range)
{
    if(this->setPC1(STANDBY) == 1){
        perror("KX224: Failed write Range to register\n");
        return 1;
    }

	this->range = range;

    if(this->setPC1(OPERATING) == 1){
        perror("KX224: Failed write Range to register\n");
        return 1;
    }

    /*
	if (updateRegisters() == 1) {
		perror("KX224: Failed write Range to register\n");
		return 1;
	}
     */
	return 0;
}

/**
 * @brief sets resolution on KX224 register 0x18
 * @return 0 on success and 1 on failure
 */
int KX224::setResolution(KX224::KX224_RESOLUTION resulution)
{
    if(this->setPC1(STANDBY)==1){
        perror("KX224: Failed write Resolution to register\n");
        return 1;
    }

    this->resolution = resulution;

    if(this->setPC1(OPERATING)==1){
        perror("KX224: Failed write Resolution to register\n");
        return 1;
    }


	/*
	if (updateRegisters() == 1) {
		perror("KX224: Failed write resulotion to register\n");
		return 1;
	}
	 */
	return 0;
}

/**
 * @brief sets baud rate on KX224 register 0x1B
 * @return 0 on success and 1 on failure
 */
int KX224::setBWrate(KX224::KX224_BAUD baud)
{
    if(this->setPC1(STANDBY)==1){
        perror("KX224: Failed write BW rate to register\n");
        return 1;
    }

    char data_format = 0x00;  // no filter 12.5 hz outputrate
    // 0-3 LSB output date rate
    data_format = data_format | baud;


    if (this->writeRegister(ODCNTL, data_format) == 1) {
        perror("KX224: Failed write Baud rate to register\n");
        return 1;
    }

    this->baud = baud;

    if(this->setPC1(OPERATING)==1){
        perror("KX224: Failed write BW rate to register\n");
        return 1;
    }

	return 0;

}
/**
 * @brief Reads sensor state, by reading register 0x06-0x0B and combining 2 registers
 * @param samples int number of successive reads
 * @return 0 if the registers are successfully read and -1 if error occurrs.
 */
int KX224::ReadSensorState(int samples) {

	return 0;
}

int KX224::readSensorData(){

    this->registers = this->readRegisters(BUFFER_SIZE, XOUTL);

    if(this->registers == NULL){
        perror("KX224: Failure Condition - Sensor ID not Verified");
        return -1;
    }

    this->accelX = this->combineRegisters(*(registers + 1), *(registers + 0));
    this->accelY = this->combineRegisters(*(registers + 3), *(registers + 2));
    this->accelZ = this->combineRegisters(*(registers + 5), *(registers + 4));

    return 0;
}


/**
 * @brief Opens or creates output file, truncates existing file and writes
 * header
 * @return 0 if the file is opened correctly
 */
int KX224::OpenOutFile() {
	//open output file
	this->outFile.open(OUT_FILE, ios::out | ios::trunc);
	if (!this->outFile.is_open()) {
		return 1;
	}

	//write header for file
	this->outFile << "x,y,z\n" << endl;
	return 0;
}

/**
 * @brief Close output file
 * @return 0 if file is closed
 */
int KX224::CloseOutFile() {
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
 * @brief Writes X, Y and Z data to output file
 * @return 0 if write is successful
 * @param x short
 * @param y short
 * @param z short
 */
int KX224::WriteDataToFile(short x, short y, short z) {
	//write line to output file
	//check if bad bit is set. this bit is only set when there is
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

/**
 * @brief Writes X, Y and Z data to output file
 * @return 0 if write is successful
 */
int KX224::WriteDataToFile(ostream& os, short x, short y, short z) {
	//function for testing write funcktion - boost variant
	if (os) {
		os << x << "," << y << "," << z << endl;
	}
	if (os.bad()) {
		return 1;
	}
	return 0;
}