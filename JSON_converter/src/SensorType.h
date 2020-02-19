/*
 * Data.h
 *
 *  Created on: 12 Feb 2020
 *      Author: Rikke
 */

#ifndef SENSORTYPE_H_
#define SENSORTYPE_H_
using namespace std;
#include <string.h>
#include <iostream>
#include <stdio.h>


class SensorType
{
	public:
		int sensorType; //type of sensor
		int sweepType; //type of sweep
		int samples; // number of samples
		int sampleFrequency; //sampling freq
		SensorType ( );
		virtual ~SensorType ( );
		void InitParam();
};

#endif /* SENSORTYPE_H_ */
