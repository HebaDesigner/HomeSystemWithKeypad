/*
 * Program.c
 * DIO driver for the microcontroller ATMega 32
 * Created on: May 6, 2023
 * Author: Heba Atef Ahmed
 */
#include"STD_TYPES.h"
#include"BIT_CALC.h"
#include"DIO_Private.h"
#include"DIO_Interface.h"

u8 DIO_u8_SetPin_value(u8 Copy_u8_PortID,u8 Copy_u8_Pin_ID,u8 Copy_u8_Pin_Val)
{

	if( (Copy_u8_Pin_ID >= 0) && (Copy_u8_Pin_ID <= 7) ){

		if( (Copy_u8_Pin_Val == DIO_u8_Low) || (Copy_u8_Pin_Val == DIO_u8_High) ){

			switch(Copy_u8_PortID){

			case Group_A:
				ASSIGN_Bit(DIO_u8_PORTA, Copy_u8_Pin_ID, Copy_u8_Pin_Val);
				break;

			case Group_B:
				ASSIGN_Bit(DIO_u8_PORTB, Copy_u8_Pin_ID, Copy_u8_Pin_Val);
				break;

			case Group_C:
				ASSIGN_Bit(DIO_u8_PORTC, Copy_u8_Pin_ID, Copy_u8_Pin_Val);
				break;

			case Group_D:
			ASSIGN_Bit(DIO_u8_PORTD, Copy_u8_Pin_ID, Copy_u8_Pin_Val);
			break;

			default: return Invalid_u8_Error ;
			}
		}else
             return Invalid_u8_Error ;
	}else
         return Invalid_u8_Error ;
	return Valid;
}
u8 DIO_u8_SetPin_Dir(u8 Copy_u8_PortID,u8 Copy_u8_Pin_ID,u8 Copy_u8_Pin_Dir)
{

	if( (Copy_u8_Pin_ID >= 0) && (Copy_u8_Pin_ID <= 7) ){

		if((Copy_u8_Pin_Dir == DIO_u8_Input) || (Copy_u8_Pin_Dir == DIO_u8_Output)){

			switch(Copy_u8_PortID){

			case Group_A:
				ASSIGN_Bit(DIO_u8_DDRA, Copy_u8_Pin_ID, Copy_u8_Pin_Dir);
				break;

			case Group_B:
				ASSIGN_Bit(DIO_u8_DDRB, Copy_u8_Pin_ID, Copy_u8_Pin_Dir);
				break;

			case Group_C:
				ASSIGN_Bit(DIO_u8_DDRC, Copy_u8_Pin_ID, Copy_u8_Pin_Dir);
				break;

			case Group_D:
			ASSIGN_Bit(DIO_u8_DDRD, Copy_u8_Pin_ID, Copy_u8_Pin_Dir);
			break;

			default: return Invalid_u8_Error;
			}
		}else
			return Invalid_u8_Error;
	}else
		return Invalid_u8_Error;

	return Valid;
}

u8 DIO_u8_SetPort_value(u8 Copy_u8_PortID, u8 Copy_u8_Port_Val)
{
	switch(Copy_u8_PortID)
	{
	case Group_A: DIO_u8_PORTA = Copy_u8_Port_Val;
			break;
	case Group_B: DIO_u8_PORTB = Copy_u8_Port_Val;
			break;
	case Group_C: DIO_u8_PORTC = Copy_u8_Port_Val;
			break;
	case Group_D: DIO_u8_PORTD = Copy_u8_Port_Val;
			break;
	default: return Invalid_u8_Error ;
	}
	return Valid;
}

u8 DIO_u8_SetPort_Dir(u8 Copy_u8_PortID, u8 Copy_u8_Port_Dir)
{
	switch(Copy_u8_PortID)
	{
	case Group_A: DIO_u8_DDRA = Copy_u8_Port_Dir;
			break;
	case Group_B: DIO_u8_DDRB = Copy_u8_Port_Dir;
			break;
	case Group_C: DIO_u8_DDRC = Copy_u8_Port_Dir;
			break;
	case Group_D: DIO_u8_DDRD = Copy_u8_Port_Dir;
			break;
	default: return Invalid_u8_Error ;
	}

	return Valid;
}

u8 DIO_u8_GetPin_value(u8 Copy_u8_PortID,u8 Copy_u8_Pin_ID, u8 *Copy_Pu8_u8_Pin_Val)
{
	switch(Copy_u8_PortID)
	{
	case Group_A: *Copy_Pu8_u8_Pin_Val = GET_BIT(DIO_u8_PINA,Copy_u8_Pin_ID);
			break;
	case Group_B: *Copy_Pu8_u8_Pin_Val = GET_BIT(DIO_u8_PINB,Copy_u8_Pin_ID);
			break;
	case Group_C: *Copy_Pu8_u8_Pin_Val = GET_BIT(DIO_u8_PINC,Copy_u8_Pin_ID);
			break;
	case Group_D: *Copy_Pu8_u8_Pin_Val = GET_BIT(DIO_u8_PIND,Copy_u8_Pin_ID);
			break;
	default: return Invalid_u8_Error ;
	}
	return Valid;
}

u8 DIO_u8_GetPort_value(u8 Copy_u8_PortID, u8 *Copy_Pu8_u8_Pin_Val)
{
	switch(Copy_u8_PortID)
	{
	case Group_A: *Copy_Pu8_u8_Pin_Val = DIO_u8_PORTA;
			break;
	case Group_B: *Copy_Pu8_u8_Pin_Val = DIO_u8_PORTB;
			break;
	case Group_C: *Copy_Pu8_u8_Pin_Val = DIO_u8_PORTC;
			break;
	case Group_D: *Copy_Pu8_u8_Pin_Val = DIO_u8_PORTD;
			break;
	default: return Invalid_u8_Error ;
	}
	return Valid;
}






