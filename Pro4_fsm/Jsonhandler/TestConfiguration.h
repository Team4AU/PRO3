/*
 * TestConfiguration.h
 *
 *  Created on: 22 Feb 2020
 *      Author: Rikke
 */

#ifndef TESTCONFIGURATION_H_
#define TESTCONFIGURATION_H_

class TestConfiguration
{
	public:
		int sensorID;
		int steps;
		int stepTimems;
		int stepSize;
		int sampleFrequency;
		TestConfiguration ( );
		TestConfiguration (int SID, int steps, int steptimems, int stepsize, int fs);
		virtual ~TestConfiguration ( );
};

#endif /* TESTCONFIGURATION_H_ */
