################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../community.cpp \
../driver.cpp \
../graph.cpp \
../tabulist.cpp \
../weighted_graph.cpp 

OBJS += \
./community.o \
./driver.o \
./graph.o \
./tabulist.o \
./weighted_graph.o 

CPP_DEPS += \
./community.d \
./driver.d \
./graph.d \
./tabulist.d \
./weighted_graph.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


