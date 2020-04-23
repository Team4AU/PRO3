////////////////////////////////////////////////////////////
//
// Source file	: Testcase.cpp
// Author				: Nikolaj
// Date 				: 9 Apr 2020
// Version 			:
//
// Description : standard return if not implementet -1000
//
////////////////////////////////////////////////////////////
#include "Testcase.h"

Testcase::Testcase ( )
{
	// TODO Auto-generated constructor stub
	this->sensorid = -1;
	this->samplefrequency = -1;
	this->steps = -1;
	this->stepsize = -1;
	this->start = -1;
	this->stop = -1;
	this->steptimems = -1;
	this->testtype = -1;

}

Testcase::~Testcase ( )
{
	// TODO Auto-generated destructor stub
}

Testcase::Testcase (int sensorid_,
                    int steps_,
                    int stepsize_,
                    int samplefrequency_,
                    int start_,
                    int stop_,
                    int steptimems_,
                    int testtype_)
{
	this->sensorid = sensorid_;
	this->samplefrequency = samplefrequency_;
	this->steps = steps_;
	this->stepsize = stepsize_;
	this->start = start_;
	this->stop = -stop_;
	this->steptimems = steptimems_;
	this->testtype = testtype_;
}

int Testcase::startTestcase ( )
{
	int code;
	//calls all the private functions in testcase
	//returns 1 on succes annd -100 on fail
	/*
	 * 1. 	first it calls isensor and sets up the sensor, returns -101 on fail to setup
	 * 2. 	then it initalises PWM and sets frequency if fail returns -201 OR
	 * 2.1 	PWM sets up start,stop, steps and steptimems if fail returns -202 OR
	 * 2.2  PWM sets up steps,stepsize and steptimems, if fail returns -203
	 * 3.		PWM start test on fail returns -204
	 * 4.		ISensor start test on fail returns -102
	 * 5.	  PWM stop test on fail return -205
	 * 			retrun -1000 is if not implemeted.
	 */
	if (sensorid == adxl345i2c)	//ADXL345 I2C
	{
		I2C i2c (BUSADXL345, ADXL345I2C);
		ADXL345 adxl345 (&i2c);
		adxl345.setBWrate (ADXL345::BANDWITH_800_Hz);
		PWM pwm (BBB);
		if ((code = (this->initpwm (pwm))) != 0)
		{
			return code;
		}
		if (!pwm.startPWM ())
		{
			return -204;
		}
		if (adxl345.ReadSensorState (SAMPLES_I2C_ADXL) != 0)
		{
			return -102;
		}
		if (!pwm.stopPWM ())
		{
			return -205;
		}

	}
	else if (sensorid == adxl345spi) 	//ADXL345 SPI
	{
		SPI spi (BUSADXL345, ADXL345SPI);
		ADXL345 adxl345 (&spi);	//default bandwith is 1600 Hz
		PWM pwm (BBB);

		if ((code = (this->initpwm (pwm))) != 0)
		{
			return code;
		}
		if (!pwm.startPWM ())
		{
			return -204;
		}
		if (adxl345.ReadSensorState (SAMPLES_SPI_ADXL) != 0)
		{
			return -102;
		}
		if (!pwm.stopPWM ())
		{
			return -205;
		}

	}
	else if (sensorid == kx224i2c)		//KX224 I2C
	{
		I2C i2c (BUSKX224, KX224I2C);
		KX224 kx224 (&i2c);
		PWM pwm (BBB);
		kx224.setBWrate(KX224::BANDWIDTH_800_Hz);
		if ((code = (this->initpwm (pwm))) != 0)
		{
			return code;
		}
		if (!pwm.startPWM ())
		{
			return -204;
		}
		if (kx224.ReadSensorState (SAMPLES_I2C_KX224) != 0)
		{
			return -102;
		}
		if (!pwm.stopPWM ())
		{
			return -205;
		}

	}
	else if (sensorid == kx224spi)		//KX224 SPI
	{
		return -1000; // not implemented (spi not connected on dev-board)
		SPI spi (BUSKX224, KX224SPI);
		KX224 kx224 (&spi);
		PWM pwm (BBB);
		if ((code = (this->initpwm (pwm))) != 0)
		{
			return code;
		}
		if (!pwm.startPWM ())
		{
			return -204;
		}
		if (kx224.ReadSensorState (SAMPLES_SPI_KX224) != 0)
		{
			return -102;
		}
		if (!pwm.stopPWM ())
		{
			return -205;
		}
	}

	return 0;
}

int Testcase::initpwm (PWM pwm)
{
	if (!pwm.init ())
	{
		return -201;
	}
	if (testtype == ONEFREQ)
	{
		pwm.setup (samplefrequency, DUTY);
	}
	else if (testtype == SWEEP)
	{
		return -1000; // not implemented yet
		pwm.runSweep (start, stop, stepsize);
	}

	return 0;
}

