/*
 * TestConfiguration.cpp
 *
 *  Created on: 22 Feb 2020
 *      Author: Rikke
 */

#include "TestConfiguration.h"
#include <stdio.h>

TestConfiguration::TestConfiguration ( )
{
	/*
	 * Predefined parameters for testing
	 */
	this->sampleFrequency = 150; //Hz
	this->sensorID = 1;
	this->stepSize = 100; //Hz
	this->stepTimems = 20; //ms
	this->steps = 5;

//	this->sampleFrequency = 0;
//	this->sensorID = 0;
//	this->stepInterval = 0;
//	this->stepTimems = 0;
//	this->steps = 0;

	// TODO Auto-generated constructor stub

}

TestConfiguration::TestConfiguration (int SID, int steps, float steptimems, float stepsize, float fs)
{
	/*
	 * Predefined parameters for testing
	 */
	this->sensorID = SID;
	this->steps = steps;
	this->stepTimems = steptimems; //ms
	this->stepSize = stepsize; //Hz
	this->sampleFrequency = fs; //Hz


//	this->sampleFrequency = 0;
//	this->sensorID = 0;
//	this->stepInterval = 0;
//	this->stepTimems = 0;
//	this->steps = 0;

	// TODO Auto-generated constructor stub

}


TestConfiguration::~TestConfiguration ( )
{
	// TODO Auto-generated destructor stub
}

