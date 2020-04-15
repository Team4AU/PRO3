//
// Created by dani on 4/11/20.
//

#ifndef MQTT_NETWORKTHREAD_H
#define MQTT_NETWORKTHREAD_H

#include <thread>
#include "mqttClient.h"

class networkThread {
public:
    networkThread();
    virtual ~networkThread();
    void closeMqtt();
    int openMqtt();
private:
    mqttClient mqttClient;
};


#endif //MQTT_NETWORKTHREAD_H
