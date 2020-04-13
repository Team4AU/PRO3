/*
 * JSONhandler.cpp
 *
 *  Created on: 2 Mar 2020
 *      Author: jdoe
 */

#include "JSONhandler.h"
#include "TestData.h"

#include <string>
using namespace std;

JSONhandler::JSONhandler ( )
{
	// TODO Auto-generated constructor stub

}

JSONhandler::JSONhandler (string s)
{
	TestData test;
	this->jsonFormat=test.ToString(s);
	// TODO Auto-generated constructor stub

}

JSONhandler::~JSONhandler ( )
{
	// TODO Auto-generated destructor stub
}

