################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj_lib/blt_ll/ble_ll_smp_master.c \
../proj_lib/blt_ll/blt_ll_17H26.c 

OBJS += \
./proj_lib/blt_ll/ble_ll_smp_master.o \
./proj_lib/blt_ll/blt_ll_17H26.o 


# Each subdirectory must supply rules for building sources it contributes
proj_lib/blt_ll/%.o: ../proj_lib/blt_ll/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


