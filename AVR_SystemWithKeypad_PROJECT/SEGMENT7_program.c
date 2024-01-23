#include "STD_TYPES.h"
#include "BIT_CALC.h"
#include "DIO_interface.h"
#include "SEGMENT7_interface.h"
#include "SEGMENT7_config.h"

void Segment7_VoidInit(void)
{
	DIO_u8_SetPort_Dir(u8Port7Seg, DIO_u8_PORT_Output);
	DIO_u8_SetPin_Dir(u8ComPort7Seg, u8ComPin7SegNumOne, DIO_u8_Output);
	DIO_u8_SetPin_Dir(u8ComPort7Seg, u8ComPin7SegNumTwo, DIO_u8_Output);
	Segment7_VidClearDisplay();
	Segment7_VidEnableDisplayOne();
	Segment7_VidEnableDisplayOne();
}

void Segment7_VidSetDisplay(u8 u8ArrCopy)
{
	switch (u8ComPinTypeCopy)
	{
	case ComAnode:
		DIO_u8_SetPort_value(u8Port7Seg, ~(u8ArrCopy));
	break;
	case ComCathode:
		DIO_u8_SetPort_value(u8Port7Seg, u8ArrCopy);
	break;
	}
}

void Segment7_VidClearDisplay(void)
{
	switch (u8ComPinTypeCopy)
	{
	case ComAnode:
		DIO_u8_SetPort_value(u8Port7Seg, DIO_u8_High);
	break;
	case ComCathode:
		DIO_u8_SetPort_value(u8Port7Seg, DIO_u8_Low);
	break;
	}
}

 void Segment7_VidEnableDisplayOne(void){
	switch (u8ComPinTypeCopy)
		{
		case ComAnode:
			DIO_u8_SetPin_value(u8ComPort7Seg, u8ComPin7SegNumOne, DIO_u8_High);
			break;
		case ComCathode:
			DIO_u8_SetPin_value(u8ComPort7Seg, u8ComPin7SegNumOne, DIO_u8_Low);
			break;
		}
}

 void Segment7_VidEnableDisplayTwo(void){
 	switch (u8ComPinTypeCopy)
 		{
 		case ComAnode:
 			DIO_u8_SetPin_value(u8ComPort7Seg, u8ComPin7SegNumTwo, DIO_u8_High);
 			break;
 		case ComCathode:
 			DIO_u8_SetPin_value(u8ComPort7Seg, u8ComPin7SegNumTwo, DIO_u8_Low);
 			break;
 		}
 }

 void Segment7_VidDisableDisplayOne(void){
	switch (u8ComPinTypeCopy)
			{
			case ComAnode:
				DIO_u8_SetPin_value(u8ComPort7Seg, u8ComPin7SegNumOne, DIO_u8_Low);
				break;
			case ComCathode:
				DIO_u8_SetPin_value(u8ComPort7Seg, u8ComPin7SegNumOne, DIO_u8_High);
				break;
			}
}

 void Segment7_VidDisableDisplayTwo(void){
	switch (u8ComPinTypeCopy)
			{
			case ComAnode:
				DIO_u8_SetPin_value(u8ComPort7Seg, u8ComPin7SegNumTwo, DIO_u8_Low);
				break;
			case ComCathode:
				DIO_u8_SetPin_value(u8ComPort7Seg, u8ComPin7SegNumTwo, DIO_u8_High);
				break;
			}
}
