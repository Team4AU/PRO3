//============================================================================
// Name        : main.cpp
// Author      : Rikke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h>       /* time */
#include <string.h>
#include <algorithm>
#include <string>

#include "SensorType.h"
#include "SensorData.h"

#define MY_FILE "test.json"

using namespace std;

void ReadData (SensorType *P, SensorData *T);
void JSONstart (SensorType *P, SensorData *T);
void JSONserialize (SensorType *P, SensorData *T);
void JSONfinish (SensorType *P, SensorData *T);

int main ( )
{
	srand (time (NULL)); //for testing random data

	SensorType* Test;
	Test = (SensorType*) malloc (sizeof(SensorType));
	Test->InitParam ();

	SensorData* Data;
	Data = (SensorData*) malloc (sizeof(SensorData));

	ReadData (Test, Data);

	JSONserialize (Test, Data);

	free (Test);
	free (Data);
	puts ("Done");
	return 0;
}

void JSONserialize (SensorType *P, SensorData *T)
{
	ofstream myfile (MY_FILE, ios::app);

	JSONstart (P, T);
	if (myfile.is_open ())
	{
		myfile << "\n\t\t\"x\": [";
		int i;
		for (i = 0; i < P->samples - 1; i++)
		{
			myfile << T->x[i] << ", ";
		}
		myfile << T->x[i] << "],";

		myfile << "\n\t\t\"y\": [";

		for (i = 0; i < P->samples - 1; i++)
		{
			myfile << T->y[i] << ", ";
		}
		myfile << T->y[i] << "],";

		myfile << "\n\t\t\"z\": [";

		for (i = 0; i < P->samples - 1; i++)
		{
			myfile << T->z[i] << ", ";
		}
		myfile << T->z[i] << "]\n\t},\n";
	}
	else
		cout << "Unable to open file";
	myfile.close ();
	JSONfinish (P, T);
}

void JSONstart (SensorType *P, SensorData *T)
{
	ofstream myfile (MY_FILE);
	time_t tt;
	struct tm * ti;
	time (&tt);
	ti = localtime (&tt);
	string date = asctime (ti);
	date.erase (remove (date.begin (), date.end (), '\n'), date.end ());
	if (myfile.is_open ())
	{
		myfile << "{\n\t\"protocolVersion\": " <<
		    "1.0" << ",\n";
		myfile << "\t\"sentBy\": \"" <<
		    "accelerometerTeststand" << "\",\n";
		myfile << "\t\"msgType\": " <<
		    "\"data\"" << ",\n\n";

		myfile << "\t\"commandList\": \"" <<
		    "list\", \"of\", \"commands" << "\",\n\n";

		myfile << "\t\"statusCode\": \"" <<
		    "succes" << "\",\n\n";

		myfile << "\t\"parameterObj\": " <<
		    "{\n\t\t\"sensorType\": " << P->sensorType <<
		    ",\n";
		myfile << "\t\t\"sweepType\": " << P->sweepType <<
		    ",\n";
		myfile << "\t\t\"userID\": " << "15326" <<
		    ",\n\t},\n";

		myfile << "\t\"dataObj\": " <<
		    "{";
		myfile << "\n\t\t\"samples\": " << P->samples << ",";
		myfile << "\n\t\t\"sampleFrequency\": " << P->sampleFrequency << ",";
		myfile << "\n\t\t\"sensorType\": " << P->sensorType << ",";
		myfile << "\n\t\t\"date\": \"" << date <<
		    "\",";
		myfile.close ();
	}
	else
		cout << "Unable to open file";
}

void JSONfinish (SensorType *P, SensorData *T)
{
	ofstream myfile (MY_FILE, ios::app);

	if (myfile.is_open ())
	{

		myfile << endl << "\t\"embeddedFileFormat\": \"" <<
		    "0" << "\"," << endl;
		myfile << "\t\"embeddedFile\": \"" <<
		    "0" << "\"" << endl << endl << "}";

		myfile.close ();
	}
	else
		cout << "Unable to open file";
}

void ReadData (SensorType *P, SensorData *T)
{
	int len = sizeof(T->x) / sizeof(*T->x);
	P->samples = len;
	for (int i = 0; i < len; i++)
	{
		T->x[i] = rand () % 100;
		T->y[i] = rand () % 100;
		T->z[i] = rand () % 100;
	}
}
