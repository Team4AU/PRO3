//
// Created by dani on 4/8/20.
//

#ifndef MQTT_MQTTCLIENT_H
#define MQTT_MQTTCLIENT_H

#include "mosquittopp.h"
#include "cstring"
#include <cstdio>

class mqttClient : public mosqpp::mosquittopp {
public:
    mqttClient(const char * id, const char * host, int port);
    virtual ~mqttClient();
    int send_messasge(const char * message);
private:
    void on_message(const struct mosquitto_message *message) override;
    void on_subscribe(int mid, int qos_count, const int *granted_qos) override;
    void on_disconnect(int rc) override;
    void on_connect(int rc) override;
    int keepAlive;
    int port;
    int rc;
    bool cleanSession;
    const char * id;
    const char * host;
    const char topic;
};


#endif //MQTT_MQTTCLIENT_H
