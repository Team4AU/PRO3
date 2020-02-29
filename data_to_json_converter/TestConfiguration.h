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
		float steps;
		float stepTimems;
		int stepSize;
		float sampleFrequency;
		TestConfiguration ( );
		TestConfiguration (int SID, int steps, float steptimems, float stepsize, float fs);
		virtual ~TestConfiguration ( );
};

#endif /* TESTCONFIGURATION_H_ */
