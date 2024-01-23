################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
AVR_SystemWithKeypad_PROJECT.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: AVR_SystemWithKeypad_PROJECT.elf secondary-outputs

# Tool invocations
AVR_SystemWithKeypad_PROJECT.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,AVR_SystemWithKeypad_PROJECT.map -mmcu=atmega32 -o "AVR_SystemWithKeypad_PROJECT.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

AVR_SystemWithKeypad_PROJECT.lss: AVR_SystemWithKeypad_PROJECT.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AVR_SystemWithKeypad_PROJECT.elf  >"AVR_SystemWithKeypad_PROJECT.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AVR_SystemWithKeypad_PROJECT.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 AVR_SystemWithKeypad_PROJECT.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) AVR_SystemWithKeypad_PROJECT.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
