/*
 * Interface.h
 * DIO driver for the microcontroller ATMega 32
 * Created on: May 6, 2023
 * Author: Heba Atef Ahmed
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define Group_A 0
#define Group_B 1
#define Group_C 2
#define Group_D 3
#define Invalid_u8_Error  0
#define DIO_u8_High 1
#define DIO_u8_Low 0
#define DIO_u8_Input 0
#define DIO_u8_Output 1
#define DIO_u8_PORT_Output 255

#define Valid 1
#define DIO_u8_Pin_0  0
#define DIO_u8_Pin_1  1
#define DIO_u8_Pin_2  2
#define DIO_u8_Pin_3  3
#define DIO_u8_Pin_4  4
#define DIO_u8_Pin_5  5
#define DIO_u8_Pin_6  6
#define DIO_u8_Pin_7  7
#define Result  0


u8 DIO_u8_SetPin_value(u8 Copy_u8_PortID,u8 Copy_u8_Pin_ID,u8 Copy_u8_Pin_Val);

u8 DIO_u8_SetPin_Dir(u8 Copy_u8_PortID,u8 Copy_u8_Pin_ID,u8 Copy_u8_Pin_Dir);

u8 DIO_u8_SetPort_value(u8 Copy_u8_PortID, u8 Copy_u8_Port_Val);

u8 DIO_u8_SetPort_Dir(u8 Copy_u8_PortID, u8 Copy_u8_Port_Dir);

u8 DIO_u8_GetPin_value(u8 Copy_u8_PortID,u8 Copy_u8_Pin_ID, u8 *Copy_Pu8_u8_Pin_Val);

u8 DIO_u8_GetPort_value(u8 Copy_u8_PortID, u8 *Copy_Pu8_u8_Pin_Val);




#endif /* DIO_INTERFACE_H_ */
