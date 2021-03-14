/*********************************************************************************/
/** Author    : Ahmed Zaky                                                      **/
/** Version   : V01                                                             **/
/** Date      : 15 August 2020                                                  **/
/*********************************************************************************/

/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"

void LED_voidOnMode(LED_Temp * Copy_u8Data){
	
		if(Copy_u8Data->ConnectionType == Active_High){

			DIO_u8SetPinValue(Copy_u8Data->PortNumb, Copy_u8Data->PinNumb ,DIO_u8_LOW );
		}
		else if(Copy_u8Data->ConnectionType == Active_Low){
			
			DIO_u8SetPinValue(Copy_u8Data->PortNumb, Copy_u8Data->PinNumb , DIO_u8_HIGH);
		}
		else{
			/* Errore */
		}

}

void LED_voidOffMode(LED_Temp * Copy_u8Data){
	
		if(Copy_u8Data->ConnectionType == Active_High){
			DIO_u8SetPinValue(Copy_u8Data->PortNumb, Copy_u8Data->PinNumb ,DIO_u8_HIGH );
		}
		else if(Copy_u8Data->ConnectionType == Active_Low){
			
			DIO_u8SetPinValue(Copy_u8Data->PortNumb, Copy_u8Data->PinNumb , DIO_u8_LOW);
		}
		else{
			/* Errore */
		}

}

void LED_voidToglMode(LED_Temp * Copy_u8Data){
	
		DIO_u8TogPinValue(Copy_u8Data->PortNumb, Copy_u8Data->PinNumb );
		
}
