################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Nemico.cpp \
../src/progettoG.cpp 

O_SRCS += \
../src/Nemico.o \
../src/progettoG.o 

OBJS += \
./src/Nemico.o \
./src/progettoG.o 

CPP_DEPS += \
./src/Nemico.d \
./src/progettoG.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


