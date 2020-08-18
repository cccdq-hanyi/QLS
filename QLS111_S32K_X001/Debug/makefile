################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 63
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include FreeMaster_S32xx/src_common/subdir.mk
-include FreeMaster_S32xx/src_platforms/S32xx/subdir.mk
-include Generated_Code/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include SDK/platform/devices/S32K116/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include SDK/platform/drivers/src/adc/subdir.mk
-include SDK/platform/drivers/src/clock/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/clock/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/flexcan/subdir.mk
-include SDK/platform/drivers/src/ftm/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/lpspi/subdir.mk
-include SDK/platform/drivers/src/pdb/subdir.mk
-include SDK/platform/drivers/src/pins/subdir.mk
-include SDK/platform/pal/can/src/subdir.mk
-include SDK/rtos/osif/subdir.mk
-include Sources/subdir.mk
-include Sources/common/HW_Driver/subdir.mk
-include Sources/common/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
QLS111_S32K_X001.elf \

EXECUTABLES_QUOTED += \
"QLS111_S32K_X001.elf" \

EXECUTABLES_OS_FORMAT += \
QLS111_S32K_X001.elf \

SECONDARY_SIZE += \
QLS111_S32K_X001.siz \

SECONDARY_SIZE_QUOTED += \
"QLS111_S32K_X001.siz" \

SECONDARY_SIZE_OS_FORMAT += \
QLS111_S32K_X001.siz \


# All Target
all: warning-messages explicit-dependencies QLS111_S32K_X001.elf secondary-outputs

# Tool invocations
QLS111_S32K_X001.elf: $(OBJS) D:/QLS/QLS111_S32K_X001/Project_Settings/Linker_Files/S32K116_17_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #64 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "QLS111_S32K_X001.elf" "@QLS111_S32K_X001.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

QLS111_S32K_X001.siz: $(EXECUTABLES)
	@echo 'Executing target #65 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*/*.d ./*/*/*/*.d ./*/*.d ./*/*/*/*/*/*.d ./*/*/*/*/*/*/*.d  ./*/*/*.o ./*/*/*/*.o ./*/*.o ./*/*/*/*/*/*.o ./*/*/*/*/*/*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

