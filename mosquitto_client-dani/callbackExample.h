//
// Created by dani on 4/13/20.
//

#ifndef MQTT_CALLBACKEXAMPLE_H
#define MQTT_CALLBACKEXAMPLE_H

#include <string>
#include "IMqttCallback.h"

class callbackExample : IMqttCallback {
public:
    void startup();
    //callback methods
    void onMessage(std::string message) override;
    void onSubscribe() override;
    void onConnect(int rc)override;
    void onDisconnect() override;
};


#endif //MQTT_CALLBACKEXAMPLE_H
