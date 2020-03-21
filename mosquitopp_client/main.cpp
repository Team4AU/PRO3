/*
 * main.cpp
 *
 *  Created on: Feb 15, 2020
 *      Author: nikolaj
 */

#include <iostream>
#include "Mqttclient.h"

#define CLIENT_ID "Beaglebone Black"
#define BROKER_ADDRESS "192.168.7.1"
#define MQTT_PORT 2000;
#define CLEAN_SESSION false
#define MQTT_TOPIC "EXAMPLE_TOPIC"

int main(int argc, char **argv) {
	
	class Mqtt_client *client;
	int rc;
	char client_id[] = CLIENT_ID;
	char host[] = BROKER_ADDRESS;
	int port = MQTT_PORT;
	bool clean_session = CLEAN_SESSION;
	char topic[] = MQTT_TOPIC;
	

	client = new Mqtt_client(client_id, clean_session, port, host, topic);
	while(1)
    	{
        	rc = client->loop();
        	if (rc)
        {
        client->reconnect();
        } else client->subscribe(NULL, MQTT_TOPIC);
    	}

    	mosqpp::lib_cleanup();
	return 0;

}
