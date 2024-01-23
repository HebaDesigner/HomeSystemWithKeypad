/*
 * ADC_NProgram.c
 * ADC driver for the microcontroller ATMega 32
 * Created on: Jun 2, 2023
 * Author: Heba Atef Ahmed
 */

#include"STD_TYPES.h"
#include"BIT_CALC.h"
#include"avr/delay.h"
#include "ADC_NPrivate.h"
#include "ADC_NConfig.h"
#include "ADC_NInterface.h"


static u16* ADC_pu8Reading= NULL;
static void (*ADC_pvCallBackNotificationFunc)(void)= NULL;

static u8* ADC_pu8ChainChannelArr = NULL;                                   //Global variable to carry chain array
static u8 ADC_u8ChainSize;                                                 //Global variable to carry number of channels
static u16* ADC_pu16ChainResultArr = NULL;                                //Global variable to carry chain result
static u8 ADC_pu8ChainConversationIndex = 0;                           //Global variable to carry current conversation Index

static u8 ADC_u8ISRSource;


u8 ADC_u8BusyState= IDLE;

void ADC_voidInit(void)
{
	/*AVCC as reference voltage*/

#if VOLT_REF == AREF			//AREF, Internal Vref turned off
	CLR_BIT(ADMUX,ADMUX_REFS1);
	CLR_BIT(ADMUX,ADMUX_REFS0);

#elif VOLT_REF == AVCC			//AVCC with external capacitor at AREF pin
	CLR_BIT(ADMUX, ADMUX_REFS1);
	SET_BIT(ADMUX, ADMUX_REFS0);

#elif VOLT_REF == VREF2_56		//Internal 2.56V Voltage Reference with external capacitor at AREF pin
	SET_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);

#else
#error "VOLT_REFERENCE is not exist"

#endif

#if BITS_ADJUST == BITS_8			/*ACTIVATE Left Adjust*/
	SET_BIT(ADMUX,ADMUX_ADLAR);

#elif BITS_ADJUST == BITS_10
	CLR_BIT(ADMUX, ADMUX_ADLAR);

#else
#error "BITS_ADJUST is not exist"

#endif

	/*Set Prescaler to divide from Div_2 to Div_128*/   //select Div_128 //with Bit masking Not #if
	ADCSRA = ((ADCSRA &= 0b11111000) | ADC_PRESC);

	/*ADC ENABLE*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

}

u8 ADC_u8StartConversionSynch(u8 copy_u8Channel, u8* copy_pu8Reading)
{
	u32 Local_u32Counter=0;
	u8 Local_u8ErrorState=OK;

	if(ADC_u8BusyState == IDLE)
	{
		/*ADC is now BUSY*/
		ADC_u8BusyState= BUSY;

		/*Bit_Mask	1: Clear bits in AMUX register
					2: Set the required channel into the MUX bits*/
		ADMUX = ((ADMUX &= 0b11100000) | copy_u8Channel);

		/*Start Conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);

		/*Polling (busy waiting) until the conversion complete flag is set of counter reaching timeout value*/
		while (((GET_BIT(ADCSRA,ADCSRA_ADIF)) == 0) && (Local_u32Counter != ADC_u32TIMEOUT))
		{
			Local_u32Counter++;
		}
		if (Local_u32Counter == ADC_u32TIMEOUT)
		{
			/*loop is broken because of timeout is reached*/
			u8 Local_u8ErrorState = NOK;
		}
		else
		{
			/*loop is broken because flag is raised*/
			/*Clear the conversion complete flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);

			/*Return the reading*/
			*copy_pu8Reading = ADC;

			/*ADC is finished, return it to IDLE*/
			ADC_u8BusyState= IDLE;
		}
	}
	/*#elif AUTO_TRIGGER == ENABLE

	//Enable Auto Trigger
	SET_BIT(ADCSRA,ADCSRA_ADATE);

	//Set Channel first before starting conversion
	ADMUX = ((ADMUX &= 0b11100000) | 0b00000111);

	//Set interrupt enable for ADC
	SET_BIT(ADCSRA,ADCSRA_ADIE);

	//Set trigger mode
	SFIOR &= 0b00011111
	SFIOR |= ADC_Trigger

	//Start Convertion
	SET_BIT(ADCSRA,ADCSRA_ADSC);
#endif*/

	else
	{
		Local_u8ErrorState = BUSY_FUNC;
	}
	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsynch(u8 copy_u8Channel, u8* copy_pu8Reading, void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_uErrorState=OK;

	if(ADC_u8BusyState == IDLE)
	{
		if((copy_pu8Reading == NULL) || (Copy_pvNotificationFunc == NULL))
		{
			Local_uErrorState = NULL_POINTER;
		}
		else
		{
			/*make ADC busy in order not to work until being idle*/
			ADC_u8BusyState= BUSY;

			/*make ISR source: single channel asynchronous*/
			ADC_u8ISRSource = Single_Channel_Async;

			/*Initialize the reading variable globally*/
			ADC_pu8Reading = copy_pu8Reading;

			/*Initialize the callback notification function globally*/
			ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Bit_Mask	1: Clear bits in AMUX register
						2: Set the required channel into the MUX bits*/
			ADMUX = ((ADMUX &= 0b11100000)|copy_u8Channel);

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ADC interrupt Enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}

	}
	else
	{
		Local_uErrorState = BUSY_FUNC;
	}
	return Local_uErrorState;
}

u8 ADC_u8StartChainAsynch(Chain* Copy_Chain)
{
	u8 Local_uErrorState = OK;

	//Check Null Pointer
	if(Copy_Chain == NULL)
	{
		Local_uErrorState = NULL_POINTER;
	}
	else
	{
		if(ADC_u8BusyState == IDLE)
		{
			//make ADC busy in order not to work until being idle
			ADC_u8BusyState= BUSY;

			/*make ISR source: Chain asynchronous*/
			ADC_u8ISRSource = Chain_Async;

			//Initialize the Chain Channel Array globally
			ADC_pu8ChainChannelArr = Copy_Chain->Channel;

			//Initialize the result array globally
			ADC_pu16ChainResultArr = Copy_Chain->Res;

			//Initialize the Chain Size globally
			ADC_u8ChainSize = Copy_Chain->Size;

			//Initialize the callback notification function globally
			ADC_pvCallBackNotificationFunc = Copy_Chain->NotoficationFunc;

			//Initialize current conversation index globally
			ADC_pu8ChainConversationIndex = 0;

			//Bit_Mask	1: Clear bits in AMUX register
			//          2: Set the required channel (first channel) into the MUX bits
			ADMUX = ((ADMUX &= 0b11100000) | ADC_pu8ChainChannelArr[ADC_pu8ChainConversationIndex]);

			//Start Conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			//ADC interrupt Enable
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_uErrorState = BUSY_FUNC;
		}
	}
	return Local_uErrorState;
}


void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ISRSource == Single_Channel_Async)
	{
		/*Read ADC result*/
		*ADC_pu8Reading = ADC;

		/*make ADC state be IDLE because it finished*/
		ADC_u8BusyState = IDLE;

		/*Invoke the callback notification function*/
		ADC_pvCallBackNotificationFunc();

		/*Disable ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8ISRSource == Chain_Async)
	{
		/*Read ADC result*/
		ADC_pu16ChainResultArr[ADC_pu8ChainConversationIndex] = ADC;

		/*Increment Index*/
		ADC_pu8ChainConversationIndex++;

		/*check chain is finished or not*/
		if(ADC_pu8ChainConversationIndex == ADC_u8ChainSize)
		{
			/*Chain is finished*/

			/*make ADC state be IDLE because it finished*/
			ADC_u8BusyState = IDLE;

			/*Invoke the callback notification function*/
			ADC_pvCallBackNotificationFunc();

			/*Disable ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			/*chain is not finished*/

			//Bit_Mask	1: Clear bits in AMUX register
			//          2: Set the required channel (next channel) into the MUX bits
			ADMUX = ((ADMUX &= 0b11100000)|ADC_pu8ChainChannelArr[ADC_pu8ChainConversationIndex]);

			/*Start new Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}

s32 mapping (s32 Input_min, s32 Input_max, s32 Output_min, s32 Output_max, s32 Input_Val)
{
	return  ((((Output_max - Output_min)*(Input_Val-Input_min))/(Input_max-Input_min))+Output_min);
}
