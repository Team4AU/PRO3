################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Mqtt/callbackExample.cpp \
../src/Mqtt/mqttClient.cpp 

OBJS += \
./src/Mqtt/callbackExample.o \
./src/Mqtt/mqttClient.o 

CPP_DEPS += \
./src/Mqtt/callbackExample.d \
./src/Mqtt/mqttClient.d 


# Each subdirectory must supply rules for building sources it contributes
src/Mqtt/%.o: ../src/Mqtt/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


