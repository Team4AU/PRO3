////////////////////////////////////////////////////////////
//
// Source file	: Testcase.h
// Author				: Nikolaj
// Date 				: 9 Apr 2020
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef TESTCASE_TESTCASE_H_
#define TESTCASE_TESTCASE_H_

//includes
#include "Bus.h"
#include "ADXL345.h"
#include "I2C.h"
#include "ISensor.h"
#include "KX224.h"
#include "SPI.h"
#include "PWM.h"

//defines for PWM
#define BBB	"BBB"
#define PB	"PB"

const unsigned int ONEFREQ = 1;
const unsigned int SWEEP 	 = 2;
const unsigned int DUTY 	 = 50;

//bus for sensors
#define BUSADXL345 1
#define BUSKX224   1

//slave addresses
const unsigned int	ADXL345I2C = 0x53;
const unsigned int	KX224I2C	 = 0x1E; 	//or 0x1F
//spi id
const unsigned int	ADXL345SPI = 0;
const unsigned int	KX224SPI	 = 0;

//defines for samples
#define SAMPLES_I2C_ADXL 1600*5		//output rate 1600 Hz * seconds
#define SAMPLES_SPI_ADXL 3200*5		//output rate 3200 Hz * seconds
#define SAMPLES_I2C_KX224 1600*5	//output rate 1600 Hz * seconds
#define SAMPLES_SPI_KX224 3200		//output rate ?? Hz * seconds



class Testcase
{
	public:
		Testcase ( );
		Testcase (int sensorid_,int steps_,int stepsize_,int samplefrequency_,
		          int start_,int stop_, int steptimems_,int testtype_);
		virtual ~Testcase ( );
		int startTestcase();
	private:
		//sensor enums
		enum SENSORS
		{
			adxl345i2c = 1,
			adxl345spi = 2,
			kx224i2c	 = 3,
			kx224spi	 = 4
		};

		//variables from testconfig
		int steps, stepsize;	//from testconfig to PWM
		int start,stop;				//from testconfig to PWM
		int samplefrequency;  //from testconfig to PWM
		int steptimems;				//from testconfig to PWM
		int testtype;					//from testconfig to PWM
		int sensorid;					//from testconfig to ISensor/Bus
		//sensorid is used to choose sensor and bustype.
		//samples in ADXL345/KX224 (implement in Isensor instead?) is set by samplefrequency or (start,stop,steps,stepsize)
		//there are 2 combinations of sweep test? (steps,start,stop,steptimems) and (steps,stepsize,steptimems)

		//functions
		int initpwm(PWM pwm);

};

#endif /* TESTCASE_TESTCASE_H_ */

