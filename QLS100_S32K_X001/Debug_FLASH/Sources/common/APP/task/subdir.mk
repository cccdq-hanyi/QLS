################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"D:/QLS/common/APP/task/APP_Task_Mgt.c" \

C_SRCS += \
D:/QLS/common/APP/task/APP_Task_Mgt.c \

OBJS_OS_FORMAT += \
./Sources/common/APP/task/APP_Task_Mgt.o \

C_DEPS_QUOTED += \
"./Sources/common/APP/task/APP_Task_Mgt.d" \

OBJS += \
./Sources/common/APP/task/APP_Task_Mgt.o \

OBJS_QUOTED += \
"./Sources/common/APP/task/APP_Task_Mgt.o" \

C_DEPS += \
./Sources/common/APP/task/APP_Task_Mgt.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/common/APP/task/APP_Task_Mgt.o: D:/QLS/common/APP/task/APP_Task_Mgt.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/APP/task/APP_Task_Mgt.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/APP/task/APP_Task_Mgt.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


