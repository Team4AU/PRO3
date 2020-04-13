//
// Created by dani on 4/8/20.
//

#include "mqttClient.h"
#include <iostream>
#define PUBLISH_TOPIC "EXAMPLE_TOPIC"
#define BUFFER 1024

mqttClient::~mqttClient() {
    loop_stop();
    mosqpp::lib_cleanup();
}

int mqttClient::subscribe() {
    this->rc = mosquitto_subscribe_callback(on_message,NULL,"irc/#",0,"test.mosquitto.org",1883,NULL,60,true,NULL,NULL,NULL,NULL);
    if(rc){

    }
    return 0;
}

int mqttClient::send_messasge(const char * message) {
    return 0;
}

void mqttClient::on_disconnect(int rc) {
    //we disconnected, maybe reconnect
}

void mqttClient::on_connect(int rc) {
    if(rc == 0){
        //connected
        mosquitto_subscribe_callback(on_message,NULL,"",0,"",1883,NULL,60,true,NULL,NULL,NULL,NULL);
    }
}

void mqttClient::on_subscribe(int mid, int qos_count, const int *granted_qos) {
    //subscribed to topic
}

mqttClient::mqttClient(const char *id, const char *host, int port) : mosquittopp(id,true) {
    this->keepAlive = 60;
    this->id = id;
    this->port = port;
    this->host = host;
    mosquitto_connect()
    connect(host,port,keepAlive);
}

void mqttClient::on_message(const struct mosquitto_message *message) {
    //int payLoadSize = BUFFER + 1;

    if(strcmp(message->topic,PUBLISH_TOPIC) == 0){
        char buf[message->payloadlen];
        memset(buf,0,message->payloadlen*sizeof(char));
        // can get len with message->payloadlen
        memcpy(buf,message->payload,message->payloadlen*sizeof(char));
        //we now have message, this is what we should process to object
    }
}


