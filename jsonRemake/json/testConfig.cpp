//
// Created by dani on 4/17/20.
//

#include <sstream>
#include "testConfig.h"

#define _sensorID "sensorID"
#define _sensorType "sensorType"
#define _startFrequency "startFrequency"
#define _stopFrequency "stopFrequency"
#define _stepFrequency "stepFrequency"
#define _stepTime "stepTime"

testConfig::testConfig() {
}

testConfig::~testConfig() {

}

rapidjson::Value testConfig::toJson(rapidjson::Document::AllocatorType& allocator) {
    rapidjson::Value jObj(rapidjson::kObjectType);
    rapidjson::Value val;

    val = this->sensorID;
    jObj.AddMember(_sensorID,val,allocator);

    val = this->sensorType;
    jObj.AddMember(_sensorType,val,allocator);

    val = this->startFrequency;
    jObj.AddMember(_startFrequency,val,allocator);

    val = this->stopFrequency;
    jObj.AddMember(_stopFrequency,val,allocator);

    val = this->stepFrequency;
    jObj.AddMember(_stepFrequency,val,allocator);

    val = this->stepTimeMs;
    jObj.AddMember(_stepTime,val,allocator);

    return jObj;
}

void testConfig::toObject(const rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) {
    //we have no schema for this object
    std::stringstream validationMsg;

    //check member
    if(!value.IsObject()){
        validationMsg << "testConfig is not an object" << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    //check member sensorID
    if(!value.HasMember(_sensorID)){
        validationMsg << "Missing member: " << _sensorID << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    if(!value[_sensorID].IsInt()){
        validationMsg << _sensorID << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    this->sensorID = value[_sensorID].GetInt();

    //check member sensorType
    if(!value.HasMember(_sensorType)){
        validationMsg << "Missing member: " << _sensorType << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    if(!value[_sensorType].IsInt()){
        validationMsg << _sensorType << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    this->sensorID = value[_sensorType].GetInt();

    //check member startFrequency
    if(!value.HasMember(_startFrequency)){
        validationMsg << "Missing member: " << _startFrequency << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    if(!value[_startFrequency].IsInt()){
        validationMsg << _startFrequency << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    this->sensorID = value[_startFrequency].GetInt();

    //check member stopFrequency
    if(!value.HasMember(_stopFrequency)){
        validationMsg << "Missing member: " << _stopFrequency << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    if(!value[_stopFrequency].IsInt()){
        validationMsg << _stopFrequency << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    this->sensorID = value[_stopFrequency].GetInt();

    //check member stepFrequency
    if(!value.HasMember(_stepFrequency)){
        validationMsg << "Missing member: " << _stepFrequency << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    if(!value[_stepFrequency].IsInt()){
        validationMsg << _stepFrequency << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),0,0);
    }
    this->sensorID = value[_stepFrequency].GetInt();

    //check member stepTime
    if(!value.HasMember(_stepTime)){
        validationMsg << "Missing member: " << _stepTime << std::endl;
        throw jsonValidationException("Missing member",0,0);
    }
    if(!value[_stepTime].IsInt()){
        validationMsg << _stepTime << ": wrong datatype" << std::endl;
        throw jsonValidationException("Member wrong datatype",0,0);
    }
    this->sensorID = value[_stepTime].GetInt();
}

int testConfig::getSensorID() {
    return this->sensorID;
}

void testConfig::setSensorID(int sensorID) {
    this->sensorID = sensorID;
}

int testConfig::getSensorType() {
    return this->sensorType;
}

void testConfig::setSensorType(int sensorType) {
    this->sensorType = sensorType;
}

int testConfig::getStartFrequency() {
    return this->startFrequency;
}

void testConfig::setStartFrequency(int startFrequency) {
    this->startFrequency = startFrequency;
}

int testConfig::getStopFrequency() {
    return this->stopFrequency;
}

void testConfig::setStopFrequency(int stopFrequency) {
    this->stopFrequency = stopFrequency;
}

int testConfig::getStepFrequency() {
    return this->stepFrequency;
}

void testConfig::setStepFrequency(int stepFrequency) {
    this->stepFrequency = stepFrequency;
}

int testConfig::getStepTimeMs() {
    return this->stepTimeMs;
}

void testConfig::setStepTimeMs(int stepTimeMs) {
    this->stepTimeMs = stepTimeMs;
}