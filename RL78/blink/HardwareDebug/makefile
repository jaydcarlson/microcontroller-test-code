################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf *.lst *.lis *.lpp *.map libgcc.a blink_HardwareDebug_auto.gsi

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_UPPER_DEPS)),)
-include $(CC_UPPER_DEPS)
endif
ifneq ($(strip $(C++_UPPER_DEPS)),)
-include $(C++_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
-include $(CXX_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
-include $(CPP_UPPER_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
libblink.a \

LINKER_OUTPUT_OUTPUTS += \
blink.x \


# All Target
# Main-build Target
all: blink.mot
	@echo 'Build complete.'

# Tool invocations
blink.mot: $(LINKER_OUTPUT_OUTPUTS)
	@echo 'Invoking: Objcopy'
	@echo 'Building target:'
	rl78-elf-objcopy -O srec  $(LINKER_OUTPUT_OUTPUTS)"blink.mot"
	@echo 'Finished building target:'
	@echo.

libblink.a: 
	@echo 'Invoking: Library Generator'
	@echo 'Building target:'
	rl78-elf-libgen --select-lib=optlib --header-files=stdio,stdlib,string --compiler-options=-Os,-mg14,-ffunction-sections,-fdata-sections,-fno-tree-loop-optimize,-fno-caller-saves,-fno-cse-follow-jumps -o "libblink.a"
	@echo 'Finished building:'
	@echo.

blink.x: $(OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(ALL_ASMS)
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	rl78-elf-ld -o "blink.x" -T"C:\Users\JayLocal\e2_studio\workspace\blink\HardwareDebug\blink_HardwareDebug_auto.gsi" @"C:\Users\JayLocal\e2_studio\workspace\blink\HardwareDebug\LinkerSubCommand.tmp" $(USER_OBJS) $(LIBS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) -M=blink.map -L"C:\Users\JayLocal\e2_studio\workspace\blink\HardwareDebug" -L"C:\PROGRA~2\GCCFOR~1.201\rl78-elf\rl78-elf/lib/gcc/rl78-elf/4.9.2.201701-GNURL78/g14" --start-group -lblink -lgcc --end-group -e_PowerON_Reset
	@echo 'Finished building:'
	@echo.

# Other Targets
clean:
ifneq ($(strip $(CC_UPPER_DEPS)),)
	-$(file > clean_CC_UPPER_DEPS.tmp, $(CC_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_CC_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_CC_UPPER_DEPS.tmp
endif
ifneq ($(strip $(C++_UPPER_DEPS)),)
	-$(file > clean_C++_UPPER_DEPS.tmp, $(C++_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_C++_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_C++_UPPER_DEPS.tmp
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
	-$(file > clean_CXX_UPPER_DEPS.tmp, $(CXX_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_CXX_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_CXX_UPPER_DEPS.tmp
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
	-$(file > clean_CPP_UPPER_DEPS.tmp, $(CPP_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_CPP_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_CPP_UPPER_DEPS.tmp
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
	-$(file > clean_C_UPPER_DEPS.tmp, $(C_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_C_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_C_UPPER_DEPS.tmp
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
	-$(file > clean_SRC_UPPER_DEPS.tmp, $(SRC_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_SRC_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_SRC_UPPER_DEPS.tmp
endif
ifneq ($(strip $(S_DEPS)),)
	-$(file > clean_S_DEPS.tmp, $(S_DEPS))
	-@ xargs -s 6000 -t -a clean_S_DEPS.tmp $(RM)
	-@$(RM) clean_S_DEPS.tmp
endif
ifneq ($(strip $(C_DEPS)),)
	-$(file > clean_C_DEPS.tmp, $(C_DEPS))
	-@ xargs -s 6000 -t -a clean_C_DEPS.tmp $(RM)
	-@$(RM) clean_C_DEPS.tmp
endif
ifneq ($(strip $(SRC_DEPS)),)
	-$(file > clean_SRC_DEPS.tmp, $(SRC_DEPS))
	-@ xargs -s 6000 -t -a clean_SRC_DEPS.tmp $(RM)
	-@$(RM) clean_SRC_DEPS.tmp
endif
ifneq ($(strip $(LINKER_OUTPUT_OUTPUTS)),)
	-$(file > clean_LINKER_OUTPUT_OUTPUTS.tmp, $(LINKER_OUTPUT_OUTPUTS))
	-@ xargs -s 6000 -t -a clean_LINKER_OUTPUT_OUTPUTS.tmp $(RM)
	-@$(RM) clean_LINKER_OUTPUT_OUTPUTS.tmp
endif
ifneq ($(strip $(CC_DEPS)),)
	-$(file > clean_CC_DEPS.tmp, $(CC_DEPS))
	-@ xargs -s 6000 -t -a clean_CC_DEPS.tmp $(RM)
	-@$(RM) clean_CC_DEPS.tmp
endif
ifneq ($(strip $(C++_DEPS)),)
	-$(file > clean_C++_DEPS.tmp, $(C++_DEPS))
	-@ xargs -s 6000 -t -a clean_C++_DEPS.tmp $(RM)
	-@$(RM) clean_C++_DEPS.tmp
endif
ifneq ($(strip $(CXX_DEPS)),)
	-$(file > clean_CXX_DEPS.tmp, $(CXX_DEPS))
	-@ xargs -s 6000 -t -a clean_CXX_DEPS.tmp $(RM)
	-@$(RM) clean_CXX_DEPS.tmp
endif
ifneq ($(strip $(OBJS)),)
	-$(file > clean_OBJS.tmp, $(OBJS))
	-@ xargs -s 6000 -t -a clean_OBJS.tmp $(RM)
	-@$(RM) clean_OBJS.tmp
endif
ifneq ($(strip $(ASM_DEPS)),)
	-$(file > clean_ASM_DEPS.tmp, $(ASM_DEPS))
	-@ xargs -s 6000 -t -a clean_ASM_DEPS.tmp $(RM)
	-@$(RM) clean_ASM_DEPS.tmp
endif
ifneq ($(strip $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)),)
	-$(file > clean_LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS.tmp, $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS))
	-@ xargs -s 6000 -t -a clean_LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS.tmp $(RM)
	-@$(RM) clean_LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS.tmp
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
	-$(file > clean_S_UPPER_DEPS.tmp, $(S_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_S_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_S_UPPER_DEPS.tmp
endif
ifneq ($(strip $(OBJCOPY_OUTPUTTYPE_OUTPUTS)),)
	-$(file > clean_OBJCOPY_OUTPUTTYPE_OUTPUTS.tmp, $(OBJCOPY_OUTPUTTYPE_OUTPUTS))
	-@ xargs -s 6000 -t -a clean_OBJCOPY_OUTPUTTYPE_OUTPUTS.tmp $(RM)
	-@$(RM) clean_OBJCOPY_OUTPUTTYPE_OUTPUTS.tmp
endif
ifneq ($(strip $(CPP_DEPS)),)
	-$(file > clean_CPP_DEPS.tmp, $(CPP_DEPS))
	-@ xargs -s 6000 -t -a clean_CPP_DEPS.tmp $(RM)
	-@$(RM) clean_CPP_DEPS.tmp
endif

	rm -rf ./"src"/*.tmp1 
	rm -rf   blink.mot

	@echo.
	@echo 'Clean complete.'

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
