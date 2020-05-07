//============================================================================
// Name        : FSMTest.cpp
// Author      : dani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "fsm.h"
#include "DaemonClass.h"

using namespace std;


int main(int argc, char **argv) {
	//dæmon this
	DaemonClass Daemon;
	Daemon.createdaemon();

	std::cout << "OPSTART" << std::endl;
	fsm fsm;
	fsm.run();

	return 0;
}
