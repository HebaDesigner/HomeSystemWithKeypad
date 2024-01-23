/*
 * KPD_Config.h
 * KPD driver for the microcontroller ATMega 32
 * Created on: May 19, 2023
 * Author: Heba Atef Ahmed
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_u8Active_Col 0
#define KPD_u8Active_Row 1

#define KPD_u8Activation_Type KPD_u8Active_Col

#define KPD_u8_Pull_Up 0
#define KPD_u8_Pull_Down 1

#define KPD_u8Connection_Type KPD_u8_Pull_Up

#define KPD_u8_Col_NB 4
#define KPD_u8_Row_NB 4

#define KPD_PORT  Group_D

#define KPD_u8_Col_PIN_0  DIO_u8_Pin_0
#define KPD_u8_Col_PIN_1  DIO_u8_Pin_1
#define KPD_u8_Col_PIN_2  DIO_u8_Pin_2
#define KPD_u8_Col_PIN_3  DIO_u8_Pin_3

#define KPD_u8_Row_PIN_0  DIO_u8_Pin_4
#define KPD_u8_Row_PIN_1  DIO_u8_Pin_5
#define KPD_u8_Row_PIN_2  DIO_u8_Pin_6
#define KPD_u8_Row_PIN_3  DIO_u8_Pin_7

#define KPD_Arr_VAL	    {{7,4,1,50},{8,5,2,0},{9,6,3,24},{47,42,45,43}}

#define KPD_No_Pressed_Key  0xff

#endif /* KPD_CONFIG_H_ */
