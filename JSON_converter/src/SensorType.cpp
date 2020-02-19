/*
 * SensorType.cpp
 *
 *  Created on: 12 Feb 2020
 *      Author: Rikke
 */

#include "SensorType.h"

#include <stdio.h>
#include <string.h>

SensorType::SensorType ( )
{
		this->samples = 0;
		this->sampleFrequency = 0;
		this->sensorType = 1; //type of sensor
		this->sweepType = 1; //type of sweep
	puts ("Done");
	// TODO Auto-generated constructor stub

}

SensorType::~SensorType ( )
{
	// TODO Auto-generated destructor stub
}

void SensorType::InitParam(){
	this->sensorType = 1; //type of sensor
	this->sweepType = 1; //type of sweep
	this->sampleFrequency = 44100;
}
