################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include vendor/common/subdir.mk
-include vendor/VR/subdir.mk
-include proj/vendor/ll_test/subdir.mk
-include proj/vendor/common/subdir.mk
-include proj/proj_lib/subdir.mk
-include proj/mcu_spec/subdir.mk
-include proj/mcu/subdir.mk
-include proj/drivers/subdir.mk
-include proj/drivers/iqs263/subdir.mk
-include proj/common/subdir.mk
-include proj/app/subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LST += \
17H26_VR_flash.lst \

FLASH_IMAGE += \
17H26_VR_flash.bin \

SIZEDUMMY += \
sizedummy \


# All Target
all: pre-build main-build

# Main-build Target
main-build: 17H26_VR_flash.elf secondary-outputs

# Tool invocations
17H26_VR_flash.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: TC32 C Linker'
	tc32-elf-ld --gc-sections -L"I:\BLE\ST17H26\SDK\zhoujiyun\17H26_SDK_v0125\src_gatt\proj_lib" -T ../boot.link -o"17H26_VR_flash.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

17H26_VR_flash.lst: 17H26_VR_flash.elf
	@echo 'Invoking: TC32 Create Extended Listing'
	tc32-elf-objdump -x -D -l -S 17H26_VR_flash.elf  >"17H26_VR_flash.lst"
	@echo 'Finished building: $@'
	@echo ' '

17H26_VR_flash.bin: 17H26_VR_flash.elf
	@echo 'Create Flash image (binary format)'
	tc32-elf-objcopy -O binary 17H26_VR_flash.elf  "17H26_VR_flash.bin"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 17H26_VR_flash.elf
	@echo 'Invoking: Print Size'
	tc32-elf-size -t 17H26_VR_flash.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(FLASH_IMAGE)$(ELFS)$(LST)$(SIZEDUMMY) 17H26_VR_flash.elf
	-@echo ' '

pre-build:
	-I:\BLE\ST17H26\SDK\zhoujiyun\17H26_SDK_v0125\src_gatt/getver.sh
	-@echo ' '

secondary-outputs: $(LST) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

-include ../makefile.targets
