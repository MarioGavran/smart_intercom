################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../tensorflow_lite/tensorflow/lite/micro/kernels/activations.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/activations_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/add_n.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/arg_min_max.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/assign_variable.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/batch_to_space_nd.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/call_once.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/cast.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/ceil.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/comparisons.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/concatenation.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/conv_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/cumsum.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/depth_to_space.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/depthwise_conv_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/dequantize.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/detection_postprocess.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/elementwise.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/elu.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/ethosu.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/exp.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/expand_dims.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/fill.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/floor.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/floor_div.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/floor_mod.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/fully_connected_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/gather.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/gather_nd.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/if.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/kernel_runner.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/kernel_util.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/l2_pool_2d.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/l2norm.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/log_softmax.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/logical.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/logical_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/logistic.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/logistic_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/maximum_minimum.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/neg.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/pack.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/pad.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/pooling_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/prelu.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/quantize.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/quantize_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/read_variable.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/reduce.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/reshape.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/resize_bilinear.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/resize_nearest_neighbor.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/round.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/shape.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/softmax_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/space_to_batch_nd.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/space_to_depth.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/split.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/split_v.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/squeeze.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/strided_slice.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/sub.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/svdf_common.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/tanh.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/transpose.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/transpose_conv.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/unpack.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/var_handle.cc \
../tensorflow_lite/tensorflow/lite/micro/kernels/zeros_like.cc 

CC_DEPS += \
./tensorflow_lite/tensorflow/lite/micro/kernels/activations.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/activations_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/add_n.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/arg_min_max.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/assign_variable.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/batch_to_space_nd.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/call_once.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/cast.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/ceil.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/comparisons.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/concatenation.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/conv_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/cumsum.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/depth_to_space.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/depthwise_conv_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/dequantize.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/detection_postprocess.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/elementwise.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/elu.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/ethosu.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/exp.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/expand_dims.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/fill.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/floor.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/floor_div.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/floor_mod.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/fully_connected_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/gather.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/gather_nd.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/if.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/kernel_runner.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/kernel_util.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/l2_pool_2d.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/l2norm.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/log_softmax.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/logical.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/logical_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/logistic.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/logistic_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/maximum_minimum.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/neg.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/pack.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/pad.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/pooling_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/prelu.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/quantize.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/quantize_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/read_variable.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/reduce.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/reshape.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/resize_bilinear.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/resize_nearest_neighbor.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/round.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/shape.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/softmax_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/space_to_batch_nd.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/space_to_depth.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/split.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/split_v.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/squeeze.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/strided_slice.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/sub.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/svdf_common.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/tanh.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/transpose.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/transpose_conv.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/unpack.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/var_handle.d \
./tensorflow_lite/tensorflow/lite/micro/kernels/zeros_like.d 

OBJS += \
./tensorflow_lite/tensorflow/lite/micro/kernels/activations.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/activations_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/add_n.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/arg_min_max.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/assign_variable.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/batch_to_space_nd.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/call_once.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/cast.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/ceil.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/comparisons.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/concatenation.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/conv_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/cumsum.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/depth_to_space.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/depthwise_conv_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/dequantize.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/detection_postprocess.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/elementwise.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/elu.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/ethosu.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/exp.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/expand_dims.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/fill.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/floor.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/floor_div.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/floor_mod.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/fully_connected_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/gather.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/gather_nd.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/if.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/kernel_runner.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/kernel_util.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/l2_pool_2d.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/l2norm.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/log_softmax.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/logical.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/logical_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/logistic.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/logistic_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/maximum_minimum.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/neg.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/pack.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/pad.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/pooling_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/prelu.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/quantize.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/quantize_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/read_variable.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/reduce.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/reshape.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/resize_bilinear.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/resize_nearest_neighbor.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/round.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/shape.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/softmax_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/space_to_batch_nd.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/space_to_depth.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/split.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/split_v.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/squeeze.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/strided_slice.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/sub.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/svdf_common.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/tanh.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/transpose.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/transpose_conv.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/unpack.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/var_handle.o \
./tensorflow_lite/tensorflow/lite/micro/kernels/zeros_like.o 


# Each subdirectory must supply rules for building sources it contributes
tensorflow_lite/tensorflow/lite/micro/kernels/%.o: ../tensorflow_lite/tensorflow/lite/micro/kernels/%.cc tensorflow_lite/tensorflow/lite/micro/kernels/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -DUSE_HAL_DRIVER -DSTM32F413xx -D__ARM_FEATURE_DSP=1 -D__FPU_PRESENT=1 -D__TARGET_FPU_VFP -D__FPU_USED=1 -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/flatbuffers/include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/gemmlowp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/third_party/ruy" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Source/SoftmaxFunctions" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/Core/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/DSP/Include/dsp" -I"/home/enio/STM32CubeIDE/workspace_1.6.1/smart_intercom2/tensorflow_lite/tensorflow/lite/micro/tools/make/downloads/cmsis/CMSIS/NN/Include" -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1 -I/opt/st/stm32cubeide_1.6.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/arm-none-eabi/include/c++/9.3.1/arm-none-eabi -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-tensorflow_lite-2f-tensorflow-2f-lite-2f-micro-2f-kernels

clean-tensorflow_lite-2f-tensorflow-2f-lite-2f-micro-2f-kernels:
	-$(RM) ./tensorflow_lite/tensorflow/lite/micro/kernels/activations.d ./tensorflow_lite/tensorflow/lite/micro/kernels/activations.o ./tensorflow_lite/tensorflow/lite/micro/kernels/activations_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/activations_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/add_n.d ./tensorflow_lite/tensorflow/lite/micro/kernels/add_n.o ./tensorflow_lite/tensorflow/lite/micro/kernels/arg_min_max.d ./tensorflow_lite/tensorflow/lite/micro/kernels/arg_min_max.o ./tensorflow_lite/tensorflow/lite/micro/kernels/assign_variable.d ./tensorflow_lite/tensorflow/lite/micro/kernels/assign_variable.o ./tensorflow_lite/tensorflow/lite/micro/kernels/batch_to_space_nd.d ./tensorflow_lite/tensorflow/lite/micro/kernels/batch_to_space_nd.o ./tensorflow_lite/tensorflow/lite/micro/kernels/call_once.d ./tensorflow_lite/tensorflow/lite/micro/kernels/call_once.o ./tensorflow_lite/tensorflow/lite/micro/kernels/cast.d ./tensorflow_lite/tensorflow/lite/micro/kernels/cast.o ./tensorflow_lite/tensorflow/lite/micro/kernels/ceil.d ./tensorflow_lite/tensorflow/lite/micro/kernels/ceil.o ./tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer.d ./tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer.o ./tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/circular_buffer_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/comparisons.d ./tensorflow_lite/tensorflow/lite/micro/kernels/comparisons.o ./tensorflow_lite/tensorflow/lite/micro/kernels/concatenation.d ./tensorflow_lite/tensorflow/lite/micro/kernels/concatenation.o ./tensorflow_lite/tensorflow/lite/micro/kernels/conv_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/conv_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/cumsum.d ./tensorflow_lite/tensorflow/lite/micro/kernels/cumsum.o ./tensorflow_lite/tensorflow/lite/micro/kernels/depth_to_space.d ./tensorflow_lite/tensorflow/lite/micro/kernels/depth_to_space.o ./tensorflow_lite/tensorflow/lite/micro/kernels/depthwise_conv_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/depthwise_conv_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/dequantize.d ./tensorflow_lite/tensorflow/lite/micro/kernels/dequantize.o ./tensorflow_lite/tensorflow/lite/micro/kernels/detection_postprocess.d ./tensorflow_lite/tensorflow/lite/micro/kernels/detection_postprocess.o ./tensorflow_lite/tensorflow/lite/micro/kernels/elementwise.d ./tensorflow_lite/tensorflow/lite/micro/kernels/elementwise.o ./tensorflow_lite/tensorflow/lite/micro/kernels/elu.d ./tensorflow_lite/tensorflow/lite/micro/kernels/elu.o ./tensorflow_lite/tensorflow/lite/micro/kernels/ethosu.d ./tensorflow_lite/tensorflow/lite/micro/kernels/ethosu.o ./tensorflow_lite/tensorflow/lite/micro/kernels/exp.d ./tensorflow_lite/tensorflow/lite/micro/kernels/exp.o ./tensorflow_lite/tensorflow/lite/micro/kernels/expand_dims.d ./tensorflow_lite/tensorflow/lite/micro/kernels/expand_dims.o ./tensorflow_lite/tensorflow/lite/micro/kernels/fill.d ./tensorflow_lite/tensorflow/lite/micro/kernels/fill.o ./tensorflow_lite/tensorflow/lite/micro/kernels/floor.d ./tensorflow_lite/tensorflow/lite/micro/kernels/floor.o ./tensorflow_lite/tensorflow/lite/micro/kernels/floor_div.d ./tensorflow_lite/tensorflow/lite/micro/kernels/floor_div.o ./tensorflow_lite/tensorflow/lite/micro/kernels/floor_mod.d ./tensorflow_lite/tensorflow/lite/micro/kernels/floor_mod.o ./tensorflow_lite/tensorflow/lite/micro/kernels/fully_connected_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/fully_connected_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/gather.d ./tensorflow_lite/tensorflow/lite/micro/kernels/gather.o ./tensorflow_lite/tensorflow/lite/micro/kernels/gather_nd.d ./tensorflow_lite/tensorflow/lite/micro/kernels/gather_nd.o ./tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish.d ./tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish.o ./tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/hard_swish_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/if.d ./tensorflow_lite/tensorflow/lite/micro/kernels/if.o ./tensorflow_lite/tensorflow/lite/micro/kernels/kernel_runner.d ./tensorflow_lite/tensorflow/lite/micro/kernels/kernel_runner.o ./tensorflow_lite/tensorflow/lite/micro/kernels/kernel_util.d ./tensorflow_lite/tensorflow/lite/micro/kernels/kernel_util.o ./tensorflow_lite/tensorflow/lite/micro/kernels/l2_pool_2d.d ./tensorflow_lite/tensorflow/lite/micro/kernels/l2_pool_2d.o ./tensorflow_lite/tensorflow/lite/micro/kernels/l2norm.d ./tensorflow_lite/tensorflow/lite/micro/kernels/l2norm.o ./tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu.d ./tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu.o ./tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/leaky_relu_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/log_softmax.d ./tensorflow_lite/tensorflow/lite/micro/kernels/log_softmax.o ./tensorflow_lite/tensorflow/lite/micro/kernels/logical.d ./tensorflow_lite/tensorflow/lite/micro/kernels/logical.o ./tensorflow_lite/tensorflow/lite/micro/kernels/logical_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/logical_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/logistic.d ./tensorflow_lite/tensorflow/lite/micro/kernels/logistic.o ./tensorflow_lite/tensorflow/lite/micro/kernels/logistic_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/logistic_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/maximum_minimum.d ./tensorflow_lite/tensorflow/lite/micro/kernels/maximum_minimum.o ./tensorflow_lite/tensorflow/lite/micro/kernels/neg.d ./tensorflow_lite/tensorflow/lite/micro/kernels/neg.o ./tensorflow_lite/tensorflow/lite/micro/kernels/pack.d ./tensorflow_lite/tensorflow/lite/micro/kernels/pack.o ./tensorflow_lite/tensorflow/lite/micro/kernels/pad.d
	-$(RM) ./tensorflow_lite/tensorflow/lite/micro/kernels/pad.o ./tensorflow_lite/tensorflow/lite/micro/kernels/pooling_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/pooling_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/prelu.d ./tensorflow_lite/tensorflow/lite/micro/kernels/prelu.o ./tensorflow_lite/tensorflow/lite/micro/kernels/quantize.d ./tensorflow_lite/tensorflow/lite/micro/kernels/quantize.o ./tensorflow_lite/tensorflow/lite/micro/kernels/quantize_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/quantize_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/read_variable.d ./tensorflow_lite/tensorflow/lite/micro/kernels/read_variable.o ./tensorflow_lite/tensorflow/lite/micro/kernels/reduce.d ./tensorflow_lite/tensorflow/lite/micro/kernels/reduce.o ./tensorflow_lite/tensorflow/lite/micro/kernels/reshape.d ./tensorflow_lite/tensorflow/lite/micro/kernels/reshape.o ./tensorflow_lite/tensorflow/lite/micro/kernels/resize_bilinear.d ./tensorflow_lite/tensorflow/lite/micro/kernels/resize_bilinear.o ./tensorflow_lite/tensorflow/lite/micro/kernels/resize_nearest_neighbor.d ./tensorflow_lite/tensorflow/lite/micro/kernels/resize_nearest_neighbor.o ./tensorflow_lite/tensorflow/lite/micro/kernels/round.d ./tensorflow_lite/tensorflow/lite/micro/kernels/round.o ./tensorflow_lite/tensorflow/lite/micro/kernels/shape.d ./tensorflow_lite/tensorflow/lite/micro/kernels/shape.o ./tensorflow_lite/tensorflow/lite/micro/kernels/softmax_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/softmax_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/space_to_batch_nd.d ./tensorflow_lite/tensorflow/lite/micro/kernels/space_to_batch_nd.o ./tensorflow_lite/tensorflow/lite/micro/kernels/space_to_depth.d ./tensorflow_lite/tensorflow/lite/micro/kernels/space_to_depth.o ./tensorflow_lite/tensorflow/lite/micro/kernels/split.d ./tensorflow_lite/tensorflow/lite/micro/kernels/split.o ./tensorflow_lite/tensorflow/lite/micro/kernels/split_v.d ./tensorflow_lite/tensorflow/lite/micro/kernels/split_v.o ./tensorflow_lite/tensorflow/lite/micro/kernels/squeeze.d ./tensorflow_lite/tensorflow/lite/micro/kernels/squeeze.o ./tensorflow_lite/tensorflow/lite/micro/kernels/strided_slice.d ./tensorflow_lite/tensorflow/lite/micro/kernels/strided_slice.o ./tensorflow_lite/tensorflow/lite/micro/kernels/sub.d ./tensorflow_lite/tensorflow/lite/micro/kernels/sub.o ./tensorflow_lite/tensorflow/lite/micro/kernels/svdf_common.d ./tensorflow_lite/tensorflow/lite/micro/kernels/svdf_common.o ./tensorflow_lite/tensorflow/lite/micro/kernels/tanh.d ./tensorflow_lite/tensorflow/lite/micro/kernels/tanh.o ./tensorflow_lite/tensorflow/lite/micro/kernels/transpose.d ./tensorflow_lite/tensorflow/lite/micro/kernels/transpose.o ./tensorflow_lite/tensorflow/lite/micro/kernels/transpose_conv.d ./tensorflow_lite/tensorflow/lite/micro/kernels/transpose_conv.o ./tensorflow_lite/tensorflow/lite/micro/kernels/unpack.d ./tensorflow_lite/tensorflow/lite/micro/kernels/unpack.o ./tensorflow_lite/tensorflow/lite/micro/kernels/var_handle.d ./tensorflow_lite/tensorflow/lite/micro/kernels/var_handle.o ./tensorflow_lite/tensorflow/lite/micro/kernels/zeros_like.d ./tensorflow_lite/tensorflow/lite/micro/kernels/zeros_like.o

.PHONY: clean-tensorflow_lite-2f-tensorflow-2f-lite-2f-micro-2f-kernels

