/*
 * SensorData.cpp
 *
 *  Created on: 22 Feb 2020
 *      Author: Rikke
 */

#include "SensorData.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

SensorData::SensorData ( )
{

	// TODO Auto-generated constructor stub

}

SensorData::~SensorData ( )
{
	// TODO Auto-generated destructor stub
}

string SensorData::ToString ( )
{
	// {x:1,y:2,z:3},

	string s = "{\"x\":";
	s.append(x);
	s.append(",\"y\":");
	s.append(y);
	s.append(",\"z\":");
	s.append(z);
	s.append("}");
	return s;
}
