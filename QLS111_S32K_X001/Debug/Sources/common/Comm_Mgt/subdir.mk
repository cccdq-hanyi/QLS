################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"D:/s32dsworkspace/QLS/common/Comm_Mgt/comm_mgt.c" \

C_SRCS += \
D:/s32dsworkspace/QLS/common/Comm_Mgt/comm_mgt.c \

OBJS_OS_FORMAT += \
./Sources/common/Comm_Mgt/comm_mgt.o \

C_DEPS_QUOTED += \
"./Sources/common/Comm_Mgt/comm_mgt.d" \

OBJS += \
./Sources/common/Comm_Mgt/comm_mgt.o \

OBJS_QUOTED += \
"./Sources/common/Comm_Mgt/comm_mgt.o" \

C_DEPS += \
./Sources/common/Comm_Mgt/comm_mgt.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/common/Comm_Mgt/comm_mgt.o: D:/s32dsworkspace/QLS/common/Comm_Mgt/comm_mgt.c
	@echo 'Building file: $<'
	@echo 'Executing target #60 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Comm_Mgt/comm_mgt.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Comm_Mgt/comm_mgt.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


