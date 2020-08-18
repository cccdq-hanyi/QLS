################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"D:/QLS/common/Sys_Init.c" \
"D:/QLS/common/adsample.c" \
"D:/QLS/common/helper_functions.c" \
"D:/QLS/common/ntc_calibration.c" \
"D:/QLS/common/tmr_level.c" \
"D:/QLS/common/ultrasonic.c" \

C_SRCS += \
D:/QLS/common/Sys_Init.c \
D:/QLS/common/adsample.c \
D:/QLS/common/helper_functions.c \
D:/QLS/common/ntc_calibration.c \
D:/QLS/common/tmr_level.c \
D:/QLS/common/ultrasonic.c \

OBJS_OS_FORMAT += \
./Sources/common/Sys_Init.o \
./Sources/common/adsample.o \
./Sources/common/helper_functions.o \
./Sources/common/ntc_calibration.o \
./Sources/common/tmr_level.o \
./Sources/common/ultrasonic.o \

C_DEPS_QUOTED += \
"./Sources/common/Sys_Init.d" \
"./Sources/common/adsample.d" \
"./Sources/common/helper_functions.d" \
"./Sources/common/ntc_calibration.d" \
"./Sources/common/tmr_level.d" \
"./Sources/common/ultrasonic.d" \

OBJS += \
./Sources/common/Sys_Init.o \
./Sources/common/adsample.o \
./Sources/common/helper_functions.o \
./Sources/common/ntc_calibration.o \
./Sources/common/tmr_level.o \
./Sources/common/ultrasonic.o \

OBJS_QUOTED += \
"./Sources/common/Sys_Init.o" \
"./Sources/common/adsample.o" \
"./Sources/common/helper_functions.o" \
"./Sources/common/ntc_calibration.o" \
"./Sources/common/tmr_level.o" \
"./Sources/common/ultrasonic.o" \

C_DEPS += \
./Sources/common/Sys_Init.d \
./Sources/common/adsample.d \
./Sources/common/helper_functions.d \
./Sources/common/ntc_calibration.d \
./Sources/common/tmr_level.d \
./Sources/common/ultrasonic.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/common/Sys_Init.o: D:/QLS/common/Sys_Init.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Sys_Init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Sys_Init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/adsample.o: D:/QLS/common/adsample.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/adsample.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/adsample.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/helper_functions.o: D:/QLS/common/helper_functions.c
	@echo 'Building file: $<'
	@echo 'Executing target #45 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/helper_functions.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/helper_functions.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/ntc_calibration.o: D:/QLS/common/ntc_calibration.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/ntc_calibration.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/ntc_calibration.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/tmr_level.o: D:/QLS/common/tmr_level.c
	@echo 'Building file: $<'
	@echo 'Executing target #47 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/tmr_level.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/tmr_level.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/ultrasonic.o: D:/QLS/common/ultrasonic.c
	@echo 'Building file: $<'
	@echo 'Executing target #48 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/ultrasonic.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/ultrasonic.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


