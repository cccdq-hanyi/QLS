################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"D:/QLS/common/Comm_Mgt/Can_Com/can_busoff.c" \
"D:/QLS/common/Comm_Mgt/Can_Com/can_com.c" \

C_SRCS += \
D:/QLS/common/Comm_Mgt/Can_Com/can_busoff.c \
D:/QLS/common/Comm_Mgt/Can_Com/can_com.c \

OBJS_OS_FORMAT += \
./Sources/common/Comm_Mgt/Can_Com/can_busoff.o \
./Sources/common/Comm_Mgt/Can_Com/can_com.o \

C_DEPS_QUOTED += \
"./Sources/common/Comm_Mgt/Can_Com/can_busoff.d" \
"./Sources/common/Comm_Mgt/Can_Com/can_com.d" \

OBJS += \
./Sources/common/Comm_Mgt/Can_Com/can_busoff.o \
./Sources/common/Comm_Mgt/Can_Com/can_com.o \

OBJS_QUOTED += \
"./Sources/common/Comm_Mgt/Can_Com/can_busoff.o" \
"./Sources/common/Comm_Mgt/Can_Com/can_com.o" \

C_DEPS += \
./Sources/common/Comm_Mgt/Can_Com/can_busoff.d \
./Sources/common/Comm_Mgt/Can_Com/can_com.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/common/Comm_Mgt/Can_Com/can_busoff.o: D:/QLS/common/Comm_Mgt/Can_Com/can_busoff.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Comm_Mgt/Can_Com/can_busoff.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Comm_Mgt/Can_Com/can_busoff.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/Comm_Mgt/Can_Com/can_com.o: D:/QLS/common/Comm_Mgt/Can_Com/can_com.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Comm_Mgt/Can_Com/can_com.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Comm_Mgt/Can_Com/can_com.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


