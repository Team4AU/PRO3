//
// Created by dani on 4/17/20.
//

#ifndef JSON_MQTTPAYLOAD_H
#define JSON_MQTTPAYLOAD_H


#include "jsonBase.h"
#include "testConfig.h"

class mqttPayload {
public:
    mqttPayload();
    virtual ~mqttPayload();
    void setTestConfig(testConfig test);
    testConfig getTestConfig();
    std::vector<dataPoint> getDataPoints();
    void addDataPoint(dataPoint dataPoint);
    void addDataPoints(dataPoint *dataPoints, int size);
    std::string getSentBy();
    void setSentBy(std::string sentBy);
    std::string getProtocolVersion();
    void setProtocolVersion(std::string protocolVersion);
    std::string getMsgType();
    void setMsgType(std::string msgType);
    std::vector<std::string> getCommandList();
    void addCommand(std::string command);
    std::string getStatusCode();
    void setStatusCode(std::string statusCode);
    const std::string _protocolVersion = "protocolVersion";
    const std::string _sentBy = "sentBy";
    const std::string _msgType = "msgType";
    const std::string _commandList = "commandList";
    const std::string _statusCode = "statusCode";
    const std::string _parameterObj = "parameterObj";
    const std::string _dataObj = "dataObj";
private:
    std::vector<dataPoint> dataPoints;
    testConfig test;
    std::string sentBy;
    std::string protocolVersion;
    std::string msgType;
    std::vector<std::string> commandList;
    std::string statusCode;
};


#endif //JSON_MQTTPAYLOAD_H
