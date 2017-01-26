################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/I2C.c \
../Sources/MMA8451Q.c \
../Sources/TSI.c \
../Sources/log.c \
../Sources/main.c \
../Sources/uart.c \
../Sources/usb.c 

OBJS += \
./Sources/I2C.o \
./Sources/MMA8451Q.o \
./Sources/TSI.o \
./Sources/log.o \
./Sources/main.o \
./Sources/uart.o \
./Sources/usb.o 

C_DEPS += \
./Sources/I2C.d \
./Sources/MMA8451Q.d \
./Sources/TSI.d \
./Sources/log.d \
./Sources/main.d \
./Sources/uart.d \
./Sources/usb.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


