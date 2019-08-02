################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/mcu/analog.c \
../proj/mcu/anareg.c \
../proj/mcu/audhw.c \
../proj/mcu/clock.c \
../proj/mcu/cpu.c \
../proj/mcu/otp.c \
../proj/mcu/putchar.c \
../proj/mcu/random.c \
../proj/mcu/register.c \
../proj/mcu/swire.c 

OBJS += \
./proj/mcu/analog.o \
./proj/mcu/anareg.o \
./proj/mcu/audhw.o \
./proj/mcu/clock.o \
./proj/mcu/cpu.o \
./proj/mcu/otp.o \
./proj/mcu/putchar.o \
./proj/mcu/random.o \
./proj/mcu/register.o \
./proj/mcu/swire.o 


# Each subdirectory must supply rules for building sources it contributes
proj/mcu/%.o: ../proj/mcu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -DDEBUG_FROM_FLASH=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


