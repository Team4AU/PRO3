//
// Created by dani on 4/12/20.
//

#ifndef MQTT_MQTTMISC_H
#define MQTT_MQTTMISC_H

namespace mqtt{
    //overvej om det er muligt have en global instans af klassen, ellers dur static ikke
    void onMessage(struct mosquitto *mosq, void *userdata,
                   const struct mosquitto_message *msg);
    void onSubscribe(struct mosquitto *mosq, void *obj, int mid,
                     int qos_count, const int *granted_qos);
    void onConnect(struct mosquitto *mosq, void *obj, int rc);
    void onDisconnect(struct mosquitto *mosq, void *obj, int rc);
    mqttTest *instance;
}

#endif //MQTT_MQTTMISC_H
