/*
 * SensorData.h
 *
 *  Created on: 22 Feb 2020
 *      Author: Rikke
 */

#ifndef SENSORDATA_H_
#define SENSORDATA_H_

#include "SensorData.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

class SensorData
{
	public:
		string x;
		string y;
		string z;
		string ToString ();
		SensorData ( );
		virtual ~SensorData ( );
};

#endif /* SENSORDATA_H_ */
