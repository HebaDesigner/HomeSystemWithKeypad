/*
 * Config.h
 * CLCD driver for the microcontroller ATMega 32
 * Created on: May 8, 2023
 * Author: Heba Atef Ahmed
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

#define CLCD_DATA_PORT			Group_C

#define CLCD_CONTROL_PORT		Group_A
#define CLCD_RS_PIN				DIO_u8_Pin_5
#define CLCD_RW_PIN				DIO_u8_Pin_6
#define CLCD_E_PIN     			DIO_u8_Pin_7

#endif /* CLCD_CONFIG_H_ */
