/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 13/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : KEY_PAD    *************************/
/*****************************************************************/
/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU   8000000UL
#include <util/delay.h>

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "KEY_PAD_interface.h"
#include "KEY_PAD_private.h"
#include "KEY_PAD_config.h"

u8 Keybad_u8GetButtonStatus(u8 *Copy_pu8ReturnedSwitch){
	
	u8 Local_u8ReturnStat=STD_TYPES_OK,Local_u8PinVal,Copy_u8Flag=0;
	static u8 RealRow[KEY_PAD_u8_Rows_Number]=KEY_PAD_RealRow;
	
	static u8 RealCol[KEY_PAD_u8_Cols_Number]=KEY_PAD_RealCol;
	
	static u8 RealPortForRow[KEY_PAD_u8_Rows_Number]=KEY_PAD_RealPortForRow;
	
	static u8 RealPortForCol[KEY_PAD_u8_Cols_Number]=KEY_PAD_RealPortForCol;
	
	static u8 Local_u8KeyPadValues[KEY_PAD_u8_Rows_Number][KEY_PAD_u8_Cols_Number]=KEY_PAD_Values;
	
	if(Copy_pu8ReturnedSwitch != NULL){
		for(u8 Local_u8CounterForRow=0 ; Local_u8CounterForRow < KEY_PAD_u8_Rows_Number; ++Local_u8CounterForRow){
			/* Activate One Row  At a time  */
			DIO_u8SetPinValue(RealPortForRow[Local_u8CounterForRow],RealRow[Local_u8CounterForRow],DIO_u8_LOW);
			/* Check Col Pins */
			for(u8 Local_u8CounterForCol=0 ; Local_u8CounterForCol < KEY_PAD_u8_Cols_Number; ++Local_u8CounterForCol){
				/* Read Pin Col Value */
				DIO_u8GetPinValue(RealPortForCol[Local_u8CounterForCol],RealCol[Local_u8CounterForCol],&Local_u8PinVal);
				if(Local_u8PinVal == DIO_u8_LOW){
					
					_delay_ms(10);
					
					DIO_u8GetPinValue(RealPortForCol[Local_u8CounterForCol],RealCol[Local_u8CounterForCol],&Local_u8PinVal);
					if(Local_u8PinVal == DIO_u8_LOW){
						*Copy_pu8ReturnedSwitch = Local_u8KeyPadValues[Local_u8CounterForRow][Local_u8CounterForCol];

						while(Local_u8PinVal == DIO_u8_LOW){
							DIO_u8GetPinValue(RealPortForCol[Local_u8CounterForCol],RealCol[Local_u8CounterForCol],&Local_u8PinVal);
						}
						Copy_u8Flag=1;
						break;
					}
				}
			}
			/* Deactivate Row */
			DIO_u8SetPinValue(RealPortForRow[Local_u8CounterForRow],RealRow[Local_u8CounterForRow],DIO_u8_HIGH);
			if(Copy_u8Flag == 1){
				break;
			}
		}
		if(Copy_u8Flag == 0){
			Local_u8ReturnStat=STD_TYPES_NOK;
		}
	}
	else{
		Local_u8ReturnStat=STD_TYPES_NOK;
	}
	
	return Local_u8ReturnStat;
}
