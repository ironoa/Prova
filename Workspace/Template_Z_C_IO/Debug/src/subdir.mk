################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Main.c \
../src/Utils_SysCallFile.c \
../src/Utils_file.c \
../src/Utils_stdinRead.c 

OBJS += \
./src/Main.o \
./src/Utils_SysCallFile.o \
./src/Utils_file.o \
./src/Utils_stdinRead.o 

C_DEPS += \
./src/Main.d \
./src/Utils_SysCallFile.d \
./src/Utils_file.d \
./src/Utils_stdinRead.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


