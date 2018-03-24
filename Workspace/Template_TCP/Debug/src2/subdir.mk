################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src2/Template_TCP.c 

OBJS += \
./src2/Template_TCP.o 

C_DEPS += \
./src2/Template_TCP.d 


# Each subdirectory must supply rules for building sources it contributes
src2/%.o: ../src2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


