/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 11/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : LCD        *************************/
/*****************************************************************/
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define LCD_u8_LINE_ONE      1
#define LCD_u8_LINE_TWO      2

void LCD_voidInit    (void);

void LCD_voidWriteComand(u8 Copy_u8Cmnd);

void LCD_voidWriteData(u8 Copy_u8Char);

void LCD_voidSetPosition  (u8 Copy_u8LineNb,u8 Copy_u8Pos);

void LCD_vidWriteString(u8 *data );

void LCD_voidWriteNumber(f64 number);

void LCD_voidClear(void);


#endif