/*
 * fsm.cpp
 *
 *  Created on: Apr 23, 2020
 *      Author: nikolaj
 */
#include "Testcase/busException.h"
#include "fsm.h"


#define HOST "localhost"
#define PORT 1883
#define SUBTOP "test/sub"
#define PUBTOP "test/pub"


fsm::fsm() :
		mqtt(NULL, HOST, PORT, SUBTOP, PUBTOP, true) {
	this->connectedFlag = false;
	this->subFlag = false;
	this->publishSucc = false;
	this->nextState = connect;
	this->messRecviedFlag = false;
	this->returncode = 0;

}

fsm::~fsm() {

}

/*
 *  @breif on message if not busy goes to next state
 */
void fsm::onMessage(std::string message) {
	try {
		if (nextState != busy) {

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
		Jsonhandler.acknowledgeJsonMsg("", WebStatusCodes::_400,
				WebMsgTypes::_STATUS);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

/*
 * @breif on subscribe sets subscribe flag
 */
void fsm::onSubscribe() {
	// std::cout << "subscribed" << std::endl;
	this->subFlag = true;
}

/*
 * @breif on connect sets connect flag
 */
void fsm::onConnect(int rc) {
	//std::cout << "connect status: " << rc << std::endl;
	if (!rc)	// tjek rc returværdi
	{
		this->connectedFlag = true;
	}
}
/*
 * @breif on disconnect, sets flags to false and goes to connect state
 */
void fsm::onDisconnect() {
	// std::cout << "disconnected" << std::endl;
	this->connectedFlag = false;
	this->subFlag = false;
	nextState = connect;
}

/*
 * @breif on publish do something?
 */
void fsm::onPublish(int rc) {
	//std::cout << "publish status: " << rc << std::endl;
}

void fsm::run() {

	mqtt.setCallback(this);
	//starts mqtt thread
	std::thread mqttthread = mqtt.mqttThread();

	// ready state
	while (1) {
		switch (nextState) {
		case connect:
			if (connectedFlag && subFlag) {
				nextState = ready;
			}
			break;

		case ready:
			if (messRecviedFlag) {
				nextState = busy;
			}
			break;

		case busy:
			messRecviedFlag = false;
			if(this->startTest() == -1){
				//ERROR - stadig go to ready
				nextState = ready;
			}
			break;
		case done:
			nextState = ready;
			break;

		default:
			cout<< "something went wrong"<<endl;
			break;
		}
	}
}

/*
 * @breif starts testcase and publishes message
 */
int fsm::startTest() {
	try {
		bool contin = false;
		for(auto & it : this->sucPayload.getCommandList()){
		        if(it == WebCommands::_RUN){
		            contin = true;
		        }
		    }
		if (contin) {
			Testcase test(sucPayload.getTestConfig().getSensorID(),
					sucPayload.getTestConfig().getSensorType(),
					sucPayload.getTestConfig().getStartFrequency(),
					sucPayload.getTestConfig().getStopFrequency(),
					sucPayload.getTestConfig().getStepFrequency(),
					sucPayload.getTestConfig().getStepTimeMs()); // initalize test class
			if((returncode = test.startTestcase()) != 0) {
				std::cout << "starttest error " << returncode << std::endl;
				throw(returncode);
			}

			sucPayload.addDataPoints(test.getDataPoints(),test.getDataLength()); // tilføj datapoints her
			sucPayload.setStatusCode(WebStatusCodes::_200);
			sucPayload.setMsgType(WebMsgTypes::_DATA);
			std::string dataStr = Jsonhandler.payloadJsonMsg(sucPayload);
			mqtt.publish(dataStr.c_str());
			nextState = done;
			return 1;

		}
	} catch (jsonValidationException &je) {
		std::cout << je.getErrorNumber() << " " << je.what() << std::endl;
	} catch (busException &be){
		std::cout << be.getErrorNumber() << " " << be.what() << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	} catch (int &errorTC)
	{
		cout << "Something went wrong, contact support, error code is:"
				<<errorTC<<endl;
	}
	return -1;
}
