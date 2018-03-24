################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Main.c \
../src/Struttura_Matrix_Malloc2Livelli.c \
../src/Struttura_statica_automatica.c 

OBJS += \
./src/Main.o \
./src/Struttura_Matrix_Malloc2Livelli.o \
./src/Struttura_statica_automatica.o 

C_DEPS += \
./src/Main.d \
./src/Struttura_Matrix_Malloc2Livelli.d \
./src/Struttura_statica_automatica.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


