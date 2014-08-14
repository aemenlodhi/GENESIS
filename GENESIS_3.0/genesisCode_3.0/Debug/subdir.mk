################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../codeDump.cpp \
../genesis.cpp \
../geography.cpp \
../initialization.cpp \
../ixp.cpp \
../logDebug.cpp \
../node.cpp \
../peerSelection.cpp \
../peeringTrials.cpp \
../routing.cpp \
../support.cpp \
../traffic.cpp \
../trafficEstimation.cpp 

OBJS += \
./codeDump.o \
./genesis.o \
./geography.o \
./initialization.o \
./ixp.o \
./logDebug.o \
./node.o \
./peerSelection.o \
./peeringTrials.o \
./routing.o \
./support.o \
./traffic.o \
./trafficEstimation.o 

CPP_DEPS += \
./codeDump.d \
./genesis.d \
./geography.d \
./initialization.d \
./ixp.d \
./logDebug.d \
./node.d \
./peerSelection.d \
./peeringTrials.d \
./routing.d \
./support.d \
./traffic.d \
./trafficEstimation.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


