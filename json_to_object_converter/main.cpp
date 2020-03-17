//============================================================================
// Name        : main.cpp
// Author      : Rikke
// Version     :
// Copyright   : Your copyright notice
// Description : data to json string converter
//============================================================================

#include "TestData.h"
#include "TestConfiguration.h"
#include "SensorData.h"
#include "JSONhandler.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define MY_FILE "dummy_json.txt"

int main (int argC, char* argV[])
{
	ifstream myfile (MY_FILE);
	string jsonIN ((std::istreambuf_iterator<char> (myfile)),
	                (std::istreambuf_iterator<char> ()));
	myfile.close ();


	JSONhandler jsonOUT (jsonIN);
	printf ("%s", jsonOUT.jsonFormat.c_str ());
	return 0;
}
