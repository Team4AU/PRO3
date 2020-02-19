/*
 * main.cpp
 *
 *  Created on: Feb 15, 2020
 *      Author: nikolaj
 * Description: a simple mqqt client program
 */

#include <iostream>
#include "Mqttclient.h"

#define CLIENT_ID "Team 4"
#define BROKER_ADDRESS "localhost"
#define MQTT_PORT 2000;
#define CLEAN_SESSION false
#define MQTT_TOPIC "EXAMPLE_TOPIC"

int main(int argc, char **argv) {
	class Mqtt_client *client;

	//variables used to connect with broker
	char client_id[] = CLIENT_ID;
	char host[] = BROKER_ADDRESS;
	int port = MQTT_PORT;
	bool clean_session = CLEAN_SESSION;
	char topic[] = MQTT_TOPIC;

	//creates a new mosquitto instance
	client = new Mqtt_client(client_id, clean_session, port, host, topic);



	return 0;

}

