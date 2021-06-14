################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/add.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/conv.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/depthwise_conv.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/fully_connected.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/mul.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/pooling.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/softmax.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/svdf.cc 

CC_DEPS += \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/add.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/conv.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/depthwise_conv.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/fully_connected.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/mul.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/pooling.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/softmax.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/svdf.d 

OBJS += \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/add.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/conv.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/depthwise_conv.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/fully_connected.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/mul.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/pooling.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/softmax.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/svdf.o 


# Each subdirectory must supply rules for building sources it contributes
tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/add.o: ../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/add.cc tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx '-D__ARM_FEATURE_DSP=1' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/add.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/conv.o: ../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/conv.cc tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx '-D__ARM_FEATURE_DSP=1' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/conv.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/depthwise_conv.o: ../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/depthwise_conv.cc tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx '-D__ARM_FEATURE_DSP=1' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/depthwise_conv.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/fully_connected.o: ../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/fully_connected.cc tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx '-D__ARM_FEATURE_DSP=1' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/fully_connected.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/mul.o: ../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/mul.cc tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx '-D__ARM_FEATURE_DSP=1' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/mul.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/pooling.o: ../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/pooling.cc tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx '-D__ARM_FEATURE_DSP=1' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/pooling.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/softmax.o: ../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/softmax.cc tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx '-D__ARM_FEATURE_DSP=1' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/softmax.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/svdf.o: ../tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/svdf.cc tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx '-D__ARM_FEATURE_DSP=1' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.2/smart_intercom/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"tensorflow_lite/tensorflow/lite/micro/kernels/cmsis_nn/svdf.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

