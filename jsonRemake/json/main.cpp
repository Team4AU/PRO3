#include <iostream>
#include "jsonHandler.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string jj = R"({"protocolVersion":1.1,
"sentBy":"kage",
"msgType":"command",
"commandList":["run"],
"statusCode":"200",
"parameterObj":{"sensorID":1,
"sensorType":2,
"startFrequency":100,
"stopFrequency":800,
"stepFrequency":0,
"stepTime":5000},
"dataObj":{}})";

    std::string js = R"({"protocolVersion":1.1,
"sentBy":"kage",
"msgType":"status",
"commandList":["status"],
"statusCode":"200",
"parameterObj":{},
"dataObj":{}})";



    jsonHandler jsonHandler;
    try {
        mqttPayload payload = jsonHandler.toMqttMessage(jj);
        std::string jsonStr = jsonHandler.payloadJsonMsg(payload);
        std::cout << jsonStr << std::endl;


        std::string ackStr = jsonHandler.acknowledgeJsonMsg(payload.getSentBy(),
                WebStatusCodes::_202,WebMsgTypes::_STATUS); //make sure other fields are correct....
        std::cout << ackStr << std::endl;


        //get string to send
        dataPoint dp(4,5,6);
        payload.addDataPoint(dp);
        payload.setMsgType(WebMsgTypes::_DATA);
        payload.setStatusCode(WebStatusCodes::_200);
        std::string dataStr = jsonHandler.payloadJsonMsg(payload);
        std::cout << dataStr << std::endl;


    } catch (jsonValidationException &je) {
        std::cout << je.getErrorNumber() << " " << je.what() << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
