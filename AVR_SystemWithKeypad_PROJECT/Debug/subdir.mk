################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_NProgram.c \
../CLCD_program.c \
../DIO_Program.c \
../GIE_Program.c \
../KPD_Program.c \
../SEGMENT7_program.c \
../main.c 

OBJS += \
./ADC_NProgram.o \
./CLCD_program.o \
./DIO_Program.o \
./GIE_Program.o \
./KPD_Program.o \
./SEGMENT7_program.o \
./main.o 

C_DEPS += \
./ADC_NProgram.d \
./CLCD_program.d \
./DIO_Program.d \
./GIE_Program.d \
./KPD_Program.d \
./SEGMENT7_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


