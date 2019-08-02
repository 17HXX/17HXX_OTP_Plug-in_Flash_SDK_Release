################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/VR/Ui.c \
../vendor/VR/app_att.c \
../vendor/VR/main.c 

OBJS += \
./vendor/VR/Ui.o \
./vendor/VR/app_att.o \
./vendor/VR/main.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/VR/%.o: ../vendor/VR/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


