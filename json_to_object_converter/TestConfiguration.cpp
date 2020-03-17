/*
 * TestConfiguration.cpp
 *
 *  Created on: 22 Feb 2020
 *      Author: Rikke
 */

#include "TestConfiguration.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

TestConfiguration::TestConfiguration ( )
{

	this->sampleFrequency = 0; //Hz
	this->sensorID = 0;
	this->stepSize = 0; //Hz
	this->stepTimems = 0; //ms
	this->steps = 0;
	// TODO Auto-generated constructor stub

}

TestConfiguration::~TestConfiguration ( )
{
	// TODO Auto-generated destructor stub
}

void TestConfiguration::fromJSON (string s)
{
	int fs, SID, stepsize, steptime, steps;

	string temp = s;
	size_t pos = temp.find ("SensorID");      // position of "SensorID" in str
	string temp2 = temp.substr (pos + 11, 3);
	temp2.erase (remove (temp2.begin (), temp2.end (), '\n'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), '\t'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), ','), temp2.end ());
	SID = stoi (temp2);

	temp = s;
	pos = temp.find ("Time");      // position of "Time" in str
	temp2 = temp.substr (pos + 9, 5);
	temp2.erase (remove (temp2.begin (), temp2.end (), '\n'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), '\t'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), ','), temp2.end ());
	steptime = stoi (temp2);

	temp = s;
	pos = temp.find ("Freq");      // position of "Freq" in str
	temp2 = temp.substr (pos + 12, 6);
	temp2.erase (remove (temp2.begin (), temp2.end (), '\n'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), '\t'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), ','), temp2.end ());
	fs = stoi (temp2);

	temp = s;
	pos = temp.find ("Steps");      // position of "Steps" in str
	temp2 = temp.substr (pos + 8, 3);
	temp2.erase (remove (temp2.begin (), temp2.end (), '\n'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), '\t'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), ','), temp2.end ());
	steps = stoi (temp2);

	temp = s;
	pos = temp.find ("Size");      // position of "Size" in str
	temp2 = temp.substr (pos + 7, 4);
	temp2.erase (remove (temp2.begin (), temp2.end (), '\n'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), '\t'), temp2.end ());
	temp2.erase (remove (temp2.begin (), temp2.end (), ','), temp2.end ());
	stepsize = stoi (temp2);

	this->sensorID = SID;
	this->sampleFrequency = fs; //Hz
	this->stepSize = stepsize; //Hz
	this->stepTimems = steptime; //ms
	this->steps = steps;

}
