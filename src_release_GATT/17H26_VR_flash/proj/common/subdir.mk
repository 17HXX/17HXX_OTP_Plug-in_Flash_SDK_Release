################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/common/breakpoint.c \
../proj/common/compatibility.c \
../proj/common/list.c \
../proj/common/log.c \
../proj/common/mempool.c \
../proj/common/mmem.c \
../proj/common/printf.c \
../proj/common/qsort.c \
../proj/common/selection_sort.c \
../proj/common/string.c \
../proj/common/trace_17H26.c \
../proj/common/utility.c 

OBJS += \
./proj/common/breakpoint.o \
./proj/common/compatibility.o \
./proj/common/list.o \
./proj/common/log.o \
./proj/common/mempool.o \
./proj/common/mmem.o \
./proj/common/printf.o \
./proj/common/qsort.o \
./proj/common/selection_sort.o \
./proj/common/string.o \
./proj/common/trace_17H26.o \
./proj/common/utility.o 


# Each subdirectory must supply rules for building sources it contributes
proj/common/%.o: ../proj/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -DDEBUG_FROM_FLASH=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


