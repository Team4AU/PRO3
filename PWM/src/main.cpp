//============================================================================
// Name        : PWM_control.cpp
// Author      : Rikke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "PWM.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main (int argC, char** argV)
{
	if (argC < 2)
	{
		PWM sweep;
		if (sweep.init ())
		{
			cout << "PWM initialised" << endl;
		}
		else
		{
			cout << "Error (pin setup)" << endl;
			return 0;
		}
		sweep.runSweep(1000,10000,1000);
	}
	else
	{
		PWM test (argV[1]);
		if (test.init ())
		{
			cout << "PWM initialised" << endl;
		}
		else
		{
			cout << "Error (pin setup)" << endl;
			return 0;
		}
		test.testMenu ();
	}
	return 0;
}
