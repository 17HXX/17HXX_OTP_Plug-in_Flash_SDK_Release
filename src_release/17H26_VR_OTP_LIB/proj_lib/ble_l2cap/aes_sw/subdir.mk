################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj_lib/ble_l2cap/aes_sw/aes_sw.c 

OBJS += \
./proj_lib/ble_l2cap/aes_sw/aes_sw.o 


# Each subdirectory must supply rules for building sources it contributes
proj_lib/ble_l2cap/aes_sw/%.o: ../proj_lib/ble_l2cap/aes_sw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


