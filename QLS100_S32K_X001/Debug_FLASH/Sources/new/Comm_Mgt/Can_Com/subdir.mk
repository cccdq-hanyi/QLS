################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/new/Comm_Mgt/Can_Com/can_busoff.c" \
"../Sources/new/Comm_Mgt/Can_Com/can_com.c" \

C_SRCS += \
../Sources/new/Comm_Mgt/Can_Com/can_busoff.c \
../Sources/new/Comm_Mgt/Can_Com/can_com.c \

OBJS_OS_FORMAT += \
./Sources/new/Comm_Mgt/Can_Com/can_busoff.o \
./Sources/new/Comm_Mgt/Can_Com/can_com.o \

C_DEPS_QUOTED += \
"./Sources/new/Comm_Mgt/Can_Com/can_busoff.d" \
"./Sources/new/Comm_Mgt/Can_Com/can_com.d" \

OBJS += \
./Sources/new/Comm_Mgt/Can_Com/can_busoff.o \
./Sources/new/Comm_Mgt/Can_Com/can_com.o \

OBJS_QUOTED += \
"./Sources/new/Comm_Mgt/Can_Com/can_busoff.o" \
"./Sources/new/Comm_Mgt/Can_Com/can_com.o" \

C_DEPS += \
./Sources/new/Comm_Mgt/Can_Com/can_busoff.d \
./Sources/new/Comm_Mgt/Can_Com/can_com.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/new/Comm_Mgt/Can_Com/can_busoff.o: ../Sources/new/Comm_Mgt/Can_Com/can_busoff.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/Comm_Mgt/Can_Com/can_busoff.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/Comm_Mgt/Can_Com/can_busoff.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/new/Comm_Mgt/Can_Com/can_com.o: ../Sources/new/Comm_Mgt/Can_Com/can_com.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/Comm_Mgt/Can_Com/can_com.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/Comm_Mgt/Can_Com/can_com.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


