################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ov7670_driver/Src/OV7670.c 

C_DEPS += \
./ov7670_driver/Src/OV7670.d 

OBJS += \
./ov7670_driver/Src/OV7670.o 


# Each subdirectory must supply rules for building sources it contributes
ov7670_driver/Src/%.o: ../ov7670_driver/Src/%.c ov7670_driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -D__ARM_FEATURE_DSP=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ov7670_driver-2f-Src

clean-ov7670_driver-2f-Src:
	-$(RM) ./ov7670_driver/Src/OV7670.d ./ov7670_driver/Src/OV7670.o

.PHONY: clean-ov7670_driver-2f-Src

