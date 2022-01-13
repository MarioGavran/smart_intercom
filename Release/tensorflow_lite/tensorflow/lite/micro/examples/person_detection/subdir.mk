################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../tensorflow_lite/tensorflow/lite/micro/examples/person_detection/detection_responder.cc \
../tensorflow_lite/tensorflow/lite/micro/examples/person_detection/image_provider.cc \
../tensorflow_lite/tensorflow/lite/micro/examples/person_detection/main_functions.cc \
../tensorflow_lite/tensorflow/lite/micro/examples/person_detection/model_settings.cc 

CC_DEPS += \
./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/detection_responder.d \
./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/image_provider.d \
./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/main_functions.d \
./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/model_settings.d 

OBJS += \
./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/detection_responder.o \
./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/image_provider.o \
./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/main_functions.o \
./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/model_settings.o 


# Each subdirectory must supply rules for building sources it contributes
tensorflow_lite/tensorflow/lite/micro/examples/person_detection/%.o: ../tensorflow_lite/tensorflow/lite/micro/examples/person_detection/%.cc tensorflow_lite/tensorflow/lite/micro/examples/person_detection/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx -D__ARM_FEATURE_DSP=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-tensorflow_lite-2f-tensorflow-2f-lite-2f-micro-2f-examples-2f-person_detection

clean-tensorflow_lite-2f-tensorflow-2f-lite-2f-micro-2f-examples-2f-person_detection:
	-$(RM) ./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/detection_responder.d ./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/detection_responder.o ./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/image_provider.d ./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/image_provider.o ./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/main_functions.d ./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/main_functions.o ./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/model_settings.d ./tensorflow_lite/tensorflow/lite/micro/examples/person_detection/model_settings.o

.PHONY: clean-tensorflow_lite-2f-tensorflow-2f-lite-2f-micro-2f-examples-2f-person_detection

