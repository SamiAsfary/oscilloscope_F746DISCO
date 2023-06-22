################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/TPuP2021/Src/GENERATE.c \
../Drivers/TPuP2021/Src/INTERFACE.c \
../Drivers/TPuP2021/Src/LED.c \
../Drivers/TPuP2021/Src/OBSERVE.c 

OBJS += \
./Drivers/TPuP2021/Src/GENERATE.o \
./Drivers/TPuP2021/Src/INTERFACE.o \
./Drivers/TPuP2021/Src/LED.o \
./Drivers/TPuP2021/Src/OBSERVE.o 

C_DEPS += \
./Drivers/TPuP2021/Src/GENERATE.d \
./Drivers/TPuP2021/Src/INTERFACE.d \
./Drivers/TPuP2021/Src/LED.d \
./Drivers/TPuP2021/Src/OBSERVE.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/TPuP2021/Src/%.o Drivers/TPuP2021/Src/%.su Drivers/TPuP2021/Src/%.cyclo: ../Drivers/TPuP2021/Src/%.c Drivers/TPuP2021/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/sasfa/STM32CubeIDE/workspace_1.12.0/oscilloscope_F746DISCO/Drivers/TPuP2021/Inc" -I"C:/Users/sasfa/STM32CubeIDE/workspace_1.12.0/oscilloscope_F746DISCO/Drivers/BSP/inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-TPuP2021-2f-Src

clean-Drivers-2f-TPuP2021-2f-Src:
	-$(RM) ./Drivers/TPuP2021/Src/GENERATE.cyclo ./Drivers/TPuP2021/Src/GENERATE.d ./Drivers/TPuP2021/Src/GENERATE.o ./Drivers/TPuP2021/Src/GENERATE.su ./Drivers/TPuP2021/Src/INTERFACE.cyclo ./Drivers/TPuP2021/Src/INTERFACE.d ./Drivers/TPuP2021/Src/INTERFACE.o ./Drivers/TPuP2021/Src/INTERFACE.su ./Drivers/TPuP2021/Src/LED.cyclo ./Drivers/TPuP2021/Src/LED.d ./Drivers/TPuP2021/Src/LED.o ./Drivers/TPuP2021/Src/LED.su ./Drivers/TPuP2021/Src/OBSERVE.cyclo ./Drivers/TPuP2021/Src/OBSERVE.d ./Drivers/TPuP2021/Src/OBSERVE.o ./Drivers/TPuP2021/Src/OBSERVE.su

.PHONY: clean-Drivers-2f-TPuP2021-2f-Src

