################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"D:/s32dsworkspace/QLS/common/Comm_Mgt/Int_Mgt/Int_interface.c" \
"D:/s32dsworkspace/QLS/common/Comm_Mgt/Int_Mgt/Int_para.c" \

C_SRCS += \
D:/s32dsworkspace/QLS/common/Comm_Mgt/Int_Mgt/Int_interface.c \
D:/s32dsworkspace/QLS/common/Comm_Mgt/Int_Mgt/Int_para.c \

OBJS_OS_FORMAT += \
./Sources/common/Comm_Mgt/Int_Mgt/Int_interface.o \
./Sources/common/Comm_Mgt/Int_Mgt/Int_para.o \

C_DEPS_QUOTED += \
"./Sources/common/Comm_Mgt/Int_Mgt/Int_interface.d" \
"./Sources/common/Comm_Mgt/Int_Mgt/Int_para.d" \

OBJS += \
./Sources/common/Comm_Mgt/Int_Mgt/Int_interface.o \
./Sources/common/Comm_Mgt/Int_Mgt/Int_para.o \

OBJS_QUOTED += \
"./Sources/common/Comm_Mgt/Int_Mgt/Int_interface.o" \
"./Sources/common/Comm_Mgt/Int_Mgt/Int_para.o" \

C_DEPS += \
./Sources/common/Comm_Mgt/Int_Mgt/Int_interface.d \
./Sources/common/Comm_Mgt/Int_Mgt/Int_para.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/common/Comm_Mgt/Int_Mgt/Int_interface.o: D:/s32dsworkspace/QLS/common/Comm_Mgt/Int_Mgt/Int_interface.c
	@echo 'Building file: $<'
	@echo 'Executing target #58 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Comm_Mgt/Int_Mgt/Int_interface.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Comm_Mgt/Int_Mgt/Int_interface.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/Comm_Mgt/Int_Mgt/Int_para.o: D:/s32dsworkspace/QLS/common/Comm_Mgt/Int_Mgt/Int_para.c
	@echo 'Building file: $<'
	@echo 'Executing target #59 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/common/Comm_Mgt/Int_Mgt/Int_para.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/common/Comm_Mgt/Int_Mgt/Int_para.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


