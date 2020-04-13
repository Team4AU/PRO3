//
// Created by dani on 4/12/20.
//

#include "mqttClient2.h"
/**
 * initialize mqttclient
 * no default constructor
 * @param id - Client id, If null random id will be used and cleanSession must be true
 * @param host - hostname or ip address of host
 * @param port - network port
 * @param subscribeTopic - topic to subscribe to
 * @param publishTopic - topic to publish to
 * @param cleanSession - clean all messages and subscriptions on disconnect
 */
mqttClient2::mqttClient2(const char * id, const char * host, int port, const char * subscribeTopic,
                         const char * publishTopic, bool cleanSession) {
    this->id = id;
    this->host = host;
    this->port = port;
    this->publishTopic = publishTopic;
    this->subscribeTopic = subscribeTopic;
    this->cleanSession = cleanSession;
    mosquitto_lib_init(); //init
}

/**
 * destructor
 */
mqttClient2::~mqttClient2() {
    //cleanup
    mosquitto_destroy(this->m_mosq);
    mosquitto_lib_cleanup();
}

/**
 * subscribe to mqtt broker on topic
 * (we can only handle 1 topic)
 * @return -1 on error, 0 on success
 */
int mqttClient2::subscribe() {
    //id is clientId - can be null
    this->m_mosq = mosquitto_new(this->id,this->cleanSession,this);
    if(!this->m_mosq){
        //error
        return -1;
    }

    mosquitto_subscribe_callback_set(this->m_mosq,_onSubscribe); //mqtt callback
    mosquitto_message_callback_set(this->m_mosq, _onMessage); //mqtt callback
    mosquitto_disconnect_callback_set(this->m_mosq,_onDisconnect); //mqtt callback
    mosquitto_connect_callback_set(this->m_mosq,_onConnect); //mqtt callback

    //connect to broker
    this->rc = mosquitto_connect(this->m_mosq,this->host,this->port,this->keepAlive);
    if(rc != MOSQ_ERR_SUCCESS){
        //error
        return -1;
    }

    //subscribe to topic - mid is message Id can be NULL - qos is quality of
    // ser
    /**
     * Subscribe to topic
     * mid - message id, can be NULL we do not need it
     * qos - quality of service - 0 is none????
     */
    if(mosquitto_subscribe(this->m_mosq,NULL,this->subscribeTopic,0)
       != MOSQ_ERR_SUCCESS) {
        //ERROR subscribing
        return -1;
    }

    //start mqtt thread
    if(mosquitto_loop_start(this->m_mosq) != MOSQ_ERR_SUCCESS){
        //error
        return -1;
    }
    //return success
    return 0;
}

/**
 * send message to mqtt broker
 * @param message - message to publish to broker
 * @return -1 on error, 0 on success
 */
int mqttClient2::publish(const char *message) {
    /**
     * publish - send message
     * mid - message id
     * retain - not sure......
     */
    if(mosquitto_publish(this->m_mosq,NULL,this->publishTopic,strlen(message),
                         message,0,0) != MOSQ_ERR_SUCCESS){
        //error
        return -1;
    }
    //return success
    return 0;
}

/**
 * disconnects mqtt
 * cleans up before leaving
 */
void mqttClient2::disconnect() {
    //we disconnect - clean up
    mosquitto_disconnect(this->m_mosq);
    mosquitto_loop_stop(this->m_mosq,true);
    mosquitto_destroy(this->m_mosq);
    mosquitto_lib_cleanup();
}

/**
 * mqtt onmessage event
 * calls listener
 * @param mosq - instance of mosquitto
 * @param obj - instance of "this"
 * @param msg - message received
 */
void mqttClient2::_onMessage(struct mosquitto *mosq, void *obj,
                            const struct mosquitto_message *msg) {
    //get ref to mqttClient instance
    mqttClient2 * instance = reinterpret_cast<mqttClient2*>(obj);
    //process message received
    if(strcmp(msg->topic,"TOPIC") == 0){
        char buf[msg->payloadlen];
        memset(buf,0,msg->payloadlen*sizeof(char));
        // can get len with message->payloadlen
        memcpy(buf,msg->payload,msg->payloadlen*sizeof(char));
        //we now have message, send it back to observer
        instance->_icallback->onMessage(std::string(buf));
    }
}

/**
 * mqtt onsubscribe event
 * calls listener
 * @param mosq - instance of mosquitto
 * @param obj - instance of "this"
 * @param mid - message id
 * @param qos_count - number of granted subscriptions
 * @param granted_qos - Array of int indicating qos(quality of service) for each subscriptions
 */
void mqttClient2::_onSubscribe(struct mosquitto *mosq, void *obj, int mid,
                              int qos_count, const int *granted_qos) {
    //get ref to mqttClient instance
    auto * instance = reinterpret_cast<mqttClient2*>(obj);
    //tell world we subscribed - and can receive messages now
    instance->_icallback->onSubscribe();
}

/**
 * mqtt onconnect event
 * calls listener
 * @param mosq - instance of mosquitto
 * @param obj - instance of "this"
 * @param rc - status
 */
void mqttClient2::_onConnect(struct mosquitto *mosq, void *obj, int rc) {
    /*
     * status
     * 0 - success
     * 1 - connection refused (unacceptable protocol version)
     * 2 - connection refused (identifier rejected)
     * 3 - connection refused (broker unavailable)
     * 4-255 - reserved for future use
     */

    //get ref to mqttClient instance
    auto * instance = reinterpret_cast<mqttClient2*>(obj);
    //tell "world" we connected - this might not be needed
    instance->_icallback->onConnect(rc);
}

/**
 * mqtt ondisconnect event
 * calls listener
 * @param mosq - instance of mosquitto
 * @param obj - instance of "this"
 * @param rc - int indicating what happened
 */
void mqttClient2::_onDisconnect(struct mosquitto *mosq, void *obj, int rc) {
    /*
     * MQTT automatically tries to reconnect every 1 second forever
     * to change this behaviour use mosquitto_reconnect_delay_set
     * because we use loop()
     * if rc == 0 then we called disconnect.... else its unexpected
     */

    //get ref to mqttClient instance
    auto * instance = reinterpret_cast<mqttClient2*>(obj);
    //tell "world" we disconnected and can not send or receive atm.
    instance->_icallback->onDisconnect();
}

/**
 * Set listener for callbacks
 * @param _icallback - ref to listener
 */
void mqttClient2::setCallback(IMqttCallback *_icallback) {
    this->_icallback = _icallback;
}


