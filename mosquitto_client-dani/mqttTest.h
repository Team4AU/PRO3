//
// Created by dani on 4/11/20.
//

#ifndef MQTT_MQTTTEST_H
#define MQTT_MQTTTEST_H

#include "mosquitto.h"
#include "mqttClient2.h"
#include <thread>
#include "cstring"
#include <cstdio>


    class mqttTest {
    public:
        mqttTest(const char * id, const char * host, int port,
                const char * topic, bool cleanSession);
        virtual ~mqttTest();
        int subscribe();
        //int subscribe(void (*onMessage)(struct mosquitto *, void *, const struct mosquitto_message *)); use this if shit is not working
        int publish(const char * message);
        void stop();
        void disconect();
        std::thread mqttClientThread();
    private:
        void worker();
        struct mosquitto *m_mosq;
        int rc;
        const char * topic;
        const char * id;
        const char * host;
        int port;
        bool cleanSession;
        const int keepAlive = 60;
        bool stopFlag = false;
    };





#endif //MQTT_MQTTTEST_H
