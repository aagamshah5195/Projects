################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/buffer.c \
../Sources/log.c \
../Sources/main.c \
../Sources/message.c \
../Sources/nordic.c \
../Sources/profiler.c \
../Sources/spi.c \
../Sources/uart.c 

OBJS += \
./Sources/buffer.o \
./Sources/log.o \
./Sources/main.o \
./Sources/message.o \
./Sources/nordic.o \
./Sources/profiler.o \
./Sources/spi.o \
./Sources/uart.o 

C_DEPS += \
./Sources/buffer.d \
./Sources/log.d \
./Sources/main.d \
./Sources/message.d \
./Sources/nordic.d \
./Sources/profiler.d \
./Sources/spi.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


