//
// Created by dani on 4/17/20.
//

#ifndef JSON_JSONHANDLER_H
#define JSON_JSONHANDLER_H

#include <string>
#include "testConfig.h"
#include "mqttPayload.h"

class jsonHandler {
public:
    jsonHandler();
    virtual ~jsonHandler();
    std::string toJsonString(mqttPayload data);
    mqttPayload toMqttMessage(const std::string& jsonString);
private:
    std::string getSchema();
    const std::string schemaFilePath = "protocol_v1_1.schema";
};


#endif //JSON_JSONHANDLER_H
