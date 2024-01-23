/*
 *  main.c
 *  Created on: Jul 20, 2023
 *  Author: Heba Atef Ahmed
 */
#include "STD_TYPES.h"
#include "BIT_CALC.h"
#include "DIO_Interface.h"
#include "ADC_NInterface.h"
#include "CLCD_interface.h"
#include "CLCD_extra.h"
#include "KPD_Interface.h"
#include "SEGMENT7_interface.h"
#include "GIE_Interface.h"
#include "avr/delay.h"

u16 App_u16ADCReading;

void ADCTempNotification (void);
void ADCLDRNotification (void);


void main (void)
{
	//Local variable to Store data from keypad when pressed any key
	u8 Local_u8Key;

	//local Array to Store ID to compare passord
	u8 Local_u8ArrID[4],IteratorID=0,i;

	//local Array to Store Pass to compare with ID if It write or wrong
	u8 Local_u8ArrPass[4],IteratorPass=0;

	u32 Local_u8Pass=0,j=1000;
	u32 Local_u8UserPass=0;

	//Local Variable make 3 tries only to Enter password
	u8 Local_u8Wrong_pass=3;

	KPD_Void_Init();
	CLCD_voidInit();
	Segment7_VoidInit();

	//7Segment Array to display Numbers*
	u8 NUMBERS [10] = {zero, one, two, three, four, five, six, seven, eight, nine};

	//First display on screen welocm for 3 seconds
	CLCD_voidWriteString("WELCOME");
	_delay_ms(350);
	CLCD_voidSendCommand(lcd_Clear);
	//Ask user to Enter ID
	CLCD_voidWriteString("ENTER ID:");


	while(1)
	{
		//Busy wating to Keep check if any key pressed first
		do
		{
			Local_u8Key=KPD_voidGet_KPD_Status();
			//0xff meaning no key pressed
		}while(Local_u8Key==0xff);



		// function to write key numbers Only on keypad
		if(Local_u8Key<10 && Local_u8Key != 50 && Local_u8Key != 24 && IteratorID<4)
		{
			CLCD_voidWriteOneNumber(Local_u8Key);

			//Store numbers pressed on keypad in local Array
			Local_u8ArrID[IteratorID] = Local_u8Key;
			IteratorID++;
			// Action when User click on button On/C on Keypad
		}else if (Local_u8Key == 50)
		{
			CLCD_voidSendCommand(lcd_Clear);
			CLCD_voidWriteString("ENTER ID:");
			IteratorID=0;
			//	Action when User click on button = on Keypad to ask user Enter Password (password always Equal Invert ID)
		}else if (Local_u8Key == 24)
		{
			CLCD_voidSendCommand(lcd_Clear);
			CLCD_voidWriteString("PASS:");
			Segment7_VidSetDisplay(NUMBERS[Local_u8Wrong_pass]);
			//new Busy waiting to wait user to enter Right Password
			while(1)
			{
				do
				{
					Local_u8Key=KPD_voidGet_KPD_Status();
				}while(Local_u8Key==0xff);

				if(Local_u8Key<10 && Local_u8Key != 50 && Local_u8Key != 24 && IteratorPass<4)
				{
					CLCD_voidWriteOneNumber(Local_u8Key);

					Local_u8ArrPass[IteratorPass] = Local_u8Key;
					IteratorPass++;

				}else if (Local_u8Key == 50)
				{
					CLCD_voidSendCommand(lcd_Clear);
					CLCD_voidWriteString("PASS:");
					IteratorPass=0;
				}else if (Local_u8Key == 24)
				{

					CLCD_voidSendCommand(lcd_Clear);

					if(Local_u8ArrPass[3]==Local_u8ArrID[0] && Local_u8ArrPass[2]==Local_u8ArrID[1] && Local_u8ArrPass[1]==Local_u8ArrID[2] && Local_u8ArrPass[0]==Local_u8ArrID[3])
					{
						Segment7_VidDisableDisplayOne();
						CLCD_voidWriteString("WELCOME ID:");
						for(i=0;i<4;i++)
						{
							CLCD_voidWriteOneNumber(Local_u8ArrID[i]);
						}

						CLCD_voidWriteExtraChar(Hamoksha_Char,1,1,8);

						_delay_ms(1000);
						CLCD_voidSendCommand(lcd_Clear);

						ADC_voidInit();
						GIE_voidEnable();
						while(1)
						{
							ADC_u8StartConversionAsynch(Channel_A0,&App_u16ADCReading,&ADCTempNotification);
							ADC_u8StartConversionAsynch(Channel_A1,&App_u16ADCReading,&ADCLDRNotification);
						}

					}else
					{
						Local_u8Wrong_pass--;
						if(Local_u8Wrong_pass == 0)
						{
							Segment7_VidSetDisplay(NUMBERS[Local_u8Wrong_pass]);
							CLCD_voidWriteString("Bye Hamoksha");
							_delay_ms(1000);
							break;
						}

						Segment7_VidSetDisplay(NUMBERS[Local_u8Wrong_pass]);
						IteratorPass=0;
						CLCD_voidSendCommand(lcd_Clear);
						CLCD_voidWriteString("Try Again");
						_delay_ms(1000);
						CLCD_voidSendCommand(lcd_Clear);
						CLCD_voidWriteString("PASS:");
					}
				}
			}
			break;
		}else if(Local_u8Key>10 && Local_u8Key != 50 && Local_u8Key != 24)
		{

		}
	}
	CLCD_voidSendCommand(lcd_DisplayOff);
	Segment7_VidDisableDisplayOne();
}

void ADCTempNotification (void)
{
	//ADC signal Input
	DIO_u8_SetPin_Dir(Group_A,DIO_u8_Pin_0,DIO_u8_Input);
	DIO_u8_SetPin_value(Group_A,DIO_u8_Pin_0,DIO_u8_Low);

	u16 MilliVolt;
	u8 Temp;

	MilliVolt = (u16) ((App_u16ADCReading*5000UL)/1024UL);
	Temp = MilliVolt/10;

	CLCD_voidWriteString("Temp: ");
	CLCD_voidWriteNumber(Temp);
	CLCD_voidWriteString(" c");
	CLCD_voidSendCommand(lcd_Home);

	if(Temp > 30)
	{
		DIO_u8_SetPin_Dir(Group_A,DIO_u8_Pin_2,DIO_u8_Output);
		DIO_u8_SetPin_value(Group_A,DIO_u8_Pin_2,DIO_u8_High);
		CLCD_Gotoxy(0,15);
		CLCD_voidWriteString("M");

	}else
	{
		DIO_u8_SetPin_value(Group_A,DIO_u8_Pin_2,DIO_u8_Low);
		CLCD_Gotoxy(0,15);
		CLCD_voidWriteString(" ");
	}
}

void ADCLDRNotification (void)
{
	//ADC signal Input
	DIO_u8_SetPin_Dir(Group_A,DIO_u8_Pin_1,DIO_u8_Input);
	DIO_u8_SetPin_value(Group_A,DIO_u8_Pin_1,DIO_u8_Low);

	//ADC signal Output Light Leds
	DIO_u8_SetPort_Dir(Group_B,DIO_u8_PORT_Output);

	//Connect Ground to Leds
	DIO_u8_SetPin_Dir(Group_A,DIO_u8_Pin_4,DIO_u8_Output);
	DIO_u8_SetPin_value(Group_A,DIO_u8_Pin_4,DIO_u8_High);

	DIO_u8_SetPin_Dir(Group_D,DIO_u8_Pin_5,DIO_u8_Output);
	DIO_u8_SetPin_value(Group_D,DIO_u8_Pin_5,DIO_u8_High);

	u16 MilliVolt;
	u16 Reading;

	MilliVolt = (u16) ((App_u16ADCReading*5000UL)/1024UL);
	CLCD_Gotoxy(1,0);
	ADC_u8StartConversionSynch(Channel_A1, &MilliVolt);
	Reading = mapping(0, 1024, 0, 9, MilliVolt);
	CLCD_voidWriteNumber(Reading);
	CLCD_voidWriteString(" LEVEL");

	CLCD_voidSendCommand(lcd_Home);

	switch(Reading)
	{
	case 1:
		DIO_u8_SetPort_value(Group_B,0b00000001);
		break;
	case 2:
		DIO_u8_SetPort_value(Group_B,0b00000011);
		break;
	case 3:
		DIO_u8_SetPort_value(Group_B,0b00000111);
		break;
	case 4:
		DIO_u8_SetPort_value(Group_B,0b00001111);
		break;
	case 5:
		DIO_u8_SetPort_value(Group_B,0b00011111);
		break;
	case 6:
		DIO_u8_SetPort_value(Group_B,0b00111111);
		break;
	case 7:
		DIO_u8_SetPort_value(Group_B,0b01111111);
		break;
	case 8:
		DIO_u8_SetPort_value(Group_B,0b11111111);
		break;
	default:
		DIO_u8_SetPort_value(Group_B,0b00000000);
		break;
	}
}

