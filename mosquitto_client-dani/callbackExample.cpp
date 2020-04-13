//
// Created by dani on 4/13/20.
//

#include "callbackExample.h"
#include "mqttClient2.h"

void callbackExample::onMessage(std::string message) {

}

void callbackExample::onSubscribe() {

}

void callbackExample::onConnect(int rc) {

}

void callbackExample::onDisconnect() {

}

void callbackExample::startup() {
    mqttClient2 client2("client id","host ip",1883,
            "subTopic","pubTopic",true);
    client2.setCallback(this);
    client2.subscribe();
    client2.publish("IT MIGHT ACTUALLY WORK");
    client2.disconnect();
}
