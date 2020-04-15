//============================================================================
// Name        : mosquitto.cpp
// Author      : dani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "callbackExample.h"
using namespace std;

int main() {
	cout << "server" << endl; // prints server
	callbackExample exp;
	exp.startup();

	return 0;
}
