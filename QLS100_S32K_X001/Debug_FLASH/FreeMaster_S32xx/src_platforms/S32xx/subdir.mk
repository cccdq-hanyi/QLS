################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.c" \

C_SRCS += \
../FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.c \

OBJS_OS_FORMAT += \
./FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.o \

C_DEPS_QUOTED += \
"./FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.d" \

OBJS += \
./FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.o \

OBJS_QUOTED += \
"./FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.o" \

C_DEPS += \
./FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.d \


# Each subdirectory must supply rules for building sources it contributes
FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.o: ../FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_platforms/S32xx/freemaster_S32xx.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


