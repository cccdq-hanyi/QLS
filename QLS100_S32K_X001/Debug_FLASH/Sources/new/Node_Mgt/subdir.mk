################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/new/Node_Mgt/node_cfg.c" \
"../Sources/new/Node_Mgt/node_interface.c" \
"../Sources/new/Node_Mgt/node_para.c" \

C_SRCS += \
../Sources/new/Node_Mgt/node_cfg.c \
../Sources/new/Node_Mgt/node_interface.c \
../Sources/new/Node_Mgt/node_para.c \

OBJS_OS_FORMAT += \
./Sources/new/Node_Mgt/node_cfg.o \
./Sources/new/Node_Mgt/node_interface.o \
./Sources/new/Node_Mgt/node_para.o \

C_DEPS_QUOTED += \
"./Sources/new/Node_Mgt/node_cfg.d" \
"./Sources/new/Node_Mgt/node_interface.d" \
"./Sources/new/Node_Mgt/node_para.d" \

OBJS += \
./Sources/new/Node_Mgt/node_cfg.o \
./Sources/new/Node_Mgt/node_interface.o \
./Sources/new/Node_Mgt/node_para.o \

OBJS_QUOTED += \
"./Sources/new/Node_Mgt/node_cfg.o" \
"./Sources/new/Node_Mgt/node_interface.o" \
"./Sources/new/Node_Mgt/node_para.o" \

C_DEPS += \
./Sources/new/Node_Mgt/node_cfg.d \
./Sources/new/Node_Mgt/node_interface.d \
./Sources/new/Node_Mgt/node_para.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/new/Node_Mgt/node_cfg.o: ../Sources/new/Node_Mgt/node_cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/Node_Mgt/node_cfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/Node_Mgt/node_cfg.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/new/Node_Mgt/node_interface.o: ../Sources/new/Node_Mgt/node_interface.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/Node_Mgt/node_interface.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/Node_Mgt/node_interface.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/new/Node_Mgt/node_para.o: ../Sources/new/Node_Mgt/node_para.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/Node_Mgt/node_para.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/Node_Mgt/node_para.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


