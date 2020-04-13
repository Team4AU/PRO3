/*
 * TestConfiguration.h
 *
 *  Created on: 22 Feb 2020
 *      Author: Rikke
 */

#ifndef TESTCONFIGURATION_H_
#define TESTCONFIGURATION_H_

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <string>
#include <iostream>

using namespace std;

class TestConfiguration
{
	public:
		int sensorID;
		int steps;
		int stepTimems;
		int stepSize;
		int sampleFrequency;
		void fromJSON(string s);
		TestConfiguration ( );
		virtual ~TestConfiguration ( );
};

#endif /* TESTCONFIGURATION_H_ */
