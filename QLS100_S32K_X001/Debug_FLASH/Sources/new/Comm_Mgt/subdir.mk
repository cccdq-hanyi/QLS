################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/new/Comm_Mgt/comm_mgt.c" \

C_SRCS += \
../Sources/new/Comm_Mgt/comm_mgt.c \

OBJS_OS_FORMAT += \
./Sources/new/Comm_Mgt/comm_mgt.o \

C_DEPS_QUOTED += \
"./Sources/new/Comm_Mgt/comm_mgt.d" \

OBJS += \
./Sources/new/Comm_Mgt/comm_mgt.o \

OBJS_QUOTED += \
"./Sources/new/Comm_Mgt/comm_mgt.o" \

C_DEPS += \
./Sources/new/Comm_Mgt/comm_mgt.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/new/Comm_Mgt/comm_mgt.o: ../Sources/new/Comm_Mgt/comm_mgt.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/Comm_Mgt/comm_mgt.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/Comm_Mgt/comm_mgt.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


