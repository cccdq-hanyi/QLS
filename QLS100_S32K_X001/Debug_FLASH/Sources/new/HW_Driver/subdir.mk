################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/new/HW_Driver/CAN.c" \
"../Sources/new/HW_Driver/SPI.c" \
"../Sources/new/HW_Driver/WatchDog.c" \
"../Sources/new/HW_Driver/hw_abstract.c" \
"../Sources/new/HW_Driver/prj_gpio.c" \

C_SRCS += \
../Sources/new/HW_Driver/CAN.c \
../Sources/new/HW_Driver/SPI.c \
../Sources/new/HW_Driver/WatchDog.c \
../Sources/new/HW_Driver/hw_abstract.c \
../Sources/new/HW_Driver/prj_gpio.c \

OBJS_OS_FORMAT += \
./Sources/new/HW_Driver/CAN.o \
./Sources/new/HW_Driver/SPI.o \
./Sources/new/HW_Driver/WatchDog.o \
./Sources/new/HW_Driver/hw_abstract.o \
./Sources/new/HW_Driver/prj_gpio.o \

C_DEPS_QUOTED += \
"./Sources/new/HW_Driver/CAN.d" \
"./Sources/new/HW_Driver/SPI.d" \
"./Sources/new/HW_Driver/WatchDog.d" \
"./Sources/new/HW_Driver/hw_abstract.d" \
"./Sources/new/HW_Driver/prj_gpio.d" \

OBJS += \
./Sources/new/HW_Driver/CAN.o \
./Sources/new/HW_Driver/SPI.o \
./Sources/new/HW_Driver/WatchDog.o \
./Sources/new/HW_Driver/hw_abstract.o \
./Sources/new/HW_Driver/prj_gpio.o \

OBJS_QUOTED += \
"./Sources/new/HW_Driver/CAN.o" \
"./Sources/new/HW_Driver/SPI.o" \
"./Sources/new/HW_Driver/WatchDog.o" \
"./Sources/new/HW_Driver/hw_abstract.o" \
"./Sources/new/HW_Driver/prj_gpio.o" \

C_DEPS += \
./Sources/new/HW_Driver/CAN.d \
./Sources/new/HW_Driver/SPI.d \
./Sources/new/HW_Driver/WatchDog.d \
./Sources/new/HW_Driver/hw_abstract.d \
./Sources/new/HW_Driver/prj_gpio.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/new/HW_Driver/CAN.o: ../Sources/new/HW_Driver/CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/HW_Driver/CAN.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/HW_Driver/CAN.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/new/HW_Driver/SPI.o: ../Sources/new/HW_Driver/SPI.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/HW_Driver/SPI.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/HW_Driver/SPI.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/new/HW_Driver/WatchDog.o: ../Sources/new/HW_Driver/WatchDog.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/HW_Driver/WatchDog.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/HW_Driver/WatchDog.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/new/HW_Driver/hw_abstract.o: ../Sources/new/HW_Driver/hw_abstract.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/HW_Driver/hw_abstract.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/HW_Driver/hw_abstract.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/new/HW_Driver/prj_gpio.o: ../Sources/new/HW_Driver/prj_gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/HW_Driver/prj_gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/HW_Driver/prj_gpio.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


