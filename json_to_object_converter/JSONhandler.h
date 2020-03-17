/*
 * JSONhandler.h
 *
 *  Created on: 2 Mar 2020
 *      Author: jdoe
 */

#ifndef JSONHANDLER_H_
#define JSONHANDLER_H_

#include <string>
using namespace std;

class JSONhandler
{
	public:
		string jsonFormat;
		JSONhandler ( );
		JSONhandler (string s);
		virtual ~JSONhandler ( );
};

#endif /* JSONHANDLER_H_ */
