################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/mcu_spec/adc_17H26.c \
../proj/mcu_spec/gpio_17H26.c \
../proj/mcu_spec/pwm_17H26.c 

S_UPPER_SRCS += \
../proj/mcu_spec/cstartup_17H26.S \
../proj/mcu_spec/cstartup_17H26_ram.S 

OBJS += \
./proj/mcu_spec/adc_17H26.o \
./proj/mcu_spec/cstartup_17H26.o \
./proj/mcu_spec/cstartup_17H26_ram.o \
./proj/mcu_spec/gpio_17H26.o \
./proj/mcu_spec/pwm_17H26.o 


# Each subdirectory must supply rules for building sources it contributes
proj/mcu_spec/%.o: ../proj/mcu_spec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -DDEBUG_FROM_FLASH=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

proj/mcu_spec/%.o: ../proj/mcu_spec/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 CC/Assembler'
	tc32-elf-gcc -DMCU_CORE_8263 -D__LOAD_RAM_SIZE__=6 -D__IRQ_STK_SIZE__=0 -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


