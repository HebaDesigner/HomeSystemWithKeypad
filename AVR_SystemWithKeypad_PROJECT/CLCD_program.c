/*
 * Program.c
 * CLCD driver for the microcontroller ATMega 32
 * Created on: May 8, 2023
 * Author: Heba Atef Ahmed
 */

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "util/delay.h"

#define F_CPU 8000000

void CLCD_voidInit(void){

	DIO_u8_SetPort_Dir(CLCD_DATA_PORT,DIO_u8_PORT_Output);

	DIO_u8_SetPin_Dir(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_u8_Output);
	DIO_u8_SetPin_Dir(CLCD_CONTROL_PORT,CLCD_RW_PIN,DIO_u8_Output);
	DIO_u8_SetPin_Dir(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8_Output);

	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8_Low);

	/*wait for more than 30 msec*/
	_delay_ms(40);

	CLCD_voidSendCommand(lcd_Home);

	CLCD_voidSendCommand(lcd_FunctionSet8bit);

	CLCD_voidSendCommand(lcd_DisplayOn);

	CLCD_voidSendCommand(lcd_Clear);

	CLCD_voidSendCommand(lcd_EntryMode_Incr);
	_delay_ms(2);
}

void CLCD_voidSendCommand(u8 Copy_u8Command){

	/*Set RS pin to low for command*/
	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_u8_Low);
	/*Set Rw pin to low for write*/
	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_RW_PIN,DIO_u8_Low);
	/*Set command to data pins*/
	DIO_u8_SetPort_value(CLCD_DATA_PORT,Copy_u8Command);
	/*Set enable pulse*/
	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8_Low);
	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8_High);
	_delay_ms(2);
	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8_Low);

}

void CLCD_voidWriteCharctr(u8 Copy_u8Data){
	/*Set RS pin to high for data*/
	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_u8_High);
		/*Set Rw pin to low for write*/
	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_RW_PIN,DIO_u8_Low);
		/*Set Data to data pins*/
	DIO_u8_SetPort_value(CLCD_DATA_PORT,Copy_u8Data);
		/*Set enable pulse*/
	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8_Low);
	DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8_High);
		_delay_ms(2);
		DIO_u8_SetPin_value(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8_Low);
}

void CLCD_voidWriteString (u8* Copy_pcString)
{
	u8 Local_u8Counter=0;
	while(Copy_pcString[Local_u8Counter]!='\0')
	{
		CLCD_voidWriteCharctr(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void CLCD_Gotoxy (u8 cpy_u8Xpos,u8 cpy_u8Ypos)
{
	u8 Local_u8Address;
	if (cpy_u8Xpos==0)
	{
		/*location in first line*/
		Local_u8Address=cpy_u8Ypos;
	}
	else if (cpy_u8Xpos==1)
	{
		/*location in second line*/
		Local_u8Address=cpy_u8Ypos+0x40;
	}
	/*Set DDRAM Adress 0b10000000=128*/
	CLCD_voidSendCommand(Local_u8Address+128);
}

//Store and write only one character in specific position//
void CLCD_voidWriteOneExtraChar (u8* cpy_ExtraChar,u8 cpy_ExtraChar_pos,u8 cpy_u8Xpos,u8 cpy_u8Ypos)
{
	u8 local_u8CGRAMAdress=0,Local_u8Iterator;

	//Calculate the CGRAM Address whose each block is 8 bytes
	local_u8CGRAMAdress=cpy_ExtraChar_pos*8;

	//Send CGRAM Address command to LCD, with setting bit 6, clearing bit 7
	CLCD_voidSendCommand(local_u8CGRAMAdress+64);

	//write the pattern into CGRAM
	for (Local_u8Iterator=0;Local_u8Iterator<9;Local_u8Iterator++)
	{
		CLCD_voidWriteCharctr(cpy_ExtraChar[Local_u8Iterator]);
	}

	//Go back to the DDRAM to display the pattern
	CLCD_Gotoxy(cpy_u8Xpos,cpy_u8Ypos);

	//Display the pattern written in the CGRAM
	CLCD_voidWriteCharctr(cpy_ExtraChar_pos);
}

//Store and write many characters//
//ExtraChar_No-> Many characters will be store (one char or 2 or ...8 characters) then written
void CLCD_voidWriteExtraChar (u8* cpy_ExtraChar,u8 cpy_ExtraChar_No,u8 cpy_u8Xpos,u8 cpy_u8Ypos)
{
	u8 Local_u8Iterator;

	//Send CGRAM Address command to LCD, with setting bit 6, clearing bit 7
	CLCD_voidSendCommand(64);

	//write the pattern into CGRAM
	for (Local_u8Iterator=0;Local_u8Iterator<(cpy_ExtraChar_No*8);Local_u8Iterator++)
	{
		CLCD_voidWriteCharctr(cpy_ExtraChar[Local_u8Iterator]);
	}

	//Go back to the DDRAM to display the pattern
	CLCD_Gotoxy(cpy_u8Xpos,cpy_u8Ypos);

	//For arabic to write from right to left
	//CLCD_voidSendCommand(lcd_EntryMode_Decr);

	//Display the pattern written in the CGRAM
	for (Local_u8Iterator=0;Local_u8Iterator<cpy_ExtraChar_No;Local_u8Iterator++)
		{
			CLCD_voidWriteCharctr(Local_u8Iterator);
		}
}

//Store only one character without write on screen in specific position//
void CLCD_voidStoreOneExtraChar (u8* cpy_ExtraChar,u8 cpy_ExtraChar_pos)
{
	u8 local_u8CGRAMAdress=0,Local_u8Iterator;

	//Calculate the CGRAM Address whose each block is 8 bytes
	local_u8CGRAMAdress=cpy_ExtraChar_pos*8;

	//Send CGRAM Address command to LCD, with setting bit 6, clearing bit 7
	CLCD_voidSendCommand(local_u8CGRAMAdress+64);

	//write the pattern into CGRAM
	for (Local_u8Iterator=0;Local_u8Iterator<9;Local_u8Iterator++)
	{
		CLCD_voidWriteCharctr(cpy_ExtraChar[Local_u8Iterator]);
	}

	//Go back to the DDRAM to display the pattern
	CLCD_Gotoxy(0,0);

	//Display the pattern written in the CGRAM
	//CLCD_voidWriteCharctr(cpy_ExtraChar_pos);
}

void CLCD_voidWriteNumber(u32 Cpy_Number)
{
CLCD_voidWriteCharctr((Cpy_Number/1000)+48);
CLCD_voidWriteCharctr(((Cpy_Number%1000)/100)+48);
CLCD_voidWriteCharctr(((Cpy_Number%100)/10)+48);
CLCD_voidWriteCharctr((Cpy_Number%10)+48);
}

void CLCD_voidWriteOneNumber(u8 Cpy_OneNumber)
{
	CLCD_voidWriteCharctr((Cpy_OneNumber%10)+48);

}

