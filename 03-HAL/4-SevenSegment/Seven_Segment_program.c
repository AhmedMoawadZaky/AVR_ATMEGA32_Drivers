/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 3/1/2021   *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : Seven_Segment **********************/
/*****************************************************************/

/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "Seven_Segment_interface.h"
#include "Seven_Segment_private.h"
#include "Seven_Segment_config.h"



/* Options To Display Number In PORT?:    	
				DIO_u8_PORTA
				DIO_u8_PORTB
				DIO_u8_PORTC
				DIO_u8_PORTD
               			   */
u8 SevenSegment_u8SetNumber(u8 Copy_CommonAnodeOrCathod , u8 Copy_Seven_Segment_PORT , u8 Copy_u8Number){
	
	
	u8 Local_u8ReturnStat=STD_TYPES_OK;
	if(Copy_Seven_Segment_PORT <= DIO_u8_PORTD && Copy_u8Number < 10){
		u8 PinLoop = 0;
		u8 LocalArrayForNumbersValue[]={0X3F, 0X06 , 0X5B , 0X4F , 0X66 , 0X6D , 0X7D , 0X07 , 0X7F , 0X6F};
		u8 PinMap[]={Segment_A , Segment_B , Segment_C , Segment_D , Segment_E , Segment_F , Segment_G ,Segment_DOT};

		for(PinLoop = 0; PinLoop < LengthOfSegment ; ++PinLoop){
			
			if(Copy_CommonAnodeOrCathod == COMMON_ANODE){
				
				DIO_u8SetPinValue( Copy_Seven_Segment_PORT , PinMap[PinLoop], !GET_BIT(LocalArrayForNumbersValue[Copy_u8Number] , PinLoop ));
			}
			else if(Copy_CommonAnodeOrCathod == COMMON_CATHOD){
				
				DIO_u8SetPinValue( Copy_Seven_Segment_PORT , PinMap[PinLoop] , GET_BIT(LocalArrayForNumbersValue[Copy_u8Number] , PinLoop ));
			}
			else{
				Local_u8ReturnStat=STD_TYPES_NOK;
			}
			
		}
	}
	else{
		Local_u8ReturnStat=STD_TYPES_NOK;
	}
	return Local_u8ReturnStat;
}


u8 SevenSegment_u8OnCommon	(u8 Copy_CommonAnodeOrCathod , u8 Copy_Seven_Segment_PORT , u8 Copy_u8CommonPin){
	
	u8 Local_u8ReturnStat=STD_TYPES_OK;
	if(Copy_CommonAnodeOrCathod == COMMON_ANODE){
		
		DIO_u8SetPinValue( Copy_Seven_Segment_PORT , Copy_u8CommonPin , DIO_u8_HIGH );
	}
	else if(Copy_CommonAnodeOrCathod == COMMON_CATHOD){
		
		DIO_u8SetPinValue( Copy_Seven_Segment_PORT , Copy_u8CommonPin , DIO_u8_LOW );
	}
	else{
		Local_u8ReturnStat=STD_TYPES_NOK;
	}
	
	return Local_u8ReturnStat;
}

u8 SevenSegment_u8OFFCommon	(u8 Copy_CommonAnodeOrCathod , u8 Copy_Seven_Segment_PORT , u8 Copy_u8CommonPin){
	
	u8 Local_u8ReturnStat=STD_TYPES_OK;
	if(Copy_CommonAnodeOrCathod == COMMON_ANODE){
		
		DIO_u8SetPinValue( Copy_Seven_Segment_PORT , Copy_u8CommonPin , DIO_u8_LOW );
	}
	else if(Copy_CommonAnodeOrCathod == COMMON_CATHOD){
		
		DIO_u8SetPinValue( Copy_Seven_Segment_PORT , Copy_u8CommonPin ,DIO_u8_HIGH );
	}
	else{
		Local_u8ReturnStat=STD_TYPES_NOK;
	}
	
	return Local_u8ReturnStat;
}
