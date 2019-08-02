################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/drivers/audio.c \
../proj/drivers/battery.c \
../proj/drivers/button.c \
../proj/drivers/dfifo.c \
../proj/drivers/dma_uart_ctrl.c \
../proj/drivers/dma_uart_hw.c \
../proj/drivers/flash.c \
../proj/drivers/i2c.c \
../proj/drivers/id.c \
../proj/drivers/ip_adapt.c \
../proj/drivers/keyboard.c \
../proj/drivers/mic.c \
../proj/drivers/spi.c \
../proj/drivers/syshw.c \
../proj/drivers/uart.c \
../proj/drivers/usb.c \
../proj/drivers/usb_uart.c \
../proj/drivers/usbdesc.c \
../proj/drivers/usbhw.c 

OBJS += \
./proj/drivers/audio.o \
./proj/drivers/battery.o \
./proj/drivers/button.o \
./proj/drivers/dfifo.o \
./proj/drivers/dma_uart_ctrl.o \
./proj/drivers/dma_uart_hw.o \
./proj/drivers/flash.o \
./proj/drivers/i2c.o \
./proj/drivers/id.o \
./proj/drivers/ip_adapt.o \
./proj/drivers/keyboard.o \
./proj/drivers/mic.o \
./proj/drivers/spi.o \
./proj/drivers/syshw.o \
./proj/drivers/uart.o \
./proj/drivers/usb.o \
./proj/drivers/usb_uart.o \
./proj/drivers/usbdesc.o \
./proj/drivers/usbhw.o 


# Each subdirectory must supply rules for building sources it contributes
proj/drivers/%.o: ../proj/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -D__PROJECT_VR_17H26__=1 -DDEBUG_FROM_FLASH=1 -Wall -Os -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


