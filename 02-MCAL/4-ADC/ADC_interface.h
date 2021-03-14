/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 18/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : ADC        *************************/
/*****************************************************************/
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC_u8_Channel_0				0
#define ADC_u8_Channel_1				1
#define ADC_u8_Channel_2				2
#define ADC_u8_Channel_3				3
#define ADC_u8_Channel_4				4
#define ADC_u8_Channel_5				5
#define ADC_u8_Channel_6				6
#define ADC_u8_Channel_7				7

#define ADC_u16DigitalValueOutOfTheRange    2500

typedef struct{
	u8 *Arrayofchannels;
	u16 *ArrayofADCResults;
	u8 ChainSize;
	void (*EndNotificationFunc)(void);
}ADC_Chain;

void ADC_voidInit(void);

u8   ADC_u8GetDigitalValueSynchronous   (u8 Copy_u8ChannelNum , u16 * Copy_pu16DigitalValue);


u8   ADC_u8GetDigitalValueAsynchronous   (u8 Copy_u8ChannelNum , void (* Copy_pfunctionNotification)(u16));


u8   ADC_u8startChainConversion(ADC_Chain * Copy_Chain);

/*
 * u8 	 ADC_u8SetCallBackFunc				(void (*Copy_PtrFunc)(void));
 */

#endif
