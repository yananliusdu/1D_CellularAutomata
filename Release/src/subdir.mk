################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/scamp5_main.cpp 

OBJS += \
./src/scamp5_main.o 

CPP_DEPS += \
./src/scamp5_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=gnu++14 -D__NEWLIB__ -DNDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -DNO_BOARD_LIB -DCPP_USE_HEAP -D__LPC43XX__ -D__MULTICORE_M0APP -DCORE_M0APP -DWORKSPACE_PATH='R"RRR(C:\MCUWorkspace\LPCworkspace2)RRR"' -DPROJECT_NAME='R"RRR(1D_CellularAutomata)RRR"' -I"C:\MCUWorkspace\LPCworkspace2\lpc_chip_43xx_m0\inc" -I"C:\MCUWorkspace\LPCworkspace2\s5d_m0\inc" -I"C:\MCUWorkspace\LPCworkspace2\s5d_m4\inc" -O2 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


