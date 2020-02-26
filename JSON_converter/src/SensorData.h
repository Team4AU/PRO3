/*
 * SensorData.h
 *
 *  Created on: 12 Feb 2020
 *      Author: Rikke
 */

#ifndef SENSORDATA_H_
#define SENSORDATA_H_
using namespace std;
#include <string.h>
#include <iostream>
#include <stdio.h>

#define SIZE 10

class SensorData
{
	public:
		float x[SIZE];
		float y[SIZE];
		float z[SIZE];
		SensorData ( );
		virtual ~SensorData ( );
};

#endif /* SENSORDATA_H_ */
