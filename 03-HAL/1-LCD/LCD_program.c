/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 11/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : LCD        *************************/
/*****************************************************************/
/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU   8000000UL
#include <util/delay.h>

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"


void LCD_voidInit(void){
	/*
	 * first we sit all pins in data port and in control port by 1 to enable us to send electrical in LCD
	 * Notes 1- RS "register select " is use to control command and data
	 * 			1 for sending data to display it
	 * 			0 for sending command to initialize the LCD
	 *
	 * Below this is called a edge when the signal is high for a 1ms the LCD can tack input to write it
	 * and this operation tack time and while this happening LCD can not tack input until signal become low then
	 * return high
	 * summary LCD can execute on order in the high signal and when it come back low then high it can tack another one
	 * 	 --->--
	 * 	 ^    |
	 *   |    |
	 * ->------>-
	 * */
	_delay_ms(50);
	#if LCD_u8_MODE == LCD_u8_8_BIT_MODE	
		
		LCD_voidWriteComand(0x38);
		
	#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE
		DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
		
		DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
				
		/* Enable Pulse */
		DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_HIGH);
		_delay_ms(1);
		DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_LOW);	
		
		LCD_voidWriteComand(0x28);
	#endif
		_delay_ms(1);

		LCD_voidWriteComand(0x0C);
		
		_delay_ms(2);
		/* Display Clear */
		LCD_voidWriteComand(0x01);
}

void LCD_voidWriteComand(u8 Copy_u8Cmnd){
	
	/*
	 * to write a command at begin we should sit a RS bit by 0 because 0 mean control mode
	 * then to write a command at begin we should sit a RW bit by 0 because 0 mean write mode
	 * all in the above in the control port
	 *
	 * Notes 1- RS "register select " is use to control command and data
	 * 			1 for sending data to display it
	 * 			0 for sending command to initialize the LCD
	 *
	 * Below this is called a edge when the signal is high for a 1ms the LCD can tack input to write it
	 * and this operation tack time and while this happening LCD can not tack input until signal become low then
	 * return high
	 * summary LCD can execute on order in the high signal and when it come back low then high it can tack another one
	 * 	 --->--
	 * 	 ^    |
	 *   |    |
	 * ->------>-
	 * */
	 
	/* Rs pin = 0 */
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
	/* Rw pin = 0 */
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
	
	#if LCD_u8_MODE == LCD_u8_8_BIT_MODE
		/* Write Command on Data Pins */
		DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Cmnd);
		
	#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE
		/* Send To LCD Most 4 bits */
		Private_voidWriteHalfPort(Copy_u8Cmnd>>4);
			/* Enable Pulse *//* H => L */
		DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_HIGH);
		_delay_ms(1);
		DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_LOW);
		
		/* Send To LCD the Least 4 bits of the Cmnd */
		Private_voidWriteHalfPort(Copy_u8Cmnd);
	
	#endif	
	/* Enable Pulse *//* H => L */
	DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_LOW);
}

void LCD_voidWriteData(u8 Copy_u8Char){
	/* Rs pin = 1 */
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
	/* Rw pin = 0 */
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
	
	#if LCD_u8_MODE == LCD_u8_8_BIT_MODE
		/* Write Char on Data Pins */
		DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Char);
		
	#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE

		/* Send To LCD Most 4 bits */
		Private_voidWriteHalfPort(Copy_u8Char>>4);
			/* Enable Pulse *//* H => L */
		DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_HIGH);
		_delay_ms(1);
		DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_LOW);
		
		/* Send To LCD the Least 4 bits of the Cmnd */
		Private_voidWriteHalfPort(Copy_u8Char);
	
	#endif
	/* Enable Pulse *//* H => L */
	DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(LCD_u8_En_PORT,LCD_u8_En_PIN,DIO_u8_LOW);
}
void LCD_voidSetPosition  (u8 Copy_u8LineNb,u8 Copy_u8Pos)
{
	/*
	 * 0b1-------
	 * you can change any bit from - but first one should be 1 so we add 128 to the number
	 * we change command in LCD to make it print in any position we want
	 *
	 * */
	LCD_voidWriteComand((Copy_u8LineNb*64)+Copy_u8Pos+128);
}

static void Private_voidWriteHalfPort(u8 Copy_u8Value){
	
	u8 Local_u8BitValue;
	Local_u8BitValue = GET_BIT(Copy_u8Value,0);
	if(Local_u8BitValue == 0){
		DIO_u8SetPinValue(LCD_u8_D4_PORT,LCD_u8_D4_PIN,DIO_u8_LOW);
	}
	else{
		DIO_u8SetPinValue(LCD_u8_D4_PORT,LCD_u8_D4_PIN,DIO_u8_HIGH);
	}

	Local_u8BitValue = GET_BIT(Copy_u8Value,1);
	if(Local_u8BitValue == 0){
		DIO_u8SetPinValue(LCD_u8_D5_PORT,LCD_u8_D5_PIN,DIO_u8_LOW);
	}
	else{
		DIO_u8SetPinValue(LCD_u8_D5_PORT,LCD_u8_D5_PIN,DIO_u8_HIGH);
	}

	Local_u8BitValue = GET_BIT(Copy_u8Value,2);
	if(Local_u8BitValue == 0){
		DIO_u8SetPinValue(LCD_u8_D6_PORT,LCD_u8_D6_PIN,DIO_u8_LOW);
	}
	else{
		DIO_u8SetPinValue(LCD_u8_D6_PORT,LCD_u8_D6_PIN,DIO_u8_HIGH);
	}

	Local_u8BitValue = GET_BIT(Copy_u8Value,3);
	if(Local_u8BitValue == 0){
		DIO_u8SetPinValue(LCD_u8_D7_PORT,LCD_u8_D7_PIN,DIO_u8_LOW);
	}
	else{
		DIO_u8SetPinValue(LCD_u8_D7_PORT,LCD_u8_D7_PIN,DIO_u8_HIGH);
	}	
}

/* begin of LCD_vidWriteString function*/
void LCD_voidWriteString(u8 *data ){

	for(int i=0;data[i];++i){

		LCD_voidWriteData(data[i]);

	}
}/* end of LCD_vidWriteString function*/



/* begin of LCD_vidWriteNumber function*/
void LCD_voidWriteNumber(f64 number){
	if(number<0){
		number*=-1;
		LCD_voidWriteData('-');
	}
	u32 data=(u32)number;

	if(number==0){
		LCD_voidWriteData('0');
	}
	else{
		if(data ==0){
				LCD_voidWriteData('0');
		}
		u32 reverse=1;
		while(data){
			reverse=(reverse*10)+(data%10);
			data/=10;
		}
		data=reverse;
		while(data!=1){

			LCD_voidWriteData((data%10)+'0');
			data/=10;

		}
		f64 casr=(number-(u32)number);
		if(casr>0){
			LCD_voidWriteData('.');
			casr*=10.0;
			LCD_voidWriteData((u8)casr+'0');
			casr*=10.0;
			LCD_voidWriteData(((u8)casr%10)+'0');
		}
	}
}/* end of LCD_vidWriteNumber function*/


/* begin of LCD_vidSetPosition function*/
void LCD_voidClear(void){

	LCD_voidWriteComand(0x01);

}/* end of LCD_vidClear function*/

