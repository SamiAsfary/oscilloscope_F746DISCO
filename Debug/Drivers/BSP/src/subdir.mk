################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/src/stm32746g_discovery.c \
../Drivers/BSP/src/stm32746g_discovery_lcd.c \
../Drivers/BSP/src/stm32746g_discovery_sdram.c \
../Drivers/BSP/src/stm32746g_discovery_ts.c 

OBJS += \
./Drivers/BSP/src/stm32746g_discovery.o \
./Drivers/BSP/src/stm32746g_discovery_lcd.o \
./Drivers/BSP/src/stm32746g_discovery_sdram.o \
./Drivers/BSP/src/stm32746g_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/src/stm32746g_discovery.d \
./Drivers/BSP/src/stm32746g_discovery_lcd.d \
./Drivers/BSP/src/stm32746g_discovery_sdram.d \
./Drivers/BSP/src/stm32746g_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/src/%.o Drivers/BSP/src/%.su Drivers/BSP/src/%.cyclo: ../Drivers/BSP/src/%.c Drivers/BSP/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/sasfa/STM32CubeIDE/workspace_1.12.0/oscilloscope_F746DISCO/Drivers/TPuP2021/Inc" -I"C:/Users/sasfa/STM32CubeIDE/workspace_1.12.0/oscilloscope_F746DISCO/Drivers/BSP/inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-src

clean-Drivers-2f-BSP-2f-src:
	-$(RM) ./Drivers/BSP/src/stm32746g_discovery.cyclo ./Drivers/BSP/src/stm32746g_discovery.d ./Drivers/BSP/src/stm32746g_discovery.o ./Drivers/BSP/src/stm32746g_discovery.su ./Drivers/BSP/src/stm32746g_discovery_lcd.cyclo ./Drivers/BSP/src/stm32746g_discovery_lcd.d ./Drivers/BSP/src/stm32746g_discovery_lcd.o ./Drivers/BSP/src/stm32746g_discovery_lcd.su ./Drivers/BSP/src/stm32746g_discovery_sdram.cyclo ./Drivers/BSP/src/stm32746g_discovery_sdram.d ./Drivers/BSP/src/stm32746g_discovery_sdram.o ./Drivers/BSP/src/stm32746g_discovery_sdram.su ./Drivers/BSP/src/stm32746g_discovery_ts.cyclo ./Drivers/BSP/src/stm32746g_discovery_ts.d ./Drivers/BSP/src/stm32746g_discovery_ts.o ./Drivers/BSP/src/stm32746g_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-src

