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

//defines
#define BUFFER_SIZE 0x40

//ADXL345 register defines
#define DEVID          0x00   //Device ID
#define THRESH_TAP     0x1D   //Tap Threshold
#define OFSX           0x1E   //X-axis Offset
#define OFSY           0x1F   //Y-axis Offset
#define OFSZ           0x20   //Z-axis Offset
#define DUR            0x21   //Tap duration
#define LATENT         0x22   //Tap latency
#define WINDOW         0x23   //Tap window
#define THRESH_ACT     0x24   //Activity threshold
#define THRESH_INACT   0x25   //Threshold inactivity
#define TIME_INACT     0x26   //Inactivity time
#define ACT_INACT_CTL  0x27   //Axis enable control for activity and inactivity detection
#define THRESH_FF      0x28   //Free-fall threshold
#define TIME_FF        0x29   //Free-fall time
#define TAP_AXES       0x2A   //Axis control for single tap/double tap
#define ACT_TAP_STATUS 0x2B   //Source of single tap/double tap
#define BW_RATE        0x2C   //Data rate and power mode control
#define POWER_CTL      0x2D   //Power-saving features control
#define INT_ENABLE     0x2E   //Interrupt enable control
#define INT_MAP        0x2F   //Interrupt mapping control
#define INT_SOURCE     0x30   //Source of interrupts
#define DATA_FORMAT    0x31   //Data format control
#define DATAX0         0x32   //X-axis Data 0
#define DATAX1         0x33   //X-axis Data 1
#define DATAY0         0x34   //Y-axis Data 0
#define DATAY1         0x35   //Y-axis Data 1
#define DATAZ0         0x36   //Z-axis Data 0
#define DATAZ1         0x37   //Z-axis Data 1
#define FIFO_CTL       0x38   //FIFO control
#define FIFO_STATUS    0x39   //FIFO status
#define OUT_FILE       "adxl345.txt"     //Output file
#define DATALEN				6				//length of data registers in bytes

/**
* @brief Constructor for the ADXL345 class. It requires the bus nr. and device Id.
* @param bus The bus number. Usually 0 or 1 on the BBB
* @param address The device ID on the bus.
 */

ADXL345::ADXL345(Bus *busType)
{
	this->accelX = 0;
	this->accelY = 0;
	this->accelZ = 0;
	this->registers = NULL;
	this->range = ADXL345::PLUSMINUS_16_G;
	this->resolution = ADXL345::HIGH;
	this->baud = ADXL345::BANDWITH_1600_Hz;
	this->busType->writeRegister(BW_RATE, 0x0f);
	this->busType->writeRegister(POWER_CTL, 0x08);
	this->updateRegisters();
	this->olddata = new unsigned char[DATALEN];

}


ADXL345::~ADXL345()
{
	// TODO Auto-generated destructor stub
	delete(olddata);
}

/**
 * @brief combining two 8-bit registers.
 * @param msb an unsigned character that contains the most significant byte
 * @param lsb an unsigned character that contains the least significant byte
 */
short ADXL345::combineRegisters(unsigned char msb, unsigned char lsb) {
	//shift the MSB left by 8 bits and OR with LSB
	return ((short)msb << 8) | (short)lsb;
}
/**
 *  @brief used to update the DATA_FORMAT register
 * @return 0 if the register is updated successfully and 1 on failure
 */
int ADXL345::updateRegisters() {
	//update the DATA_FORMAT register
	char data_format = 0x00;  //+/- 2g with normal resolution
	//Full_resolution is the 3rd LSB
	data_format = data_format | ((this->resolution) << 3);
	data_format = data_format | this->range; // 1st and 2nd LSB therefore no shift
	return this->busType->writeRegister(DATA_FORMAT, data_format);
}

/**
 * @brief sets range on ADXL345 register 0x31
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
 * @brief sets resolution on ADXL345 register 0x31
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
 * @brief sets baud rate on ADXL345 register 0x2C
 * @return 0 on success and 1 on failure
 */
int ADXL345::setBWrate(ADXL345::BAUD baud)
{
	this->baud = baud;
	if (this->busType->writeRegister(BW_RATE, baud) == 1) {
		perror("ADXL345: Failed write Baud rate to register\n");
		return 1;
	}
	return 0;

}
/**
 * @brief Reads sensor state, by reading register 0x32-0x37 and combining 2 registers
 * @param samples int number of successive reads
 * @return 0 if the registers are successfully read and -1 if error occurrs.
 */
int ADXL345::ReadSensorState(int samples) {
	//open file here..
	if (OpenOutFile()) {
		perror("ADXL345: Failed open file");
		return -1;
	}

	for (int i = 0; i < samples;i++) {
		this->registers = this->busType->readRegisters(BUFFER_SIZE, 0x00);
		if (*this->registers != 0xe5) {
			perror("ADXL345: Failure Condition - Sensor ID not Verified");
			return -1;
		}
		//checks if data is the same as before. Registers start at the first data register
		if ((memcmp (olddata, registers + DATAX0, DATALEN)) == 0) {
			i--;
		}
		else {

		this->accelX = this->combineRegisters(*(registers + DATAX1), *(registers + DATAX0));
		this->accelY = this->combineRegisters(*(registers + DATAY1), *(registers + DATAY0));
		this->accelZ = this->combineRegisters(*(registers + DATAZ1), *(registers + DATAZ0));
		this->resolution = (ADXL345::RESOLUTION) (((*(registers + DATA_FORMAT)) & 0x08) >> 3);
		this->range = (ADXL345::RANGE) ((*(registers + DATA_FORMAT)) & 0x03);
		if (WriteDataToFile(this->accelX, this->accelY, this->accelZ)) {
			perror("ADXL345: Failed write X, Y & Z to file");
			return -1;
		}
		//sets new data to old data. Register starts at first data register
		memcpy(olddata,registers+DATAX0,DATALEN);
		}
	}
	if (CloseOutFile()) {
		perror("ADXL345: Failed close out file");
		return 1;
	}
	return 0;
}

/**
 * @brief Opens or creates output file, truncates existing file and writes
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
	this->outFile << "x,y,z\n" << endl;
	return 0;
}

/**
 * @brief Close output file
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
 * @brief Writes X, Y and Z data to output file
 * @return 0 if write is successful
 * @param x short
 * @param y short
 * @param z short
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

/**
 * @brief Writes X, Y and Z data to output file
 * @return 0 if write is successful
 */
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
