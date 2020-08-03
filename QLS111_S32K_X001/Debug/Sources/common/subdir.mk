################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"D:/s32dsworkspace/QLS/common/Sys_Init.c" \
"D:/s32dsworkspace/QLS/common/adsample.c" \
"D:/s32dsworkspace/QLS/common/helper_functions.c" \
"D:/s32dsworkspace/QLS/common/ntc_calibration.c" \
"D:/s32dsworkspace/QLS/common/ultrasonic.c" \

C_SRCS += \
D:/s32dsworkspace/QLS/common/Sys_Init.c \
D:/s32dsworkspace/QLS/common/adsample.c \
D:/s32dsworkspace/QLS/common/helper_functions.c \
D:/s32dsworkspace/QLS/common/ntc_calibration.c \
D:/s32dsworkspace/QLS/common/ultrasonic.c \

OBJS_OS_FORMAT += \
./Sources/common/Sys_Init.o \
./Sources/common/adsample.o \
./Sources/common/helper_functions.o \
./Sources/common/ntc_calibration.o \
./Sources/common/ultrasonic.o \

C_DEPS_QUOTED += \
"./Sources/common/Sys_Init.d" \
"./Sources/common/adsample.d" \
"./Sources/common/helper_functions.d" \
"./Sources/common/ntc_calibration.d" \
"./Sources/common/ultrasonic.d" \

OBJS += \
./Sources/common/Sys_Init.o \
./Sources/common/adsample.o \
./Sources/common/helper_functions.o \
./Sources/common/ntc_calibration.o \
./Sources/common/ultrasonic.o \

OBJS_QUOTED += \
"./Sources/common/Sys_Init.o" \
"./Sources/common/adsample.o" \
"./Sources/common/helper_functions.o" \
"./Sources/common/ntc_calibration.o" \
"./Sources/common/ultrasonic.o" \

C_DEPS += \
./Sources/common/Sys_Init.d \
./Sources/common/adsample.d \
./Sources/common/helper_functions.d \
./Sources/common/ntc_calibration.d \
./Sources/common/ultrasonic.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/common/Sys_Init.o: D:/s32dsworkspace/QLS/common/Sys_Init.c
	@echo 'Building file: $<'
	@echo 'Executing target #58 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Sys_Init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Sys_Init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/adsample.o: D:/s32dsworkspace/QLS/common/adsample.c
	@echo 'Building file: $<'
	@echo 'Executing target #59 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/adsample.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/adsample.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/helper_functions.o: D:/s32dsworkspace/QLS/common/helper_functions.c
	@echo 'Building file: $<'
	@echo 'Executing target #60 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/helper_functions.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/helper_functions.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/ntc_calibration.o: D:/s32dsworkspace/QLS/common/ntc_calibration.c
	@echo 'Building file: $<'
	@echo 'Executing target #61 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/ntc_calibration.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/ntc_calibration.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/ultrasonic.o: D:/s32dsworkspace/QLS/common/ultrasonic.c
	@echo 'Building file: $<'
	@echo 'Executing target #62 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/ultrasonic.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/ultrasonic.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


