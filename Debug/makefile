################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include tensorflow_lite/tensorflow/lite/schema/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SVDFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/ReshapeFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/PoolingFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/NNSupportFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/ConvolutionFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/ConcatenationFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/BasicMathFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/ActivationFunctions/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/models/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/memory_planner/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/kernels/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/examples/person_detection/testdata/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/examples/person_detection/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/cortex_m_generic/subdir.mk
-include tensorflow_lite/tensorflow/lite/micro/subdir.mk
-include tensorflow_lite/tensorflow/lite/kernels/internal/reference/subdir.mk
-include tensorflow_lite/tensorflow/lite/kernels/internal/subdir.mk
-include tensorflow_lite/tensorflow/lite/kernels/subdir.mk
-include tensorflow_lite/tensorflow/lite/core/api/subdir.mk
-include tensorflow_lite/tensorflow/lite/c/subdir.mk
-include ov7670_driver/Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
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
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := smart_intercom2
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
smart_intercom2.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
smart_intercom2.list \

OBJCOPY_BIN += \
smart_intercom2.bin \


# All Target
all: main-build

# Main-build Target
main-build: smart_intercom2.elf secondary-outputs

# Tool invocations
smart_intercom2.elf: $(OBJS) $(USER_OBJS) /home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/STM32F413ZHTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "smart_intercom2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/STM32F413ZHTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="smart_intercom2.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

smart_intercom2.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "smart_intercom2.list"
	@echo 'Finished building: $@'
	@echo ' '

smart_intercom2.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "smart_intercom2.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout smart_intercom2.bin smart_intercom2.elf smart_intercom2.list
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
