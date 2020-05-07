################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Testcase/ADXL345.cpp \
../src/Testcase/Bus.cpp \
../src/Testcase/I2C.cpp \
../src/Testcase/KX224.cpp \
../src/Testcase/PWM.cpp \
../src/Testcase/SPI.cpp \
../src/Testcase/Testcase.cpp \
../src/Testcase/busException.cpp 

OBJS += \
./src/Testcase/ADXL345.o \
./src/Testcase/Bus.o \
./src/Testcase/I2C.o \
./src/Testcase/KX224.o \
./src/Testcase/PWM.o \
./src/Testcase/SPI.o \
./src/Testcase/Testcase.o \
./src/Testcase/busException.o 

CPP_DEPS += \
./src/Testcase/ADXL345.d \
./src/Testcase/Bus.d \
./src/Testcase/I2C.d \
./src/Testcase/KX224.d \
./src/Testcase/PWM.d \
./src/Testcase/SPI.d \
./src/Testcase/Testcase.d \
./src/Testcase/busException.d 


# Each subdirectory must supply rules for building sources it contributes
src/Testcase/%.o: ../src/Testcase/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


