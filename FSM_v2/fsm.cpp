/*
 * fsm.cpp
 *
 *  Created on: Apr 23, 2020
 *      Author: nikolaj
 */

#include "fsm.h"

/*const char * id, const char * host, int port, const char * subscribeTopic,
 const char * publishTopic, bool cleanSession */

#define HOST ""
#define PORT 1883
#define SUBTOP ""
#define PUBTOP ""

fsm::fsm() :
		mqtt(NULL, HOST, PORT, SUBTOP, PUBTOP, true) {
	// TODO Auto-generated constructor stub

}

fsm::~fsm() {
	// TODO Auto-generated destructor stub
}

// sæt flag og put besked i log (start state)
// skal kunne sende status tilbage også
void fsm::onMessage(std::string message) {
	std::cout << message << std::endl;
	// hvis state er busy send busy tilbage til server
	// hvis state er ready send ok tilbage (202)
	try {
		if (busy != busy) {

			sucPayload = Jsonhandler.toMqttMessage(message);
			Jsonhandler.acknowledgeJsonMsg(sucPayload.getSentBy(),
					WebStatusCodes::_202, WebMsgTypes::_STATUS);
			this->messRecviedFlag = true;
		} else {
			mqttPayload payload = Jsonhandler.toMqttMessage(message);
			Jsonhandler.acknowledgeJsonMsg(payload.getSentBy(),
					WebStatusCodes::_501, WebMsgTypes::_STATUS);
		}
	} catch (jsonValidationException &je) {
		std::cout << je.getErrorNumber() << " " << je.what() << std::endl;
		Jsonhandler.acknowledgeJsonMsg("",
							WebStatusCodes::_400, WebMsgTypes::_STATUS);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

// sæt flag istedet for besked ( ready state 2 )
void fsm::onSubscribe() {
	std::cout << "subscribed" << std::endl;
	this->subFlag = true;
	// log? hvis onmessage ok, sæt flag gå ind i statemachine
}
// sæt flag istedet for besked ( ready state 1)
void fsm::onConnect(int rc) {
	std::cout << "connect status: " << rc << std::endl;
	if (rc)	// tjek rc returværdi
	{
		this->connectedFlag = true;
	}
}
// sæt flag istedet for besked ( sleep state)
// stop eller reconnect,
void fsm::onDisconnect() {
	std::cout << "disconnected" << std::endl;
	this->connectedFlag = false;
	this->subFlag = false;
	nextState = connect;
}
// sæt flag istedet for besked (done state)
// sender data, aknwo og status?
void fsm::onPublish(int rc) {
	std::cout << "publish status: " << rc << std::endl;
}

void fsm::run() {

	mqtt.setCallback(this);
	//starts mqtt thread
	std::thread mqttthread = mqtt.mqttThread();

	// connect (før statemachine)

	// ready state
	while (1) {
		switch (nextState) {
		case connect:
			if (connectedFlag && subFlag) {
				nextState = ready;
			}
			break;
		case ready:
			//magicsk
			if (messRecviedFlag) {
				nextState = busy;
			}
			break;
		case busy:
			messRecviedFlag = false;

			//
			break;
		default:
			break;
		}
	}
	// busy state (test, send data)
	// dc state ( er denne nødvendig)
}

void fsm::startTest() {

	try {
		if (sucPayload.getMsgType() == WebCommands::_RUN) {
			Testcase test(sucPayload.getTestConfig().getSensorID()); // NJM fix dis
			test.startTestcase();

			sucPayload.addDataPoints(); // tilføj datapoints her
			sucPayload.setStatusCode(WebStatusCodes::_200);
			sucPayload.setMsgType(WebMsgTypes::_DATA);
			std::string dataStr = Jsonhandler.payloadJsonMsg(sucPayload);
			mqtt.publish(dataStr.c_str());
			nextState = ready;

		}
	} catch (jsonValidationException &je) {
		//std::cout << je.getErrorNumber() << " " << je.what() << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
