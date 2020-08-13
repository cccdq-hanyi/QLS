################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"D:/QLS/common/HW_Driver/SPI.c" \
"D:/QLS/common/HW_Driver/WatchDog.c" \
"D:/QLS/common/HW_Driver/hw_abstract.c" \
"D:/QLS/common/HW_Driver/prj_gpio.c" \

C_SRCS += \
D:/QLS/common/HW_Driver/SPI.c \
D:/QLS/common/HW_Driver/WatchDog.c \
D:/QLS/common/HW_Driver/hw_abstract.c \
D:/QLS/common/HW_Driver/prj_gpio.c \

OBJS_OS_FORMAT += \
./Sources/common/HW_Driver/SPI.o \
./Sources/common/HW_Driver/WatchDog.o \
./Sources/common/HW_Driver/hw_abstract.o \
./Sources/common/HW_Driver/prj_gpio.o \

C_DEPS_QUOTED += \
"./Sources/common/HW_Driver/SPI.d" \
"./Sources/common/HW_Driver/WatchDog.d" \
"./Sources/common/HW_Driver/hw_abstract.d" \
"./Sources/common/HW_Driver/prj_gpio.d" \

OBJS += \
./Sources/common/HW_Driver/SPI.o \
./Sources/common/HW_Driver/WatchDog.o \
./Sources/common/HW_Driver/hw_abstract.o \
./Sources/common/HW_Driver/prj_gpio.o \

OBJS_QUOTED += \
"./Sources/common/HW_Driver/SPI.o" \
"./Sources/common/HW_Driver/WatchDog.o" \
"./Sources/common/HW_Driver/hw_abstract.o" \
"./Sources/common/HW_Driver/prj_gpio.o" \

C_DEPS += \
./Sources/common/HW_Driver/SPI.d \
./Sources/common/HW_Driver/WatchDog.d \
./Sources/common/HW_Driver/hw_abstract.d \
./Sources/common/HW_Driver/prj_gpio.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/common/HW_Driver/SPI.o: D:/QLS/common/HW_Driver/SPI.c
	@echo 'Building file: $<'
	@echo 'Executing target #49 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/HW_Driver/SPI.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/HW_Driver/SPI.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/HW_Driver/WatchDog.o: D:/QLS/common/HW_Driver/WatchDog.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/HW_Driver/WatchDog.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/HW_Driver/WatchDog.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/HW_Driver/hw_abstract.o: D:/QLS/common/HW_Driver/hw_abstract.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/HW_Driver/hw_abstract.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/HW_Driver/hw_abstract.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/HW_Driver/prj_gpio.o: D:/QLS/common/HW_Driver/prj_gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #52 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/HW_Driver/prj_gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/HW_Driver/prj_gpio.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


