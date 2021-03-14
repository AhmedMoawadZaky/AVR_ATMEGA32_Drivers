#ifndef LCD_H_
#define LCD_H_

/*Function prototype or Declaration */

void LCD_vidWriteData(u8 data ); /* function use to write Character in LCD by sending data */

void LCD_vidWriteComand(u8 Comand );/* function use to write command in LCD to initialize it */

void LCD_vidInit(void); /* use to initialize the LCD one time */

void LCD_vidWriteString(u8 *data );

void LCD_vidWriteNumber(f64 data );

void LCD_vidSetPosition(u8 row ,u8 col);

void LCD_vidClear(void);

u8 LCD_u8WriteSpecialChar(u8 *data ,u8 Copy_u8Posation);

#define LCD_SpecialChar1    {\
								0b00001111,\
								0b00001100,\
								0b00011111,\
								0b00001100,\
								0b00001100,\
								0b00001100,\
								0b00001100,\
								0b00001100\
											}


#define LCD_SpecialChar2    {\
								0b00000000,\
								0b00000000,\
								0b00000000,\
								0b00000000,\
								0b00001110,\
								0b00000011,\
								0b00011111,\
								0b00000000,\
											}


#define LCD_SpecialChar3    {\
								0b00000000,\
								0b00000000,\
								0b00000000,\
								0b00000000,\
								0b00000000,\
								0b00001100,\
								0b00010011,\
								0b00001100\
											}


#define LCD_SpecialChar4    {\
								0b00011110,\
								0b00011110,\
								0b00000100,\
								0b00001110,\
								0b00001111,\
								0b00000100,\
								0b00001010,\
								0b00001010\
											}


#define LCD_SpecialChar5    {\
								0b00011110,\
								0b00011110,\
								0b00000100,\
								0b00001110,\
								0b00001110,\
								0b00000101,\
								0b00001011,\
								0b00001000\
											}




#define LCD_SpecialChar6    {\
								0b00011110,\
								0b00011110,\
								0b00000100,\
								0b00010101,\
								0b00011111,\
								0b00000100,\
								0b00001110,\
								0b00010101\
											}


#define LCD_SpecialChar7    {\
								0b00011110,\
								0b00011110,\
								0b00000100,\
								0b00000100,\
								0b00011111,\
								0b00010101,\
								0b00001110,\
								0b00010101\
											}

#define LCD_SpecialChar8    {\
								0b00001111,\
								0b00001100,\
								0b00011111,\
								0b00001100,\
								0b00001100,\
								0b00001100,\
								0b00001100,\
								0b00001100\
											}

#endif /* LCD_H_ */
