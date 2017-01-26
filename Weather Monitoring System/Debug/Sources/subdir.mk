################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/adc.c \
../Sources/dac.c \
../Sources/dma.c \
../Sources/i2c.c \
../Sources/log.c \
../Sources/main.c \
../Sources/profiler.c \
../Sources/rtc.c \
../Sources/uart.c 

OBJS += \
./Sources/adc.o \
./Sources/dac.o \
./Sources/dma.o \
./Sources/i2c.o \
./Sources/log.o \
./Sources/main.o \
./Sources/profiler.o \
./Sources/rtc.o \
./Sources/uart.o 

C_DEPS += \
./Sources/adc.d \
./Sources/dac.d \
./Sources/dma.d \
./Sources/i2c.d \
./Sources/log.d \
./Sources/main.d \
./Sources/profiler.d \
./Sources/rtc.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


