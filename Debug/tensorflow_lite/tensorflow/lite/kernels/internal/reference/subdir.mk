################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../tensorflow_lite/tensorflow/lite/kernels/internal/reference/portable_tensor_utils.cc 

CC_DEPS += \
./tensorflow_lite/tensorflow/lite/kernels/internal/reference/portable_tensor_utils.d 

OBJS += \
./tensorflow_lite/tensorflow/lite/kernels/internal/reference/portable_tensor_utils.o 


# Each subdirectory must supply rules for building sources it contributes
tensorflow_lite/tensorflow/lite/kernels/internal/reference/%.o: ../tensorflow_lite/tensorflow/lite/kernels/internal/reference/%.cc tensorflow_lite/tensorflow/lite/kernels/internal/reference/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -D__ARM_FEATURE_DSP=1 -D__FPU_PRESENT=1 -D__TARGET_FPU_VFP -D__FPU_USED=1 -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-tensorflow_lite-2f-tensorflow-2f-lite-2f-kernels-2f-internal-2f-reference

clean-tensorflow_lite-2f-tensorflow-2f-lite-2f-kernels-2f-internal-2f-reference:
	-$(RM) ./tensorflow_lite/tensorflow/lite/kernels/internal/reference/portable_tensor_utils.d ./tensorflow_lite/tensorflow/lite/kernels/internal/reference/portable_tensor_utils.o

.PHONY: clean-tensorflow_lite-2f-tensorflow-2f-lite-2f-kernels-2f-internal-2f-reference

