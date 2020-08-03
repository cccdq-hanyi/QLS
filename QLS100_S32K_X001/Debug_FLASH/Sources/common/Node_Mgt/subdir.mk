################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"D:/s32dsworkspace/QLS/common/Node_Mgt/node_cfg.c" \
"D:/s32dsworkspace/QLS/common/Node_Mgt/node_interface.c" \
"D:/s32dsworkspace/QLS/common/Node_Mgt/node_para.c" \

C_SRCS += \
D:/s32dsworkspace/QLS/common/Node_Mgt/node_cfg.c \
D:/s32dsworkspace/QLS/common/Node_Mgt/node_interface.c \
D:/s32dsworkspace/QLS/common/Node_Mgt/node_para.c \

OBJS_OS_FORMAT += \
./Sources/common/Node_Mgt/node_cfg.o \
./Sources/common/Node_Mgt/node_interface.o \
./Sources/common/Node_Mgt/node_para.o \

C_DEPS_QUOTED += \
"./Sources/common/Node_Mgt/node_cfg.d" \
"./Sources/common/Node_Mgt/node_interface.d" \
"./Sources/common/Node_Mgt/node_para.d" \

OBJS += \
./Sources/common/Node_Mgt/node_cfg.o \
./Sources/common/Node_Mgt/node_interface.o \
./Sources/common/Node_Mgt/node_para.o \

OBJS_QUOTED += \
"./Sources/common/Node_Mgt/node_cfg.o" \
"./Sources/common/Node_Mgt/node_interface.o" \
"./Sources/common/Node_Mgt/node_para.o" \

C_DEPS += \
./Sources/common/Node_Mgt/node_cfg.d \
./Sources/common/Node_Mgt/node_interface.d \
./Sources/common/Node_Mgt/node_para.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/common/Node_Mgt/node_cfg.o: D:/s32dsworkspace/QLS/common/Node_Mgt/node_cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #62 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Node_Mgt/node_cfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Node_Mgt/node_cfg.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/Node_Mgt/node_interface.o: D:/s32dsworkspace/QLS/common/Node_Mgt/node_interface.c
	@echo 'Building file: $<'
	@echo 'Executing target #63 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Node_Mgt/node_interface.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Node_Mgt/node_interface.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/Node_Mgt/node_para.o: D:/s32dsworkspace/QLS/common/Node_Mgt/node_para.c
	@echo 'Building file: $<'
	@echo 'Executing target #64 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Node_Mgt/node_para.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Node_Mgt/node_para.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


