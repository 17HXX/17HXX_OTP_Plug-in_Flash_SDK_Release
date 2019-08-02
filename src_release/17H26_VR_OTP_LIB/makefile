################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include proj_lib/subdir.mk
-include proj_lib/blt_ll/subdir.mk
-include proj_lib/ble_l2cap/subdir.mk
-include proj_lib/ble_l2cap/aes_sw/subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LST += \
17H26_VR_OTP_LIB.lst \

FLASH_IMAGE += \

SIZEDUMMY += \
sizedummy \


# All Target
all: pre-build main-build

# Main-build Target
main-build: lib17H26_VR_OTP_LIB.a secondary-outputs

# Tool invocations
lib17H26_VR_OTP_LIB.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: TC32 Archiver'
	tc32-elf-ar -r "lib17H26_VR_OTP_LIB.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

17H26_VR_OTP_LIB.lst: lib17H26_VR_OTP_LIB.a
	@echo 'Invoking: TC32 Create Extended Listing'
	tc32-elf-objdump -x -D -l -S lib17H26_VR_OTP_LIB.a  >"17H26_VR_OTP_LIB.lst"
	@echo 'Finished building: $@'
	@echo ' '

: lib17H26_VR_OTP_LIB.a
	@echo 'Create Flash image (binary format)'
	tc32-elf-objcopy lib17H26_VR_OTP_LIB.a
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: lib17H26_VR_OTP_LIB.a
	@echo 'Invoking: Print Size'
	tc32-elf-size -t lib17H26_VR_OTP_LIB.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(ARCHIVES)$(FLASH_IMAGE)$(LST)$(SIZEDUMMY) lib17H26_VR_OTP_LIB.a
	-@echo ' '

pre-build:
	-D:\telink\projects\BlueLight-Lenze\src/getver.sh
	-@echo ' '

secondary-outputs: $(LST) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

-include ../makefile.targets
