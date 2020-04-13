/*
 * Mqttclient.cpp
 *
 *  Created on: Feb 15, 2020
 *      Author: nikolaj
 */

#include "Mqttclient.h"
#include <iostream>

Mqtt_client::Mqtt_client() {
	// TODO Auto-generated constructor stub
	id = NULL;
	clean_session = true;
	port = NULL;
	host = NULL;
	topic = NULL;
	obj = NULL;
	keepalive = 60;


}

Mqtt_client::~Mqtt_client() {
	// TODO Auto-generated destructor stub
	loop();              // Kill the thread
	mosqpp::lib_cleanup();    // Mosquitto library cleanup
}

Mqtt_client::Mqtt_client(const char *id, bool clean_session, int port,
	const char *host, const char *topic) :
	mosquittopp(id, clean_session) {
	mosqpp::lib_init();
	this->keepalive = 60;
	this->id = id;
	this->clean_session = clean_session;
	this->port = port;
	this->host = host;
	this->topic = topic;
	this->obj = NULL;



	connect_to();
	//mosquitto_connect_callback_set()

}

//void Mqtt_client::start_server(const char * id, bool clean_session, void * obj) {

//}

void Mqtt_client::connect_to() {

	if((connect_async(host, port, keepalive)) == MOSQ_ERR_SUCCESS) {
		std::cout <<"connected!"<<std::endl;
		loop_start();
	}
	else
		std::cout <<"failed to connect"<<std::endl;

}

/*void Mqtt_client::subscribe_to(struct mosquitto *mosq, int *mid,
		const char *sub, int qos) {
}*/

/*void Mqtt_client::publish_to(struct mosquitto *mosqm, int *mid,
		const char *topic, int payloadlen, const char *payload, int qos,
		bool retain) {
} */


void Mqtt_client::on_disconnect(int rc) {
	std::cout << ">> Beaglebone Black MQTT client - disconnection(" << rc << ")"
			<< std::endl;
}
void Mqtt_client::on_connect(int rc) {
	if (rc == 0) {
		std::cout << ">> Beaglebone Black MQTT client - connected with server"
				<< std::endl;
	} else {
		std::cout
				<< ">> Beaglebone Black MQTT client - Impossible to connect with server("
				<< rc << ")" << std::endl;
	}
}
