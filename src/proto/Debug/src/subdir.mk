################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/addressbook.pb.cc \
../src/list_people.cc 

OBJS += \
./src/addressbook.pb.o \
./src/list_people.o 

CC_DEPS += \
./src/addressbook.pb.d \
./src/list_people.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/root/Downloads/boost_1_56_0 -I/home/developer/Downloads/boost_1_56_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


