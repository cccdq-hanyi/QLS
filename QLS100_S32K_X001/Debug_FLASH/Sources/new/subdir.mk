################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/new/Sys_Init.c" \

C_SRCS += \
../Sources/new/Sys_Init.c \

OBJS_OS_FORMAT += \
./Sources/new/Sys_Init.o \

C_DEPS_QUOTED += \
"./Sources/new/Sys_Init.d" \

OBJS += \
./Sources/new/Sys_Init.o \

OBJS_QUOTED += \
"./Sources/new/Sys_Init.o" \

C_DEPS += \
./Sources/new/Sys_Init.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/new/Sys_Init.o: ../Sources/new/Sys_Init.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/Sys_Init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/Sys_Init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


