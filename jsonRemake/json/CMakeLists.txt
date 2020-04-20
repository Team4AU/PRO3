cmake_minimum_required(VERSION 3.16)
project(json)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR}/rapidjson)

add_executable(json main.cpp jsonValidationException.cpp jsonValidationException.h jsonHandler.cpp jsonHandler.h testConfig.cpp testConfig.h dataPoint.cpp dataPoint.h jsonBase.h mqttPayload.cpp mqttPayload.h)