//
// Created by dani on 4/17/20.
//

#ifndef JSON_JSONBASE_H
#define JSON_JSONBASE_H

#include "document.h"
#include "jsonValidationException.h"

class jsonBase {
public:
    jsonBase() = default;
    virtual ~jsonBase() = default;
    virtual rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator) = 0;
    virtual void toObject(const rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) = 0;
};


#endif //JSON_JSONBASE_H
