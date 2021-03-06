//
// Created by dani on 4/17/20.
//

#include "dataPoint.h"
#define _x "x"
#define _y "y"
#define _z "z"

dataPoint::dataPoint(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

dataPoint::~dataPoint() {

}

float dataPoint::getX() {
    return this->x;
}

float dataPoint::getY() {
    return this->y;
}

float dataPoint::getZ() {
    return this->z;
}

rapidjson::Value dataPoint::toJson(rapidjson::Document::AllocatorType& allocator) {
    rapidjson::Value jObj(rapidjson::kObjectType);
    rapidjson::Value val;
    val = this->x;
    jObj.AddMember(_x,val,allocator);

    val = this->y;
    jObj.AddMember(_y,val,allocator);

    val = this->z;
    jObj.AddMember(_z,val,allocator);

    return jObj;
}

void dataPoint::toObject(const rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) {
    //we have no schema for this object
    // and do not need to do json to object at this point.
    throw "Function not implemented yet";
}

dataPoint::dataPoint() {

}
