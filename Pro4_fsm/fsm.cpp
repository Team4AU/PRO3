////////////////////////////////////////////////////////////
//
// Source file	: fsm.cpp
// Author				: Nikolaj
// Date 				: 9 Apr 2020
// Version 			: 1.0
//
// Description : a fsm that controls the accelerometer teststand
//
////////////////////////////////////////////////////////////

#include <iostream>
#include "Testcase/Testcase.h"
#include "Jsonhandler/Datahandler.h"

#define SLEEPTIME 1000	//in micro seconds

using namespace std;

//global for mqtt
int starttest = 0;

int main (int argc, char **argv)
{
	//variables from testconfig
	int sensorid = 0;
	int steps = 0;
	int stepsize = 0;
	int samplefrequency = 0;
	int start = 0;
	int stop = 0;
	int steptimems = 0;
	int testtype = 1;

	string Jsondata; // Json string with data
	int returncode = 0;

	if (starttest)
	{
		{
			//first we convert the recived string from mqtt client to readable string
		}
		try
		{
			Datahandler toJson;
			Testcase test (sensorid, steps, stepsize, samplefrequency, start, stop,
			               steptimems,
			               testtype);
			//running testcase
			if ((returncode = (test.startTestcase ())) != 0)
			{
				throw(returncode);
			}
			//converts data to json string
			Jsondata = toJson.convertdata();
			if(Jsondata.compare(NULL) == 0)
			{
				cout <<"someting went wrong converting to data to json"<<endl;
			}
		}
		catch (int errorcode)
		{
			cout << "Something went wrong, contact support, error code is:"
					<<errorcode<<endl;
		}
		catch (exception &e)
		{
			cout << "Well, we caugth something irregular: " << e.what () << endl;
		}
		catch (...)
		{
			cout << "Another exception caught...\n";
		}

	}
	else
	{
		usleep (SLEEPTIME);
	}
	return 0;
}
