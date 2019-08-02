################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/common/e2prom.c \
../vendor/common/myprintf.c \
../vendor/common/tl_audio.c 

OBJS += \
./vendor/common/e2prom.o \
./vendor/common/myprintf.o \
./vendor/common/tl_audio.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/common/%.o: ../vendor/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -DDEBUG_FROM_FLASH=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


