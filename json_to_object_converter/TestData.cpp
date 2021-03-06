/*
 * TestData.cpp
 *
 *  Created on: 22 Feb 2020
 *      Author: Rikke
 */

#include "TestData.h"
#include "TestConfiguration.h"
#include "SensorData.h"
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MY_FILE "dummy_file.csv"

TestData::TestData ( )
{

	// TODO Auto-generated constructor stub

}

TestData::TestData (string s){

}

TestData::~TestData ( )
{
	// TODO Auto-generated destructor stub
}

string TestData::ToString (string json)
{
	TestConfiguration Setup;
	Setup.fromJSON(json);

	int samples = (float)Setup.sampleFrequency
		    * (((float)Setup.stepTimems * (float)Setup.steps) / 1000);

	SensorData Data[samples];

	ifstream myfile (MY_FILE);
	string text;
	if (myfile.is_open ())
	{
		for (int j = 0; j < samples; j++)
		{
			getline (myfile, text, ',');
			text.erase (remove (text.begin (), text.end (), '\n'), text.end ());
			text.erase (remove (text.begin (), text.end (), '\r'), text.end ());
			if (text == "")
			{
				break;
			}
			Data[j].x = text;

			getline (myfile, text, ',');
			text.erase (remove (text.begin (), text.end (), '\n'), text.end ());
			text.erase (remove (text.begin (), text.end (), '\r'), text.end ());
			Data[j].y = text;

			getline (myfile, text, '\n');
			text.erase (remove (text.begin (), text.end (), '\n'), text.end ());
			text.erase (remove (text.begin (), text.end (), '\r'), text.end ());
			Data[j].z = text;
		}

	}
	else
	{
		puts ("error, file not found");
	}
	myfile.close ();

	string SID = to_string (Setup.sensorID);
	string Steps = to_string (Setup.steps);
	string StepTime = to_string (Setup.stepTimems);
	string StepSize = to_string (Setup.stepSize);
	string fs = to_string (Setup.sampleFrequency);

	string s = "\t\"parameterObj\": {\n\t\t";
	s.append ("\"Setup\": {\n\t\t\t");
	s.append ("\"SensorID\": ");
	s.append (SID);
	s.append (",\n\t\t\t");
	s.append ("\"Steps\": ");
	s.append (Steps);
	s.append (",\n\t\t\t");
	s.append ("\"StepTimems\": ");
	s.append (StepTime);
	s.append (",\n\t\t\t");
	s.append ("\"StepSize\": ");
	s.append (StepSize);
	s.append (",\n\t\t\t");
	s.append ("\"SampleFrequency\": ");
	s.append (fs);
	s.append ("\n\t\t},\n\t},\n");
	s.append ("\t\"dataObj\": {\n\t\t");
	s.append ("\"Data\": {\n\t\t\t");

	string temp;
	int i;
	for (i = 0; i < samples - 1; i++)
	{
		temp = Data[i].ToString ();
		s.append (temp);
		s.append (",\n\t\t\t");
	}
	temp = Data[i].ToString ();
	s.append (temp);
	s.append ("\n\t\t},\n\t},\n");
	return s;
}
