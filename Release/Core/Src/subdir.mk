################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/app_main.c \
../Core/Src/dma.c \
../Core/Src/feri_logo_image.c \
../Core/Src/fsmc.c \
../Core/Src/fsmc_driver.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/i2c_driver.c \
../Core/Src/ietk_logo_image.c \
../Core/Src/misc.c \
../Core/Src/ov7670.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c \
../Core/Src/touch_driver.c \
../Core/Src/uart_driver.c \
../Core/Src/usart.c 

CPP_SRCS += \
../Core/Src/main.cpp 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/app_main.d \
./Core/Src/dma.d \
./Core/Src/feri_logo_image.d \
./Core/Src/fsmc.d \
./Core/Src/fsmc_driver.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/i2c_driver.d \
./Core/Src/ietk_logo_image.d \
./Core/Src/misc.d \
./Core/Src/ov7670.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d \
./Core/Src/touch_driver.d \
./Core/Src/uart_driver.d \
./Core/Src/usart.d 

OBJS += \
./Core/Src/adc.o \
./Core/Src/app_main.o \
./Core/Src/dma.o \
./Core/Src/feri_logo_image.o \
./Core/Src/fsmc.o \
./Core/Src/fsmc_driver.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/i2c_driver.o \
./Core/Src/ietk_logo_image.o \
./Core/Src/main.o \
./Core/Src/misc.o \
./Core/Src/ov7670.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o \
./Core/Src/touch_driver.o \
./Core/Src/uart_driver.o \
./Core/Src/usart.o 

CPP_DEPS += \
./Core/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F413xx -D__ARM_FEATURE_DSP=1 -DCMSIS_NN -D__FPU_PRESENT=1 -D__TARGET_FPU_VFP -D__FPU_USED=1 -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx -D__ARM_FEATURE_DSP=1 -D__FPU_PRESENT=1 -D__TARGET_FPU_VFP -D__FPU_USED=1 -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/app_main.d ./Core/Src/app_main.o ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/feri_logo_image.d ./Core/Src/feri_logo_image.o ./Core/Src/fsmc.d ./Core/Src/fsmc.o ./Core/Src/fsmc_driver.d ./Core/Src/fsmc_driver.o ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c_driver.d ./Core/Src/i2c_driver.o ./Core/Src/ietk_logo_image.d ./Core/Src/ietk_logo_image.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/misc.d ./Core/Src/misc.o ./Core/Src/ov7670.d ./Core/Src/ov7670.o ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/touch_driver.d ./Core/Src/touch_driver.o ./Core/Src/uart_driver.d ./Core/Src/uart_driver.o ./Core/Src/usart.d ./Core/Src/usart.o

.PHONY: clean-Core-2f-Src

