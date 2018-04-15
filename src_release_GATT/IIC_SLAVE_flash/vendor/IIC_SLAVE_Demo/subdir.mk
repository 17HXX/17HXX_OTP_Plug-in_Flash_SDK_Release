################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/IIC_SLAVE_Demo/Ui.c \
../vendor/IIC_SLAVE_Demo/app_att.c \
../vendor/IIC_SLAVE_Demo/main.c \
../vendor/IIC_SLAVE_Demo/slave_dev.c 

OBJS += \
./vendor/IIC_SLAVE_Demo/Ui.o \
./vendor/IIC_SLAVE_Demo/app_att.o \
./vendor/IIC_SLAVE_Demo/main.o \
./vendor/IIC_SLAVE_Demo/slave_dev.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/IIC_SLAVE_Demo/%.o: ../vendor/IIC_SLAVE_Demo/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -DDEBUG_FROM_FLASH=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


