////////////////////////////////////////////////////////////
//
// Source file	: Datahandler.cpp
// Author				: Nikolaj
// Date 				: 10 Apr 2020
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#include "Datahandler.h"

Datahandler::Datahandler ( )
{
	// TODO Auto-generated constructor stub

}

Datahandler::~Datahandler ( )
{
	// TODO Auto-generated destructor stub
}

string Datahandler::convertdata ( )
{
	TestData json;
	if (json.Setup.sensorID == 1 || json.Setup.sensorID == 2)
	{
	return	Jsondata = json.ToString (ADXL345_FILE);
	}
	else if (json.Setup.sensorID == 3 || json.Setup.sensorID == 4)
	{
	return	Jsondata = json.ToString (KX224_FILE);
	}
	else {
		return NULL;
	}

}
