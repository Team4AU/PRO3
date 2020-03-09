////////////////////////////////////////////////////////////
//
// Source file	: adxl345_test.cpp
// Author				: Nikolaj
// Date 				: 27 Feb 2020
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////

#include <iostream>
#include "ADXL345.h"
#include <unistd.h>
#include <pthread.h>

#define SAMPLES 600
using namespace std;

int main(int argc, char **argv) {

	ADXL345 sensor(1,0x53);
	sensor.setResolution(ADXL345::HIGH);
	sensor.setRange(ADXL345::PLUSMINUS_16_G);
	sensor.setBWrate(ADXL345::BANDWITH_50_Hz);

	if((sensor.OpenOutFile()) == 1)  {
		cout<<"couldn't open file"<<endl;
	return -1;
	}
	sensor.ReadSensorState(SAMPLES);

	if((sensor.CloseOutFile()) == 1) {
		cout<<"couldn't close file"<<endl;
		return -2;
	}


	return 0;

}
