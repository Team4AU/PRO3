//
// Created by dani on 4/17/20.
//

#include "mqttPayload.h"

mqttPayload::mqttPayload() {

}

mqttPayload::~mqttPayload() {

}

void mqttPayload::setTestConfig(testConfig test) {
    this->test = test;
}

testConfig mqttPayload::getTestConfig() {
    return this->test;
}


void mqttPayload::addDataPoint(dataPoint dataPoint) {
    this->dataPoints.push_back(dataPoint);
}

void mqttPayload::addDataPoints(dataPoint *dataPoints, int size) {
    for (int i = 0; i < size;i++){
        this->dataPoints.push_back(dataPoints[i]);
    }
}

std::vector<dataPoint> mqttPayload::getDataPoints() {
    return this->dataPoints;
}

std::string mqttPayload::getSentBy() {
    return this->sentBy;
}

void mqttPayload::setSentBy(std::string sentBy) {
    this->sentBy = sentBy;
}

std::string mqttPayload::getProtocolVersion() {
    return this->protocolVersion;
}

void mqttPayload::setProtocolVersion(std::string protocolVersion) {
    this->protocolVersion = protocolVersion;
}

std::string mqttPayload::getMsgType() {
    return this->msgType;
}

void mqttPayload::setMsgType(std::string msgType) {
    this->msgType = msgType;
}

std::vector<std::string> mqttPayload::getCommandList() {
    return this->commandList;
}

void mqttPayload::addCommand(std::string command) {
    this->commandList.push_back(command);
}

std::string mqttPayload::getStatusCode() {
    return this->statusCode;
}

void mqttPayload::setStatusCode(std::string statusCode) {
    this->statusCode = statusCode;
}

