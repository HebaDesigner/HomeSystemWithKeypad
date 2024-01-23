/*
 * ADC_NPrivate.h
 * ADC driver for the microcontroller ATMega 32
 * Created on: Jun 2, 2023
 * Author: Heba Atef Ahmed
 */

#ifndef ADC_NPRIVATE_H_
#define ADC_NPRIVATE_H_

/*ADC Multiplexer Selection Register*/
#define ADMUX			*((volatile u8*)(0x27))

#define	ADMUX_REFS1		7		//select the voltage reference for the ADC
#define ADMUX_REFS0		6		//select the voltage reference for the ADC
#define ADMUX_ADLAR		5		//Left Adjust Result
#define ADMUX_MUX4 		4		//Analog Channel and Gain Selection Bits
#define ADMUX_MUX3 		3		//Analog Channel and Gain Selection Bits
#define ADMUX_MUX2		2		//Analog Channel and Gain Selection Bits
#define ADMUX_MUX1		1		//Analog Channel and Gain Selection Bits
#define ADMUX_MUX0		0		//Analog Channel and Gain Selection Bits
/***************************************/

/*ADC Control and Status Register*/
#define ADCSRA			*((volatile u8*)(0x26))
#define	ADCSRA_ADEN			7		//ADC Enable
#define	ADCSRA_ADSC			6		//START CONVERSION
#define	ADCSRA_ADATE		5		//Auto Trigger Enable
#define	ADCSRA_ADIF			4		//ADC Interrupt Flag
#define	ADCSRA_ADIE			3		//ADC Interrupt Enable
#define	ADCSRA_ADPS2 		2		//ADC Prescaler Select Bits
#define	ADCSRA_ADPS1 		1		//ADC Prescaler Select Bits
#define	ADCSRA_ADPS0 		0		//ADC Prescaler Select Bits
/***************************************/

//ADC Data Register High Byte
#define ADCH			*((volatile u8*)(0x25))
//ADC Data Register Low Byte
#define ADCL			*((volatile u8*)(0x24))
//ADC Data Register 10 bits
#define ADC				*((volatile u16*)(0x24))
/***************************************/

//Special FunctionIO Register –SFIOR    //ADC Auto Trigger Source
#define SFIOR           *((volatile u8*)0x50)
#define SFIOR_ADTS0     5
#define SFIOR_ADTS1     6
#define SFIOR_ADTS2     7

#define IDLE		0
#define BUSY		1

#define ENABLE		1
#define DISABLE		0

#define Single_Channel_Async     0
#define Chain_Async              1


#endif /* ADC_NPRIVATE_H_ */
