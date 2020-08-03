################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/new/APP/task/APP_Task_Mgt.c" \

C_SRCS += \
../Sources/new/APP/task/APP_Task_Mgt.c \

OBJS_OS_FORMAT += \
./Sources/new/APP/task/APP_Task_Mgt.o \

C_DEPS_QUOTED += \
"./Sources/new/APP/task/APP_Task_Mgt.d" \

OBJS += \
./Sources/new/APP/task/APP_Task_Mgt.o \

OBJS_QUOTED += \
"./Sources/new/APP/task/APP_Task_Mgt.o" \

C_DEPS += \
./Sources/new/APP/task/APP_Task_Mgt.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/new/APP/task/APP_Task_Mgt.o: ../Sources/new/APP/task/APP_Task_Mgt.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/APP/task/APP_Task_Mgt.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/APP/task/APP_Task_Mgt.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


