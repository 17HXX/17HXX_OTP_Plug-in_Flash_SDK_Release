################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include vendor/common/subdir.mk
-include vendor/IIC_SLAVE_Demo/subdir.mk
-include proj_lib/ble_l2cap/subdir.mk
-include proj/vendor/ll_test/subdir.mk
-include proj/vendor/common/subdir.mk
-include proj/proj_lib/subdir.mk
-include proj/mcu_spec/subdir.mk
-include proj/mcu/subdir.mk
-include proj/drivers/iqs263/subdir.mk
-include proj/drivers/subdir.mk
-include proj/common/subdir.mk
-include proj/app/subdir.mk
-include subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LST += \
IIC_SLAVE_flash.lst \

FLASH_IMAGE += \
IIC_SLAVE_flash.bin \

SIZEDUMMY += \
sizedummy \


# All Target
all: pre-build main-build

# Main-build Target
main-build: IIC_SLAVE_flash.elf secondary-outputs

# Tool invocations
IIC_SLAVE_flash.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: TC32 C Linker'
	tc32-elf-ld --gc-sections -L"G:\MY_work\company_common\src_release_GATT\proj_lib" -T ../boot.link -o "IIC_SLAVE_flash.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

IIC_SLAVE_flash.lst: IIC_SLAVE_flash.elf
	@echo 'Invoking: TC32 Create Extended Listing'
	tc32-elf-objdump -x -D -l -S IIC_SLAVE_flash.elf  >"IIC_SLAVE_flash.lst"
	@echo 'Finished building: $@'
	@echo ' '

IIC_SLAVE_flash.bin: IIC_SLAVE_flash.elf
	@echo 'Create Flash image (binary format)'
	tc32-elf-objcopy -O binary IIC_SLAVE_flash.elf  "IIC_SLAVE_flash.bin"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: IIC_SLAVE_flash.elf
	@echo 'Invoking: Print Size'
	tc32-elf-size -t IIC_SLAVE_flash.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(LST)$(SIZEDUMMY) IIC_SLAVE_flash.elf
	-@echo ' '

pre-build:
	-G:\MY_work\company_common\src_release_GATT/getver.sh
	-@echo ' '

secondary-outputs: $(LST) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

-include ../makefile.targets
