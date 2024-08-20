################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer_program.c \
../CLCD_program.c \
../DIO_program.c \
../GIE_program.c \
../House_System_program.c \
../Keypad_program.c \
../Led_program.c \
../Mapping_program.c \
../Servo_program.c \
../TIMER1_program.c \
../TIMER_program.c \
../main.c 

OBJS += \
./Buzzer_program.o \
./CLCD_program.o \
./DIO_program.o \
./GIE_program.o \
./House_System_program.o \
./Keypad_program.o \
./Led_program.o \
./Mapping_program.o \
./Servo_program.o \
./TIMER1_program.o \
./TIMER_program.o \
./main.o 

C_DEPS += \
./Buzzer_program.d \
./CLCD_program.d \
./DIO_program.d \
./GIE_program.d \
./House_System_program.d \
./Keypad_program.d \
./Led_program.d \
./Mapping_program.d \
./Servo_program.d \
./TIMER1_program.d \
./TIMER_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


