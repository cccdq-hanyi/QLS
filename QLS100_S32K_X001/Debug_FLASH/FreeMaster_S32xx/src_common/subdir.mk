################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../FreeMaster_S32xx/src_common/freemaster_appcmd.c" \
"../FreeMaster_S32xx/src_common/freemaster_bdm.c" \
"../FreeMaster_S32xx/src_common/freemaster_can.c" \
"../FreeMaster_S32xx/src_common/freemaster_lin.c" \
"../FreeMaster_S32xx/src_common/freemaster_pipes.c" \
"../FreeMaster_S32xx/src_common/freemaster_protocol.c" \
"../FreeMaster_S32xx/src_common/freemaster_rec.c" \
"../FreeMaster_S32xx/src_common/freemaster_scope.c" \
"../FreeMaster_S32xx/src_common/freemaster_serial.c" \
"../FreeMaster_S32xx/src_common/freemaster_sfio.c" \
"../FreeMaster_S32xx/src_common/freemaster_tsa.c" \

C_SRCS += \
../FreeMaster_S32xx/src_common/freemaster_appcmd.c \
../FreeMaster_S32xx/src_common/freemaster_bdm.c \
../FreeMaster_S32xx/src_common/freemaster_can.c \
../FreeMaster_S32xx/src_common/freemaster_lin.c \
../FreeMaster_S32xx/src_common/freemaster_pipes.c \
../FreeMaster_S32xx/src_common/freemaster_protocol.c \
../FreeMaster_S32xx/src_common/freemaster_rec.c \
../FreeMaster_S32xx/src_common/freemaster_scope.c \
../FreeMaster_S32xx/src_common/freemaster_serial.c \
../FreeMaster_S32xx/src_common/freemaster_sfio.c \
../FreeMaster_S32xx/src_common/freemaster_tsa.c \

OBJS_OS_FORMAT += \
./FreeMaster_S32xx/src_common/freemaster_appcmd.o \
./FreeMaster_S32xx/src_common/freemaster_bdm.o \
./FreeMaster_S32xx/src_common/freemaster_can.o \
./FreeMaster_S32xx/src_common/freemaster_lin.o \
./FreeMaster_S32xx/src_common/freemaster_pipes.o \
./FreeMaster_S32xx/src_common/freemaster_protocol.o \
./FreeMaster_S32xx/src_common/freemaster_rec.o \
./FreeMaster_S32xx/src_common/freemaster_scope.o \
./FreeMaster_S32xx/src_common/freemaster_serial.o \
./FreeMaster_S32xx/src_common/freemaster_sfio.o \
./FreeMaster_S32xx/src_common/freemaster_tsa.o \

C_DEPS_QUOTED += \
"./FreeMaster_S32xx/src_common/freemaster_appcmd.d" \
"./FreeMaster_S32xx/src_common/freemaster_bdm.d" \
"./FreeMaster_S32xx/src_common/freemaster_can.d" \
"./FreeMaster_S32xx/src_common/freemaster_lin.d" \
"./FreeMaster_S32xx/src_common/freemaster_pipes.d" \
"./FreeMaster_S32xx/src_common/freemaster_protocol.d" \
"./FreeMaster_S32xx/src_common/freemaster_rec.d" \
"./FreeMaster_S32xx/src_common/freemaster_scope.d" \
"./FreeMaster_S32xx/src_common/freemaster_serial.d" \
"./FreeMaster_S32xx/src_common/freemaster_sfio.d" \
"./FreeMaster_S32xx/src_common/freemaster_tsa.d" \

OBJS += \
./FreeMaster_S32xx/src_common/freemaster_appcmd.o \
./FreeMaster_S32xx/src_common/freemaster_bdm.o \
./FreeMaster_S32xx/src_common/freemaster_can.o \
./FreeMaster_S32xx/src_common/freemaster_lin.o \
./FreeMaster_S32xx/src_common/freemaster_pipes.o \
./FreeMaster_S32xx/src_common/freemaster_protocol.o \
./FreeMaster_S32xx/src_common/freemaster_rec.o \
./FreeMaster_S32xx/src_common/freemaster_scope.o \
./FreeMaster_S32xx/src_common/freemaster_serial.o \
./FreeMaster_S32xx/src_common/freemaster_sfio.o \
./FreeMaster_S32xx/src_common/freemaster_tsa.o \

OBJS_QUOTED += \
"./FreeMaster_S32xx/src_common/freemaster_appcmd.o" \
"./FreeMaster_S32xx/src_common/freemaster_bdm.o" \
"./FreeMaster_S32xx/src_common/freemaster_can.o" \
"./FreeMaster_S32xx/src_common/freemaster_lin.o" \
"./FreeMaster_S32xx/src_common/freemaster_pipes.o" \
"./FreeMaster_S32xx/src_common/freemaster_protocol.o" \
"./FreeMaster_S32xx/src_common/freemaster_rec.o" \
"./FreeMaster_S32xx/src_common/freemaster_scope.o" \
"./FreeMaster_S32xx/src_common/freemaster_serial.o" \
"./FreeMaster_S32xx/src_common/freemaster_sfio.o" \
"./FreeMaster_S32xx/src_common/freemaster_tsa.o" \

C_DEPS += \
./FreeMaster_S32xx/src_common/freemaster_appcmd.d \
./FreeMaster_S32xx/src_common/freemaster_bdm.d \
./FreeMaster_S32xx/src_common/freemaster_can.d \
./FreeMaster_S32xx/src_common/freemaster_lin.d \
./FreeMaster_S32xx/src_common/freemaster_pipes.d \
./FreeMaster_S32xx/src_common/freemaster_protocol.d \
./FreeMaster_S32xx/src_common/freemaster_rec.d \
./FreeMaster_S32xx/src_common/freemaster_scope.d \
./FreeMaster_S32xx/src_common/freemaster_serial.d \
./FreeMaster_S32xx/src_common/freemaster_sfio.d \
./FreeMaster_S32xx/src_common/freemaster_tsa.d \


# Each subdirectory must supply rules for building sources it contributes
FreeMaster_S32xx/src_common/freemaster_appcmd.o: ../FreeMaster_S32xx/src_common/freemaster_appcmd.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_appcmd.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_appcmd.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_bdm.o: ../FreeMaster_S32xx/src_common/freemaster_bdm.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_bdm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_bdm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_can.o: ../FreeMaster_S32xx/src_common/freemaster_can.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_can.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_can.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_lin.o: ../FreeMaster_S32xx/src_common/freemaster_lin.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_lin.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_lin.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_pipes.o: ../FreeMaster_S32xx/src_common/freemaster_pipes.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_pipes.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_pipes.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_protocol.o: ../FreeMaster_S32xx/src_common/freemaster_protocol.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_protocol.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_protocol.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_rec.o: ../FreeMaster_S32xx/src_common/freemaster_rec.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_rec.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_rec.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_scope.o: ../FreeMaster_S32xx/src_common/freemaster_scope.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_scope.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_scope.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_serial.o: ../FreeMaster_S32xx/src_common/freemaster_serial.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_serial.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_serial.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_sfio.o: ../FreeMaster_S32xx/src_common/freemaster_sfio.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_sfio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_sfio.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeMaster_S32xx/src_common/freemaster_tsa.o: ../FreeMaster_S32xx/src_common/freemaster_tsa.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeMaster_S32xx/src_common/freemaster_tsa.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "FreeMaster_S32xx/src_common/freemaster_tsa.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


