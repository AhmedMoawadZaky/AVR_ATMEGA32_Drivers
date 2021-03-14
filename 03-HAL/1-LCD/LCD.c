#include "STD_TYPES.h"
#include "LCD_cfg.h"
#include "LCD.h"
#include "DIO_interface.h"

#include<util/delay.h>


/* begin of LCD_vidWriteData function*/
void LCD_vidWriteData(u8 data ){

	DIO_u8SetPinValue(LCD_ControlPort,RS,1);

	DIO_u8SetPinValue(LCD_ControlPort,RW,0);

	#ifdef LCD_8bit

		DIO_u8SetPortValue(LCD_DataPort,data);

		DIO_u8SetPinValue(LCD_ControlPort,E,1);

		_delay_ms(1);

		DIO_u8SetPinValue(LCD_ControlPort,E,0);

		_delay_ms(1);

	#else

		u8 ldata=0xF0,rdata=0x0F;
		ldata&=data;
		rdata&=data;
		rdata<<=4;
		DIO_vidSetPortValue(LCD_DataPort,ldata);

		DIO_vidSetPinvalue(LCD_ControlPort,E,1);

		_delay_ms(1);

		DIO_vidSetPinvalue(LCD_ControlPort,E,0);

		_delay_ms(1);

		DIO_vidSetPortValue(LCD_DataPort,rdata);

		DIO_vidSetPinvalue(LCD_ControlPort,E,1);

		_delay_ms(1);

		DIO_vidSetPinvalue(LCD_ControlPort,E,0);

		_delay_ms(1);
	#endif
}/* end of LCD_vidWriteData function*/


/* begin of LCD_vidWriteComand function*/
void LCD_vidWriteComand(u8 Comand ){

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
	DIO_u8SetPinValue(LCD_ControlPort,RS,0);
	DIO_u8SetPinValue(LCD_ControlPort,RW,0);

	#ifdef LCD_8bit

		DIO_u8SetPortValue(LCD_DataPort,Comand);

	#else

		u8 lComand=0xF0,rComand=0x0F;
		lComand&=Comand;
		rComand&=Comand;
		rComand<<=4;
		DIO_vidSetPortValue(LCD_DataPort,lComand);

		DIO_vidSetPinvalue(LCD_ControlPort,E,1);

		_delay_ms(1);

		DIO_vidSetPinvalue(LCD_ControlPort,E,0);

		_delay_ms(1);

		DIO_vidSetPortValue(LCD_DataPort,rComand);

	#endif
	
	DIO_u8SetPinValue(LCD_ControlPort,E,1);

	_delay_ms(1);

	DIO_u8SetPinValue(LCD_ControlPort,E,0);

	_delay_ms(1);
}/* end of LCD_vidWriteComand function*/


/* begin of LCD_vidInit function*/
void LCD_vidInit(void){

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

	DIO_SetPortDirection(LCD_DataPort,0xFF);

	DIO_u8SetPinDirection(LCD_ControlPort ,RS,1);


	DIO_u8SetPinDirection(LCD_ControlPort,RW,1);

	DIO_u8SetPinDirection(LCD_ControlPort,E,1);
	_delay_ms(50);

	#ifdef LCD_8bit

		LCD_vidWriteComand(0x38);

		
	#else
		
	LCD_vidWriteComand(0x28);

	#endif
	
	_delay_ms(1);

	LCD_vidWriteComand(0x0C);

	_delay_ms(2);

	LCD_vidWriteComand(0x01);

}/* end of LCD_vidInit function*/


/* begin of LCD_vidWriteString function*/
void LCD_vidWriteString(u8 *data ){

	for(int i=0;data[i];++i){

		LCD_vidWriteData(data[i]);

	}
}/* end of LCD_vidWriteString function*/


/* begin of LCD_vidWriteNumber function*/
void LCD_vidWriteNumber(f64 number ){
	if(number<0){
		number*=-1;
		LCD_vidWriteData('-');
	}
	u32 data=(u32)number;

	if(number==0){
		LCD_vidWriteData('0');
	}
	else{
		if(data ==0){
				LCD_vidWriteData('0');
		}
		u32 reverse=1;
		while(data){
			reverse=(reverse*10)+(data%10);
			data/=10;
		}
		data=reverse;
		while(data!=1){

			LCD_vidWriteData((data%10)+'0');
			data/=10;

		}
		f64 casr=(number-(u32)number);
		if(casr>0){
			LCD_vidWriteData('.');
			casr*=10.0;
			LCD_vidWriteData((u8)casr+'0');
			casr*=10.0;
			LCD_vidWriteData(((u8)casr%10)+'0');
		}
	}
}/* end of LCD_vidWriteNumber function*/


/* begin of LCD_vidSetPosition function*/
void LCD_vidSetPosition(u8 row ,u8 col){
	/*
	 * 0b1-------
	 * you can change any bit from - but first one should be 1 so we add 128 to the number
	 * we change command in LCD to make it print in any position we want
	 *
	 * */
	LCD_vidWriteComand((row*64)+col+128);

}/* end of LCD_vidSetPosition function*/


/* begin of LCD_vidSetPosition function*/
void LCD_vidClear(void){

	LCD_vidWriteComand(0x01);

}/* end of LCD_vidClear function*/

u8 LCD_u8WriteSpecialChar(u8 *data ,u8 Copy_u8Posation){

	u8 Local_u8Stat =STD_TYPES_OK;
	/* Write Special Char*/
	/*Set Address counter (AC) To CGRAM*/
	if(Copy_u8Posation < 8){
		LCD_vidWriteComand( 0X40 + (Copy_u8Posation * 8) );

		for(u8 i=0;i< 8;++i){
			LCD_vidWriteData(data[i]);
		}
	}
	else{
		Local_u8Stat =STD_TYPES_NOK;
	}
	return Local_u8Stat;
}
