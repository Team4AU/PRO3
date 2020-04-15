//
// Created by dani on 4/11/20.
//

#include "mqttTest.h"
#include <functional>
#include "mqttMisc.h"

//ALWAYS ONLY HAVE ONE OBJECT OF THIS untill i get smarter can fix it
mqttTest::mqttTest(const char *id, const char *host, int port,
        const char * topic, bool cleanSession) {
    this->id = id;
    this->host = host;
    this->port = port;
    this->topic = topic;
    this->cleanSession = cleanSession;
    mqtt::instance = this;
}

mqttTest::~mqttTest() {
    //cleanup
    mosquitto_destroy(this->m_mosq);
    mosquitto_lib_cleanup();
}

int mqttTest::subscribe() {
    mosquitto_lib_init(); //init
    //id is clientId - can be null
    this->m_mosq = mosquitto_new(id,cleanSession,this);
    if(!this->m_mosq){
        //error
        return -1;
    }

    mosquitto_subscribe_callback_set(this->m_mosq, mqtt::onSubscribe); //callback
    mosquitto_message_callback_set(this->m_mosq, mqtt::onMessage); //callback
    mosquitto_disconnect_callback_set(this->m_mosq, mqtt::onDisconnect); //callback
    mosquitto_connect_callback_set(this->m_mosq, mqtt::onConnect); // callback

    //connect to broker
    this->rc = mosquitto_connect(this->m_mosq,this->host,this->port,this->keepAlive);
    if(rc != MOSQ_ERR_SUCCESS){
        //error
        return -1;
    }

    //subscribe to topic
    //this->rc = mosquitto_subscribe_callback(onMessage,NULL,"TOPIC",0,"HOST",1883,"CLIENT ID",60,true,"USERNAME","PASSWORD",NULL,NULL);
    if(mosquitto_subscribe(this->m_mosq,NULL,this->topic,0)
            != MOSQ_ERR_SUCCESS) {
       //ERROR subscribing
       return -1;
    }

    //start mqtt thread
    if(mosquitto_loop_start(this->m_mosq) != MOSQ_ERR_SUCCESS){
        //error
        return -1;
    }

    return 0;
}

int mqttTest::publish(const char *message) {
    if(mosquitto_publish(this->m_mosq,NULL,this->topic,strlen(message),
            message,0,0) != MOSQ_ERR_SUCCESS){
        //error
        return -1;
    }
    return 0;
}

void
mqtt::onMessage(struct mosquitto *mosq, void *userdata,
                    const struct mosquitto_message *msg) {
    //SÅDAN HER KAN JEG VIDST FÅ FAT I MIN REFERENCE - DET ER FEDT
    //mqttTest * instance = reinterpret_cast<mqttTest*>(userdata);
    //instance->disconect();
    //message received
    if(strcmp(msg->topic,"TOPIC") == 0){
        char buf[msg->payloadlen];
        memset(buf,0,msg->payloadlen*sizeof(char));
        // can get len with message->payloadlen
        memcpy(buf,msg->payload,msg->payloadlen*sizeof(char));
        //we now have message, this is what we should process to object
        //consider DO REAL CALLBACK
    }
}

void
mqtt::onSubscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count,
                      const int *granted_qos) {
    /*
    * mosq -        the mosquitto instance making the callback.
    * obj -         the user data provided in <mosquitto_new>
    * mid -         the message id of the subscribe message.
    * qos_count -   the number of granted subscriptions (size of granted_qos).
    * granted_qos - an array of integers indicating the granted QoS for each of
    *               the subscriptions.
    */

}

void mqtt::onConnect(struct mosquitto *mosq, void *obj, int rc) {
    /*
    * 0 - success
    * 1 - connection refused (unacceptable protocol version)
    * 2 - connection refused (identifier rejected)
    * 3 - connection refused (broker unavailable)
    * 4-255 - reserved for future use
    */



}

void mqtt::onDisconnect(struct mosquitto *mosq, void *obj, int rc) {
    //if rc == 0 then we called disconnect.... else its unexpected
    //alt efter hvilke fejl vi har reconnect
    mosquitto_reconnect(mosq);
}

void mqttTest::stop() {
    this->stopFlag = true;
}

void mqttTest::disconect() {
    mosquitto_disconnect(this->m_mosq);
    mosquitto_loop_stop(this->m_mosq,true);
    mosquitto_destroy(this->m_mosq);
    mosquitto_lib_cleanup();
}

/*
std::thread mqttTest::mqttClientThread() {
    return std::thread(&mqttTest::worker,this);
}

void mqttTest::worker() {
    //do my work here..
    if(subscribe() == -1){
        //failed starting up
        return;
    }

    while(!stopFlag){
        //just keep it running, callbacks handle everything else
        // DO I EVEN NEED TO RUN IT IN A THREAD ? OR LOOP ?
    }

    //here we disconnect
    mosquitto_disconnect(this->m_mosq);
    mosquitto_loop_stop(this->m_mosq,true);

}*/



