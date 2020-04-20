//
// Created by dani on 4/17/20.
//

#include "jsonHandler.h"
#include "prettywriter.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <schema.h>
/*
#define _protocolVersion "protocolVersion"
#define _sentBy "sentBy"
#define _msgType "msgType"
#define _statusCode "statusCode"
#define _parameterObj "parameterObj"
#define _dataObj "dataObj"*/

jsonHandler::jsonHandler() {

}

jsonHandler::~jsonHandler() {

}

std::string jsonHandler::toJsonString(mqttPayload payload) {
    //do my validation
    //TRY CATCH SHOULD NOT BE HERE, BUT ON OTHER SIDE WHERE WE CALL THIS FUNCTION...

    rapidjson::Document doc;

    rapidjson::Value val;

    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    //figure out why i cant use const char
    //add protocolVersion
    val.SetString(payload.getProtocolVersion().c_str(),payload.getProtocolVersion().length());
    doc.AddMember("protocolVersion",val,allocator);

    val.SetString(payload.getSentBy().c_str(),payload.getSentBy().length());
    doc.AddMember("sentBy",val,allocator);

    val.SetString(payload.getMsgType().c_str(),payload.getMsgType().length());
    doc.AddMember("msgType",val,allocator);

    //NOT SURE IF I NEED TO SEND COMMAND LIST BACK ??
    //SKIP FOR NOW

    val.SetString(payload.getStatusCode().c_str(),payload.getStatusCode().length());
    doc.AddMember("statusCode",val,allocator);

    //add paramObj
    doc.AddMember("parameterObj",payload.getTestConfig().toJson(allocator),allocator); //can i even do this?

    //add dataObj
    rapidjson::Value readings(rapidjson::kArrayType);
    //for(auto it = data.getDataPoints().begin();it != data.getDataPoints().end();++it)
    //above should work - if below does not
    for(auto & it : payload.getDataPoints()){
        readings.PushBack(it.toJson(allocator),allocator);
    }
    doc.AddMember("dataObj",readings,allocator);

    //make it a string - ready to send
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    return buffer.GetString();

    //REMEMBER TO THROW THIS EXCEPTION INSIDE
    //throw jsonValidationException("shiiiit",1,1);

}

mqttPayload jsonHandler::toMqttMessage(const std::string& jsonString) {
    rapidjson::Document doc;
    rapidjson::Document schemaDoc;

    //validate against SCHEMA
    if(schemaDoc.Parse(getSchema().c_str()).HasParseError()){
        //schema is not valid JSON
        throw jsonValidationException("JSON Schema is not valid JSON",1,0);
    }

    rapidjson::SchemaDocument schema(schemaDoc);//schemaDoc can be deallocated

    //parse to DOM
    if(doc.Parse(jsonString.c_str()).HasParseError()){
        //error
        throw jsonValidationException("Parse error in document",1,0);
    }

    rapidjson::SchemaValidator validator(schema);
    if(!doc.Accept(validator)){
        //validation error
        rapidjson::StringBuffer buffer;
        validator.GetInvalidSchemaPointer().StringifyUriFragment(buffer);
        std::stringstream errorMsg;

        errorMsg << "Invalid schema" << buffer.GetString() << std::endl <<
        "Invalid keyword: " << validator.GetInvalidSchemaKeyword() << std::endl;

        throw jsonValidationException(errorMsg.str(),1,0);
    }

    mqttPayload msg;
    testConfig testConfig;
    const rapidjson::Value& paramObj = doc[msg._parameterObj.c_str()];
    testConfig.toObject(paramObj,doc.GetAllocator()); //initialize from JSON
    msg.setTestConfig(testConfig); //set paramObj

    msg.setMsgType(doc[msg._msgType.c_str()].GetString());
    //msg.setProtocolVersion(); -- keep it like this until i know datatype
    msg.setSentBy(doc[msg._sentBy.c_str()].GetString());
    msg.setStatusCode(doc[msg._statusCode.c_str()].GetString());
    const rapidjson::Value& cmdList = doc[msg._commandList.c_str()];
    //loop array - not sure if commands are ints or strings
    for(rapidjson::Value::ConstValueIterator it = cmdList.Begin(); it != cmdList.End();++it){
        msg.addCommand(it->GetString());
    }

    /**
     * THIS IS NOT NEEDED, WHAT AM I THINKING, WE ONLY SEND DATAPOINTS NOT RECIEVE THEM
     * CODE FOR WHEN WE WANNA GO JSON TO OBJECT FOR DATAPOINTS
    const rapidjson::Value& dataObj = doc[msg._dataObj.c_str()];
    //loop array
    for(rapidjson::Value::ConstValueIterator it = dataObj.Begin(); it != dataObj.End();++it){
        dataPoint reading;
        const rapidjson::Value& jRead = *it;
        if(!reading.toObject(jRead)){
            //error - error should be thrown inside
        }
        msg.addDataPoint(reading);
    }
     */

    return mqttPayload();
}

std::string jsonHandler::getSchema() {
    //open file and get schema
    std::ifstream schemaFile;
    schemaFile.open(schemaFilePath);
    std::stringstream stringStream;
    stringStream << schemaFile.rdbuf(); //read file

    return stringStream.str();
}