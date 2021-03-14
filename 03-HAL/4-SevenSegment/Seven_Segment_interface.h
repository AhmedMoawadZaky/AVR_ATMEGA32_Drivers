/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 3/1/2021   *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : Seven_Segment **********************/
/*****************************************************************/
#ifndef Seven_Segment_INTERFACE_H
#define Seven_Segment_INTERFACE_H

u8 SevenSegment_u8SetNumber	(u8 Copy_CommonAnodeOrCathod , u8 Copy_Seven_Segment_PORT , u8 Copy_u8Number);

u8 SevenSegment_u8OnCommon	(u8 Copy_CommonAnodeOrCathod , u8 Copy_Seven_Segment_PORT , u8 Copy_u8CommonPin);

u8 SevenSegment_u8OFFCommon	(u8 Copy_CommonAnodeOrCathod , u8 Copy_Seven_Segment_PORT , u8 Copy_u8CommonPin);

/* Options For Seven Segment:    	
				COMMON_ANODE
				COMMON_CATHOD
               			   */
#define			COMMON_CATHOD		0
#define			COMMON_ANODE		1
/* Options :		
		DIO_u8_PIN0		
 		DIO_u8_PIN1		
 		DIO_u8_PIN2		
 		DIO_u8_PIN3		
 		DIO_u8_PIN4		
		DIO_u8_PIN5		
 		DIO_u8_PIN6		
 		DIO_u8_PIN7		
					*/
#define  LengthOfSegment	7

#define  Segment_A   	DIO_u8_PIN0
#define  Segment_B		DIO_u8_PIN1
#define  Segment_C   	DIO_u8_PIN2
#define  Segment_D   	DIO_u8_PIN3
#define  Segment_E   	DIO_u8_PIN4
#define  Segment_F   	DIO_u8_PIN5
#define  Segment_G   	DIO_u8_PIN6
#define  Segment_DOT  	DIO_u8_PIN7
#define  CommonPin  	DIO_u8_PIN7


#endif
