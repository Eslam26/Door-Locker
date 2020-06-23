################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPT.c \
../GPT_PBcfg.c \
../TWI.c \
../TWI_PBcfg.c \
../USART.c \
../USART_PBcfg.c \
../external_eeprom.c \
../main.c 

OBJS += \
./GPT.o \
./GPT_PBcfg.o \
./TWI.o \
./TWI_PBcfg.o \
./USART.o \
./USART_PBcfg.o \
./external_eeprom.o \
./main.o 

C_DEPS += \
./GPT.d \
./GPT_PBcfg.d \
./TWI.d \
./TWI_PBcfg.d \
./USART.d \
./USART_PBcfg.d \
./external_eeprom.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


