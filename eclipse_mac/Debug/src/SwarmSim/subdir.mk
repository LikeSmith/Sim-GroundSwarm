################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SwarmSim/Circle.cpp \
../src/SwarmSim/Line.cpp \
../src/SwarmSim/Map.cpp \
../src/SwarmSim/Polygon.cpp \
../src/SwarmSim/Rectangle.cpp \
../src/SwarmSim/Robot.cpp 

OBJS += \
./src/SwarmSim/Circle.o \
./src/SwarmSim/Line.o \
./src/SwarmSim/Map.o \
./src/SwarmSim/Polygon.o \
./src/SwarmSim/Rectangle.o \
./src/SwarmSim/Robot.o 

CPP_DEPS += \
./src/SwarmSim/Circle.d \
./src/SwarmSim/Line.d \
./src/SwarmSim/Map.d \
./src/SwarmSim/Polygon.d \
./src/SwarmSim/Rectangle.d \
./src/SwarmSim/Robot.d 


# Each subdirectory must supply rules for building sources it contributes
src/SwarmSim/%.o: ../src/SwarmSim/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/Users/kcrandall/GitHub/Sim-GroundSwarm/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


