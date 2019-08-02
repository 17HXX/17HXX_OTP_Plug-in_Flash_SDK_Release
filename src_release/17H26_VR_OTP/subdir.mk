################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../div_mod.S 

OBJS += \
./div_mod.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.S
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 CC/Assembler'
	tc32-elf-gcc -DMCU_CORE_8263 -D__LOAD_RAM_SIZE__=6 -D__IRQ_STK_SIZE__=0 -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


