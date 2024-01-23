/*
 * Interface.h
 * CLCD driver for the microcontroller ATMega 32
 * Created on: May 8, 2023
 * Author: Heba Atef Ahmed
 */
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#define lcd_Clear           0x01          /* 0000 0001 replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* 0000 0010 return cursor to first position on first line                   */
#define lcd_EntryMode_Incr  0x06          // 0000 0110 shift cursor from left to right on read/write
#define lcd_EntryMode_Decr  0x04          // 0000 0100 shift cursor from right to left on read/write
#define lcd_DisplayOff      0x08          // 0000 1000 turn display off
#define lcd_DisplayOn       0x0C          // 0000 1100 display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // 0011 0000 reset the LCD
#define lcd_FunctionSet8bit 0x38          // 0011 1000 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCGRam        0x40          // 0100 0000
#define lcd_SetCursor       0x80          // 1000 0000 set cursor position
#define lcd_CursorShift     0x10		  // 0001 0000 shifts cursor position to the left (AC decreased by1)

#define ADC_Port			PORT_A

void CLCD_voidInit(void);
void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidWriteCharctr(u8 Copy_u8Data);
void CLCD_voidWriteString (u8* Copy_pcString);
void CLCD_Gotoxy (u8 cpy_u8Xpos,u8 cpy_u8Ypos);

/*Store and write many characters*/
void CLCD_voidWriteExtraChar (u8* cpy_ExtraChar,u8 cpy_ExtraChar_No,u8 cpy_u8Xpos,u8 cpy_u8Ypos);

/*Store and write only one character in specific position*/
void CLCD_voidWriteOneExtraChar (u8* cpy_ExtraChar,u8 cpy_ExtraChar_pos,u8 cpy_u8Xpos,u8 cpy_u8Ypos);

/*Store only one character without write on screen in specific position*/
void CLCD_voidStoreOneExtraChar (u8* cpy_ExtraChar,u8 cpy_ExtraChar_pos);

void CLCD_voidWriteNumber (u32 Cpy_Number);

void CLCD_voidWriteOneNumber(u8 Cpy_OneNumber);

#endif /* CLCD_INTERFACE_H_ */
