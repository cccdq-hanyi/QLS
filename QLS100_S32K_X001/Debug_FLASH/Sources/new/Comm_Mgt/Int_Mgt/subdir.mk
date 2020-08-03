################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/new/Comm_Mgt/Int_Mgt/Int_interface.c" \
"../Sources/new/Comm_Mgt/Int_Mgt/Int_para.c" \

C_SRCS += \
../Sources/new/Comm_Mgt/Int_Mgt/Int_interface.c \
../Sources/new/Comm_Mgt/Int_Mgt/Int_para.c \

OBJS_OS_FORMAT += \
./Sources/new/Comm_Mgt/Int_Mgt/Int_interface.o \
./Sources/new/Comm_Mgt/Int_Mgt/Int_para.o \

C_DEPS_QUOTED += \
"./Sources/new/Comm_Mgt/Int_Mgt/Int_interface.d" \
"./Sources/new/Comm_Mgt/Int_Mgt/Int_para.d" \

OBJS += \
./Sources/new/Comm_Mgt/Int_Mgt/Int_interface.o \
./Sources/new/Comm_Mgt/Int_Mgt/Int_para.o \

OBJS_QUOTED += \
"./Sources/new/Comm_Mgt/Int_Mgt/Int_interface.o" \
"./Sources/new/Comm_Mgt/Int_Mgt/Int_para.o" \

C_DEPS += \
./Sources/new/Comm_Mgt/Int_Mgt/Int_interface.d \
./Sources/new/Comm_Mgt/Int_Mgt/Int_para.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/new/Comm_Mgt/Int_Mgt/Int_interface.o: ../Sources/new/Comm_Mgt/Int_Mgt/Int_interface.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/Comm_Mgt/Int_Mgt/Int_interface.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/Comm_Mgt/Int_Mgt/Int_interface.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/new/Comm_Mgt/Int_Mgt/Int_para.o: ../Sources/new/Comm_Mgt/Int_Mgt/Int_para.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/new/Comm_Mgt/Int_Mgt/Int_para.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/new/Comm_Mgt/Int_Mgt/Int_para.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


