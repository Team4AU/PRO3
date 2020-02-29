//============================================================================
// Name        : main.cpp
// Author      : Rikke
// Version     :
// Copyright   : Your copyright notice
// Description : data to json string converter
//============================================================================

#include <iostream>
#include "TestData.h"
#include "TestConfiguration.h"
#include "SensorData.h"
#include <stdio.h>
#include <string.h>
using namespace std;

int main (int argC, char* argV[])
{
	string jsonData;

	TestData json;
	jsonData = json.ToString ();
	printf ("%s", jsonData.c_str ());

	return 0;
}
