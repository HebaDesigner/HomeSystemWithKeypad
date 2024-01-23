/*
 * KPD_Program.c
 * KPD driver for the microcontroller ATMega 32
 * Created on: May 19, 2023
 * Author: Heba Atef Ahmed
 */
#include"STD_TYPES.h"
#include"BIT_CALC.h"
#include"avr/delay.h"
#include "DIO_Interface.h"
#include "CLCD_Interface.h"
#include "KPD_Config.h"
#include "KPD_Interface.h"

u8 KPD_Au8_Col_PINS[KPD_u8_Col_NB] = {KPD_u8_Col_PIN_0, KPD_u8_Col_PIN_1, KPD_u8_Col_PIN_2,KPD_u8_Col_PIN_3};
u8 KPD_Au8_Row_PINS[KPD_u8_Row_NB] = {KPD_u8_Row_PIN_0, KPD_u8_Row_PIN_1, KPD_u8_Row_PIN_2,KPD_u8_Row_PIN_3};

u8 Col_index;
u8 Row_index;


void KPD_Void_Init(void){

#if  KPD_u8Activation_Type == KPD_u8Active_Col

	for(Col_index =0; Col_index < KPD_u8_Col_NB; Col_index++)
	{
#if  KPD_u8Connection_Type == KPD_u8_Pull_Up

		DIO_u8_SetPin_Dir(KPD_PORT, KPD_Au8_Col_PINS[Col_index], DIO_u8_Output);
		DIO_u8_SetPin_value(KPD_PORT, KPD_Au8_Col_PINS[Col_index], DIO_u8_High);

		for(Row_index =0; Row_index < KPD_u8_Row_NB; Row_index++){

			DIO_u8_SetPin_Dir(KPD_PORT, KPD_Au8_Row_PINS[Row_index], DIO_u8_Input);
			DIO_u8_SetPin_value(KPD_PORT, KPD_Au8_Row_PINS[Row_index], DIO_u8_High);
		}

#endif

	}
#endif

}
u8 KPD_voidGet_KPD_Status(void)
{
	u8 Local_u8Pressed_Key = KPD_No_Pressed_Key, Col_index, Row_index, Local_u8Pin_State;
	u8 Local_u8KPD_Arr[KPD_u8_Row_NB][KPD_u8_Col_NB] = KPD_Arr_VAL;


#if  KPD_u8Activation_Type == KPD_u8Active_Col

	for(Col_index =0; Col_index < KPD_u8_Col_NB;Col_index++)
	{
#if  KPD_u8Connection_Type == KPD_u8_Pull_Up

		//Activate the current Column
		DIO_u8_SetPin_value(KPD_PORT, KPD_Au8_Col_PINS[Col_index], DIO_u8_Low);

		for(Row_index =0; Row_index < KPD_u8_Row_NB; Row_index++)
		{
			//Read the current Row
			DIO_u8_GetPin_value(KPD_PORT, KPD_Au8_Row_PINS[Row_index], &Local_u8Pin_State);

			//check if switch is pressed
			if(DIO_u8_Low == Local_u8Pin_State)
			{
				Local_u8Pressed_Key = Local_u8KPD_Arr[Row_index][Col_index];

				//Polling ( busy waiting ) until the key is released

				while(DIO_u8_Low == Local_u8Pin_State)
				{
					DIO_u8_GetPin_value(KPD_PORT, KPD_Au8_Row_PINS[Row_index], &Local_u8Pin_State);
				}
				return Local_u8Pressed_Key;
			}
		}
		//DeActivate the current Column
		DIO_u8_SetPin_value(KPD_PORT, KPD_Au8_Col_PINS[Col_index], DIO_u8_High);
#endif
	}
#endif

	return Local_u8Pressed_Key;
}
