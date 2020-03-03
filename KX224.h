////////////////////////////////////////////////////////////
//
// Source file	: KX224.h
// Author				: Dani
// Date 				: 28 Feb 2020
// Version 			:
//
// Description : KX224 driver
//
////////////////////////////////////////////////////////////

#ifndef KX224_H_
#define KX224_H_

//includes
#include <fstream>
#include"I2C.h"
#include "ISensor.h"

//defines
#define BUFFER_SIZE 0x6

#define XHPL 0x00 // X-axis high pass filter accelerometer output LSB
#define XHPH 0x01 // X-axis high pass filter accelerometer output MSB
#define YHPL 0x02 // Y-axis high pass filter accelerometer output LSB
#define YHPH 0x03 // Y-axis high pass filter accelerometer output MSB
#define ZHPL 0x04 // Z-axis high pass filter accelerometer output LSB
#define ZHPH 0x05 // Z-axis high pass filter accelerometer output MSB
#define XOUTL 0x06 // X-axis accelerometer output LSB
#define XOUTH 0x07 // X-axis accelerometer output MSB
#define YOUTL 0x08 // Y-axis accelerometer output LSB
#define YOUTH 0x09 // Y-axis accelerometer output MSB
#define ZOUTL 0x0A // Z-axis accelerometer output LSB
#define ZOUTH 0x0B // Z-axis accelerometer output MSB
#define COTR 0x0C // 
#define WHO_AM_I 0x0F // default value is 0x2B
#define TSCP 0x10 // current titlt position
#define TSPP 0x11 // previous tilt position
#define INS 0x12 //indicates tap/double tap
#define INS2 0x13 // which function caused an interrupt
#define INS3 0x14 // axis and direction detected
#define STAT 0x15 //status of interrupt
#define INT_REL 0x17 // latched interrupt source information
#define CNTL1 0x18 // controls main feature set
#define CNTL2 0x19 //provides more feature set control
#define CNTL3 0x1A // output data rates for tilt, directional tap and motion wake up digital engines
#define ODCNTL 0x1B // ODR = output data rate
#define INC1 0x1C // physical intterupt pin INT1
#define INC2 0x1D // axis and direction of detected motion interrupt
#define INC3 0x1E // axis and direction of tap/double tap interrupt
#define INC4 0x1F // routing of an interrupt reporting to physical interrupt on pin INT1
#define INC5 0x20 // physical interrupt pint INT2
#define INC6 0x21 // routing of an interupt reporting to physical interrupt in pin INT2
#define TILT_TIMER 0x22 // tilt positon state timer
#define WUFC 0x23 // initial count for motion detection timer
#define TDTRC 0x24 // enable/disable reporting of tap/double tap
#define TDTC 0x25 // counter information for dection pf double tap event
#define TTH 0x26 // high threshold to determine if a tap is detected 
#define TTL 0x27  // low threshold to determine if a tap is detected
#define FTD 0x28 // counter information of any tap event
#define STD 0x29 // counter informatino of double tap event
#define TLT 0x2A // counter information of tap event
#define TWS 0x2B // counter information of single and double taps
#define FFTH 0x2C // free fall threshold
#define FFC 0x2D // counter for free fall detection
#define FFCNTL 0x2E //free fall control
#define ATH 0x30 // wake up motion detect
#define TILT_ANGLE_L 0x32 // low threshold angle detection
#define TILT_ANGLE_H 0x33 // high threshold angle detection
#define HYST_SET 0x34 // hysteresis
#define LP_CNTL 0x35 // averaging filter control
#define BUF_CNTL1 0x3A // buffer sample threshold
#define BUF_CNTL2 0x3B // sample buffer operation
#define BUF_STATUS_1 0x3C // sample buffer status
#define BUF_STATUS_2 0x3D // sample buffer trigger function
#define BUF_CLEAR 0x3E // clear sample buffer
#define BUF_READ 0x3F // buffer output
#define SELF_TEST 0x60 // when 0xCA is written the MEMS self-test function is enabled 0x00 sets to normal operation
#define OUT_FILE       "kx224.txt"     //Output file
#define VENDOR_ADDR 0x1E //default address of KX224

//CHECK REGISTERMAP SOME REQUIRE PC1 bit in CNTL1 to be set "0" before changing contents
using namespace std;

class KX224 : protected I2C, public ISensor
{
public:
	// An enumeration to define the gravity range of the sensor
	enum KX224_RANGE {
		PLUSMINUS_8_G = 0,// plus/minus 8g
		PLUSMINUS_16_G = 1, // plus/minus 16g
		PLUSMINUS_32_G = 3 // plus/minus 32
	};
	// The resolution of the sensor. High is only available in +/- 16g range.
	enum KX224_RESOLUTION {
		LOWCURRENT = 0,//!< 8-bit resolution
		HIGH = 1   //!< HIGH 16-bit resolution
	};
	//an enumeration to define operating mode
	enum KX224_OPERATION {
	    STANDBY = 0,
	    OPERATING = 1
	};
	// an enumeration to define Baud bandwich and output rate.
	enum KX224_BAUD {
		BANDWIDTH_6f25_Hz = 0,	// BW 12.5 Hz Outputrate 2*BW Hz
		BANDWIDTH_12f5_Hz = 1,	// BW 25 Hz Outputrate 2*BW Hz
		BANDWIDTH_25_Hz = 2,	// BW 50 Hz Outputrate 2*BW Hz
		BANDWIDTH_50_Hz = 3,	// BW 100 Hz Outputrate 2*BW Hz
		BANDWIDTH_100_Hz = 4,	// BW 200 Hz Outputrate 2*BW Hz
		BANDWIDTH_200_Hz = 5,	// BW 400 Hz Outputrate 2*BW Hz
		BANDWIDTH_400_Hz = 6,	// BW 800 Hz Outputrate 2*BW Hz
		BANDWIDTH_800_Hz = 7,	// BW 1600 Hz Outputrate 2*BW Hz
		BANDWIDTH_0f39_Hz = 8,	// BW 0.781 Hz Outputrate 2*BW Hz
		BANDWIDTH_0f78_Hz = 9,	// BW 1.563 Hz Outputrate 2*BW Hz
		BANDWIDTH_1f56_Hz = 10,	// BW 3.125 Hz Outputrate 2*BW Hz
		BANDWIDTH_3f125_Hz = 11,	// BW 6.25 Hz Outputrate 2*BW Hz
		BANDWIDTH_1600_Hz = 12,	// BW 3200 Hz Outputrate 2*BW Hz
		BANDWIDTH_3200_Hz = 13,	// BW 6400 Hz Outputrate 2*BW Hz
		BANDWIDTH_6400_Hz = 14,	// BW 12800 Hz Outputrate 2*BW Hz
		BANDWIDTH_12800_Hz = 15	// BW 25600 Hz Outputrate 2*BW Hz
	};

    KX224(unsigned int bus, unsigned int address = 0x53);
    int setRange(KX224::KX224_RANGE range);
    int setResolution(KX224::KX224_RESOLUTION resolution);
    int setBWrate(KX224::KX224_BAUD baud);
    int updateRegisters();
    virtual ~KX224();
    KX224::KX224_RANGE getRange() { return this->range; };
    KX224::KX224_RESOLUTION getResolution() { return this->resolution; };
    KX224::KX224_BAUD getBaud() { return this->baud; };
    short getaccelX() { return this->accelX; };
    short getaccelY() { return this->accelY; };
    short getaccelZ() { return this->accelZ; };
    int WriteDataToFile(short x, short y, short z) override;
    int WriteDataToFile(ostream& os, short x, short y, short z);
    int OpenOutFile() override;
    int CloseOutFile() override;
    int ReadSensorState(int samples) override;
    int readSensorData();

private:
	short combineRegisters(unsigned char msb, unsigned char lsb);
	int setPC1(KX224::KX224_OPERATION operation);
	short accelX, accelY, accelZ;
	unsigned int I2CAddress, I2CBus;
	unsigned char * registers;
	unsigned int operatingMode;
    KX224::KX224_RANGE range;
    KX224::KX224_RESOLUTION resolution;
    KX224::KX224_BAUD baud;
	ofstream outFile;
};
#endif /* KX224_H_ */
