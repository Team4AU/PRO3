################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/callbackExample.cpp \
../src/mosquitto.cpp \
../src/mqttClient2.cpp 

OBJS += \
./src/callbackExample.o \
./src/mosquitto.o \
./src/mqttClient2.o 

CPP_DEPS += \
./src/callbackExample.d \
./src/mosquitto.d \
./src/mqttClient2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


