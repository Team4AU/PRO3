/*
 * TestData.h
 *
 *  Created on: 22 Feb 2020
 *      Author: Rikke
 */

#ifndef TESTDATA_H_
#define TESTDATA_H_

#include "TestConfiguration.h"
#include "SensorData.h"
#include "TestData.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define maxtimeseconds (10)

class TestData
{
	public:
		TestConfiguration Setup;
		string ToString ( );
		TestData ( );
		virtual ~TestData ( );
};

#endif /* TESTDATA_H_ */
