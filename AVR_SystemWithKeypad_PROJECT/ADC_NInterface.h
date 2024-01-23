/*
 * ADC_NInterface.h
 * ADC driver for the microcontroller ATMega 32
 * Created on: Jun 2, 2023
 * Author: Heba Atef Ahmed
 */

#ifndef ADC_NINTERFACE_H_
#define ADC_NINTERFACE_H_


#define Channel_A0	0
#define Channel_A1	1
#define Channel_A2	2
#define Channel_A3	3
#define Channel_A4	4
#define Channel_A5	5
#define Channel_A6	6
#define Channel_A7	7

#define AREF		1
#define AVCC		2
#define VREF2_56	3

#define	Div_2		0b00000000		//0
#define	Div_4		0b00000010		//2
#define	Div_8		0b00000011		//3
#define	Div_16		0b00000100		//4
#define	Div_32		0b00000101		//5
#define	Div_64		0b00000110		//6
#define	Div_128		0b00000111		//7

#define Free_Running_Mode                0b00000000
#define Analog_Comprator                 0b00100000
#define External_Interrupt_Requst_0      0b01000000
#define Counter0_Compare_Match           0b01100000
#define Counter0_Overflow                0b10000000
#define Counter0_Compare_Match_B         0b10100000
#define Counter1_Overflow                0b11000000
#define Counter1_Capture_Event           0b11100000

#define BITS_8		1
#define BITS_10		2

#define VOLT_REF		AVCC			//you can select the mode //
/*Options:
 	 	 AREF
 	 	 AVCC
 	 	 VREF2_56
*/

#define	BITS_ADJUST 	BITS_10			//you can select the mode //
/*Options:
 	 	 BITS_8
 	 	 BITS_10
*/

#define	ADC_PRESC 	Div_128				/*Set Prescaler to divide Div_128*/
/*Options:
 	 	 Div_2
 	 	 Div_4
 	 	 Div_8
 	 	 Div_16
 	 	 Div_32
 	 	 Div_64
*/
#define AUTO_TRIGGER  ENABLE
#define ADC_Trigger   Free_Running_Mode
/*Options
 *       Free Running Mode
 *       Analog_Comprator
 *       External_Interrupt_Requst 0
 *       Timer/Counter0 Compare Match
 *       Timer/Counter0 Overflow
 *       Timer/Counter Compare Match B
 *       Timer/Counter1 Overflow
 *       Timer/Counter1 Capture Event
 */
typedef struct{
	u8* Channel;
	u16* Res;
	u8 Size;
	void (*NotoficationFunc)(void);
}Chain;


void ADC_voidInit(void);
u8 ADC_u8StartConversionSynch(u8 copy_u8Channel, u8* copy_pu8Reading);
u8 ADC_u8StartConversionAsynch(u8 copy_u8Channel, u8* copy_pu8Reading, void(*Copy_pvNotificationFunc)(void));
u8 ADC_u8StartChainAsynch(Chain* Copy_Chain);

s32 mapping (s32 Input_min, s32 Input_max, s32 Output_min, s32 Output_max, s32 Input_Val);

#endif /* ADC_NINTERFACE_H_ */
