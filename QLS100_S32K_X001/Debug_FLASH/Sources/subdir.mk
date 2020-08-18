################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/main.c" \
"../Sources/spi_comm.c" \
"../Sources/tof_capture.c" \

C_SRCS += \
../Sources/main.c \
../Sources/spi_comm.c \
../Sources/tof_capture.c \

OBJS_OS_FORMAT += \
./Sources/main.o \
./Sources/spi_comm.o \
./Sources/tof_capture.o \

C_DEPS_QUOTED += \
"./Sources/main.d" \
"./Sources/spi_comm.d" \
"./Sources/tof_capture.d" \

OBJS += \
./Sources/main.o \
./Sources/spi_comm.o \
./Sources/tof_capture.o \

OBJS_QUOTED += \
"./Sources/main.o" \
"./Sources/spi_comm.o" \
"./Sources/tof_capture.o" \

C_DEPS += \
./Sources/main.d \
./Sources/spi_comm.d \
./Sources/tof_capture.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #49 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/spi_comm.o: ../Sources/spi_comm.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/spi_comm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/spi_comm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/tof_capture.o: ../Sources/tof_capture.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/tof_capture.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/tof_capture.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


