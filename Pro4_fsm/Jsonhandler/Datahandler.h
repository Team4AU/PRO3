////////////////////////////////////////////////////////////
//
// Source file	: Datahandler.h
// Author				: Nikolaj
// Date 				: 10 Apr 2020
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef JSONHANDLER_DATAHANDLER_H_
#define JSONHANDLER_DATAHANDLER_H_

#include <iostream>
#include "TestData.h"
#include "TestConfiguration.h"
#include "SensorData.h"
#include <stdio.h>
#include <string.h>

#define ADXL345_FILE "adxl345.txt"
#define KX224_FILE	 "kx224.txt"

class Datahandler
{
	public:
		Datahandler ( );
		virtual ~Datahandler ( );

		string convertdata();
	private:
		string Jsondata;
};

#endif /* JSONHANDLER_DATAHANDLER_H_ */
