/*
 * Mqttclient.h
 *
 *  Created on: Feb 15, 2020
 *      Author: nikolaj
 */

#ifndef MQTTCLIENT_H_
#define MQTTCLIENT_H_

#include <mosquittopp.h>

class Mqtt_client : public mosqpp::mosquittopp
{
private:
	const char * id;
	const char * host;
	bool clean_session;
	int port;
	const char * topic;
	void * obj;
	int keepalive;

	void connect_to();
	void on_disconnect(int rc);
	void on_connect(int rc);

public:
	Mqtt_client();
	Mqtt_client(const char * id, bool clean_session, int port,
				const char * host, const char * topic);
	virtual ~Mqtt_client();

	//void start_server(const char * id, bool clean_session, void * obj); // ikke sikkert den er nødvendig

	void subscribe_to(struct mosquitto * mosq,int * mid,
					  const char * sub, int qos);
	void publish_to(struct mosquitto * mosqm, int * mid,const char *topic,
				   int payloadlen, const char * payload, int qos, bool retain);

//tests...


};

#endif /* MQTTCLIENT_H_ */
