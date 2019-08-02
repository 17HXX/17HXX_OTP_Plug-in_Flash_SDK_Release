################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj_lib/ble_l2cap/aes_ccm.c \
../proj_lib/ble_l2cap/ble_ll_ota.c \
../proj_lib/ble_l2cap/ble_ll_pair.c \
../proj_lib/ble_l2cap/blt_att.c \
../proj_lib/ble_l2cap/blt_smp.c 

OBJS += \
./proj_lib/ble_l2cap/aes_ccm.o \
./proj_lib/ble_l2cap/ble_ll_ota.o \
./proj_lib/ble_l2cap/ble_ll_pair.o \
./proj_lib/ble_l2cap/blt_att.o \
./proj_lib/ble_l2cap/blt_smp.o 


# Each subdirectory must supply rules for building sources it contributes
proj_lib/ble_l2cap/%.o: ../proj_lib/ble_l2cap/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


