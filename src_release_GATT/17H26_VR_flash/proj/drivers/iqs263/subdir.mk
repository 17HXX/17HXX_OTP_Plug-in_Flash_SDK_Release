################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/drivers/iqs263/IQS263_Handler.c \
../proj/drivers/iqs263/i2c_high_level.c \
../proj/drivers/iqs263/i2c_low_level.c \
../proj/drivers/iqs263/iqs_led.c 

OBJS += \
./proj/drivers/iqs263/IQS263_Handler.o \
./proj/drivers/iqs263/i2c_high_level.o \
./proj/drivers/iqs263/i2c_low_level.o \
./proj/drivers/iqs263/iqs_led.o 


# Each subdirectory must supply rules for building sources it contributes
proj/drivers/iqs263/%.o: ../proj/drivers/iqs263/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -DDEBUG_FROM_FLASH=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


