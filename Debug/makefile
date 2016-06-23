################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/DevelopmentTools/CCSv6/ccsv6/tools/compiler/c2000_6.2.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./Source/DSP2833x_usDelay.obj" \
"./Source/DSP2833x_Xintf.obj" \
"./Source/DSP2833x_SysCtrl.obj" \
"./Source/DSP2833x_Spi.obj" \
"./Source/DSP2833x_Sci.obj" \
"./Source/DSP2833x_PieVect.obj" \
"./Source/DSP2833x_PieCtrl.obj" \
"./Source/DSP2833x_MemCopy.obj" \
"./Source/DSP2833x_Mcbsp.obj" \
"./Source/DSP2833x_I2C.obj" \
"./Source/DSP2833x_Gpio.obj" \
"./Source/DSP2833x_GlobalVariableDefs.obj" \
"./Source/DSP2833x_EQep.obj" \
"./Source/DSP2833x_EPwm.obj" \
"./Source/DSP2833x_ECap.obj" \
"./Source/DSP2833x_ECan.obj" \
"./Source/DSP2833x_DisInt.obj" \
"./Source/DSP2833x_DefaultIsr.obj" \
"./Source/DSP2833x_DMA.obj" \
"./Source/DSP2833x_DBGIER.obj" \
"./Source/DSP2833x_CpuTimers.obj" \
"./Source/DSP2833x_CodeStartBranch.obj" \
"./Source/DSP2833x_CSMPasswords.obj" \
"./Source/DSP2833x_Adc.obj" \
"./Source/DSP2833x_ADC_cal.obj" \
"./Source/AD7176.obj" \
"./main.obj" \
"../Lib/IQmath.lib" \
"../Lib/IQmath_fpu32.lib" \
"../Lib/SFO_TI_Build.lib" \
"../Lib/SFO_TI_Build_V5.lib" \
"../Lib/SFO_TI_Build_V5B.lib" \
"../Lib/SFO_TI_Build_V5B_fpu.lib" \
"../Lib/SFO_TI_Build_V5_fpu.lib" \
"../Lib/SFO_TI_Build_fpu.lib" \
"../CMD/28335_RAM_lnk.cmd" \
"../CMD/DSP2833x_Headers_nonBIOS.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Source/subdir_vars.mk
-include Lib/subdir_vars.mk
-include CMD/subdir_vars.mk
-include subdir_rules.mk
-include Source/subdir_rules.mk
-include Lib/subdir_rules.mk
-include CMD/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
AD7176.out \

EXE_OUTPUTS__QUOTED += \
"AD7176.out" \

BIN_OUTPUTS += \
AD7176.hex \

BIN_OUTPUTS__QUOTED += \
"AD7176.hex" \


# All Target
all: AD7176.out

# Tool invocations
AD7176.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"D:/DevelopmentTools/CCSv6/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"AD7176.map" --stack_size=0x300 --warn_sections -i"D:/DevelopmentTools/CCSv6/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"D:/DevelopmentTools/CCSv6/Workspace/AD7176/Include" -i"D:/DevelopmentTools/CCSv6/ccsv6/tools/compiler/c2000_6.2.5/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="AD7176_linkInfo.xml" --rom_model -o "AD7176.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

AD7176.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"D:/DevelopmentTools/CCSv6/ccsv6/tools/compiler/c2000_6.2.5/bin/hex2000"  -o "AD7176.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "Source\AD7176.pp" "Source\DSP2833x_Adc.pp" "Source\DSP2833x_CpuTimers.pp" "Source\DSP2833x_DMA.pp" "Source\DSP2833x_DefaultIsr.pp" "Source\DSP2833x_ECan.pp" "Source\DSP2833x_ECap.pp" "Source\DSP2833x_EPwm.pp" "Source\DSP2833x_EQep.pp" "Source\DSP2833x_GlobalVariableDefs.pp" "Source\DSP2833x_Gpio.pp" "Source\DSP2833x_I2C.pp" "Source\DSP2833x_Mcbsp.pp" "Source\DSP2833x_MemCopy.pp" "Source\DSP2833x_PieCtrl.pp" "Source\DSP2833x_PieVect.pp" "Source\DSP2833x_Sci.pp" "Source\DSP2833x_Spi.pp" "Source\DSP2833x_SysCtrl.pp" "Source\DSP2833x_Xintf.pp" 
	-$(RM) "main.obj" "Source\AD7176.obj" "Source\DSP2833x_ADC_cal.obj" "Source\DSP2833x_Adc.obj" "Source\DSP2833x_CSMPasswords.obj" "Source\DSP2833x_CodeStartBranch.obj" "Source\DSP2833x_CpuTimers.obj" "Source\DSP2833x_DBGIER.obj" "Source\DSP2833x_DMA.obj" "Source\DSP2833x_DefaultIsr.obj" "Source\DSP2833x_DisInt.obj" "Source\DSP2833x_ECan.obj" "Source\DSP2833x_ECap.obj" "Source\DSP2833x_EPwm.obj" "Source\DSP2833x_EQep.obj" "Source\DSP2833x_GlobalVariableDefs.obj" "Source\DSP2833x_Gpio.obj" "Source\DSP2833x_I2C.obj" "Source\DSP2833x_Mcbsp.obj" "Source\DSP2833x_MemCopy.obj" "Source\DSP2833x_PieCtrl.obj" "Source\DSP2833x_PieVect.obj" "Source\DSP2833x_Sci.obj" "Source\DSP2833x_Spi.obj" "Source\DSP2833x_SysCtrl.obj" "Source\DSP2833x_Xintf.obj" "Source\DSP2833x_usDelay.obj" 
	-$(RM) "Source\DSP2833x_ADC_cal.pp" "Source\DSP2833x_CSMPasswords.pp" "Source\DSP2833x_CodeStartBranch.pp" "Source\DSP2833x_DBGIER.pp" "Source\DSP2833x_DisInt.pp" "Source\DSP2833x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

